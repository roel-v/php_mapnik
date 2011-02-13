#include <mapnik/params.hpp>

DEFINE_CLASS(parameters, Parameters);

PHP_METHOD(Parameters, __construct)
{
	mapnik::parameters* Parameters = PHP_NEW mapnik::parameters();
	INIT_CPP_OBJECT(Parameters);
}

//boost::optional<T> get(std::string const& key) const
PHP_METHOD(Parameters, get)
{
	GET_THIS_CPP_OBJECT(parameters, Parameters);

	char* parameter_name;
	int parameter_name_length;

	if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "s", &parameter_name, &parameter_name_length) == SUCCESS) {
		std::string param_name(parameter_name, parameter_name_length);
		boost::optional<std::string> result = this_Parameters->get<std::string>(param_name);
		if (result == NULL) {
			RETURN_NULL();	
		} else {
			RETURN_STRING(result->c_str(), 1);
		}
	}

	php_error_docref(NULL TSRMLS_CC, E_WARNING, "Wrong arguments passed to get");

	RETURN_NULL();
}

PHP_METHOD(Parameters, set)
{
	GET_THIS_CPP_OBJECT(parameters, Parameters);

	char* parameter_name;
	int parameter_name_length;
	double d;
	char* string;
	int string_len;

	if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "ss", &parameter_name, &parameter_name_length, &string, &string_len) == SUCCESS) {
		std::string param_name(parameter_name, parameter_name_length);
		(*this_Parameters)[param_name] = string;
		return;
	} else if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "sd", &parameter_name, &parameter_name_length, &d) == SUCCESS) {
		std::string param_name(parameter_name, parameter_name_length);
		(*this_Parameters)[param_name] = d;
		return;
	}

	php_error_docref(NULL TSRMLS_CC, E_WARNING, "Wrong arguments passed to set");

	RETURN_NULL();
}

static function_entry php_Mapnik_Parameters_methods[] = {
	PHP_ME(Parameters, __construct,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Parameters, set,					NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Parameters, get,					NULL,	ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};
         //boost::optional<T> get(std::string const& key) const
         //boost::optional<T> get(std::string const& key, T const& default_value) const

// vim:set noexpandtab:
