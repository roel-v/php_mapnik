#include <mapnik/feature_type_style.hpp>

DEFINE_CLASS(feature_type_style, FeatureStyle);

PHP_METHOD(FeatureStyle, __construct)
{
	mapnik::feature_type_style* FeatureStyle = PHP_NEW mapnik::feature_type_style();

	INIT_CPP_OBJECT(FeatureStyle);
}

// void add_rule(rule_type const& rule)
PHP_METHOD(FeatureStyle, addRule)
{
	GET_THIS_CPP_OBJECT(feature_type_style, FeatureStyle);

	GET_OBJECT_ARGUMENT(rule_type, Rule, passed_in_object, addRule);

	this_FeatureStyle->add_rule(*passed_in_object);

	RETURN_TRUE;
}

// rules const& get_rules() const
PHP_METHOD(FeatureStyle, getRules)
{
	GET_THIS_CPP_OBJECT(feature_type_style, FeatureStyle);
	// @todo
}

static function_entry php_Mapnik_FeatureStyle_methods[] = {
	PHP_ME(FeatureStyle, __construct,	NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(FeatureStyle, addRule,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(FeatureStyle, getRules,		NULL,	ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};
