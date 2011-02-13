<?php

include('lime.php');

$t = new lime_test(1, new lime_output_color());

$feature_style = new Mapnik\FeatureStyle();
$t->isnt($feature_style, null, 'FeatureStyle created OK');

$rule = new Mapnik\Rule();
$feature_style->addRule($rule);

// @todo
// PHP_ME(FeatureStyle, getRules,		NULL,	ZEND_ACC_PUBLIC)
