#include <mapnik/font_engine_freetype.hpp>

DEFINE_CLASS(freetype_engine, FreetypeEngine);

PHP_METHOD(FreetypeEngine, __construct)
{
	RETURN_NULL();	// No public constructor.
}

// static bool register_font(std::string const& file_name);
PHP_METHOD(FreetypeEngine, registerFont)
{
	char* font_path = NULL;
	int font_path_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &font_path, &font_path_len) == FAILURE) {
		RETURN_FALSE;
	}

	mapnik::freetype_engine::register_font(font_path);

	RETURN_TRUE;
}

// static std::vector<std::string> face_names ();
PHP_METHOD(FreetypeEngine, getFaceNames)
{
	array_init(return_value);
	std::vector<std::string> face_names = mapnik::freetype_engine::face_names();
	BOOST_FOREACH (std::string face_name, face_names) {
		add_next_index_string(return_value, face_name.c_str(), 1);
	}
}

// face_ptr create_face(std::string const& family_name);
PHP_METHOD(FreetypeEngine, createFace)
{
	// @todo
}

static function_entry php_Mapnik_FreetypeEngine_methods[] = {
	PHP_ME(FreetypeEngine, __construct,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(FreetypeEngine, registerFont,	NULL,	ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(FreetypeEngine, getFaceNames,	NULL,	ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(FreetypeEngine, createFace,		NULL,	ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};
