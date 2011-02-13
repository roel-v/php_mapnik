<?php

include('lime.php');

$t = new lime_test(3, new lime_output_color());

$register_font_result = Mapnik\FreetypeEngine::registerFont("..\\mapnik-0.7.1\\fonts\\DejaVuSans.ttf");
$t->is($register_font_result, true, 'Register a font');

$all_face_names = Mapnik\FreetypeEngine::getFaceNames();
$t->is(is_array($all_face_names), true, 'getFaceNames returns array');
$t->is(sizeof($all_face_names), 1, 'getFaceNames has 1 entry');

// @todo
//createFace
