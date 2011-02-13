#include <mapnik/Envelope.hpp>

DEFINE_CLASS(Envelope<double>, Envelope);

/*
Envelope();
Envelope(T minx,T miny,T maxx,T maxy);
Envelope(const coord<T,2>& c0,const coord<T,2>& c1);
Envelope(const EnvelopeType& rhs);
 */
PHP_METHOD(Envelope, __construct)
{
	mapnik::Envelope<double>* Envelope = NULL;

	double minx, miny, maxx, maxy;

	if (ZEND_NUM_ARGS() == 0) {
		Envelope = PHP_NEW mapnik::Envelope<double>();
	} else if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "dddd", &minx, &miny, &maxx, &maxy) == SUCCESS) {
		Envelope = PHP_NEW mapnik::Envelope<double>(minx, miny, maxx, maxy);
	} else {
		// None of the supported parameter formats. Fail construction.
		zend_throw_exception(zend_exception_get_default(TSRMLS_C), "Wrong arguments passed to constructor", 0 TSRMLS_CC);
		RETURN_NULL();
	}

	assert(Envelope != NULL);

	INIT_CPP_OBJECT(Envelope);
}

IMPLEMENT_DOUBLE_GETTER(minx, getMinX, Envelope<double>, Envelope)
IMPLEMENT_DOUBLE_GETTER(miny, getMinY, Envelope<double>, Envelope)
IMPLEMENT_DOUBLE_GETTER(maxx, getMaxX, Envelope<double>, Envelope)
IMPLEMENT_DOUBLE_GETTER(maxy, getMaxY, Envelope<double>, Envelope)
IMPLEMENT_DOUBLE_GETTER(width, getWidth, Envelope<double>, Envelope)
IMPLEMENT_DOUBLE_GETTER(height, getHeight, Envelope<double>, Envelope)
IMPLEMENT_DOUBLE_SETTER(width, setWidth, Envelope<double>, Envelope)
IMPLEMENT_DOUBLE_SETTER(height, setHeight, Envelope<double>, Envelope)
BEGIN_IMPLEMENT_OBJECT_GETTER(center, getCenter, Envelope<double>, Envelope, coord2d, Coord2D, 2)
	SETUP_ARGUMENT(0, DOUBLE, Coord2D.x)
	SETUP_ARGUMENT(1, DOUBLE, Coord2D.y)
END_IMPLEMENT_OBJECT_GETTER()

/*
void expand_to_include(T x,T y);
void expand_to_include(const coord<T,2>& c);
void expand_to_include(const EnvelopeType& other);
*/
PHP_METHOD(Envelope, expandToInclude)
{
	GET_THIS_CPP_OBJECT(Envelope<double>, Envelope);

	double x, y;
	zval* value;

	if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "dd", &x, &y) == SUCCESS) {
		this_Envelope->expand_to_include(x, y);
		return;
	} else if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "O", &value, php_Mapnik_Coord2D_entry) == SUCCESS) {
		GET_CPP_OBJECT_FROM_ZVAL(value, coord2d, Coord2D, passed_in_object);
		this_Envelope->expand_to_include(*passed_in_object);
		return;
	} else if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "O", &value, php_Mapnik_Envelope_entry) == SUCCESS) {
		GET_CPP_OBJECT_FROM_ZVAL(value, Envelope<double>, Envelope, passed_in_object);
		this_Envelope->expand_to_include(*passed_in_object);
		return;
	}

	php_error_docref(NULL TSRMLS_CC, E_WARNING, "Wrong arguments passed to expandToInclude");

	RETURN_NULL();
}

/*
bool contains(const coord<T,2> &c) const;
bool contains(T x,T y) const;
bool contains(const EnvelopeType &other) const;
*/
PHP_METHOD(Envelope, contains)
{
	GET_THIS_CPP_OBJECT(Envelope<double>, Envelope);

	double x, y;
	zval* value;

	if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "dd", &x, &y) == SUCCESS) {
		RETURN_BOOL(this_Envelope->contains(x, y));
	} else if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "O", &value, php_Mapnik_Coord2D_entry) == SUCCESS) {
		GET_CPP_OBJECT_FROM_ZVAL(value, coord2d, Coord2D, passed_in_object);
		RETURN_BOOL(this_Envelope->contains(*passed_in_object));
	} else if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "O", &value, php_Mapnik_Envelope_entry) == SUCCESS) {
		GET_CPP_OBJECT_FROM_ZVAL(value, Envelope<double>, Envelope, passed_in_object);
		RETURN_BOOL(this_Envelope->contains(*passed_in_object));
	}

	php_error_docref(NULL TSRMLS_CC, E_WARNING, "Wrong arguments passed to contains");

	RETURN_NULL();
}

