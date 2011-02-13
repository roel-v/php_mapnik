#include <mapnik/text_symbolizer.hpp>

DEFINE_CLASS(text_symbolizer, TextSymbolizer);

// text_symbolizer(std::string const& name,std::string const& face_name, unsigned size, color const& fill);
/*
ZEND_BEGIN_ARG_INFO_EX(TextSymbolizer_construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 4)
	ZEND_ARG_INFO		(ZEND_SEND_BY_VAL, name)
	ZEND_ARG_INFO		(ZEND_SEND_BY_VAL, font_face_name)
	ZEND_ARG_INFO		(ZEND_SEND_BY_VAL, size)
	ZEND_ARG_OBJ_INFO	(ZEND_SEND_BY_VAL, color, Color, ZEND_DONT_ALLOW_NULL)
ZEND_END_ARG_INFO()
*/

/*
 text_symbolizer(std::string const& name,std::string const& face_name, unsigned size, color const& fill);
 text_symbolizer(std::string const& name, unsigned size, color const& fill);
 */
PHP_METHOD(TextSymbolizer, __construct)
{
	mapnik::text_symbolizer* TextSymbolizer = NULL;

	char* str1 = NULL;
	char* str2 = NULL;
	int str1_len = -1;
	int str2_len = -1;
	long l1;
	zval* zval_param;

	if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC,
						"sslO", &str1, &str1_len, &str2, &str2_len, &l1, &zval_param, php_Mapnik_Color_entry) == SUCCESS) {
		std::string name(str1, str1_len);
		std::string font_face(str2, str2_len);
		GET_CPP_OBJECT_FROM_ZVAL(zval_param, color, Color, color_parameter);
		TextSymbolizer = PHP_NEW mapnik::text_symbolizer(name, font_face, l1, *color_parameter);
	} else if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC,
						"slO", &str1, &str1_len, &l1, &zval_param, php_Mapnik_Color_entry) == SUCCESS) {
		std::string name(str1, str1_len);
		GET_CPP_OBJECT_FROM_ZVAL(zval_param, color, Color, color_parameter);
		TextSymbolizer = PHP_NEW mapnik::text_symbolizer(name, l1, *color_parameter);
	} else {
		// None of the supported parameter formats. Fail construction.
		zend_throw_exception(zend_exception_get_default(TSRMLS_C), "Wrong arguments passed to constructor", 0 TSRMLS_CC);
		RETURN_NULL();
	}

	assert(TextSymbolizer);

	INIT_CPP_OBJECT(TextSymbolizer);
}

/*
ZEND_BEGIN_ARG_INFO_EX(setHaloFill_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_OBJ_INFO(ZEND_SEND_BY_VAL, color, Color, 0)
ZEND_END_ARG_INFO()
*/

/*
PHP_METHOD(TextSymbolizer, setHaloFill)
{
	zval* value;
	if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "O", &value, php_Mapnik_Color_entry) == SUCCESS) {
		GET_THIS_CPP_OBJECT(text_symbolizer, TextSymbolizer);
		GET_CPP_OBJECT_FROM_ZVAL(value, color, Color, passed_in_object);
		this_TextSymbolizer->set_halo_fill(*passed_in_object);
	}

	php_error_docref(NULL TSRMLS_CC, E_WARNING, "Wrong arguments passed to setHaloFill");

	RETURN_NULL();
}
*/

/*
ZEND_BEGIN_ARG_INFO_EX(setHaloRadius_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(ZEND_SEND_BY_VAL, radius)
ZEND_END_ARG_INFO()
PHP_METHOD(TextSymbolizer, setHaloRadius)
{
	GET_THIS_CPP_OBJECT(text_symbolizer, TextSymbolizer);

	//do ...

	RETURN_TRUE;
}
*/

IMPLEMENT_LONG_SETTER(set_halo_radius, setHaloRadius, text_symbolizer, TextSymbolizer);
IMPLEMENT_OBJECT_SETTER(set_halo_fill, setHaloFill, text_symbolizer, TextSymbolizer, color, Color);

