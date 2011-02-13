<?php

include('lime.php');

$t = new lime_test(4, new lime_output_color());

/* Test the various constructors.  */
$t->isnt(new Mapnik\Coord2D(), null, 'Default constructor');
$t->isnt(new Mapnik\Coord2D(5, 10), null, 'Construct with two arguments');

$c = new Mapnik\Coord2D(10.5, 20.5);
$t->is($c->getX(), 10.5, 'Getter: X coordinate');
$t->is($c->getY(), 20.5, 'Getter: Y coordinate');


