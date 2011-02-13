<?php

include('lime.php');

$t = new lime_test(13, new lime_output_color());

$defined_classes = get_declared_classes();

$namespace = 'Mapnik';
$expected_classes = array(
    'Map',
    'DatasourceCache',
    'Datasource',
    'AggRenderer',
    'Color',
    'Envelope',
    'FeatureTypeStyle',
    'FreetypeEngine',
    'Image32',
    'Layer',
    'Parameters',
    'RuleType',
    'TextSymbolizer',
    'FontSet',
    'CoordTransform',
    'Coord2D',
    'Query',
    'FeatureSet',
    'Feature',
    'Geometry',
);

foreach ($expected_classes as $expected_class) {
    $t->ok(in_array("$namespace\\$expected_class", $defined_classes), "Class $expected_class defined");
}

$t->ok(function_exists("$namespace\save_to_file"), 'function "save_to_file" exists');
