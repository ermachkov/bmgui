#ifndef SPRITES_H
#define SPRITES_H

#include "globals.h"


//флаг разрезки
enum E_Scussored
{
	SCISSORED_NONE = 0,
	SCISSORED_LEFT,
	SCISSORED_CENTER,
	SCISSORED_RIGHT

};

//коллизии
struct S_Collision
{
	S_Collision(CL_String collisionName = "bitmaps") :
		mFileOffset(0)
	{
		SetCollisionName(collisionName);
	}

	void SetCollisionName(CL_String collisionName)
	{
		mCollisionName = collisionName;
		mCollisionFileName = mCollisionName + ".bin";
	}

	const CL_String & GetCollisionName() const
	{
		return mCollisionName;
	}

	const CL_String & GetCollisionFileName() const
	{
		return mCollisionFileName;
	}

	int mFileOffset; //смещение в файле коллизии

private:
	CL_String mCollisionName; //имя коллизий
	CL_String mCollisionFileName; //имя файла для сохранения информации о коллизиях

};

//ClanLib овская архитектура image
struct S_Image
{
	S_Image(CL_String sourceFileName) :
		mSourceFileName(sourceFileName),
		mDelay(0)
	{
	}

	//входные данные
	CL_String mSourceFileName; //имя файла исходного изображения
	int mDelay; //задержка кадра (для анимации)
	CL_Vec2i mOffset; //смещение относительно позиции спрайта (для анимации)

	//промежуточные
	CL_String mSourceFullName; //полное имя файла изображения
	CL_PixelBuffer mImage; //исходное изображение
	S_Collision mCollision; //информация о коллизии
	bool mNoTransparent; //картинка полностью непрозрачная
	
	//выходные
	size_t mITexture; //номер файла-текстуры для размещения
	CL_Rect mSrcRect; //SrcRect в текстурном атласе
	CL_Rect mDeltaGrid; //поправки сетки
};
//ClanLib овская архитектура спрайта
struct S_Sprite
{
	S_Sprite(CL_String name, CL_Vec2i pos) : 
		mName(name),
		mPos(pos),
		mIsFrame(false)
	{
	}

	//входные данные
	CL_String mName; //имя спрайта в скрипте
	CL_Vec2i mPos; //позиция для отрисовки на экране
	typedef std::vector<S_Image> T_Images;
	T_Images mImages; //массив спрайтов
	bool mIsFrame; //есть ли назначение анимации

	void AddImage(CL_String sourceFileName)
	{
		mImages.push_back(S_Image(sourceFileName));
	}

	bool SetAnimationsParam(size_t i, int delay, CL_Vec2i offset)
	{
		if(i >= mImages.size())
			return false;

		mIsFrame = true; //данный спрайт - анимационный
		mImages[i].mDelay = delay;
		mImages[i].mOffset = offset;
		return true;
	}
};

typedef std::vector<S_Sprite> T_Sprites;
//глобальный список спрайтов
extern T_Sprites sprites;


#endif // SPRITES_H