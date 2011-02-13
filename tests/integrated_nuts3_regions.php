<?php
$num_tests = 12;

include 'integrated_nuts3_common.php';

/* Render NUTS3 regions, with a different color for each one.
 * Exercises:
 * 	- shape data source
 * 	- PolygonSymbolizer
 */

// Set up the map data
$nuts3_symbolizer = new Mapnik\Symbolizer();
$t->isnt($nuts3_symbolizer, null, 'Created PolygonSymbolizer');
$nuts3_symbolizer->setFill(new Mapnik\Color(255, 0, 0));
$t->is($nuts3_symbolizer->getFill()->toHexString(), '#ff0000', 'Polygon fill set to red');

$nuts3_rule = new Mapnik\Rule();
$t->isnt($nuts3_rule, null, 'Created Rule');
$nuts3_rule->append($nuts3_symbolizer);
$t->pass('Appended symbolizer to rule without crashing');

$nuts3_feature_style = new Mapnik\FeatureStyle();
$t->isnt($nuts3_feature_style, null, 'Created feature style');
$nuts3_feature_style->addRule($nuts3_rule);
$t->pass('Rule added to feature style without crashing');

$m->addStyle('nuts3', $nuts3_feature_style);
$t->pass('Style added to map');

$p = new Mapnik\Parameters();
$p->set('type', 'shape');
$p->set('file', '../sample data/NUTS_03M_2006_SH/data/NUTS_BN_03M_2006');
$p->set('encoding', 'latin1');
$shapefile_datasource = Mapnik\DatasourceCache::create($p);
$t->pass('Shapefile datasource created');

$lyr = new Mapnik\Layer('NUTS3 regions');
$lyr->setDatasource($shapefile_datasource);

$lyr->addStyle('nuts3');

// Add query here:
// STAT_LEVL_ = 0

$m->addLayer($lyr);

// Render the map
// LL: -11.96 ,36.59
// UR: 44.31 ,72.12
$m->zoomToBox(new Mapnik\Envelope(-11.96, 36.59, 44.31, 72.12));
$buf = new Mapnik\Image32($m->getWidth(), $m->getHeight());
$agg_renderer = new Mapnik\AggRenderer($m, $buf);
$agg_renderer->apply();

// Save the map
Mapnik\save_to_file($buf, 'demo.png', 'png');
