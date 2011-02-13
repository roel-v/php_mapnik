<?php

include('lime.php');

$t = new lime_test(5, new lime_output_color());

$p = new Mapnik\Parameters();

$t->isnt($p, null, 'Created parameters object');

$p->set('string_test', 'hello');
$t->is($p->get('string_test'), 'hello', 'Setter/getter with string key');

$p->set('integer_test', 5);
$t->is($p->get('integer_test'), 5, 'Setter/getter with integer key');

$p->set('double_test', 3.14);
$t->is($p->get('double_test'), 3.14, 'Setter/getter with double key');

$t->is($p->get('doesnt_exist'), null, 'Getter for unknown key returns null');
