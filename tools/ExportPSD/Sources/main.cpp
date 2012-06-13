//http://www.gamedev.ru/pages/coriolis/articles/Packing_Lightmaps

//http://blog.wonderville.ru/texture-atlas/
//http://www.rsdn.ru/forum/media/2874639.flat.aspx
//http://www.gamedev.ru/code/forum/?id=19113
//http://forum.boolean.name/showthread.php?t=13290

//TO DO:
//Добавить работу с CL_ZipArchive


#include <math.h>

#include "globals.h"
#include "Sprites.h"
#include "Textures.h"

//имена выходных файлов
const CL_String OUTPUT_TEXTURE_NAME = "texture";
const CL_String RESOURCES_FILE_NAME = "resources.xml";
const CL_String LUA_SCRIPT_NAME = "sprites.lua";

class ConsoleProgram
{
public:
	static int main(const std::vector<CL_String> &args);
};

CL_ClanApplication app(&ConsoleProgram::main);

int PrintError(const CL_String &str)
{
	CL_Console::write_line( str );
	CL_Console::wait_for_key();
	return -1;
}

#define ALPHA_LIMIT 252
//ф-ция проверки на наличие прозрачных пикселей
bool testAlpha(CL_PixelBuffer &image)
{
	int width = image.get_width();
	int height = image.get_height();
	int pitch = image.get_pitch();
	unsigned char *row = static_cast<unsigned char *>(image.get_data());
	for (int y = 0; y < height; ++y, row += pitch)
	{
		unsigned char *pixel = row;
		for (int x = 0; x < width; ++x, pixel += 4)
		{
			//pixel[0]; //alpha
			//pixel[1]; //blue
			//pixel[2]; //green
			//pixel[3]; //red
			if (pixel[0] < ALPHA_LIMIT)
				return false;
		}
	}
	return true;
}

//сохранение данных о коллизии в файл
void saveCollision(CL_PixelBuffer &image, CL_File file)
{
	int width = image.get_width();
	int height = image.get_height();
	int pitch = image.get_pitch();

	std::vector<unsigned char> collusionBits((width+7)/8*height, 0);

	unsigned char *row = static_cast<unsigned char *>(image.get_data());
	for (int y = 0; y < height; ++y, row += pitch)
	{
		unsigned char *pixel = row;
		for (int x = 0; x < width; ++x, pixel += 4)
		{
			if (pixel[0] <= 255 - ALPHA_LIMIT)
			{
				//номер байта
				int i = y*(width/8) + x/8;
				//CL_Console::write_line("$$ x= %1 y= %2 -> i= %3 ", x, y, i);
				//установка бита смещения
				collusionBits[i] |= 1<<(7 - x%8);
			}
		}
	}

	//сохранение в файл сигнатуры
	file.write_uint32(0x4D534442);
	//сохранение в файл ширины спрайта
	file.write_uint32(width);
	//сохранение в файл высоты спрайта
	file.write_uint32(height);

	//сохранение в файл массива
	for(std::vector<unsigned char>::const_iterator iterCollusionBits = collusionBits.begin(); iterCollusionBits != collusionBits.end(); ++iterCollusionBits)
		file.write_uint8(*iterCollusionBits);
}

//конвертирование из CP-1251 в UTF-8
CL_String decode(const CL_String &str)
{
	//строка символов в текущей локали преобразовать в UCS-2 через MultiByteToWideChar,
	//а потом из UCS-2 в кланлибовский UTF-8 через CL_StringHelp::ucs2_to_text.
	CL_String16 result;
	int count = MultiByteToWideChar(1251, 0, str.c_str(), str.size(), NULL, 0);
	result.resize(count);
	MultiByteToWideChar(1251, 0, str.c_str(), str.size(), result.data(), count);
	
	return CL_StringHelp::ucs2_to_text(result);
}

//рекурсивное клонирование XML-элемента
CL_DomElement cloneElement(CL_DomElement &element, CL_DomDocument &doc)
{
	//создаем элемент-клон
	CL_DomElement clone(doc, element.get_tag_name());

	//копируем атрибуты
	CL_DomNamedNodeMap attributes = element.get_attributes();
	unsigned long length = attributes.get_length();
	for (unsigned long i = 0; i < length; ++i)
	{
		CL_DomNode attr = attributes.item(i);
		clone.set_attribute(attr.get_node_name(), attr.get_node_value());
	}

	//рекурсивно копируем дочерние элементы
	for (CL_DomElement child = element.get_first_child_element(); !child.is_null(); child = child.get_next_sibling_element())
		clone.append_child(cloneElement(child, doc));

	//возвращаем клонированный элемент
	return clone;
}

