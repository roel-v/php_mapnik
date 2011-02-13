#include <mapnik/map.hpp>

DEFINE_CLASS(Map, Map);

/*
    Map();
    Map(int width, int height, std::string const& srs="+proj=latlong +datum=WGS84");
 */
PHP_METHOD(Map, __construct)
{
	mapnik::Map* Map = NULL;
	long width, height;
	char* zstring;
	int string_len;

	if (ZEND_NUM_ARGS() == 0) {
		Map = PHP_NEW mapnik::Map();
	} else if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "ll", &width, &height) == SUCCESS) {
		Map = PHP_NEW mapnik::Map(width, height);
	} else if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "lls", &width, &height, &zstring, &string_len) == SUCCESS) {
		Map = PHP_NEW mapnik::Map(width, height, zstring);
	} else {
		zend_throw_exception(zend_exception_get_default(TSRMLS_C), "Wrong arguments passed to constructor", 0 TSRMLS_CC);
		RETURN_FALSE;
	}

	assert(Map != NULL);

	INIT_CPP_OBJECT(Map);
}

// Returns an array of all style names
// std::map<std::string,feature_type_style> & styles();
PHP_METHOD(Map, getStyleNames)
{
	array_init(return_value);

	GET_THIS_CPP_OBJECT(Map, Map);

	typedef std::pair<std::string, mapnik::feature_type_style> TStyleInfo;
	std::map<std::string, mapnik::feature_type_style>& styles = this_Map->styles();

	BOOST_FOREACH (TStyleInfo style, styles) {
		add_next_index_stringl(return_value, style.first.c_str(), style.first.size(), 1); // 1: duplicate the string
	}
}

// Get a style by name
PHP_METHOD(Map, getStyle)
{
	GET_THIS_CPP_OBJECT(Map, Map);

	//std::map<std::string,feature_type_style> & styles();
	//boost::optional<feature_type_style const&> find_style(std::string const& name) const;
}

// Adds a style
// bool insert_style(std::string const& name,feature_type_style const& style);
PHP_METHOD(Map, addStyle)
{
	GET_THIS_CPP_OBJECT(Map, Map);
		
	char* name;
	int name_len;
	zval* feature_style_zval;

	if (::zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sO", &name, &name_len, &feature_style_zval, php_Mapnik_FeatureStyle_entry) == SUCCESS) {
		std::string name_str(name, name_len);
		GET_CPP_OBJECT_FROM_ZVAL(feature_style_zval, feature_type_style, FeatureStyle, feature_style_argument);
		this_Map->insert_style(name_str, *feature_style_argument);
		RETURN_TRUE;
	} else {
		zend_throw_exception(zend_exception_get_default(TSRMLS_C), "Wrong arguments passed to constructor", 0 TSRMLS_CC);
		RETURN_FALSE;
	}

	RETURN_TRUE;	
}

// Removes a style
PHP_METHOD(Map, removeStyle)
{
	GET_THIS_CPP_OBJECT(Map, Map);
	//std::map<std::string,feature_type_style> & styles();
	//void remove_style(const std::string& name);
}

PHP_METHOD(Map, removeAllStyles)
{
	GET_THIS_CPP_OBJECT(Map, Map);
	//void remove_style(const std::string& name);
}

PHP_METHOD(Map, getFontSetNames)
{
	GET_THIS_CPP_OBJECT(Map, Map);
	//std::map<std::string,FontSet> const& fontsets() const;
}

PHP_METHOD(Map, getFontSet)
{
	GET_THIS_CPP_OBJECT(Map, Map);
	//FontSet const& find_fontset(std::string const& name) const;
	//std::map<std::string,FontSet> const& fontsets() const;
}

PHP_METHOD(Map, addFontSet)
{
	GET_THIS_CPP_OBJECT(Map, Map);
	//bool insert_fontset(std::string const& name, FontSet const& fontset);
}

// size_t layerCount() const;
PHP_METHOD(Map, getLayerCount)
{
	GET_THIS_CPP_OBJECT(Map, Map);

	RETURN_LONG(this_Map->layerCount());
}

PHP_METHOD(Map, getLayer)
{
	GET_THIS_CPP_OBJECT(Map, Map);
	//const Layer& getLayer(size_t index) const;
}

