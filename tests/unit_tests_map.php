<?php

include('lime.php');

$t = new lime_test(7, new lime_output_color());

/* Test the various constructors.  */
$m = new Mapnik\Map();
$t->is($m->getWidth(), 400, 'Default constructor: width is 400');
$t->is($m->getHeight(), 400, 'Default constructor: height is 400');
$t->is($m->getSrs(), '+proj=latlong +datum=WGS84', 'Default constructor: projection is "+proj=latlong +datum=WGS84"');

$fs = new Mapnik\FeatureStyle();
$t->is($m->addStyle('feature style name', $fs), true, 'Add feature style to map');

$t->is($m->getBackgroundColor(), null, 'No background color set yet, getBackgroundColor returns null');
$bg_color = new Mapnik\Color(255, 255, 255);
$m->setBackgroundColor($bg_color);
$t->isa_ok($m->getBackgroundColor(), 'Mapnik\\Color', 'getBackgroundColor returns a Color object');
$t->is($m->getBackgroundColor()->toHexString(), $bg_color->toHexString(), 'getBackgroundColor returns the right color');

$l = new Mapnik\Layer('test layer');
$m->addLayer($l);
// @todo test getLayer

$m->zoomToBox(new Mapnik\Envelope(0.0, 0.0, 1.0, 1.0));
// @todo test zoomToBox

/*
$t->getStyleNames
getStyle
removeStyle
removeAllStyles
*/

//$m = new Mapnik\Map(800, 600);

//$t->is();


//m->setBackground(Mapnik\ColorFactory::FromString("white"));
//m->zoomToBox(new Mapnik\Envelope(1405120.04127408, -247003.813399447, 1706357.31328276, -25098.593149577));
//m->addLayer(lyr);

/*
	PHP_ME(Map, __construct,	NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, getWidth,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, setWidth,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, getHeight,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, setHeight,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, getSrs,				NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, setSrs,				NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, setBufferSize,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, getBufferSize,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, getBackgroundColor,	NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, setBackgroundColor,	NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, getAspectFixMode,	NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, setAspectFixMode,	NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, getStyleNames,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, getStyle,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, addStyle,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, removeStyle,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, removeAllStyles,	NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, getFontSetNames,	NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, getFontSet,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, addFontSet,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, getLayerCount,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, getLayer,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, addLayer,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, removeLayer,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, removeAllLayers,	NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, resize,				NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, queryPoint,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, queryMapPoint,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, getScale,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, getScaleDenominator,	NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, getViewTransform,	NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, getCurrentExtent,	NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, getBufferedExtent,	NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, zoom,				NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, zoomToBox,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, zoomAll,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, pan,				NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, panAndZoom,			NULL,	ZEND_ACC_PUBLIC)
*/

