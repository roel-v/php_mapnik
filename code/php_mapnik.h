#ifndef PHP_MAPNIK_H
#define PHP_MAPNIK_H

#define PHP_MAPNIK_EXTNAME  "mapnik"
#define PHP_MAPNIK_EXTVER   "0.1"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <vector>
#include <iostream>

extern "C" {
#include "php.h"
};

extern zend_module_entry mapnik_module_entry;
#define phpext_mapnik_ptr &mapnik_module_entry

#endif /* PHP_MAPNIK_H */