#include <stdio.h>

#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>

#include "php_mapnik.h"

void* operator new(size_t size, char const * file, int line)
{
	return emalloc(size);
}

void operator delete(void * p, char const * file, int line)
{
	if (p) {	// Check pointer, otherwise Zend memory manager will send warnings to memory 
				// debugging about null pointer.
		efree(p);	
	}
}

#include "php_cpp_wrapping_tools.h"

#include <assert.h>

#include <boost/foreach.hpp>

#include <zend_hash.h>
#include <zend_exceptions.h>

#include "Coord2D.h"
#include "Color.h"
#include "Stroke.h"
#include "Envelope.h"
#include "Parameters.h"
#include "Query.h"
#include "Datasource.h"
#include "DatasourceCache.h"
#include "FreetypeEngine.h"
#include "Feature.h"
#include "FeatureSet.h"
#include "TextSymbolizer.h"	// All symbolizers have to be before Rule
#include "PolygonSymbolizer.h"	// All symbolizers have to be before Rule
#include "Rule.h"
#include "FeatureStyle.h"
#include "Layer.h"
#include "Image32.h"
#include "Map.h"
#include "AggRenderer.h" // Needs Image32 and Map

#include "standalone_functions.h"

PHP_MINIT_FUNCTION(mapnik)
{
	INIT_CLASS(Coord2D);
	INIT_CLASS(Envelope);
	INIT_CLASS(Color);
	INIT_CLASS(Stroke);
	INIT_CLASS(Query);
	INIT_CLASS(Parameters);
	INIT_CLASS(Datasource);
	INIT_CLASS(FreetypeEngine);
	INIT_STATIC_CLASS(DatasourceCache);
	//INIT_CLASS(Feature);
	INIT_CLASS(Featureset);
	INIT_CLASS(Rule);
	INIT_CLASS(FeatureStyle);
	INIT_CLASS(TextSymbolizer);
	INIT_CLASS(PolygonSymbolizer);
	INIT_CLASS(Layer);
	INIT_CLASS(AggRenderer);
	INIT_CLASS(Image32);
	INIT_CLASS(Map);

	return SUCCESS;
}

zend_module_entry mapnik_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_MAPNIK_EXTNAME,
    php_mapnik_functions,	/* Functions */
    PHP_MINIT(mapnik),		/* MINIT */
    NULL,					/* MSHUTDOWN */
    NULL,					/* RINIT */
    NULL,					/* RSHUTDOWN */
    NULL,					/* MINFO */
#if ZEND_MODULE_API_NO >= 20010901
    PHP_MAPNIK_EXTVER,
#endif
    STANDARD_MODULE_PROPERTIES
};

// Not sure why this ifdef is here, I just took it from the docs.
#ifdef COMPILE_DL_MAPNIK
extern "C" {
ZEND_GET_MODULE(mapnik)
}
#endif
