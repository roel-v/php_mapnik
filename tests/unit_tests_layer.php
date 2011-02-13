<?php

include('lime.php');

$t = new lime_test(5, new lime_output_color());

// Default constructors
$l = new Mapnik\Layer('test layer');
$t->isnt($l, null, 'Layer constructor with one argument');
$t->isa_ok($l, 'Mapnik\\Layer', 'Layer constructor with one argument returned right type');

$l = new Mapnik\Layer('test layer');
$t->isnt($l, null, 'Layer constructor with two arguments', '+proj=latlong +datum=WGS84');
$t->isa_ok($l, 'Mapnik\\Layer', 'Layer constructor with two arguments returned right type');

try {
	$l = new Mapnik\Layer();
	$t->fail('No arguments passed to Layer constructor but no exception thrown');
}
catch (Exception $e) {
	$t->pass('No arguments passed to Layer constructor, exception thrown');
}

