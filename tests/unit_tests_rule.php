<?php

include('lime.php');

$t = new lime_test(11, new lime_output_color());

// __construct
$t->isnt(new Mapnik\Rule(), null, 'Empty constructor');
$t->isnt(new Mapnik\Rule('some_name'), null, 'Constructor with one argument');
$t->isnt(new Mapnik\Rule('some_name', 'some_title'), null, 'Constructor with two arguments');
$t->isnt(new Mapnik\Rule('some_name', 'some_title', 5), null, 'Constructor with three arguments');
$t->isnt(new Mapnik\Rule('some_name', 'some_title', 5, 50), null, 'Constructor with four arguments');

$rule = new Mapnik\Rule();

$rule->setMaxScale(5);
$t->is($rule->getMaxScale(), 5, 'Get/set max scale');

$rule->setMinScale(3);
$t->is($rule->getMinScale(), 3, 'Get/set min scale');

$rule->setName('test name');
$t->is($rule->getName(), 'test name', 'Get/set name');

$rule->setTitle('test title');
$t->is($rule->getTitle(), 'test title', 'Get/set title');

$rule->setAbstract('test abstract');
$t->is($rule->getAbstract(), 'test abstract', 'Get/set abstract');

$rule->append(new Mapnik\TextSymbolizer('GEONAME', 'DejaVu Sans Book', 10, new Mapnik\Color(0,255,0)));
$t->pass('Append of a new TextSymbolizer doesn\t crash');
// @todo
// removeAt
// getSymbolizers
// setFilter
// getFilter
// setElse
// hasElseFilter
// active