// void addLayer(const Layer& l);
PHP_METHOD(Map, addLayer)
{
	GET_THIS_CPP_OBJECT(Map, Map);

	zval* layer_zval;

	if (::zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &layer_zval, php_Mapnik_Layer_entry) == SUCCESS) {
		GET_CPP_OBJECT_FROM_ZVAL(layer_zval, Layer, Layer, passed_in_layer);
		this_Map->addLayer(*passed_in_layer);
		RETURN_TRUE;
	} else {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Wrong arguments passed to expandToInclude");
		RETURN_NULL();
	}
}

PHP_METHOD(Map, removeLayer)
{
	GET_THIS_CPP_OBJECT(Map, Map);
	//void removeLayer(size_t index);
}

PHP_METHOD(Map, removeAllLayers)
{
	GET_THIS_CPP_OBJECT(Map, Map);
	//void remove_all();
}

PHP_METHOD(Map, resize)
{
	GET_THIS_CPP_OBJECT(Map, Map);
	//void resize(unsigned width,unsigned height);
}

PHP_METHOD(Map, queryPoint)
{
	GET_THIS_CPP_OBJECT(Map, Map);
	//featureset_ptr query_point(unsigned index, double x, double y) const;
}

PHP_METHOD(Map, queryMapPoint)
{
	GET_THIS_CPP_OBJECT(Map, Map);
	//featureset_ptr query_map_point(unsigned index, double x, double y) const;
}

// double scale() const;
PHP_METHOD(Map, getScale)
{
	GET_THIS_CPP_OBJECT(Map, Map);
	RETURN_DOUBLE(this_Map->scale());
}

// double scale_denominator() const;
PHP_METHOD(Map, getScaleDenominator)
{
	GET_THIS_CPP_OBJECT(Map, Map);
	RETURN_DOUBLE(this_Map->scale_denominator());
}

PHP_METHOD(Map, getViewTransform)
{
	GET_THIS_CPP_OBJECT(Map, Map);
	//CoordTransform view_transform() const;
}

	//PHP_ME(Map, getCurrentExtent,	NULL,	ZEND_ACC_PUBLIC)
	//PHP_ME(Map, getBufferedExtent,	NULL,	ZEND_ACC_PUBLIC)
    //    const Envelope<double>& getCurrentExtent() const;
    //    Envelope<double> get_buffered_extent() const;

PHP_METHOD(Map, zoom)
{
	GET_THIS_CPP_OBJECT(Map, Map);
	//void zoom(double factor);
}

// void zoomToBox(const Envelope<double>& box);
PHP_METHOD(Map, zoomToBox)
{
	GET_THIS_CPP_OBJECT(Map, Map);
	GET_OBJECT_ARGUMENT(Envelope<double>, Envelope, envelope_argument, zoomToBox);

	this_Map->zoomToBox(*envelope_argument);
}

// void zoom_all();
PHP_METHOD(Map, zoomAll)
{
	GET_THIS_CPP_OBJECT(Map, Map);
	this_Map->zoom_all();
}

PHP_METHOD(Map, pan)
{
	GET_THIS_CPP_OBJECT(Map, Map);
	//void pan(int x,int y);
}

PHP_METHOD(Map, panAndZoom)
{
	GET_THIS_CPP_OBJECT(Map, Map);
	//void pan_and_zoom(int x,int y,double zoom);
}

IMPLEMENT_LONG_GETTER(getWidth, getWidth, Map, Map)
IMPLEMENT_LONG_GETTER(getHeight, getHeight, Map, Map)
IMPLEMENT_STRING_GETTER(srs, getSrs, Map, Map)
IMPLEMENT_LONG_GETTER(buffer_size, getBufferSize, Map, Map)

//BEGIN_IMPLEMENT_OBJECT_GETTER(background, getBackgroundColor, Map, Map, color, Color, 4)
// Implement manually because background() returns boost::optional
PHP_METHOD(Map, getBackgroundColor)
{
	GET_THIS_CPP_OBJECT(Map, Map);
	boost::optional<mapnik::color> Color = this_Map->background();
	if (Color == NULL) {
		RETURN_NULL();
	}

	BEGIN_RETURN_PHP_OBJECT(Color, 4)
		SETUP_ARGUMENT(0, DOUBLE, Color->red())
		SETUP_ARGUMENT(1, DOUBLE, Color->green())
		SETUP_ARGUMENT(2, DOUBLE, Color->blue())
		SETUP_ARGUMENT(3, DOUBLE, Color->alpha())
	END_RETURN_PHP_OBJECT()
}

