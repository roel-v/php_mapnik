<?php

include('lime.php');

$t = new lime_test(20, new lime_output_color());

/* Test the various constructors.  */
$t->isnt(new Mapnik\Color(), null, 'Default constructor');
$t->isnt(new Mapnik\Color(128, 128, 128), null, 'Constructor with RGB components');
$t->isnt(new Mapnik\Color(128, 128, 128, 128), null, 'Constructor with RGB and alpha components');
$t->isnt(new Mapnik\Color("chocolate"), null, 'Constructor From CSS named color'); // ColorT(210, 105, 30)

/* See that other forms of constructors actually fail and don't crash. */
try {
    $c = new Mapnik\Color(1, 2);
    $t->fail('Wrong number of arguments in constructor (too few) but no exception thrown');
}
catch (Exception $e) {
    $t->pass('Wrong number of arguments in constructor (too few) successfully threw exception');
}

try {
    $c = new Mapnik\Color(1, 2, 3, 4, 5);
    $t->fail('Wrong number of arguments in constructor (too many) but no exception thrown');
}
catch (Exception $e) {
    $t->pass('Wrong number of arguments in constructor (too many) successfully threw exception');
}

try {
    $c = new Mapnik\Color("str1", "str2", "str3");
    $t->fail('Wrong argument types in constructor (3) but no exception thrown');
}
catch (Exception $e) {
    $t->pass('Wrong argument types in constructor (3) successfully threw exception');
}

try {
    $c = new Mapnik\Color("str1", "str2", "str3", "str4");
    $t->fail('Wrong argument types in constructor (4) but no exception thrown');
}
catch (Exception $e) {
    $t->pass('Wrong argument types in constructor (4) successfully threw exception');
}

/*
 * Getters and setters for color components.
 */
$c = new Mapnik\Color();
$c->setRed(200);
$t->is($c->getRed(), 200, 'Red setter and getter');
$c->setGreen(200);
$t->is($c->getGreen(), 200, 'Green setter and getter');
$c->setBlue(200);
$t->is($c->getBlue(), 200, 'Blue setter and getter');
$c->setAlpha(200);
$t->is($c->getAlpha(), 200, 'Alpha setter and getter');

$c = new Mapnik\Color(1, 2, 3, 4);
$t->is($c->getRed(), 1, 'Constructing with RGBA components: red');
$t->is($c->getGreen(), 2, 'Constructing with RGBA components: green');
$t->is($c->getBlue(), 3, 'Constructing with RGBA components: blue');
$t->is($c->getAlpha(), 4, 'Constructing with RGBA components: alpha');
$c = new Mapnik\Color(1, 1, 1);
$t->is($c->getAlpha(), 255, 'Constructing with default alpha: alpha is 255');

/*
 * Some conversion functions to various formats.
 */
$c = new Mapnik\Color(10, 10, 10, 0);
$t->is((string)$c, 'rgba(10,10,10,0)', '__toString');
$t->is($c->rgba(), 657930, 'rgba');
$t->is($c->toHexString(), '#0a0a0a', 'toHexString');

// Constructor from CSS named color.
