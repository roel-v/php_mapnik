<?php

include('lime.php');

$t = new lime_test(7, new lime_output_color());

$m = new Mapnik\Map();
$i = new Mapnik\Image32(800, 600);
$r = new Mapnik\AggRenderer($m, $i);
