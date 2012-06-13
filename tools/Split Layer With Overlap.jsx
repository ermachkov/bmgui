#target photoshop

function getRulerEndpoints()
{
	var ref = new ActionReference()
	ref.putProperty(charIDToTypeID('Prpr'), charIDToTypeID('RrPt'))
	ref.putEnumerated(charIDToTypeID('Dcmn'), charIDToTypeID('Ordn'), charIDToTypeID('Trgt'))

	var desc = new ActionDescriptor()
	desc.putReference(charIDToTypeID('null'), ref)
	var result = executeAction(charIDToTypeID('getd'), desc, DialogModes.NO)

	if (result.hasKey(charIDToTypeID('Pts ')))
	{
		var i, ptList = result.getList(charIDToTypeID('Pts '))
		var p0 = ptList.getObjectValue(0)
		var p1 = ptList.getObjectValue(2)

		var idx = charIDToTypeID('X   ')
		var idy = charIDToTypeID('Y   ')

		return [p0.getUnitDoubleValue(idx), p0.getUnitDoubleValue(idy), p1.getUnitDoubleValue(idx), p1.getUnitDoubleValue(idy)]
	}

	return []
}

function main()
{
	if (documents.length == 0)
	{
		alert("No opened documents")
		return
	}

	var pts = getRulerEndpoints()
	if (pts.length == 0)
	{
		alert("Ruler is not found")
		return
	}

	var x1 = pts[0]
	var y1 = pts[1]
	var x2 = pts[2]
	var y2 = pts[3]

	//alert("Endpoints: " + x1 + ", " + y1 + ", " + x2 + ", " + y2)

	var doc = activeDocument
	var layer = doc.activeLayer

	if (y1 == y2)
	{
		if (y1 <= 0 || y1 >= doc.height)
		{
			alert("Ruler is outside the image")
			return
		}

		doc.activeLayer = layer.duplicate()
		doc.selection.select([[0, y1 + 1], [doc.width, y1 + 1], [doc.width, doc.height], [0, doc.height], [0, y1 + 1]])
		doc.selection.clear()

		doc.activeLayer = layer.duplicate()
		doc.selection.select([[0, 0], [doc.width, 0], [doc.width, y1 - 1], [0, y1 - 1], [0, 0]])
		doc.selection.clear()
	}
	else if (x1 == x2)
	{
		if (x1 <= 0 || x1 >= doc.width)
		{
			alert("Ruler is outside the image")
			return
		}

		doc.activeLayer = layer.duplicate()
		doc.selection.select([[x1 + 1, 0], [doc.width, 0], [doc.width, doc.height], [x1 + 1, doc.height], [x1 + 1, 0]])
		doc.selection.clear()

		doc.activeLayer = layer.duplicate()
		doc.selection.select([[0, 0], [x1 - 1, 0], [x1 - 1, doc.height], [0, doc.height], [0, 0]])
		doc.selection.clear()
	}
	else
	{
		alert("Ruler is not horizontal or vertical")
		return
	}

	doc.selection.deselect()
}

var oldRulerUnits = preferences.rulerUnits
preferences.rulerUnits = Units.PIXELS

try
{
	main()
}
catch (e)
{
}

preferences.rulerUnits = oldRulerUnits
