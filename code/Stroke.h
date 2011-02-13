#include <mapnik/stroke.hpp>

DEFINE_CLASS(stroke, Stroke)

/*
	explicit stroke();
	stroke(color const& c, float width=1.0);
	stroke(stroke const& other);
	stroke& operator=(const stroke& rhs);
 */
PHP_METHOD(Stroke, __construct)
{
	mapnik::stroke Stroke = NULL;
}

static function_entry php_Mapnik_LineSymbolizer_methods[] = {
	PHP_ME(PolygonSymbolizer, __construct,		NULL,	ZEND_ACC_PUBLIC)
	// Properties
	{ NULL, NULL, NULL }
};

/*
    void set_color(const color& c);
    color const& get_color() const;
    float get_width() const;
    void set_width(float w);
    void set_opacity(float opacity);
    float get_opacity() const;
    void set_line_cap(line_cap_e line_cap);
    line_cap_e get_line_cap() const;
    void set_line_join(line_join_e line_join);
    line_join_e get_line_join() const;
    void add_dash(float dash,float gap);
    bool has_dash() const;
    dash_array const& get_dash_array() const;
*/