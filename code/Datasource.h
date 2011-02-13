#include <mapnik/datasource.hpp>

DEFINE_CLASS(datasource, Datasource);

// datasource (parameters const& params)
PHP_METHOD(Datasource, __construct)
{
}

// parameters const& params() const
PHP_METHOD(Datasource, getParams)
{

}

// virtual int type() const=0;
PHP_METHOD(Datasource, getType)
{

}

// virtual featureset_ptr features(const query& q) const=0;
PHP_METHOD(Datasource, getFeatures)
{

}

// virtual featureset_ptr features_at_point(coord2d const& pt) const=0;
PHP_METHOD(Datasource, getFeaturesAtPoint)
{

}

// virtual Envelope<double> envelope() const=0;
PHP_METHOD(Datasource, getEnvelope)
{

}

// virtual layer_descriptor get_descriptor() const=0;
PHP_METHOD(Datasource, getDescriptor)
{
	
}

static function_entry php_Mapnik_Datasource_methods[] = {
	PHP_ME(Datasource, __construct,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Datasource, getParams,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Datasource, getType,				NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Datasource, getFeatures,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Datasource, getFeaturesAtPoint,	NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Datasource, getEnvelope,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Datasource, getDescriptor,		NULL,	ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};
