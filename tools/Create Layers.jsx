#target photoshop

var WIDTH = 1820
var HEIGHT = 1024

//определение наличия запрещенных символов для формата - имя переменной
function isWrongChar(str)
{
	return str.length <= 0 || (/[^\w]/).test(str) || (/^[0-9]/).test(str);
}

function main()
{
	//определение местоположения файла
	var layersFile = File.openDialog("Open File");
	//var layersFile = new File("f:\\ProjJS\\Level1\\Level1.layers");
	if (layersFile == null)
		return;
	//подключение файла - скрипта со слоями
	$.evalFile(layersFile);
	
	//alert(layersFile.length);

	//установка измерения в пикселях
	var originalRulerUnits = preferences.rulerUnits;
	preferences.rulerUnits = Units.PIXELS;

	//имя документа
	var documentName = "Dima";
	//close all open documents
	while (app.documents.length)
		app.activeDocument.close()
	// create a working document
	var docRef = app.documents.add(WIDTH, HEIGHT, 72, documentName, NewDocumentMode.RGB, DocumentFill.TRANSPARENT);
	//сохранение начального слоя для его удаления в конце
	var layerToRemove = docRef.activeLayer;
	
	//обход массива
	for (var i = 0; i < sprites.length; ++i)
	{
		var spriteName = sprites[i][0];
		//alert("spriteName: " + spriteName);
		if (isWrongChar(spriteName))
			alert("Недопустимый символ в имени спрайта: " + spriteName);
		
		//куда добавлять слой 
		var whereToAddLayers;
		
		var frames = sprites[i][1];		
		//один кадр в спрайте
		if (frames.length == 1)
		{
			//куда добавлять слой - в корень документа
			whereToAddLayers = docRef;
		}
		else
		//несколько кадров в спрайте
		if (frames.length > 1)
		{
			//создание папки
			var layerSet = docRef.layerSets.add();
			layerSet.name = spriteName;
			
			//куда добавлять слой - в папку
			whereToAddLayers = layerSet;
		}
		else
		{
			alert("Ошибка с количеством кадров в слое");
		}

		for (var j = 0; j < frames.length; ++j)  
		{

			var frameName = frames[j];
			//проверка валидности имени кадра
			if (isWrongChar(frameName))
				alert("Недопустимый символ в имени кадра: " + frameName);

			//создание слоя
			var layer = whereToAddLayers.artLayers.add();
			//задание имени слоя
			layer.name = frameName;
		}
	}

	//удаление первого слоя
	layerToRemove.remove();

	//восстановление первоначальных едениц размерности 
	preferences.rulerUnits = originalRulerUnits;
}

main();

/*
	//открытие фала
	layersFile.open('r');
	//считывание первой строки - названия слоя
	var str = layersFile.readln();
	if (isWrongChar(str))
		alert("Недопустимый символ в имени слоя: " + str);
	//задание имени слоя
	docRef.activeLayer.name = str;

	//считывание файла
	while (!layersFile.eof)
	{
		//считывание строки - названия слоя
		var str = layersFile.readln();
		//alert(str);		
		if (isWrongChar(str))
			alert("Недопустимый символ в имени слоя: " + str);
		
		//создание слоя
		var layer = docRef.artLayers.add();
		//задание имени слоя
		layer.name = str;
	}
	
	layersFile.close();
*/
