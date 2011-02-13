<?php

include('lime.php');

$t = new lime_test(4, new lime_output_color());

Mapnik\DataSourceCache::registerDataSources('..\mapnik-0.7.1\plugins');

$all_plugins = Mapnik\DataSourceCache::getPluginNames();
$t->is(is_array($all_plugins), true, 'getPluginNames returns array');
$t->is(sizeof($all_plugins), 1, '1 plugin found');
$t->is($all_plugins[0], 'shape', 'shapefile plugin found');

$p = new Mapnik\Parameters();
$p->set('type', 'shape');
$p->set('file', '../mapnik-0.7.1/demo/data/boundaries');

$shapefile_datasource = Mapnik\DataSourceCache::create($p);
$t->isnt($shapefile_datasource, null, 'Created shapefile datasource');
