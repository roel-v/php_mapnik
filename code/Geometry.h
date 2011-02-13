#include <mapnik/geometry.hpp>

DEFINE_CLASS(geometry, Geometry);

PHP_METHOD(Geometry, __construct)
{
}

// Envelope<double> envelope() const
PHP_METHOD(Geometry, getEnvelope)
{
	GET_THIS_CPP_OBJECT():
}

// virtual int type() const=0;
PHP_METHOD(Geometry, getType)
{
	GET_THIS_CPP_OBJECT():
}

// virtual bool hit_test(value_type x,value_type y, double tol) const=0;  
PHP_METHOD(Geometry, hitTest)
{
	GET_THIS_CPP_OBJECT():
}

// virtual void label_position(double *x, double *y) const=0;
PHP_METHOD(Geometry, setLabelPosition)
{
	GET_THIS_CPP_OBJECT():
}

// virtual void move_to(value_type x,value_type y)=0;
PHP_METHOD(Geometry, moveTo)
{
	GET_THIS_CPP_OBJECT():
}

// virtual void line_to(value_type x,value_type y)=0;
PHP_METHOD(Geometry, lineTo)
{
	GET_THIS_CPP_OBJECT():
}

// virtual unsigned num_points() const = 0;
PHP_METHOD(Geometry, getPointCount)
{
	GET_THIS_CPP_OBJECT():
}

// virtual unsigned vertex(double* x, double* y) const=0;
PHP_METHOD(Geometry, vertex)
{
	GET_THIS_CPP_OBJECT():
}

// virtual void rewind(unsigned) const=0;
PHP_METHOD(Geometry, rewind)
{
	GET_THIS_CPP_OBJECT():
}

// virtual void set_capacity(size_t size)=0;
PHP_METHOD(Geometry, setCapacity)
{
	GET_THIS_CPP_OBJECT():
}

static function_entry php_Mapnik_Geometry_methods[] = {
	PHP_ME(Geometry, __construct,	    NULL,	ZEND_ACC_PUBLIC | ZEND_ACC_INTERFACE)
	PHP_ME(Geometry, getEnvelope,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Geometry, getType,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Geometry, hitTest,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Geometry, setLabelPosition,	NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Geometry, moveTo,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Geometry, lineTo,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Geometry, getPointCount,		NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Geometry, vertex,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Geometry, rewind,			NULL,	ZEND_ACC_PUBLIC)
	PHP_ME(Geometry, setCapacity,		NULL,	ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};
