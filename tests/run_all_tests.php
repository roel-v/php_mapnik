<?php

include('lime.php');

// Beware, lime.php was changed to accept a -c argument for this to work!
$harness = new lime_harness(array('php_cli' => $argv[1]));

$harness->register_glob('unit_tests_*.php');
//$harness->register('coord2d_tests.php');
//$harness->register('envelope_tests.php');

$harness->run();
