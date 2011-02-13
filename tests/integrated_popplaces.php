<?php

include('lime.php');

// (Fairly) minimal example
// Renders just the cities from the rundemo sample.

$t = new lime_test(23, new lime_output_color());

// Set up the environment
Mapnik\DatasourceCache::registerDatasources("..\\mapnik-0.7.1\\plugins");
$t->is(in_array('shape', Mapnik\DatasourceCache::getPluginNames()), true, 'Shape data source available');
$result = Mapnik\FreetypeEngine::registerFont("..\\mapnik-0.7.1\\fonts\\DejaVuSans.ttf");
$t->is($result, true, 'Registered DejaVuSans.ttf font');

// Set up the map
$m = new Mapnik\Map(800, 600);
$t->isnt($result, null, 'Created Map of 800x600 pixels');

$m->setBackgroundColor(new Mapnik\Color(255, 255, 255));
$t->is($m->getBackgroundColor()->toHexString(), '#ffffff', 'Set background to 0xffffff (white)');

// Set the map data
$popplaces_style = new Mapnik\FeatureStyle();
$t->isnt($popplaces_style, null, 'Created new feature style');

$popplaces_rule = new Mapnik\Rule();
$t->isnt($popplaces_rule, null, 'Created new rule');

$popplaces_text_symbolizer = new Mapnik\TextSymbolizer('GEONAME', 'DejaVu Sans Book', 10, new Mapnik\Color(0, 0, 0));
$t->isnt($popplaces_text_symbolizer, null, 'Created text symbolizer');
// @todo
//$t->is($popplaces_text_symbolizer->getName(), 'GEONAME', 'Text symbolizer name is GEONAME');
//$t->is($popplaces_text_symbolizer->getFontFace(), '', 'Text symbolizer font face is DejaVu Sans Book');
//$t->is($popplaces_text_symbolizer->getTextSize(), 10, 'Text symbolizer text size is 10');
//$t->is($popplaces_text_symbolizer->getColor(), '', 'Text symbolizer text color is black');

$popplaces_text_symbolizer->setHaloFill(new Mapnik\Color(255, 255, 200));
$t->isa_ok($popplaces_text_symbolizer->getHaloFill(), 'Mapnik\\Color', 'halo_fill set to a Color');
$t->is($popplaces_text_symbolizer->getHaloFill()->toHexString(), '#ffffc8', 'halo_fill returns the right color');

$popplaces_text_symbolizer->setHaloRadius(1);
$t->is($popplaces_text_symbolizer->getHaloRadius(), 1, 'halo_radius set to 1');

$popplaces_rule->append($popplaces_text_symbolizer);
$t->pass('Appended symbolizer to rule');

$result = $popplaces_style->addRule($popplaces_rule);
$t->is($result, true, 'Rule added to feature style');

$result = $m->addStyle('popplaces', $popplaces_style);
$t->is($result, true, 'Feature style \'popplaces\' added to map');

$p = new Mapnik\Parameters();
$t->isnt($p, null, 'Created parameters to pass to layer');

$p->set('type', 'shape');
$p->set('file', '../mapnik-0.7.1/demo/data/popplaces');
$p->set('encoding', 'latin1');

$lyr = new Mapnik\Layer('Populated places');
$t->isnt($lyr, null, 'Created layer \'Populated places\'');

$shapefile_datasource = Mapnik\DatasourceCache::create($p);
$t->isnt($shapefile_datasource, null, 'Shape file data source created');
$lyr->setDatasource($shapefile_datasource);
$t->pass('Data source set');

$lyr->addStyle('popplaces');
$t->pass('popplaces style added');

$m->addLayer($lyr);
$t->pass('Layer added');

// Render the map

$m->zoomToBox(new Mapnik\Envelope(1405120.04127408, -247003.813399447, 1706357.31328276, -25098.593149577));
$t->pass('Zoomed to box');

$buf = new Mapnik\Image32($m->getWidth(), $m->getHeight());
$t->isnt($buf, null, 'Created Image32 image buffer');
// @todo test width and height

$agg_renderer = new Mapnik\AggRenderer($m, $buf);
$t->isnt($agg_renderer, null, 'Created renderer');

$agg_renderer->apply();
$t->pass('Agg renderer apply() didn\'t crash');

// Save the map
Mapnik\save_to_file($buf, 'demo.jpg', 'jpeg');
Mapnik\save_to_file($buf, 'demo.png', 'png');
Mapnik\save_to_file($buf, 'demo256.png', 'png256');
