#include <mapnik/polygon_symbolizer.hpp>

DEFINE_CLASS(polygon_symbolizer, PolygonSymbolizer);

// explicit polygon_symbolizer() 
// polygon_symbolizer(color const& fill)
PHP_METHOD(PolygonSymbolizer, __construct)
{
	mapnik::polygon_symbolizer* PolygonSymbolizer = NULL;

	zval* color_zval;

	if (ZEND_NUM_ARGS() == 0) {
		PolygonSymbolizer = PHP_NEW mapnik::polygon_symbolizer();
	} else if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "O", &color_zval, php_Mapnik_Color_entry) == SUCCESS) {
		GET_CPP_OBJECT_FROM_ZVAL(color_zval, color, Color, color_argument)
		PolygonSymbolizer = PHP_NEW mapnik::polygon_symbolizer(*color_argument);
	} else {
		// None of the supported parameter formats. Fail construction.
		zend_throw_exception(zend_exception_get_default(TSRMLS_C), "Wrong arguments passed to constructor", 0 TSRMLS_CC);
		RETURN_FALSE;
	}

	assert(PolygonSymbolizer);

	INIT_CPP_OBJECT(PolygonSymbolizer);
}

IMPLEMENT_DOUBLE_GETTER(get_opacity, getOpacity, polygon_symbolizer, PolygonSymbolizer);
IMPLEMENT_DOUBLE_GETTER(get_gamma, getGamma, polygon_symbolizer, PolygonSymbolizer);
BEGIN_IMPLEMENT_OBJECT_GETTER(get_fill, getFill, polygon_symbolizer, PolygonSymbolizer, color, Color, 4)
	SETUP_ARGUMENT(0, DOUBLE, Color.red())
	SETUP_ARGUMENT(1, DOUBLE, Color.green())
	SETUP_ARGUMENT(2, DOUBLE, Color.blue())
	SETUP_ARGUMENT(3, DOUBLE, Color.alpha())
END_IMPLEMENT_OBJECT_GETTER()

IMPLEMENT_FLOAT_SETTER(set_opacity, setOpacity, polygon_symbolizer, PolygonSymbolizer);
IMPLEMENT_FLOAT_SETTER(set_gamma, setGamma, polygon_symbolizer, PolygonSymbolizer);
IMPLEMENT_OBJECT_SETTER(set_fill, setFill, polygon_symbolizer, PolygonSymbolizer, color, Color);

static function_entry php_Mapnik_PolygonSymbolizer_methods[] = {
	PHP_ME(PolygonSymbolizer, __construct,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(PolygonSymbolizer, getFill,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(PolygonSymbolizer, setFill,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(PolygonSymbolizer, getOpacity,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(PolygonSymbolizer, setOpacity,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(PolygonSymbolizer, getGamma,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(PolygonSymbolizer, setGamma,		NULL,	ZEND_ACC_PUBLIC)
	// Properties
	{ NULL, NULL, NULL }
};