IMPLEMENT_LONG_GETTER(get_halo_radius, getHaloRadius, text_symbolizer, TextSymbolizer);
BEGIN_IMPLEMENT_OBJECT_GETTER(get_halo_fill, getHaloFill, text_symbolizer, TextSymbolizer, color, Color, 4)
	SETUP_ARGUMENT(0, DOUBLE, Color.red())
	SETUP_ARGUMENT(1, DOUBLE, Color.green())
	SETUP_ARGUMENT(2, DOUBLE, Color.blue())
	SETUP_ARGUMENT(3, DOUBLE, Color.alpha())
END_IMPLEMENT_OBJECT_GETTER()

static function_entry php_Mapnik_TextSymbolizer_methods[] = {
	PHP_ME(TextSymbolizer, __construct,		NULL,	ZEND_ACC_PUBLIC)
	// Properties
	PHP_ME(TextSymbolizer, setHaloFill,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(TextSymbolizer, getHaloFill,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(TextSymbolizer, setHaloRadius,	NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(TextSymbolizer, getHaloRadius,	NULL,	ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

/*
		@todo
         text_symbolizer(std::string const& name,std::string const& face_name,
                         unsigned size, color const& fill);
         text_symbolizer(std::string const& name, unsigned size, color const& fill);
         text_symbolizer(text_symbolizer const& rhs);
         text_symbolizer& operator=(text_symbolizer const& rhs);
         std::string const& get_name() const;
         void set_name(std::string name);
         unsigned get_text_ratio() const; // target ratio for text bounding box in pixels
         void set_text_ratio(unsigned ratio);
         unsigned get_wrap_width() const; // width to wrap text at, or trigger ratio
         void set_wrap_width(unsigned ratio);
         unsigned char get_wrap_char() const; // character used to wrap lines
         std::string get_wrap_char_string() const; // character used to wrap lines as std::string
         void set_wrap_char(unsigned char character);
         void set_wrap_char_from_string(std::string const& character);
         text_convert_e get_text_convert() const; // text conversion on strings before display
         void set_text_convert(text_convert_e convert);
         unsigned get_line_spacing() const; // spacing between lines of text
         void set_line_spacing(unsigned spacing);
         unsigned get_character_spacing() const; // spacing between characters in text
         void set_character_spacing(unsigned spacing);
         unsigned get_label_spacing() const; // spacing between repeated labels on lines
         void set_label_spacing(unsigned spacing);
         unsigned get_label_position_tolerance() const; //distance the label can be moved on the line to fit, if 0 the default is used
         void set_label_position_tolerance(unsigned tolerance);
         bool get_force_odd_labels() const; // try render an odd amount of labels
         void set_force_odd_labels(bool force);
         double get_max_char_angle_delta() const; // maximum change in angle between adjacent characters
         void set_max_char_angle_delta(double angle);
         unsigned get_text_size() const;
         void set_text_size(unsigned size);
         std::string const& get_face_name() const;
         void set_face_name(std::string face_name);
         FontSet const& get_fontset() const;
         void set_fontset(FontSet const& fontset);
         color const& get_fill() const;
         void set_fill(color const& fill);
         void set_halo_fill(color const& fill);
         color const& get_halo_fill() const;
         void set_halo_radius(unsigned radius);
         unsigned get_halo_radius() const;
         void set_label_placement(label_placement_e label_p);
         label_placement_e get_label_placement() const;
         void set_vertical_alignment(vertical_alignment_e valign);
         vertical_alignment_e get_vertical_alignment() const;
         void set_anchor(double x, double y);
         position const& get_anchor() const;
         void set_displacement(double x, double y);
         position const& get_displacement() const;
         void set_avoid_edges(bool avoid);
         bool get_avoid_edges() const;
         void set_minimum_distance(double distance);
         double get_minimum_distance() const;
         void set_allow_overlap(bool overlap);
         bool get_allow_overlap() const;
         void set_opacity(double opacity);
         double get_opacity() const;
         bool get_wrap_before() const; // wrap text at wrap_char immediately before current work
         void set_wrap_before(bool wrap_before);
         void set_horizontal_alignment(horizontal_alignment_e valign);
         horizontal_alignment_e get_horizontal_alignment() const;
         void set_justify_alignment(justify_alignment_e valign);
         justify_alignment_e get_justify_alignment() const;
*/
