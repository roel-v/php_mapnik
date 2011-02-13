#include <mapnik/query.hpp>

DEFINE_CLASS(query, Query);

// explicit query(const Envelope<double>& bbox, double resolution, double scale_denominator)
// explicit query(const Envelope<double>& bbox, double resolution)
PHP_METHOD(Query, __construct)
{
	mapnik::query* Query = NULL;

	zval* envelope_arg;
	double res, scale_denom;

	if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "Od", &envelope_arg, &res) == SUCCESS) {
		GET_CPP_OBJECT_FROM_ZVAL(envelope_arg, Envelope<double>, Envelope, envelope_ptr);
		Query = PHP_NEW mapnik::query(*envelope_ptr, res);
	} else if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "Odd", &envelope_arg, &res, &scale_denom) == SUCCESS) {
		GET_CPP_OBJECT_FROM_ZVAL(envelope_arg, Envelope<double>, Envelope, envelope_ptr);
		Query = PHP_NEW mapnik::query(*envelope_ptr, res, scale_denom);
	} else {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Wrong arguments passed to Query constructor");
		RETURN_NULL();
	}
	
	assert(Query != NULL);

	INIT_CPP_OBJECT(Query);
}

// const Envelope<double>& get_bbox() const
PHP_METHOD(Query, getBoundingBox)
{
	GET_THIS_CPP_OBJECT(query, Query);

	const mapnik::Envelope<double>& bbox = this_Query->get_bbox();

	BEGIN_RETURN_PHP_OBJECT(Envelope, 4)
		SETUP_ARGUMENT(0, DOUBLE, bbox.minx())
		SETUP_ARGUMENT(1, DOUBLE, bbox.miny())
		SETUP_ARGUMENT(2, DOUBLE, bbox.maxx())
		SETUP_ARGUMENT(3, DOUBLE, bbox.maxy())
	END_RETURN_PHP_OBJECT()
}

// void add_property_name(const std::string& name)
PHP_METHOD(Query, addPropertyName)
{
	char* property_name = NULL;
	int property_name_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &property_name, &property_name_len) == FAILURE) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Wrong argument passed to addPropertyName");
		RETURN_FALSE;
	}
	std::string prop_name(property_name, property_name_len);

	GET_THIS_CPP_OBJECT(query, Query);
	
	this_Query->add_property_name(prop_name);
}

// const std::set<std::string>& property_names() const
PHP_METHOD(Query, getPropertyNames)
{
	GET_THIS_CPP_OBJECT(query, Query);

	const std::set<std::string>& property_names = this_Query->property_names();

	array_init(return_value);
	BOOST_FOREACH (std::string str, property_names) {
		add_next_index_string(return_value, str.c_str(), 1);
	}
}

IMPLEMENT_DOUBLE_GETTER(resolution, getResolution, query, Query);
IMPLEMENT_DOUBLE_GETTER(scale_denominator, getScaleDenominator, query, Query);

static function_entry php_Mapnik_Query_methods[] = {
	PHP_ME(Query, __construct,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Query, getResolution,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Query, getScaleDenominator,	NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Query, getBoundingBox,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Query, addPropertyName,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Query, getPropertyNames,		NULL,	ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};
