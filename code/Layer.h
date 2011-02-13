#include <mapnik/Layer.hpp>

DEFINE_CLASS(Layer, Layer);

// explicit Layer(std::string const& name, std::string const& srs="+proj=latlong +datum=WGS84");
PHP_METHOD(Layer, __construct)
{
	mapnik::Layer* Layer = NULL;

	char* name = NULL;
	char* srs = NULL;
	int name_len, srs_len;

	if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &name, &name_len, &srs, &srs_len) == SUCCESS) {
		std::string name_str(name, name_len);
		if (srs != NULL) {
			std::string srs_str(srs, srs_len);
			Layer = PHP_NEW mapnik::Layer(name_str, srs_str);
		} else {
			Layer = PHP_NEW mapnik::Layer(name_str);
		}
	} else {
		// None of the supported parameter formats. Fail construction.
		zend_throw_exception(zend_exception_get_default(TSRMLS_C), "Wrong arguments passed to constructor", 0 TSRMLS_CC);
		RETURN_NULL();
	}

	assert(Layer);

	INIT_CPP_OBJECT(Layer);
}

// void set_datasource(datasource_ptr const& ds);
PHP_METHOD(Layer, setDatasource)
{
	GET_THIS_CPP_OBJECT(Layer, Layer);
	//GET_OBJECT_ARGUMENT(datasource, Datasource, datasource_argument, setDatasource);

	zval* value;
	// Need to fetch manually, because we need the shared_ptr from the DatasourceObject.
	if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "O", &value, php_Mapnik_Datasource_entry) == FAILURE) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Wrong arguments passed to setDatasource");
		RETURN_NULL();
	}

	DatasourceObject* Datasource_object = (DatasourceObject*)zend_object_store_get_object(value TSRMLS_CC);
		
	assert(Datasource_object->Datasource_shared_ptr != NULL);
	this_Layer->set_datasource(Datasource_object->Datasource_shared_ptr);
}

// void add_style(std::string const& stylename);
PHP_METHOD(Layer, addStyle)
{
	GET_THIS_CPP_OBJECT(Layer, Layer);

	char* zstring;
	int string_len;

	if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "s", &zstring, &string_len) == FAILURE) {
		// None of the supported parameter formats.
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Wrong arguments passed to addStyle");
		RETURN_FALSE;
	}

	std::string style_name(zstring, string_len);

	this_Layer->add_style(style_name);
}

static function_entry php_Mapnik_Layer_methods[] = {
	PHP_ME(Layer, __construct,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Layer, setDatasource,	NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Layer, addStyle,			NULL,	ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

/*
    explicit Layer(std::string const& name, std::string const& srs="+proj=latlong +datum=WGS84");
    void set_name(std::string const& name);
    const std::string& name() const;
    void set_title(std::string const& title);
    const std::string& title() const;
    void set_abstract(std::string const& abstract);
    const std::string& abstract() const;
    void set_srs(std::string const& srs);
    std::string const& srs() const;
    void add_style(std::string const& stylename);
    std::vector<std::string> const& styles() const;
    std::vector<std::string>& styles();
    void setMinZoom(double minZoom);
    void setMaxZoom(double maxZoom);
    double getMinZoom() const;
    double getMaxZoom() const;
    void setActive(bool active);
    bool isActive() const;
    void setQueryable(bool queryable);
    bool isQueryable() const;
    bool isVisible(double scale) const;
    void set_clear_label_cache(bool clear_cache);
    bool clear_label_cache() const; 
    void set_datasource(datasource_ptr const& ds);
    datasource_ptr datasource() const;
    Envelope<double> envelope() const;
*/
