<?php

include('lime.php');

$t = new lime_test(4, new lime_output_color());

$symbolizer = new Mapnik\TextSymbolizer('GEONAME', 'DejaVu Sans Book', 10, new Mapnik\Color(0,255,0));
$t->isnt($symbolizer, null, 'Constructor with 4 arguments');

$symbolizer = new Mapnik\TextSymbolizer('GEONAME', 10, new Mapnik\Color(0,255,0));
$t->isnt($symbolizer, null, 'Constructor with 3 arguments');

$symbolizer->setHaloFill(new Mapnik\Color(0, 0, 255));
$control_color = new Mapnik\Color(0, 0, 255);
$t->is($symbolizer->getHaloFill()->toHexString(), $control_color->toHexString(), 'halo fill getter/setter');

$symbolizer->setHaloRadius(5);
$t->is($symbolizer->getHaloRadius(), 5, 'halo radius getter/setter');

// @todo all the rest
