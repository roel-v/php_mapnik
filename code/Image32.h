#include <mapnik/graphics.hpp>

DEFINE_CLASS(Image32, Image32);

PHP_METHOD(Image32, __construct)
{
	mapnik::Image32* Image32 = NULL;

	int width, height;

	if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "ll", &width, &height) == SUCCESS) {
		Image32 = PHP_NEW mapnik::Image32(width, height);
	} else {
		// None of the supported parameter formats. Fail construction.
		zend_throw_exception(zend_exception_get_default(TSRMLS_C), "Wrong arguments passed to constructor", 0 TSRMLS_CC);
		RETURN_NULL();
	}

	assert(Image32);

	INIT_CPP_OBJECT(Image32);
}

// const ImageData32& data() const;
PHP_METHOD(Image32, getData)
{
	GET_THIS_CPP_OBJECT(Image32, Image32);

	this_Image32->data();
}
	
/*
PHP_METHOD(Image32, )
{
	GET_CPP_OBJECT(Image32, Image32);

	//do ...

	RETURN_TRUE;
}
*/

static function_entry php_Mapnik_Image32_methods[] = {
	PHP_ME(Image32, __construct,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Image32, getData,			NULL,	ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

/*
 * @todo
        Image32(int width,int height);
        void setBackground(color const& background);
        const color& getBackground() const;
        const ImageData32& data() const;

        inline ImageData32& data()
        inline const unsigned char* raw_data() const
        inline unsigned char* raw_data()
        inline image_view<ImageData32> get_view(unsigned x,unsigned y, unsigned w,unsigned h)
*/