/*
bool intersects(const coord<T,2> &c) const;
bool intersects(T x,T y) const;
bool intersects(const EnvelopeType &other) const;
*/
PHP_METHOD(Envelope, intersects)
{
	GET_THIS_CPP_OBJECT(Envelope<double>, Envelope);

	double x, y;
	zval* value;

	if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "dd", &x, &y) == SUCCESS) {
		RETURN_BOOL(this_Envelope->intersects(x, y));
	} else if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "O", &value, php_Mapnik_Coord2D_entry) == SUCCESS) {
		GET_CPP_OBJECT_FROM_ZVAL(value, coord2d, Coord2D, passed_in_object);
		RETURN_BOOL(this_Envelope->intersects(*passed_in_object));
	} else if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "O", &value, php_Mapnik_Envelope_entry) == SUCCESS) {
		GET_CPP_OBJECT_FROM_ZVAL(value, Envelope<double>, Envelope, passed_in_object);
		RETURN_BOOL(this_Envelope->intersects(*passed_in_object));
	}

	php_error_docref(NULL TSRMLS_CC, E_WARNING, "Wrong arguments passed to intersects");

	RETURN_NULL();
}

// EnvelopeType intersect(const EnvelopeType& other) const;
PHP_METHOD(Envelope, intersect)
{
	zval* value;

	if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "O", &value, php_Mapnik_Envelope_entry) == SUCCESS) {
		GET_THIS_CPP_OBJECT(Envelope<double>, Envelope);
		GET_CPP_OBJECT_FROM_ZVAL(value, Envelope<double>, Envelope, passed_in_envelope);
	
		mapnik::Envelope<double> result_value = this_Envelope->intersect(*passed_in_envelope);

		BEGIN_RETURN_PHP_OBJECT(Envelope, 4)
			SETUP_ARGUMENT(0, DOUBLE, result_value.minx())
			SETUP_ARGUMENT(1, DOUBLE, result_value.miny())
			SETUP_ARGUMENT(2, DOUBLE, result_value.maxx())
			SETUP_ARGUMENT(3, DOUBLE, result_value.maxy())
		END_RETURN_PHP_OBJECT()

		return;
	}

	php_error_docref(NULL TSRMLS_CC, E_WARNING, "Wrong arguments passed to intersect");

	RETURN_NULL();
}


// void re_center(T cx,T cy);
PHP_METHOD(Envelope, reCenter)
{
	GET_THIS_CPP_OBJECT(Envelope<double>, Envelope);

	double x, y;

	if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "dd", &x, &y) == SUCCESS) {
		this_Envelope->re_center(x, y);
		return;
	}

	php_error_docref(NULL TSRMLS_CC, E_WARNING, "Wrong arguments passed to reCenter");

	RETURN_NULL();
}

// void init(T x0,T y0,T x1,T y1);
PHP_METHOD(Envelope, init)
{
	GET_THIS_CPP_OBJECT(Envelope<double>, Envelope);

	double minx, miny, maxx, maxy;

	if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "dddd", &minx, &miny, &maxx, &maxy) == SUCCESS) {
		this_Envelope->init(minx, miny, maxx, maxy);
		return;
	}

	php_error_docref(NULL TSRMLS_CC, E_WARNING, "Wrong arguments passed to init");

	RETURN_NULL();
}

static function_entry php_Mapnik_Envelope_methods[] = {
	PHP_ME(Envelope, __construct,	NULL,	ZEND_ACC_PUBLIC)
	// Getters and setters
	PHP_ME(Envelope, getMinX,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Envelope, getMinY,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Envelope, getMaxX,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Envelope, getMaxY,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Envelope, getWidth,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Envelope, getHeight,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Envelope, setWidth,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Envelope, setHeight,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Envelope, getCenter,		NULL,	ZEND_ACC_PUBLIC)
	// Operations
	PHP_ME(Envelope, expandToInclude,NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Envelope, contains,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Envelope, intersects,	NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Envelope, intersect,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Envelope, reCenter,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Envelope, init,			NULL,	ZEND_ACC_PUBLIC)

	{ NULL, NULL, NULL }
};

// vim:set noexpandtab: