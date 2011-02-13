#pragma once

//  Some symbolic names to the ARG_INFO macros that are imo missing from the zend headers.
#define ZEND_DONT_ALLOW_NULL 0
#define ZEND_ALLOW_NULL 1

#define ZEND_RETURN_VALUE 0
#define ZEND_RETURN_REFERENCE 1

struct ZValSmartPtr {
	ZValSmartPtr(zval** zval_)
		: m_ZVal(zval_)
	{ }
	~ZValSmartPtr()
	{
		if (*m_ZVal) {
			zval_ptr_dtor(m_ZVal);
		}
	}
private:
	zval** m_ZVal;
};

#define DEFINE_CLASS(cpp_class_name, php_class_name)				\
struct php_class_name##Object {										\
    zend_object std;												\
	mapnik::##cpp_class_name##* php_class_name;						\
	boost::shared_ptr<mapnik::##cpp_class_name##> php_class_name##_shared_ptr;				\
};																	\
zend_object_handlers php_class_name##_object_handlers;				\
void php_class_name##_free_storage(void *object TSRMLS_DC)			\
{																	\
	php_class_name##Object* obj = (##php_class_name##Object*)object;\
	if (obj->php_class_name##_shared_ptr == NULL) {					\
		operator delete(obj->##php_class_name##, __FILE__, __LINE__);	\
	}																\
    zend_hash_destroy(obj->std.properties);							\
    FREE_HASHTABLE(obj->std.properties);							\
    efree(obj);														\
}																	\
zend_object_value php_class_name##_create_handler(zend_class_entry* type TSRMLS_DC)					\
{																									\
    zval* tmp;																						\
    zend_object_value retval;																		\
    php_class_name##Object *obj = (php_class_name##Object *)emalloc(sizeof(php_class_name##Object));\
    memset(obj, 0, sizeof(php_class_name##Object));													\
    obj->std.ce = type;																				\
    ALLOC_HASHTABLE(obj->std.properties);															\
    zend_hash_init(obj->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);									\
    zend_hash_copy(obj->std.properties, &type->default_properties, (copy_ctor_func_t)zval_add_ref, (void *)&tmp, sizeof(zval *));	\
    retval.handle = zend_objects_store_put(obj, NULL, php_class_name##_free_storage, NULL TSRMLS_CC);	\
    retval.handlers = &php_class_name##_object_handlers;												\
    return retval;																						\
}																										\
	zend_class_entry* php_Mapnik_##php_class_name##_entry = NULL;

#define INIT_STATIC_CLASS(class_name)																			\
	{ zend_class_entry class_name##_ce;																	\
	INIT_NS_CLASS_ENTRY(class_name##_ce, "Mapnik", #class_name, php_Mapnik_##class_name##_methods);		\
	php_Mapnik_##class_name##_entry = zend_register_internal_class(&class_name##_ce TSRMLS_CC);			\
	}

#define INIT_CLASS(class_name)																			\
	{ zend_class_entry class_name##_ce;																	\
	INIT_NS_CLASS_ENTRY(class_name##_ce, "Mapnik", #class_name, php_Mapnik_##class_name##_methods);		\
	class_name##_ce.create_object = ##class_name##_create_handler;										\
	php_Mapnik_##class_name##_entry = zend_register_internal_class(&class_name##_ce TSRMLS_CC);			\
    memcpy(&class_name##_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));\
    class_name##_object_handlers.clone_obj = NULL;														\
	}

#define GET_CPP_OBJECT_FROM_ZVAL(zval_name, cpp_class_name, php_class_name, variable_name)	\
	php_class_name##Object* php_class_name##_object = (php_class_name##Object*)zend_object_store_get_object(zval_name TSRMLS_CC);	\
	mapnik::cpp_class_name* variable_name = php_class_name##_object->php_class_name;

/*
 * This macro will extract the C++ object from the getThis() zval. If it can't find
 * it, it will return false; otherwise it will set a variable called 'this_<php_class_name>'.
 */
#define GET_THIS_CPP_OBJECT(cpp_class_name, php_class_name)	\
	mapnik::cpp_class_name* this_##php_class_name = NULL;	\
	{ php_class_name##Object* php_class_name##_object =		\
		(php_class_name##Object*)zend_object_store_get_object(getThis() TSRMLS_CC);	\
	this_##php_class_name = php_class_name##_object->php_class_name;	}			\
	if (this_##php_class_name == NULL) {					\
		RETURN_FALSE;										\
	}
/*
 * This macro does the same as GET_THIS_CPP_OBJECT except that it has an extra parameter in which
 * you can specify the name of the variable to store the object in.
 */
#define GET_THIS_NAMED_CPP_OBJECT(cpp_class_name, php_class_name, variable_name)	\
	mapnik::cpp_class_name* variable_name = NULL;									\
	{ php_class_name##Object* php_class_name##_object =								\
		(php_class_name##Object*)zend_object_store_get_object(getThis() TSRMLS_CC);	\
	variable_name = php_class_name##_object->php_class_name;	}					\
	if (variable_name == NULL) {													\
		RETURN_FALSE;																\
	}

#define INIT_CPP_OBJECT(class_name)		\
	class_name##Object* obj = (class_name##Object*)zend_object_store_get_object(getThis() TSRMLS_CC);	\
	obj->class_name = class_name;

#define INIT_NAMED_CPP_OBJECT(class_name, variable_name)		\
	class_name##Object* obj = (class_name##Object*)zend_object_store_get_object(getThis() TSRMLS_CC);	\
	obj->class_name = class_name;

#define PHP_NEW new (__FILE__, __LINE__)

#define IMPLEMENT_GETTER(cpp_getter_name, php_getter_name, cpp_class_name, php_class_name, type)	\
PHP_METHOD(php_class_name, php_getter_name)					\
{															\
	GET_THIS_CPP_OBJECT(cpp_class_name, php_class_name);			\
	RETURN_##type(this_##php_class_name->cpp_getter_name());	\
}

#define IMPLEMENT_LONG_GETTER(cpp_getter_name, php_getter_name, cpp_class_name, php_class_name) IMPLEMENT_GETTER(cpp_getter_name, php_getter_name, cpp_class_name, php_class_name, LONG)
#define IMPLEMENT_DOUBLE_GETTER(cpp_getter_name, php_getter_name, cpp_class_name, php_class_name) IMPLEMENT_GETTER(cpp_getter_name, php_getter_name, cpp_class_name, php_class_name, DOUBLE)

#define IMPLEMENT_SETTER(cpp_setter_name, php_setter_name, cpp_class_name, php_class_name, cpp_type, zval_type_id)	\
PHP_METHOD(php_class_name, php_setter_name)					\
{															\
	cpp_type value;											\
	if (::zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, #zval_type_id, &value) == FAILURE) {	\
		RETURN_FALSE;										\
	}														\
	GET_THIS_CPP_OBJECT(cpp_class_name, php_class_name);			\
	this_##php_class_name->cpp_setter_name(value);			\
}

#define IMPLEMENT_DOUBLE_SETTER(cpp_setter_name, php_setter_name, cpp_class_name, php_class_name) IMPLEMENT_SETTER(cpp_setter_name, php_setter_name, cpp_class_name, php_class_name, double, d)
#define IMPLEMENT_FLOAT_SETTER(cpp_setter_name, php_setter_name, cpp_class_name, php_class_name) IMPLEMENT_SETTER(cpp_setter_name, php_setter_name, cpp_class_name, php_class_name, float, d)
#define IMPLEMENT_LONG_SETTER(cpp_setter_name, php_setter_name, cpp_class_name, php_class_name) IMPLEMENT_SETTER(cpp_setter_name, php_setter_name, cpp_class_name, php_class_name, long, l)

#define IMPLEMENT_STRING_GETTER(cpp_getter_name, php_getter_name, cpp_class_name, php_class_name)	\
PHP_METHOD(php_class_name, php_getter_name)						\
{																\
	GET_THIS_CPP_OBJECT(cpp_class_name, php_class_name);				\
	std::string tmp = this_##php_class_name->cpp_getter_name();	\
	RETURN_STRING(tmp.c_str(), tmp.c_str());					\
}

#define IMPLEMENT_STRING_SETTER(cpp_setter_name, php_setter_name, cpp_class_name, php_class_name)	\
PHP_METHOD(php_class_name, php_setter_name)					\
{															\
	char* value = NULL;										\
	int value_len;											\
	if (::zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &value, &value_len) == FAILURE) {	\
		RETURN_FALSE;										\
	}														\
	GET_THIS_CPP_OBJECT(cpp_class_name, php_class_name);			\
	this_##php_class_name->cpp_setter_name(value);			\
}

#define BEGIN_RETURN_PHP_OBJECT(php_class_name, arg_count)				\
	object_init_ex(return_value, php_Mapnik_##php_class_name##_entry);	\
	zval* ctor = NULL;													\
	MAKE_STD_ZVAL(ctor);												\
	ZVAL_STRING(ctor, "__construct", 1)									\
	ZValSmartPtr ctor_ptr(&ctor);										\
	zval* dummy_retval = NULL;											\
	ZValSmartPtr dummy_retval_ptr(&dummy_retval);						\
	zval*** args = (zval***)safe_emalloc(sizeof(zval**), arg_count, 0);	\
	int local_arg_count = arg_count;

#define SETUP_ARGUMENT(counter, type, value)			\
	zval* arg##counter;									\
	MAKE_STD_ZVAL(arg##counter);						\
	ZVAL_##type(arg##counter, value);					\
	args[counter] = &arg##counter;						\
	ZValSmartPtr arg##counter##_ptr(&arg##counter);

#define END_RETURN_PHP_OBJECT()							\
	if (call_user_function_ex(NULL, &return_value,		\
					ctor, &dummy_retval,				\
					local_arg_count, args,							\
					0, NULL TSRMLS_CC					\
					) == FAILURE) {						\
		/* What to do here?	*/							\
	}													\
	efree(args);


#define BEGIN_IMPLEMENT_OBJECT_GETTER(cpp_getter_name, php_getter_name, this_class_cpp_class_name, this_class_php_class_name, return_value_cpp_class_name, return_value_php_class_name, arg_count)	\
PHP_METHOD(this_class_php_class_name, php_getter_name)																					\
{																															\
	GET_THIS_CPP_OBJECT(this_class_cpp_class_name, this_class_php_class_name);													\
	mapnik::return_value_cpp_class_name return_value_php_class_name = this_##this_class_php_class_name->cpp_getter_name();	\
	BEGIN_RETURN_PHP_OBJECT(return_value_php_class_name, arg_count)

#define END_IMPLEMENT_OBJECT_GETTER()	\
	END_RETURN_PHP_OBJECT() }

#define IMPLEMENT_OBJECT_SETTER(cpp_setter_name, php_setter_name, this_cpp_class_name, this_php_class_name, argument_cpp_class_name, argument_php_class_name)	\
PHP_METHOD(this_php_class_name, php_setter_name)									\
{																					\
	zval* value;																	\
	if (::zend_parse_parameters_ex(													\
				ZEND_PARSE_PARAMS_QUIET,											\
				ZEND_NUM_ARGS() TSRMLS_CC, "O",										\
				&value,php_Mapnik_##argument_php_class_name##_entry) == SUCCESS) {	\
		GET_THIS_CPP_OBJECT(this_cpp_class_name, this_php_class_name);				\
		GET_CPP_OBJECT_FROM_ZVAL(value, argument_cpp_class_name, argument_php_class_name, passed_in_object);	\
		this_##this_php_class_name->cpp_setter_name(*passed_in_object);				\
		return;																		\
	}																				\
	php_error_docref(NULL TSRMLS_CC, E_WARNING,										\
						"Wrong arguments passed to " #php_setter_name);				\
	RETURN_NULL();																	\
}

#define GET_OBJECT_ARGUMENT(argument_cpp_type, argument_php_type, variable_name, function_name)	\
zval* value;																		\
if (::zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET,								\
			ZEND_NUM_ARGS() TSRMLS_CC, "O", &value,									\
			php_Mapnik_##argument_php_type##_entry) == FAILURE) {					\
	php_error_docref(NULL TSRMLS_CC, E_WARNING,										\
		"Wrong arguments passed to " #function_name );								\
	RETURN_NULL();																	\
}																					\
GET_CPP_OBJECT_FROM_ZVAL(value, argument_cpp_type, argument_php_type, variable_name);