#include <mapnik\image_util.hpp>

/*
   inline MAPNIK_DECL void save_to_file (Image32 const& image,
                                         std::string const& file,
                                         std::string const& type) 
   inline MAPNIK_DECL void save_to_file(Image32 const& image,
                                        std::string const& file) 
 */
PHP_FUNCTION(save_to_file)
{
	zval* image32_zval;
	char* file = NULL;
	char* type = NULL;
	int file_len, type_len;

	if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "Os|s",
				&image32_zval, php_Mapnik_Image32_entry, &file, &file_len, &type, &type_len) == SUCCESS) {
		GET_CPP_OBJECT_FROM_ZVAL(image32_zval, Image32, Image32, image32_argument);
		std::string file_str(file, file_len);
		if (type == NULL){
			mapnik::save_to_file(*image32_argument, file_str);
		} else {
			std::string type_str(type, type_len);
			mapnik::save_to_file(*image32_argument, file_str, type_str);
		}
	} else {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Wrong arguments passed to save_to_file");
		RETURN_NULL();
	}

	RETURN_TRUE;
}

static function_entry php_mapnik_functions[] = {
	ZEND_NS_FENTRY("Mapnik", save_to_file, ZEND_FN(save_to_file), NULL, 0)
	{ NULL, NULL, NULL }
};