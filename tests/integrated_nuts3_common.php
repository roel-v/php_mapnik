<?php
/*
 * Shared part of all integrated tests that use the NUTS3 data set.
 * Download the data from http://epp.eurostat.ec.europa.eu/portal/page/portal/gisco/popups/references/administrative_units_statistical_units_1 .
 */

include('lime.php');

$t = new lime_test($num_tests, new lime_output_color());

// Set up the environment
Mapnik\DatasourceCache::registerDatasources("..\\mapnik-0.7.1\\plugins");
$result = $t->is(in_array('shape', Mapnik\DatasourceCache::getPluginNames()), true, 'Shape data source available');
// If we can't find a data source, no use continueing.
if ($result == false) {
	echo "No datasource found, giving up\n";
	exit(1);
}

$result = Mapnik\FreetypeEngine::registerFont("..\\mapnik-0.7.1\\fonts\\DejaVuSans.ttf");
$t->is($result, true, 'Registered DejaVuSans.ttf font');

// Set up the map
// Default: "+proj=latlong +datum=WGS84"
// GISCO NUTS3 dataset datum: D_ETRS_1989
// Projection: Lambert Azimuthal Equal Area (laea)
$m = new Mapnik\Map(800, 600);
$t->isnt($result, null, 'Created Map of 800x600 pixels');
$m->setBackgroundColor(new Mapnik\Color(255, 255, 255));
$t->is($m->getBackgroundColor()->toHexString(), '#ffffff', 'Set background to 0xffffff (white)');
