#include <mapnik/line_symbolizer.hpp>

DEFINE_CLASS(line_symbolizer, LineSymbolizer)

/*
    explicit line_symbolizer()
    line_symbolizer(stroke const& stroke)
    line_symbolizer(color const& pen,float width=1.0)
 */
PHP_METHOD(LineSymbolizer, __construct)
{
	mapnik::line_symbolizer LineSymbolizer = NULL;

	zval* stroke_zval;
	zval* color_zval;
	double width;

	if (ZEND_NUM_ARGS() == 0) {
		LineSymbolizer = PHP_NEW mapnik::line_symbolizer();
	} else if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "O", &stroke_zval, php_Mapnik_Stroke_entry) == SUCCESS) {
		assert(false);
		GET_CPP_OBJECT_FROM_ZVAL(stroke_zval, stroke, Stroke, stroke_argument);
		LineSymbolizer = PHP_NEW mapnik::line_symbolizer(width, height);
	} else if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "Od", &color_zval, php_Mapnik_Color_entry, &width) == SUCCESS) {
		GET_CPP_OBJECT_FROM_ZVAL(color_zval, color, Color, color_argument);
		LineSymbolizer = PHP_NEW mapnik::line_symbolizer(*color_argument, width);
	} else {
		zend_throw_exception(zend_exception_get_default(TSRMLS_C), "Wrong arguments passed to constructor", 0 TSRMLS_CC);
		RETURN_FALSE;
	}

	assert(LineSymbolizer);

	INIT_CPP_OBJECT(LineSymbolizer);
}

static function_entry php_Mapnik_LineSymbolizer_methods[] = {
	PHP_ME(PolygonSymbolizer, __construct,		NULL,	ZEND_ACC_PUBLIC)
	// Properties
	{ NULL, NULL, NULL }
};