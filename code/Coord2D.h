#include <mapnik/coord.hpp>

DEFINE_CLASS(coord2d, Coord2D);

PHP_METHOD(Coord2D, __construct)
{
	mapnik::coord2d* Coord2D = NULL;

	double x, y;

	if (ZEND_NUM_ARGS() == 0) {
		Coord2D = PHP_NEW mapnik::coord2d();
	} else if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "dd", &x, &y) == SUCCESS) {
		Coord2D = PHP_NEW mapnik::coord2d(x, y);
	} else {
		// None of the supported parameter formats. Fail construction.
		zend_throw_exception(zend_exception_get_default(TSRMLS_C), "Wrong arguments passed to constructor", 0 TSRMLS_CC);
		RETURN_FALSE;
	}

	assert(Coord2D != NULL);

	INIT_CPP_OBJECT(Coord2D);
}

PHP_METHOD(Coord2D, getX)
{
	GET_THIS_CPP_OBJECT(coord2d, Coord2D);
	RETURN_DOUBLE(this_Coord2D->x);
}

PHP_METHOD(Coord2D, getY)
{
	GET_THIS_CPP_OBJECT(coord2d, Coord2D);
	RETURN_DOUBLE(this_Coord2D->y);
}

static function_entry php_Mapnik_Coord2D_methods[] = {
	PHP_ME(Coord2D, __construct,	NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Coord2D, getX,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Coord2D, getY,		NULL,	ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};
