#ifndef ZEND_OBJECTS_H
#define ZEND_OBJECTS_H

#include "zend.h"

typedef struct _zend_object_bucket {
	zend_bool valid;
	zend_bool constructor_called;
	union _bucket {
		struct {
			zend_object object;
			zend_uint refcount;
		} obj;
		struct {
			int next;
		} free_list;
	} bucket;
} zend_object_bucket;

typedef struct _zend_objects {
	zend_object_bucket *object_buckets;
	zend_uint top;
	zend_uint size;
	int free_list_head;
} zend_objects;

void zend_objects_init(zend_objects *objects, zend_uint init_size);
void zend_objects_call_destructors(zend_objects *objects TSRMLS_DC);
void zend_objects_destroy(zend_objects *objects);
zend_object_value zend_objects_new(zend_object **object, zend_class_entry *class_type);

zend_object *zend_objects_get_address(zval *object);

void zend_objects_add_ref(zval *object);
void zend_objects_del_ref(zval *object);
void zend_objects_delete_obj(zval *object);
zend_object_value zend_objects_clone_obj(zval *object);

#define Z_GET_OBJ(object_zval) zend_objects_get_address(object_zval)

#endif /* ZEND_OBJECTS_H */
