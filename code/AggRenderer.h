#include <mapnik/agg_renderer.hpp>

DEFINE_CLASS(agg_renderer<mapnik::Image32>, AggRenderer);

PHP_METHOD(AggRenderer, __construct)
{
	/*
	mapnik::Map map;
	mapnik::Image32 image(800, 600);
	mapnik::agg_renderer<mapnik::Image32>* AggRenderer = PHP_NEW mapnik::agg_renderer<mapnik::Image32>(map, image);
	*/
	zval* map_zval;
	zval* image32_zval;

	if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "OO",
				&map_zval, php_Mapnik_Map_entry, &image32_zval, php_Mapnik_Image32_entry) == FAILURE) {
		// None of the supported parameter formats. Fail construction.
		zend_throw_exception(zend_exception_get_default(TSRMLS_C), "Wrong arguments passed to constructor", 0 TSRMLS_CC);
		RETURN_NULL();
	}

	GET_CPP_OBJECT_FROM_ZVAL(map_zval, Map, Map, map_argument);
	GET_CPP_OBJECT_FROM_ZVAL(image32_zval, Image32, Image32, image32_argument);

	mapnik::agg_renderer<mapnik::Image32>* AggRenderer =
		PHP_NEW mapnik::agg_renderer<mapnik::Image32>(*map_argument, *image32_argument);

	INIT_CPP_OBJECT(AggRenderer);
}

PHP_METHOD(AggRenderer, apply)
{
	GET_THIS_CPP_OBJECT(agg_renderer<mapnik::Image32>, AggRenderer);

	this_AggRenderer->apply();

	RETURN_TRUE;
}

static function_entry php_Mapnik_AggRenderer_methods[] = {
	PHP_ME(AggRenderer, __construct,	NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(AggRenderer, apply,			NULL,	ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

// vim:set noexpandtab:
