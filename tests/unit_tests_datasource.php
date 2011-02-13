<?php

include('lime.php');

$t = new lime_test(4, new lime_output_color());

Mapnik\DataSourceCache::registerDataSources('..\mapnik-0.7.1\plugins');

$data_sources = Mapnik\DatasourceCache::getPluginNames();
$t->is(is_array($data_sources), true, 'getPluginNames returns an array');
$t->is(count($data_sources), 1, 'One plugin found');
$t->is($data_sources[0], 'shape', 'Shape plugin found');

$p = new Mapnik\Parameters();
$p->set('type', 'shape');
$p->set('file', '../mapnik-0.7.1/demo/data/boundaries');
$datasource = Mapnik\DataSourceCache::createDatasource($p);
$t->isnt($datasource, null, 'Shape datasource created.');
