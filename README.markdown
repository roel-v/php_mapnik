php_mapnik
==========

php_mapnik is a PHP extension that wraps the [mapnik](www.mapnik.org) map rendering library.

Compiling
---------
The whole package is very much under development, only try when you have experience with Visual Studio or have lots of time.

Hasn't been build on anything but Windws yet. For Windows:
- Set up php in a subdirectory called php-sdk.
- follow instructions on php.net to build it + the dependencies.
- Make a directory called 'thirdparty' in the mapnik-0.7.1 direcotory.
- Use the mapnik version in this repo, because it has some tweaks to get it to build! Patches are in mapnik trac (look for roel_v).
- Build instructions for mapnik are forthcoming...
- VS 2008 solution is in vs_project directory.

Running
-------
There are a bunch of examples in the tests directory, look for the 'integrated_XXX' files.
