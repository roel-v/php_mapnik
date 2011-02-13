<?php

include('lime.php');

$t = new lime_test(44, new lime_output_color());

/* Test the various constructors.  */
$t->isnt(new Mapnik\Envelope(), null, 'Default constructor');
$t->isnt(new Mapnik\Envelope(100.50, 100.50, 200.50, 200.50), null, 'Constructor with 4 arguments');

/* See that other forms of constructors actually fail and don't crash. */
try {
    $e = new Mapnik\Envelope(1, 2, 3);
    $t->fail('Wrong number of arguments in constructor (too few) but no exception thrown');
}
catch (Exception $e) {
    $t->pass('Wrong number of arguments in constructor (too few) successfully threw exception');
}

try {
    $e = new Mapnik\Envelope(1, 2, 3, 4, 5);
    $t->fail('Wrong number of arguments in constructor (too many) but no exception thrown');
}
catch (Exception $e) {
    $t->pass('Wrong number of arguments in constructor (too many) successfully threw exception');
}

try {
    $e = new Mapnik\Envelope("test", 2, 3, 4);
    $t->fail('Wrong type of arguments in constructor but no exception thrown');
}
catch (Exception $e) {
    $t->pass('Wrong type of arguments in constructor successfully threw exception');
}

// Test various getters / setters
$e = new Mapnik\Envelope(1, 2, 6, 8);
$t->is($e->getMinX(), 1, 'Getter: min X');
$t->is($e->getMinY(), 2, 'Getter: min Y');
$t->is($e->getMaxX(), 6, 'Getter: max X');
$t->is($e->getMaxY(), 8, 'Getter: max Y');
$t->is($e->getWidth(), 5, 'Getter: width');
$t->is($e->getHeight(), 6, 'Getter: height');
$e->setWidth(10);
$t->is($e->getWidth(), 10, 'Setter: set width');
$e->setHeight(20);
$t->is($e->getHeight(), 20, 'Setter: set height');

// Other methods
$e = new Mapnik\Envelope(0, 0, 10, 10);
$center= $e->getCenter();
$t->isa_ok($center, 'Mapnik\\Coord2D', 'getCenter returns object of type Coord2D');
$t->is($center->getX(), 5, 'Center X');
$t->is($center->getY(), 5, 'Center Y');

$e->expandToInclude(15, 20);
$t->is($e->getMaxX(), 15, 'expandToInclude, X and Y parameter version - X parameter');
$t->is($e->getMaxY(), 20, 'expandToInclude, X and Y parameter version - Y parameter');

$coord = new Mapnik\Coord2D(30, 40);
$e->expandToInclude($coord);
$t->is($e->getMaxX(), 30, 'expandToInclude, Coord2D parameter version - X parameter');
$t->is($e->getMaxY(), 40, 'expandToInclude, Coord2D parameter version - Y parameter');

$e = new Mapnik\Envelope(10, 15, 25, 35);
$other_e = new Mapnik\Envelope(0, 5, 45, 55);
$e->expandToInclude($other_e);
$t->is($e->getMinX(), 0, 'expandToInclude, Envelope parameter version - min X parameter');
$t->is($e->getMinY(), 5, 'expandToInclude, Envelope parameter version - min Y parameter');
$t->is($e->getMaxX(), 45, 'expandToInclude, Envelope parameter version - max X parameter');
$t->is($e->getMaxY(), 55, 'expandToInclude, Envelope parameter version - max Y parameter');

$e = new Mapnik\Envelope(10, 15, 25, 35);
$t->is($e->contains(17, 17), true, 'contains, X and Y parameter version, test true');
$t->is($e->contains(50, 50), false, 'contains, X and Y parameter version, test false');
$t->is($e->contains(13, 50), false, 'contains, X and Y parameter version, test X true but Y false');
$t->is($e->contains(50, 30), false, 'contains, X and Y parameter version, test Y true but X false');

$e = new Mapnik\Envelope(10, 15, 25, 35);
$t->is($e->contains(17, 17), true, 'intersects, X and Y parameter version, test true');
$t->is($e->contains(50, 50), false, 'intersects, X and Y parameter version, test false');
$t->is($e->contains(13, 50), false, 'intersects, X and Y parameter version, test X true but Y false');
$t->is($e->contains(50, 30), false, 'intersects, X and Y parameter version, test Y true but X false');

$e1 = new Mapnik\Envelope(10, 10, 20, 20);
$e2 = new Mapnik\Envelope(15, 15, 30, 30);
$result_envelope = $e1->intersect($e2);
$t->is($result_envelope->getMinX(), 15, 'intersect, min X');
$t->is($result_envelope->getMinY(), 15, 'intersect, min Y');
$t->is($result_envelope->getMaxX(), 20, 'intersect, max X');
$t->is($result_envelope->getMaxY(), 20, 'intersect, max Y');

$e = new Mapnik\Envelope(10, 10, 20, 20);
$e->reCenter(0, 0);
$t->is($e->getMinX(), -5, 'reCenter, min X');
$t->is($e->getMinY(), -5, 'reCenter, min Y');
$t->is($e->getMaxX(), 5, 'reCenter, max X');
$t->is($e->getMaxY(), 5, 'reCenter, max Y');

$e = new Mapnik\Envelope(10, 10, 20, 20);
$e->init(1, 2, 3, 4);
$t->is($e->getMinX(), 1, 'init, min X');
$t->is($e->getMinY(), 2, 'init, min Y');
$t->is($e->getMaxX(), 3, 'init, max X');
$t->is($e->getMaxY(), 4, 'init, max Y');

$e->init(1, 2, 3, 4, 5);
