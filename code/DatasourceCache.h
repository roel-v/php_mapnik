#include <mapnik/datasource_cache.hpp>

//DEFINE_CLASS(datasource_cache);	Can't be instantiated

PHP_METHOD(DatasourceCache, __construct)
{
	zend_throw_exception(zend_exception_get_default(TSRMLS_C), "DatasourceCache cannot be instantiated", 0 TSRMLS_CC);

	RETURN_NULL();	// No public constructor.
}

// static void register_datasources(const std::string& path);
PHP_METHOD(DatasourceCache, registerDatasources)
{
	char* datasources_directory = NULL;
	int datasources_directory_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &datasources_directory, &datasources_directory_len) == FAILURE) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Wrong arguments passed to registerDatasources");
		RETURN_FALSE;
	}

	mapnik::datasource_cache::instance()->register_datasources(datasources_directory); 

	RETURN_TRUE;
}

// static std::vector<std::string> plugin_names ();
PHP_METHOD(DatasourceCache, getPluginNames)
{
	std::vector<std::string> all_plugin_names = mapnik::datasource_cache::instance()->plugin_names(); 

	array_init(return_value);

	BOOST_FOREACH (std::string plugin, all_plugin_names) {
		add_next_index_string(return_value, plugin.c_str(), 1);
	}
}

// static boost::shared_ptr<datasource> create(parameters const& params);
PHP_METHOD(DatasourceCache, create)
{
	zval* value;

	if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "O", &value, php_Mapnik_Parameters_entry) == FAILURE) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Wrong arguments passed to DatasourceCache::create");
		RETURN_NULL();
	}
	GET_CPP_OBJECT_FROM_ZVAL(value, parameters, Parameters, passed_in_object);

	BEGIN_RETURN_PHP_OBJECT(Datasource, 0)
	END_RETURN_PHP_OBJECT()

	DatasourceObject* obj = (DatasourceObject*)zend_object_store_get_object(return_value TSRMLS_CC);

	std::string error_msg = "Error in DatasourceCache::create:: ";
	try {
		obj->Datasource_shared_ptr = mapnik::datasource_cache::instance()->create(*passed_in_object);
	}
	catch (const mapnik::config_error& e) {
		error_msg += e.what();
		php_error_docref(NULL TSRMLS_CC, E_WARNING, error_msg.c_str());
		RETURN_NULL();
	}
	catch (const std::runtime_error& e) {
		error_msg += e.what();
		php_error_docref(NULL TSRMLS_CC, E_WARNING, error_msg.c_str());
		RETURN_NULL();
	}
}

zend_class_entry* php_Mapnik_DatasourceCache_entry = NULL;
static function_entry php_Mapnik_DatasourceCache_methods[] = {
	PHP_ME(DatasourceCache, __construct,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(DatasourceCache, registerDatasources,	NULL,	ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(DatasourceCache, getPluginNames,			NULL,	ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(DatasourceCache, create,		NULL,	ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	{ NULL, NULL, NULL }
};