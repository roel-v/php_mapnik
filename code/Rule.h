#include <mapnik/rule.hpp>

DEFINE_CLASS(rule_type, Rule);

/*
   rule()
   rule(const std::string& name,
	   const std::string& title="",
	   double min_scale_denominator=0,
	   double max_scale_denominator=std::numeric_limits<double>::infinity())
 */
PHP_METHOD(Rule, __construct)
{
	mapnik::rule_type* Rule = NULL;

	char* str1 = NULL;
	char* str2 = NULL;
	int str1_len = -1;
	int str2_len = -1;
	double d1 = 0;
	double d2 = std::numeric_limits<double>::infinity();

	if (ZEND_NUM_ARGS() == 0) {
		Rule = PHP_NEW mapnik::rule_type();
	} else if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC,
								"s|sdd", &str1, &str1_len, &str2, &str2_len, &d1, &d2) == SUCCESS) {
		std::string name(str1, str1_len);
		if (str2 != NULL) {
			std::string title(str2, str2_len);
			Rule = PHP_NEW mapnik::rule_type(name, title, d1, d2);
		} else {
			Rule = PHP_NEW mapnik::rule_type(name);
		}
	} else {
		// None of the supported parameter formats. Fail construction.
		zend_throw_exception(zend_exception_get_default(TSRMLS_C), "Wrong arguments passed to constructor", 0 TSRMLS_CC);
		RETURN_NULL();
	}

	assert(Rule);

	INIT_CPP_OBJECT(Rule);
}

//void append(const symbolizer& sym)
/*
Can be either of these classes:
   typedef boost::variant<point_symbolizer,
                          line_symbolizer,
                          line_pattern_symbolizer,
                          polygon_symbolizer,
                          polygon_pattern_symbolizer,
                          raster_symbolizer,
                          shield_symbolizer,
                          text_symbolizer,
                          building_symbolizer,
                          markers_symbolizer> symbolizer;
 */
PHP_METHOD(Rule, append)
{
	GET_THIS_CPP_OBJECT(rule_type, Rule);

	zval* parameter_zval;

	// @todo add other symbolizers
	if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC,
								"O", &parameter_zval, php_Mapnik_TextSymbolizer_entry) == SUCCESS) {
		GET_CPP_OBJECT_FROM_ZVAL(parameter_zval, text_symbolizer, TextSymbolizer, param_symbolizer);
		this_Rule->append(*param_symbolizer);
		RETURN_TRUE;
	} else if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC,
								"O", &parameter_zval, php_Mapnik_PolygonSymbolizer_entry) == SUCCESS) {
		GET_CPP_OBJECT_FROM_ZVAL(parameter_zval, polygon_symbolizer, PolygonSymbolizer, param_symbolizer);
		this_Rule->append(*param_symbolizer);
		RETURN_TRUE;
	} else {
		// None of the supported parameter formats. Fail construction.
		zend_throw_exception(zend_exception_get_default(TSRMLS_C), "Wrong arguments passed to append", 0 TSRMLS_CC);
		RETURN_NULL();
	}
}

//void remove_at(size_t index)
PHP_METHOD(Rule, removeAt)
{
	GET_THIS_CPP_OBJECT(rule_type, Rule);

	int index;

	if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "d", &index) == SUCCESS) {
		this_Rule->remove_at(index);
	} else {
		// None of the supported parameter formats. Fail construction.
		zend_throw_exception(zend_exception_get_default(TSRMLS_C), "Wrong arguments passed to constructor", 0 TSRMLS_CC);
		RETURN_NULL();
	}
}

//const symbolizers& get_symbolizers() const
PHP_METHOD(Rule, getSymbolizers)
{
	GET_THIS_CPP_OBJECT(rule_type, Rule);
}

//void set_filter(const filter_ptr& filter)
PHP_METHOD(Rule, setFilter)
{
	GET_THIS_CPP_OBJECT(rule_type, Rule);
}

//filter_ptr const& get_filter() const
PHP_METHOD(Rule, getFilter)
{
	GET_THIS_CPP_OBJECT(rule_type, Rule);
}

//void set_else(bool else_filter)
PHP_METHOD(Rule, setElse)
{
	GET_THIS_CPP_OBJECT(rule_type, Rule);
}

//bool has_else_filter() const
PHP_METHOD(Rule, hasElseFilter)
{
	GET_THIS_CPP_OBJECT(rule_type, Rule);
}

//bool active(double scale) const
PHP_METHOD(Rule, active)
{
	GET_THIS_CPP_OBJECT(rule_type, Rule);
}

IMPLEMENT_DOUBLE_SETTER(set_max_scale,	setMaxScale,	rule_type, Rule)
IMPLEMENT_DOUBLE_SETTER(set_min_scale,	setMinScale,	rule_type, Rule)
IMPLEMENT_STRING_SETTER(set_name,		setName,		rule_type, Rule)
IMPLEMENT_STRING_SETTER(set_title,		setTitle,		rule_type, Rule)
IMPLEMENT_STRING_SETTER(set_abstract,	setAbstract,	rule_type, Rule)

IMPLEMENT_DOUBLE_GETTER(get_max_scale,	getMaxScale,	rule_type, Rule)
IMPLEMENT_DOUBLE_GETTER(get_min_scale,	getMinScale,	rule_type, Rule)
IMPLEMENT_STRING_GETTER(get_name,		getName,		rule_type, Rule)
IMPLEMENT_STRING_GETTER(get_title,		getTitle,		rule_type, Rule)
IMPLEMENT_STRING_GETTER(get_abstract,	getAbstract,	rule_type, Rule)

static function_entry php_Mapnik_Rule_methods[] = {
	PHP_ME(Rule, __construct,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Rule, setMaxScale,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Rule, getMaxScale,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Rule, setMinScale,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Rule, getMinScale,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Rule, setName,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Rule, getName,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Rule, setTitle,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Rule, getTitle,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Rule, setAbstract,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Rule, getAbstract,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Rule, append,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Rule, removeAt,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Rule, getSymbolizers,	NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Rule, setFilter,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Rule, getFilter,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Rule, setElse,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Rule, hasElseFilter,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Rule, active,			NULL,	ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};
