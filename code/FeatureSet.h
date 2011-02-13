#include <mapnik/feature.hpp>

DEFINE_CLASS(Featureset, Featureset);

PHP_METHOD(Featureset, __construct)
{
}

static function_entry php_Mapnik_Featureset_methods[] = {
	PHP_ME(Featureset, __construct,	NULL,	ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};