int ConsoleProgram::main(const std::vector<CL_String> &args)
{
	// Setup clanCore:
	CL_SetupCore setup_core;

	// Initialize the ClanLib display component
	CL_SetupDisplay setup_display;

	// Create a console Window if one does not exist:
	CL_ConsoleWindow console_window("Console", 80, 600);

try
{	
	//получение параметра запуска
	for (std::vector<CL_String>::const_iterator iter_args = args.begin(); iter_args != args.end(); ++iter_args)
		CL_Console::write_line( *iter_args );

	//получение имени директории для сохранения
	CL_String workDirectoryName;
	if (args.size() > 1)
	{
		//полное имя рабочей директории
		workDirectoryName = args[1];
		//конвертирование из CP-1251 в UTF-8 имени рабочей директории
		workDirectoryName = decode(workDirectoryName);
	}
	else
	{
		//получение полного пути к текущему каталогу
		workDirectoryName = CL_Directory::get_current();
	}

	CL_Console::write_line("workDirectoryName: %1", workDirectoryName);
	//получение имени последней директории
	CL_String locationName = CL_PathHelp::remove_trailing_slash(workDirectoryName);
	locationName = CL_PathHelp::get_filename(locationName);
	CL_Console::write_line("locationName: %1", locationName);

	CL_String tempDir = CL_PathHelp::add_trailing_slash(workDirectoryName) + "temp\\";
	CL_DirectoryScanner directoryScanner;
	directoryScanner.scan(tempDir, "*.export");
	while (directoryScanner.next())
	{
		//имя обрабатываемого файла
		CL_String fileName;

		if (directoryScanner.is_directory())
			continue;
		//получение полного имени файла экспорта
		fileName = directoryScanner.get_pathname();
		//конвертирование из CP-1251 в UTF-8
		fileName = decode(fileName);
		CL_Console::write_line("find: %1", fileName);

		//открытие XML файла
		CL_File fileXML;
		bool is_opened = fileXML.open(fileName);
		if( !is_opened )
			return PrintError( CL_String("Can't open file: ") + fileName );

		//Создание объекта DOM парсера
		CL_DomDocument document(fileXML);
		//получение root узла
		CL_DomElement root = document.get_document_element();
		if( root.get_local_name() != "resources")
		{
			CL_Console::write_line("Root name can't be: %1", root.get_local_name().c_str());
			return PrintError("");
		}

		//цикл по потомкам "resources"
		for (CL_DomNode cur = root.get_first_child(); !cur.is_null(); cur = cur.get_next_sibling())
		{
			//загрузка только спрайтов
			if (cur.get_node_name() != "sprite")
				continue;

			CL_DomElement element = cur.to_element();

			//проверка на обязательные параметры
			if (!element.has_attribute("name"))
				return PrintError("Error: can't find parametr \"name\"");

			CL_DomString name = element.get_attribute("name");
			int x = element.get_attribute_int("x");
			int y = element.get_attribute_int("y");
			//добавление спрайта
			sprites.push_back( S_Sprite(name, CL_Vec2i(x, y) ) );

			//цикл по "image" (формирование списка имен файлов)
			for (CL_DomNode cur_image = cur.get_first_child(); !cur_image.is_null(); cur_image = cur_image.get_next_sibling())
			{
				//загрузка только image
				if (cur_image.get_node_name() != "image")
					continue;
				
				CL_DomElement element_image = cur_image.to_element();
				CL_DomString file = element_image.get_attribute("file");
				
				//конвертирование из CP-1251 в UTF-8 имени файла изображения
				file = decode(file); 

				//добавление изображения для обработки
				(sprites.end()-1)->AddImage(file);
			}

			//цикл по "frame" (дополнение списка информацией о файле)
			for (CL_DomNode cur_frame = cur.get_first_child(); !cur_frame.is_null(); cur_frame = cur_frame.get_next_sibling())
			{
				if (cur_frame.get_node_name() != "frame")
					continue;
				
				CL_DomElement element_frame = cur_frame.to_element();
				//проверка на обязательные параметры
				if (!element_frame.has_attribute("nr"))
					return PrintError("Error: can't find parameter \"nr\"");

				size_t nr = element_frame.get_attribute_int("nr");
				int speed = element_frame.get_attribute_int("speed");
				int x_image = element_frame.get_attribute_int("x");
				int y_image = element_frame.get_attribute_int("y");

				(sprites.end()-1)->SetAnimationsParam(nr, speed, CL_Vec2i(x_image, y_image));
			}
		}
		fileXML.close();

	}
	//CL_Console::wait_for_key();

	// TODO:
	//проверка на перекрытие ресурсных имен
	//return PrintError( CL_String("Error: This resourse already exist") );

	//декодирование имени спрайта и генерация с декодированием полных имен файлов
	for(T_Sprites::iterator iter_sprites = sprites.begin(); iter_sprites != sprites.end(); ++iter_sprites)
	{
		for(S_Sprite::T_Images::iterator iter_images = iter_sprites->mImages.begin(); iter_images != iter_sprites->mImages.end(); ++iter_images)
		{
			//CL_Console::write_line("processing: %1 pos = %2 %3", iter_sprites->mName, iter_sprites->mPos.x, iter_sprites->mPos.y);
			//генерация полного имени файла
			iter_images->mSourceFullName = CL_PathHelp::make_absolute(tempDir, iter_images->mSourceFileName);
			//CL_Console::write_line("image: %1 pos = %2 %3", iter_images->mSourceFileName, iter_images->mOffset.x, iter_images->mOffset.y);
			CL_Console::write_line("image fullname: %1", iter_images->mSourceFullName);
		}
	}
	//CL_Console::wait_for_key();

	//загрузка файлов-картинок
	for(T_Sprites::iterator iter_sprites = sprites.begin(); iter_sprites != sprites.end(); ++iter_sprites)
		for(S_Sprite::T_Images::iterator iter_images = iter_sprites->mImages.begin(); iter_images != iter_sprites->mImages.end(); ++iter_images)
			iter_images->mImage = CL_ImageProviderFactory::load(iter_images->mSourceFullName).to_format(cl_rgba8);

	//CL_Console::wait_for_key();

	//проход по всем спрайтам для определения необходимости разрезки на несколько спрайтов

	for(T_Sprites::size_type iSprites = 0; iSprites < sprites.size(); ++iSprites)
	{
		for(S_Sprite::T_Images::size_type iImages = 0; iImages < sprites[iSprites].mImages.size(); ++iImages)
		{
			//определение размеров
			CL_Size image_size = sprites[iSprites].mImages[iImages].mImage.get_size();

			//Определение наличия прозрачности
			sprites[iSprites].mImages[iImages].mNoTransparent = testAlpha(sprites[iSprites].mImages[iImages].mImage);

			//высота превышает допустимую
			if(image_size.height > MAX_HEIGHT)
				return PrintError( CL_String("Error: image height is more then 1024") );

			//ширина превышает допустимую
			if(image_size.width > MAX_WIDTH)
			{
				
				CL_Console::write_line("scussor: sprites[iSprites].mName: %1", sprites[iSprites].mName);

				//проверка на то что у этого спрайта один image
				if(sprites[iSprites].mImages.size() > 1)
					return PrintError( CL_String("Error: animation size can't be more than MAX_WIDTH*MAX_HEIGHT (1024*1024)") );
				
				//сохранение высоты и ширины
				int h = image_size.height;
				int w = image_size.width;
				
				//определение кол-ва частей на разрезку
				int n; //кол-во частей на разрезку
				for(n = 2; n < 10; ++n)
					if (w > (n-1)*MAX_WIDTH - 2*(n-2) && w <= (n)*MAX_WIDTH - 2*(n-1))
						break;
				
				T_Sprites::iterator addedSprite;
				switch (n)
				{
				case 2: //две части
					//спрайт слева (задание имени и позиции спрайта)
					addedSprite = sprites.insert( sprites.begin()+iSprites+1, 
						S_Sprite(CL_String(sprites[iSprites].mName)+CL_StringHelp::int_to_text(0), sprites[iSprites].mPos+CL_Vec2i(0, 0) ) );

					//создание одного Image в добавленом спрайте
					addedSprite->AddImage(sprites[iSprites].mImages[iImages].mSourceFileName);
					//создание изображения (задание зазмеров спрайта)
					addedSprite->mImages[0].mImage = CL_PixelBuffer(MAX_WIDTH, h, cl_rgba8);
					//наследование флага отсутствия прозрачности
					addedSprite->mImages[0].mNoTransparent = sprites[iSprites].mImages[iImages].mNoTransparent;
					//копирование куска изображения
					sprites[iSprites].mImages[iImages].mImage.convert(addedSprite->mImages[0].mImage,
						//(dst Rect, src Rect)
						CL_Rect(0, 0, MAX_WIDTH, h), CL_Rect(0, 0, MAX_WIDTH, h));
					addedSprite->mImages[0].mDeltaGrid.left = 0;
					addedSprite->mImages[0].mDeltaGrid.right = -1;

					//спрайт справа (задание имени и позиции спрайта)
					addedSprite = sprites.insert( sprites.begin()+iSprites+1, 
						S_Sprite(CL_String(sprites[iSprites].mName)+CL_StringHelp::int_to_text(1), sprites[iSprites].mPos+CL_Vec2i(MAX_WIDTH-1, 0) ) );

					//создание одного Image в добавленом спрайте
					addedSprite->AddImage(sprites[iSprites].mImages[iImages].mSourceFileName);
					//создание изображения (задание зазмеров спрайта)
					addedSprite->mImages[0].mImage = CL_PixelBuffer(w-MAX_WIDTH+2, h, cl_rgba8);
					//наследование флага отсутствия прозрачности
					addedSprite->mImages[0].mNoTransparent = sprites[iSprites].mImages[iImages].mNoTransparent;
					//копирование куска изображения
					sprites[iSprites].mImages[iImages].mImage.convert(addedSprite->mImages[0].mImage,
						//(dst Rect, src Rect)
						CL_Rect(0, 0, w-MAX_WIDTH+2, h), CL_Rect(MAX_WIDTH-2, 0, w, h));
					addedSprite->mImages[0].mDeltaGrid.left = +1;
					addedSprite->mImages[0].mDeltaGrid.right = -1;

					break;
				default:
					return PrintError( CL_String("Error: scussored on >2 part is't writen by C++ programmer") );
					break;
				}

/*
				//разделение изображения на части
				int x = 1;
				int residual = image_size.width;
				int left, right;
				int i = 0;
				do
				{
					x -= 1;
					left = x;
					x += min(MAX_WIDTH, residual);
					right = x;
					residual -= (right-left-1);

					i++;
					//добавление куска
					T_Sprites::iterator addedSprite =
						sprites.insert( sprites.begin()+iSprites+1, 
						S_Sprite(CL_String(sprites[iSprites].mName)+CL_StringHelp::int_to_text(i), sprites[iSprites].mPos+CL_Vec2i(left, 0) ) );

					//создание одного Image в добавленом спрайте
					addedSprite->AddImage(sprites[iSprites].mImages[iImages].mSourceFileName);
					//создание изображения
					addedSprite->mImages[0].mImage = CL_PixelBuffer(right-left, h, cl_rgba8);
					//наследование флага отсутствия прозрачности
					addedSprite->mImages[0].mNoTransparent = sprites[iSprites].mImages[iImages].mNoTransparent;
					//копирование куска изображения
					sprites[iSprites].mImages[iImages].mImage.convert(addedSprite->mImages[0].mImage, CL_Rect(0,0,right-left,h), CL_Rect(left, 0, right, h));
				}
				while(residual != 1);
*/		
				//удаление исходного разрезаемого изображения
				sprites.erase( sprites.begin() + iSprites );
			}		
		}
	}

//	for(T_Sprites::iterator iter_sprites = sprites.begin(); iter_sprites != sprites.end(); ++iter_sprites)
//	{
//		//определение размеров
//		CL_Size imageSize = iter_sprites->mImage.get_size();
//		//Добавление несколько пикселей для границы спрайтов с дублированием граничных пикселей
//		iter_sprites->image = CL_PixelBufferHelp::add_border(iter_sprites->image, ADDING_BORDER, CL_Rect(0, 0, image_size.width, image_size.height) );
//	}

	///////////////////////////////////////////////////////
	//распределение картинок на текстурном атласе
	///////////////////////////////////////////////////////

	for(T_Sprites::size_type iSprites = 0; iSprites < sprites.size(); ++iSprites)
	{
		for(S_Sprite::T_Images::size_type iImages = 0; iImages < sprites[iSprites].mImages.size(); ++iImages)
		{
			//переполучение размера
			CL_Size image_size = sprites[iSprites].mImages[iImages].mImage.get_size();
			//помещение в отсортированый список указателя на image
			sortedList.insert( std::make_pair( max(image_size.width, image_size.height), S_ImagePointer(iSprites, iImages) ) );
		}
	}

	//Проверка сортировки
	//for(T_SortedList::iterator iter_sortedList = sortedList.begin(); iter_sortedList != sortedList.end(); ++iter_sortedList)
	//	CL_Console::write_line("sorted: %1, key=(%2, %3)", iter_sortedList->first, iter_sortedList->second.iSprite, iter_sortedList->second.iImage);

	//проход по всем спрайтам по убыванию большей стороны
	for(T_SortedList::reverse_iterator iter_sortedList = sortedList.rbegin(); iter_sortedList != sortedList.rend(); ++iter_sortedList)
	{
		//номер спрайта
		T_Sprites::size_type iSprite = iter_sortedList->second.iSprite;
		//номер изображения в спрайте
		S_Sprite::T_Images::size_type iImage = iter_sortedList->second.iImage;

		if( !sprites[iSprite].mImages[iImage].mNoTransparent )
			pngNodes.ConnectTexture( S_ImagePointer(iSprite, iImage) );
		else
			jpgNodes.ConnectTexture( S_ImagePointer(iSprite, iImage) );

		//проверка добавления
		CL_Console::write_line("rects are %1 %2 %3 %4", sprites[iSprite].mImages[iImage].mSrcRect.left, sprites[iSprite].mImages[iImage].mSrcRect.top, sprites[iSprite].mImages[iImage].mSrcRect.right, sprites[iSprite].mImages[iImage].mSrcRect.bottom);
	}

	size_t textureW = MAX_WIDTH;
	size_t textureH = MAX_HEIGHT;

	//список текстур PNG
	std::vector<CL_PixelBuffer> endTexturesPNG;
	//список текстур JPG
	std::vector<CL_PixelBuffer> endTexturesJPG;

	//физическое создание конечных текстур
	size_t nTexture = pngNodes.GetNumberTextures();
	for(size_t iTexture = 0; iTexture < nTexture; ++iTexture)
		endTexturesPNG.push_back( CL_PixelBuffer(textureW, textureH, cl_rgba8) );
	nTexture = jpgNodes.GetNumberTextures();
	for(size_t iTexture = 0; iTexture < nTexture; ++iTexture)
		endTexturesJPG.push_back( CL_PixelBuffer(textureW, textureH, cl_rgb8) );
	
	//обнуление цвета и альфы конечных текстур PNG
	for(std::vector<CL_PixelBuffer>::iterator iterEndTexture = endTexturesPNG.begin(); iterEndTexture != endTexturesPNG.end(); ++iterEndTexture)
		memset( (void *)iterEndTexture->get_data(), 0, iterEndTexture->get_pitch()*iterEndTexture->get_height() );
	//обнуление цвета конечных текстуры JPG
	for(std::vector<CL_PixelBuffer>::iterator iterEndTexture = endTexturesJPG.begin(); iterEndTexture != endTexturesJPG.end(); ++iterEndTexture)
		memset( (void *)iterEndTexture->get_data(), 0, iterEndTexture->get_pitch()*iterEndTexture->get_height() );
	

	//копирование подтекстур в конечные текстуры
	for(T_Sprites::iterator iter_sprites = sprites.begin(); iter_sprites != sprites.end(); ++iter_sprites)
	{
		for(S_Sprite::T_Images::iterator iter_images = iter_sprites->mImages.begin(); iter_images != iter_sprites->mImages.end(); ++iter_images)
		{
			//размеры добавляемого прямоугольника
			CL_Rect srcRect = CL_Rect(0, 0, iter_images->mImage.get_width(), iter_images->mImage.get_height());
			//номер текстуры
			size_t iTexture = iter_images->mITexture;
			
			if( !iter_images->mNoTransparent )
				iter_images->mImage.convert(endTexturesPNG[iTexture], iter_images->mSrcRect, srcRect);
			else
				iter_images->mImage.convert(endTexturesJPG[iTexture], iter_images->mSrcRect, srcRect);
		}
	}

	//сохранение текстур PNG
	std::vector<CL_PixelBuffer>::size_type iEndTexture, nEndTexture;
	nEndTexture = endTexturesPNG.size();
	for(iEndTexture = 0; iEndTexture < nEndTexture; ++iEndTexture)
	{
		//Предумножение на альфу
		endTexturesPNG[iEndTexture].premultiply_alpha();
		//сохранение
		CL_PNGProvider::save(endTexturesPNG[iEndTexture], CL_PathHelp::make_absolute(workDirectoryName, OUTPUT_TEXTURE_NAME + CL_StringHelp::int_to_text(iEndTexture) + ".png") );
		CL_Console::write_line("saved %1", CL_PathHelp::make_absolute(workDirectoryName, OUTPUT_TEXTURE_NAME + CL_StringHelp::int_to_text(iEndTexture) + ".png"));
	}
	//сохранение текстур JPG
	nEndTexture = endTexturesJPG.size();
	for(iEndTexture = 0; iEndTexture < nEndTexture; ++iEndTexture)
	{
		//сохранение
		CL_JPEGProvider::save(endTexturesJPG[iEndTexture], CL_PathHelp::make_absolute(workDirectoryName, OUTPUT_TEXTURE_NAME + CL_StringHelp::int_to_text(iEndTexture) + ".jpg"));
		CL_Console::write_line("saved %1", CL_PathHelp::make_absolute(workDirectoryName, OUTPUT_TEXTURE_NAME + CL_StringHelp::int_to_text(iEndTexture) + ".jpg"));
	}
	
	//CL_Console::wait_for_key();

#if SAVE_COLLISION != 0
//Запись файлов - контуров////////////////////////////////////////////////////////
	//удаление старых файлов
	for(T_Sprites::iterator iter_sprites = sprites.begin(); iter_sprites != sprites.end(); ++iter_sprites)
	{
		for(S_Sprite::T_Images::iterator iter_images = iter_sprites->mImages.begin(); iter_images != iter_sprites->mImages.end(); ++iter_images)
		{
			CL_String currentOutlineFileName = iter_images->mCollision.GetCollisionFileName();
			if ( CL_FileHelp::file_exists(currentOutlineFileName) ) 
				CL_FileHelp::delete_file(currentOutlineFileName);
		}
	}

	//объекты файлов для записи в них данных контуров
	std::map<CL_String, CL_File> outlineFiles;

	//открытие файлов
	for(T_Sprites::iterator iter_sprites = sprites.begin(); iter_sprites != sprites.end(); ++iter_sprites)
	{
		for(S_Sprite::T_Images::iterator iter_images = iter_sprites->mImages.begin(); iter_images != iter_sprites->mImages.end(); ++iter_images)
		{
			CL_String currentOutlineFileName = iter_images->mCollision.GetCollisionFileName();
			std::map<CL_String, CL_File>::iterator iterOutlineFiles = outlineFiles.find(currentOutlineFileName);
			if (iterOutlineFiles == outlineFiles.end())
			{
				CL_File outlineFile;
				//формирование полного имени файла
				CL_String currentOutlineFullName = CL_PathHelp::make_absolute(workDirectoryName, currentOutlineFileName);
				//открытие файла
				CL_Console::write_line("open outline file: %1", currentOutlineFullName);
				bool is_opened = outlineFile.open(currentOutlineFullName, CL_File::open_always, CL_File::access_write);
				if (!is_opened)
					return PrintError( CL_String("I Can't open file: ") + currentOutlineFullName );
				//добавление файла в список открытых файлов
				outlineFiles.insert( std::make_pair(currentOutlineFileName, outlineFile) );
				CL_Console::write_line("-inserted %1", currentOutlineFileName);
			}
		}
	}
		
	//сохранение в бинарные файлы данных о контуре
	for(T_Sprites::iterator iter_sprites = sprites.begin(); iter_sprites != sprites.end(); ++iter_sprites)
	{
		for(S_Sprite::T_Images::iterator iter_images = iter_sprites->mImages.begin(); iter_images != iter_sprites->mImages.end(); ++iter_images)
		{
			CL_String currentOutlineFileName = iter_images->mCollision.GetCollisionFileName();

			//сохранение информации о коллизии
			saveCollision(iter_images->mImage, outlineFiles[currentOutlineFileName]);

			//установка смещения для последующих таких имён
			for(T_Sprites::iterator iter_sprites2 = iter_sprites; iter_sprites2 != sprites.end(); ++iter_sprites2)
			{
				S_Sprite::T_Images::iterator iter_images2;
				if(iter_sprites2 == iter_sprites)
					iter_images2 = iter_images + 1;
				else
					iter_images2 = iter_sprites2->mImages.begin();

				for(; iter_images2 != iter_sprites2->mImages.end(); ++iter_images2)
					if(iter_images->mCollision.GetCollisionFileName() == iter_images2->mCollision.GetCollisionFileName())
						//CL_Console::write_line("+size %1", outlineFiles[currentOutlineFileName].get_position() );
						iter_images2->mCollision.mFileOffset = outlineFiles[currentOutlineFileName].get_position();
			
			}

			CL_Console::write_line("saved  %1: %2 %3", iter_images->mSourceFileName, currentOutlineFileName, iter_images->mCollision.mFileOffset);
		}
	}

	//закрытие файлов
	for(std::map<CL_String, CL_File>::iterator iterOutlineFiles = outlineFiles.begin(); iterOutlineFiles != outlineFiles.end(); ++iterOutlineFiles)
		iterOutlineFiles->second.close();
#endif
	//CL_Console::wait_for_key();
	//////////////////////////////////////////////////////////

	//формирование имени файла
	//CL_String fileResourceName = CL_PathHelp::make_absolute(workDirectoryName, locationName + ".xml");
	CL_String fileResourceName = CL_PathHelp::make_absolute(workDirectoryName, RESOURCES_FILE_NAME);

	CL_Console::write_line("fileResourceName: %1", fileResourceName);

	//открытие файла XML
	CL_File fileResourceXML;
	bool is_opened = fileResourceXML.open(fileResourceName, CL_File::create_always, CL_File::access_write);
	if( !is_opened )
		return PrintError( CL_String("I Can't open file: ") + fileResourceName );

	//запись файл заголовка
	fileResourceXML.write_string_text("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");

	//Создание объекта DOM парсера
	CL_DomDocument resourceXML;

	//корневой узел - resources
	CL_DomElement resourcesElement(resourceXML, "resources");
	resourceXML.append_child(resourcesElement);

	//узлы bitmap
	std::map<CL_String, CL_String> complianceCollisions;
	//формирование map-ы bitmap
	for(T_Sprites::iterator iter_sprites = sprites.begin(); iter_sprites != sprites.end(); ++iter_sprites)
		for(S_Sprite::T_Images::iterator iter_images = iter_sprites->mImages.begin(); iter_images != iter_sprites->mImages.end(); ++iter_images)
			complianceCollisions.insert( std::make_pair(iter_images->mCollision.GetCollisionFileName(), iter_images->mCollision.GetCollisionName()) );
#if SAVE_COLLISION != 0
	//запись в XML файл ресурсов битовых масок
	for(std::map<CL_String, CL_String>::iterator iterComplianceCollisions = complianceCollisions.begin(); iterComplianceCollisions != complianceCollisions.end(); ++iterComplianceCollisions)
	{
		CL_DomElement bitmapElement(resourceXML, "bitmap");
		bitmapElement.set_attribute("name", iterComplianceCollisions->second);
		bitmapElement.set_attribute("file", iterComplianceCollisions->first);
		resourcesElement.append_child(bitmapElement);
	}
#endif
	//запись в XML файл ресурсов результирующих прямоугольников
	for(T_Sprites::iterator iter_sprites = sprites.begin(); iter_sprites != sprites.end(); ++iter_sprites)
	{
		CL_String currentResourceName = iter_sprites->mName;

		//узел - sprite
		CL_DomElement spriteElement(resourceXML, "sprite");
		spriteElement.set_attribute("name", currentResourceName);
		resourcesElement.append_child(spriteElement);

		//тэг image
		for(S_Sprite::T_Images::iterator iter_images = iter_sprites->mImages.begin(); iter_images != iter_sprites->mImages.end(); ++iter_images)
		{
			CL_Rect currentSrcRect = iter_images->mSrcRect;

			//узел - image
			CL_DomElement imageElement(resourceXML, "image");
			if( !iter_images->mNoTransparent )
				imageElement.set_attribute("file", OUTPUT_TEXTURE_NAME + CL_StringHelp::int_to_text(iter_images->mITexture) + ".png");
			else
				imageElement.set_attribute("file", OUTPUT_TEXTURE_NAME + CL_StringHelp::int_to_text(iter_images->mITexture) + ".jpg");
			spriteElement.append_child(imageElement);
#if SAVE_COLLISION != 0
			//сохранение коллизий
			imageElement.set_attribute("bitmap", iter_images->mCollision.GetCollisionName());
			imageElement.set_attribute_int("offset", iter_images->mCollision.mFileOffset);
#endif		
			//элемент grid
			CL_DomElement GridElement(resourceXML, "grid");
			GridElement.set_attribute("pos", cl_format("%1,%2", currentSrcRect.left + iter_images->mDeltaGrid.left, currentSrcRect.top + iter_images->mDeltaGrid.top) );
			GridElement.set_attribute("size", cl_format("%1,%2", currentSrcRect.right-currentSrcRect.left + iter_images->mDeltaGrid.right, currentSrcRect.bottom-currentSrcRect.top + iter_images->mDeltaGrid.bottom) );
			imageElement.append_child(GridElement);
		}

		//прервать выполнение сохранения, если анимации нет
		if (!iter_sprites->mIsFrame)
			continue;

		for(S_Sprite::T_Images::iterator iter_images = iter_sprites->mImages.begin(); iter_images != iter_sprites->mImages.end(); ++iter_images)
		{
			//элемент frame
			CL_DomElement frameElement(resourceXML, "frame");
			frameElement.set_attribute_int("nr", iter_images - iter_sprites->mImages.begin());
			if (iter_images->mDelay != 0)
				frameElement.set_attribute_int("speed", iter_images->mDelay);
			frameElement.set_attribute_int("x", iter_images->mOffset.x);
			frameElement.set_attribute_int("y", iter_images->mOffset.y);
			spriteElement.append_child(frameElement);
		}
	}

	//подключение всех файлов с дополнительными ресурсами
	directoryScanner.scan(workDirectoryName, "*.xml");
	while (directoryScanner.next())
	{
		//проверка валидности файла
		if (directoryScanner.is_directory() || directoryScanner.get_name() == RESOURCES_FILE_NAME)
			continue;

		//открытие ресурсного XML файла
		CL_Console::write_line("include xml file: " + directoryScanner.get_pathname());
		CL_File file(directoryScanner.get_pathname());
		CL_DomDocument doc(file);
		CL_DomElement root = doc.get_document_element();
		if (root.get_tag_name() != "resources")
		{
			CL_Console::write_line("Root name can't be: %1", root.get_tag_name());
			return PrintError("");
		}

		//добавление всех ресурсов в текущий документ
		for (CL_DomElement element = root.get_first_child_element(); !element.is_null(); element = element.get_next_sibling_element())
			resourcesElement.append_child(cloneElement(element, resourceXML));
	}

	//сохранение в файл XML структуры
	resourceXML.save(fileResourceXML);
	
	//закрытие файла
	fileResourceXML.close();

	//сохранение координат спрайтов и инициализации/деинициализации в lua скрипте
	//формирование имени файла
	//CL_String luaFileName = CL_PathHelp::make_absolute(workDirectoryName, locationName + ".lua");
	CL_String luaFileName = CL_PathHelp::make_absolute(workDirectoryName, LUA_SCRIPT_NAME);
	CL_File luaFile;
	is_opened = luaFile.open(luaFileName, CL_File::create_always, CL_File::access_write);
	if( !is_opened )
		return PrintError( CL_String("Can't open file: ") + luaFileName);


	luaFile.write_string_text( cl_format("function %1_createSprites()", locationName) );
	//запись в XML файл ресурсов результирующих прямоугольников
	for(T_Sprites::iterator iter_sprites = sprites.begin(); iter_sprites != sprites.end(); ++iter_sprites)
	{
		CL_String currentResourceName = iter_sprites->mName;
		int x = iter_sprites->mPos.x;
		int y = iter_sprites->mPos.y;

		luaFile.write_string_text( cl_format("\t%1 = Sprite(\"%2\", %3, %4)", currentResourceName, currentResourceName, x, y) );
	}
	luaFile.write_string_text( cl_format("end") );
	luaFile.write_string_text(CL_String(""));

	luaFile.write_string_text( cl_format("function %1_deleteSprites()", locationName) );
	//запись в XML файл ресурсов результирующих прямоугольников
	for(T_Sprites::iterator iter_sprites = sprites.begin(); iter_sprites != sprites.end(); ++iter_sprites)
	{
		CL_String currentResourceName = iter_sprites->mName;

		luaFile.write_string_text( cl_format("\t%1 = nil", currentResourceName) );
	}
	luaFile.write_string_text( cl_format("end") );

	/*
function Location01_createSprites()
    sprite1 = Sprite("sprite1", 10, 20)
    sprite2 = Sprite("sprite2", 13, 666)
    ...
    spriten = Sprite("spriten", 999, 0)
end

function Location01_deleteSprites()
    sprite1 = nil
    sprite2 = nil
    ...
    spriten = nil
end
	*/

	luaFile.close();

	CL_Console::write_line("Press any key...");
	CL_Console::wait_for_key();
}
catch(CL_Exception &exception)
{
	CL_Console::write_line("Exception caught: " + exception.get_message_and_stack_trace());
	CL_Console::wait_for_key();
	return -1;
}
	return 0;
}