IMPLEMENT_SETTER(setWidth, setWidth, Map, Map, unsigned, l)
IMPLEMENT_SETTER(setHeight, setHeight, Map, Map, unsigned, l)
IMPLEMENT_STRING_SETTER(set_srs, setSrs, Map, Map)
IMPLEMENT_SETTER(set_buffer_size, setBufferSize, Map, Map, int, l)
IMPLEMENT_OBJECT_SETTER(set_background, setBackgroundColor, Map, Map, color, Color);

/*
PHP_METHOD(Map, getBackgroundColor)
{
	GET_THIS_CPP_OBJECT(cpp_class_name, php_class_name);				\
	mapnik::retval_cpp_class_name* = &this_##php_class_name->cpp_getter_name();	\
	return_value = ;
	RETURN_ZVAL(, 0, 0);
}

PHP_METHOD(Map, setBackgroundColor)
{
	zval* value;												\
	if (::zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &value, php_class_name##_ce, &value_len) == FAILURE) {	\
		RETURN_FALSE;											\
	}															\
	GET_NAMED_CPP_OBJECT(cpp_class_name, php_class_name, passed_in_object)	\
	GET_THIS_CPP_OBJECT(cpp_class_name, php_class_name);				\
	this_##php_class_name->cpp_setter_name(passed_in_object);	\

}
*/
	/*
	PHP_ME(Map, getAspectFixMode,	NULL,	ZEND_ACC_PUBLIC)
        inline aspect_fix_mode getAspectFixMode() const { return aspectFixMode_; }

	PHP_ME(Map, setAspectFixMode,	NULL,	ZEND_ACC_PUBLIC)
        inline void setAspectFixMode(aspect_fix_mode afm) { aspectFixMode_ = afm; }
		*/

static function_entry php_Mapnik_Map_methods[] = {
	PHP_ME(Map, __construct,	NULL,	ZEND_ACC_PUBLIC)

	// Simple properties
	PHP_ME(Map, getWidth,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, setWidth,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, getHeight,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, setHeight,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, getSrs,				NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, setSrs,				NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, setBufferSize,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, getBufferSize,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, getBackgroundColor,	NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, setBackgroundColor,	NULL,	ZEND_ACC_PUBLIC)
	//PHP_ME(Map, getAspectFixMode,	NULL,	ZEND_ACC_PUBLIC)
	//PHP_ME(Map, setAspectFixMode,	NULL,	ZEND_ACC_PUBLIC)

	// Style operations - styles are referenced by name
	PHP_ME(Map, getStyleNames,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, getStyle,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, addStyle,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, removeStyle,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, removeAllStyles,	NULL,	ZEND_ACC_PUBLIC)

	// FontSet operations - fontsets are referenced by name
	PHP_ME(Map, getFontSetNames,	NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, getFontSet,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, addFontSet,			NULL,	ZEND_ACC_PUBLIC)
	//PHP_ME(Map, removeFontSet,		NULL,	ZEND_ACC_PUBLIC)
	//PHP_ME(Map, removeAllFontSet,		NULL,	ZEND_ACC_PUBLIC)

	// Layer operations - layers are referenced by index
	PHP_ME(Map, getLayerCount,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, getLayer,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, addLayer,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, removeLayer,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, removeAllLayers,	NULL,	ZEND_ACC_PUBLIC)

	// Various operations
	PHP_ME(Map, resize,				NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, queryPoint,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, queryMapPoint,		NULL,	ZEND_ACC_PUBLIC)

	// Various properties
	PHP_ME(Map, getScale,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, getScaleDenominator,	NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, getViewTransform,	NULL,	ZEND_ACC_PUBLIC)
	//PHP_ME(Map, getCurrentExtent,	NULL,	ZEND_ACC_PUBLIC)
	//PHP_ME(Map, getBufferedExtent,	NULL,	ZEND_ACC_PUBLIC)

	// Zoom operations
	PHP_ME(Map, zoom,				NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, zoomToBox,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, zoomAll,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, pan,				NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Map, panAndZoom,			NULL,	ZEND_ACC_PUBLIC)

	{ NULL, NULL, NULL }
};
