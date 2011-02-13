#include <mapnik/color.hpp>

DEFINE_CLASS(color, Color);

PHP_METHOD(Color, __construct)
{
	mapnik::color* Color = NULL;

	// Figure out which constructor to call.
	// mapnik::color has three:
	// - no arguments, initialize everything to 0xff (done in C++ constructor)
	// - 3 or 4 numeric parameters, use as RGB(A) components
	// - 1 string: interpret as css color

	long red, green, blue, alpha;
	char* zstring;
	int string_len;

	if (ZEND_NUM_ARGS() == 0) {
		Color = PHP_NEW mapnik::color();
	} else if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "lll", &red, &green, &blue) == SUCCESS) {
		Color = PHP_NEW mapnik::color(red, green, blue);
	} else if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "llll", &red, &green, &blue, &alpha) == SUCCESS) {
		Color = PHP_NEW mapnik::color(red, green, blue, alpha);
	} else if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "s", &zstring, &string_len) == SUCCESS) {
		Color = PHP_NEW mapnik::color(zstring);
	} else {
		// None of the supported parameter formats. Fail construction.
		zend_throw_exception(zend_exception_get_default(TSRMLS_C), "Wrong arguments passed to constructor", 0 TSRMLS_CC);
		RETURN_FALSE;
	}

	assert(Color != NULL);

	INIT_CPP_OBJECT(Color);
}

IMPLEMENT_LONG_GETTER(red, getRed, color, Color);
IMPLEMENT_LONG_GETTER(green, getGreen, color, Color);
IMPLEMENT_LONG_GETTER(blue, getBlue, color, Color);
IMPLEMENT_LONG_GETTER(alpha, getAlpha, color, Color);

IMPLEMENT_LONG_SETTER(set_red, setRed, color, Color);
IMPLEMENT_LONG_SETTER(set_green, setGreen, color, Color);
IMPLEMENT_LONG_SETTER(set_blue, setBlue, color, Color);
IMPLEMENT_LONG_SETTER(set_alpha, setAlpha, color, Color);

PHP_METHOD(Color, rgba)
{
	GET_THIS_CPP_OBJECT(color, Color);
	//rgba() const
	RETURN_LONG(this_Color->rgba());
}

PHP_METHOD(Color, __toString)
{
	GET_THIS_CPP_OBJECT(color, Color);
	//std::string to_string() const;
	std::string tmp = this_Color->to_string();
	RETURN_STRING(tmp.c_str(), tmp.size());
}

PHP_METHOD(Color, toHexString)
{
	GET_THIS_CPP_OBJECT(color, Color);
	//std::string to_hex_string() const;
	std::string tmp = this_Color->to_hex_string();
	RETURN_STRING(tmp.c_str(), tmp.size());
}

static function_entry php_Mapnik_Color_methods[] = {
	PHP_ME(Color, __construct,	NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Color, __toString,	NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Color, getRed,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Color, getGreen,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Color, getBlue,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Color, getAlpha,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Color, setRed,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Color, setGreen,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Color, setBlue,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Color, setAlpha,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Color, rgba,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Color, toHexString,	NULL,	ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};
