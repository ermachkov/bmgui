#target photoshop

//определение наличия запрещенных символов для формата - имя переменной
function isWrongChar(str)
{
	return str.length <= 0 || (/[^\w]/).test(str) || (/^[0-9]/).test(str);
}

//установка активности слоя по его имени
function setLayerByName(name)
{
	var desc = new ActionDescriptor();
	var ref = new ActionReference();
	ref.putName(charIDToTypeID("Lyr "), name);
	desc.putReference(charIDToTypeID("null"), ref);
	desc.putBoolean(charIDToTypeID("MkVs"), true);
	executeAction(charIDToTypeID("slct"), desc, DialogModes.NO);
}

//функция обработки одного слоя
function exportOneLayer(doc, layer, iSprite, iFrame)
{
	//alert(layer.name);

	//преобразование к смартобъекту
	try
	{
		var idnewPlacedLayer = stringIDToTypeID("newPlacedLayer");
		executeAction(idnewPlacedLayer, undefined, DialogModes.NO);
	}
	catch (e)
	{
		alert("Невозможно преобразовать слой \"" + layer.name + "\" в смарт-объект");
		return false;
	}

	// получение ссылки на новый слой после преобразования
	layer = app.activeDocument.activeLayer;

	//определение значимой области
	var bounds = layer.bounds;
	var x = bounds[0].value;
	var y = bounds[1].value;
	var w = bounds[2].value - x;
	var h = bounds[3].value - y;
	//alert (x + " " + y + " " + w + " " + h);

	//выделение в документе
	if (w != 0 && h != 0)
	{
		// выделение
		doc.selection.select([[x, y], [x + w, y], [x + w, y + h], [x, y + h], [x, y]]);
		//копирование
		doc.selection.copy();
		//layer.copy();

		var docRef = app.documents.add(w, h, doc.resolution, layer.name, NewDocumentMode.RGB, DocumentFill.TRANSPARENT);
		docRef.paste();

		//сохранение документа
		var saveFile = new File(tempPath + layer.name + ".png");
		pngSaveOptions = new PNGSaveOptions();
		pngSaveOptions.interlaced = false;
		docRef.saveAs(saveFile, pngSaveOptions, true, Extension.LOWERCASE);

		//закрытие документа
		docRef.close(SaveOptions.DONOTSAVECHANGES);

		// сохраняем координаты спрайта (координаты нулевого кадра)
		if (iFrame == 0)
		{
			sprites[iSprite].x = x;
			sprites[iSprite].y = y;
		}

		// сохраняем смещения текущего кадра
		sprites[iSprite][1][iFrame].x = x - sprites[iSprite].x;
		sprites[iSprite][1][iFrame].y = y - sprites[iSprite].y;
	}
	else
	{
		alert("Слой с именем \"" + layer.name + "\" пуст");
		return false;
	}

	return true;
}

//получение индекса активного слоя
function getActiveLayerIndex()
{
	var ref = new ActionReference();
	ref.putProperty(charIDToTypeID("Prpr"), charIDToTypeID("ItmI"));
	ref.putEnumerated(charIDToTypeID("Lyr "), charIDToTypeID("Ordn"), charIDToTypeID("Trgt"));
	return executeActionGet(ref).getInteger(charIDToTypeID("ItmI"));
}

//обработка списка слоёв (какой документ, имя файла слоёв)
function exportAllLayers(doc, layersFileName)
{
	var layersFile = new File(layersFileName);
	if (layersFile == null || !layersFile.exists)
	{
		alert("Не найден файл \"" + layersFileName + "\"");
		return false;
	}

	//подключение файла - скрипта со слоями
	$.evalFile(layersFile);

	//обход массива
	for (var i = 0; i < sprites.length; ++i)
	{
		var spriteName = sprites[i][0];
		//alert("spriteName: " + spriteName);
		if (isWrongChar(spriteName))
		{
			alert("Недопустимый символ в имени спрайта \"" + spriteName + "\"");
			return false;
		}

		var frames = sprites[i][1];
		for (var j = 0; j < frames.length; ++j)
		{
			var frameName = frames[j];
			//проверка валидности имени кадра
			if (isWrongChar(frameName))
			{
				alert("Недопустимый символ в имени кадра \"" + frameName + "\"");
				return false;
			}

			//включение активности слоя по имени
			try
			{
				setLayerByName(frameName);
			}
			catch (e)
			{
				alert("Не найден слой с именем \"" + frameName + "\"");
				return false;
			}

			//получение слоя для обработки
			var layer = doc.activeLayer;

			//преобразование имени кадра в строковый объект (чтобы добавлять к нему свойства)
			frames[j] = new String(frames[j]);

			//получение минимального индекса слоя
			var currentLayerIndex = getActiveLayerIndex();
			//alert(currentLayerIndex);
			if (sprites[i].index === undefined)
				sprites[i].index = currentLayerIndex;
			else
				sprites[i].index = Math.min(sprites[i].index, currentLayerIndex);

			//обработка слоя
			if (!exportOneLayer(doc, layer, i, j))
				return false;
		}
	}

	return true;
}

function SaveDataToXML(fileName)
{
	//открытие файла для записи
	var file = new File(fileName);
	if (!file.open("w"))
	{
		alert("Ошибка сохранения файла \"" + fileName + "\"");
		return false;
	}

	//заголовок
	file.writeln("<?xml version=\"1.0\" encoding=\"WINDOWS-1251\"?>");
	file.writeln("<resources>");

	//обход массива
	for (var i = 0; i < sprites.length; ++i)
	{
		var spriteName = sprites[i][0];
		var frames = sprites[i][1];

		//добавление текста в файл экспорта в формате кланлиба о спрайте
		file.writeln("\t<sprite name=\"" + spriteName + "\" x=\"" + sprites[i].x + "\" y=\"" + sprites[i].y + "\">");

		for (var j = 0; j < frames.length; ++j)
		{
			//сохранение image
			var frameName = frames[j];
			file.writeln("\t\t<image file=\"" + frameName + ".png\"/>");
		}

		//несколько кадров в спрайте
		if (frames.length > 1)
		{
			for (var j = 0; j < frames.length; ++j)
				file.writeln("\t\t<frame nr=\"" + j + "\" x=\"" + frames[j].x + "\" y=\"" + frames[j].y + "\"/>");
		}

		file.writeln("\t</sprite>");
	}

	file.writeln("</resources>");

	//закрытие файла
	file.close();
	return true;
}

function main()
{
	//проверка на существование хотя бы одного документа
	if (documents.length == 0)
	{
		alert("Нет открытых документов");
		return false;
	}

	//сохранение ссылки на активный документ
	var docRef = app.activeDocument;

	//попытка загрузки параметров
	try
	{
		var d = app.getCustomOptions("4d633fbb-ed90-480d-8e03-cccb16131a34");
		var defaultFolder = d.getString(app.charIDToTypeID("Msge"));
	}
	catch (e)
	{
		//нет информации в реестре - берем путь к psd-файлу
		if (docRef.saved)
		{
			defaultFolder = docRef.fullName.path;
		}
		else
		{
			alert("Текущий документ не сохранен");
			return false;
		}
	}

	//запрос пути для сохранения результатов работы скрипта
	var selFolder = Folder.selectDialog("Select Destination", defaultFolder);
	if (selFolder != null)
	{
		destinationPath = selFolder.fsName + "\\";

		//сохранение параметров
		var d = new ActionDescriptor();
		d.putString(app.charIDToTypeID("Msge"), selFolder.fsName);
		app.putCustomOptions("4d633fbb-ed90-480d-8e03-cccb16131a34", d);
	}
	else
	{
		return false;
	}

	//определение валидности последнего каталога
	var arrayDirectory = destinationPath.split("\\");
	if (isWrongChar(arrayDirectory[arrayDirectory.length - 2]))
	{
		alert("Недопустимый символ в имени каталога для сохранения");
		return false;
	}

	//формирование имени файла со слоями
	var layersFileName = destinationPath + docRef.name;
	//удаление в имени .psd, если оно есть
	if (layersFileName.substr(layersFileName.length - 4, 4) == ".psd")
		layersFileName = layersFileName.substr(0, layersFileName.length - 4);
	layersFileName += ".layers";

	//создание временной копии документа
	var duppedDocument = docRef.duplicate();

	// создание временного каталога
	tempPath = destinationPath + "temp\\";
	var folder = new Folder(tempPath);
	folder.create();

	//установка единиц измерения в пикселях
	var originalRulerUnits = preferences.rulerUnits;
	preferences.rulerUnits = Units.PIXELS;

	//обработка списка слоёв
	if (!exportAllLayers(duppedDocument, layersFileName))
	{
		duppedDocument.close(SaveOptions.DONOTSAVECHANGES);
		preferences.rulerUnits = originalRulerUnits;
		return false;
	}

	//закрытие временной копии документа
	duppedDocument.close(SaveOptions.DONOTSAVECHANGES);

	//восстановление первоначальных едениц размерности
	preferences.rulerUnits = originalRulerUnits;

	//сортировка спрайтов по индексу
	sprites.sort(function(a, b) { return a.index - b.index; });

	//запись в XML массива объектов
	if (!SaveDataToXML(tempPath + docRef.name.match(/([^\.]+)/)[1] + ".export"))
		return false;

	//запуск C++ утилиты
	var res = app.system("ExportPSD.exe " + "\"" + destinationPath + "\"");
	return true;
}

main();
