@echo off

set PATH_TO_PHP=..\php-sdk\php53dev\vc9\x86\php-5.3.4\Debug_TS

rem #### Individual unit tests

rem call %PATH_TO_PHP%\php.exe -c ..\php.ini classes_exist_tests.php
rem call %PATH_TO_PHP%\php.exe -c ..\php.ini unit_tests_coord2d.php
rem call %PATH_TO_PHP%\php.exe -c ..\php.ini unit_tests_envelope.php
rem call %PATH_TO_PHP%\php.exe -c ..\php.ini unit_tests_color.php
rem call %PATH_TO_PHP%\php.exe -c ..\php.ini unit_tests_map.php
rem call %PATH_TO_PHP%\php.exe -c ..\php.ini unit_tests_datasource_cache.php
rem call %PATH_TO_PHP%\php.exe -c ..\php.ini unit_tests_parameters.php
rem call %PATH_TO_PHP%\php.exe -c ..\php.ini unit_tests_datasource.php
rem call %PATH_TO_PHP%\php.exe -c ..\php.ini unit_tests_classes_exist.php
rem call %PATH_TO_PHP%\php.exe -c ..\php.ini unit_tests_feature.php
rem call %PATH_TO_PHP%\php.exe -c ..\php.ini unit_tests_feature_style.php
rem call %PATH_TO_PHP%\php.exe -c ..\php.ini unit_tests_featureset.php
rem call %PATH_TO_PHP%\php.exe -c ..\php.ini unit_tests_freetype_engine.php
rem call %PATH_TO_PHP%\php.exe -c ..\php.ini unit_tests_geometry.php
rem call %PATH_TO_PHP%\php.exe -c ..\php.ini unit_tests_image32.php
rem call %PATH_TO_PHP%\php.exe -c ..\php.ini unit_tests_layer.php
rem call %PATH_TO_PHP%\php.exe -c ..\php.ini qunit_tests_uery.php
rem call %PATH_TO_PHP%\php.exe -c ..\php.ini unit_tests_rule.php
rem call %PATH_TO_PHP%\php.exe -c ..\php.ini unit_tests_text_symbolizer.php
rem call %PATH_TO_PHP%\php.exe -c ..\php.ini unit_tests_agg_renderer.php

rem #### All unit tests
rem
rem This one runs all tests (everything ending in _tests.php) from a test harness.
rem call %PATH_TO_PHP%\php.exe -c ..\php.ini run_all_tests.php %PATH_TO_PHP%\php.exe

rem #### Integrated tests
rem call %PATH_TO_PHP%\php.exe -c ..\php.ini integrated_popplaces.php
call %PATH_TO_PHP%\php.exe -c ..\php.ini integrated_nuts3_regions.php
