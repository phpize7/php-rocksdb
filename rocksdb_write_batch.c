/*
 * rocksdb_write_batch.c
 *
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

#include "php_rocksdb.h"

zend_class_entry *rocksdb_write_batch_ce;

ZEND_BEGIN_ARG_INFO_EX(rocksdb_write_batch_class__construct_arginfo, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_write_batch_class_create_from_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, bytes)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_write_batch_class_put_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_write_batch_class_put_cf_arginfo, 0, 0, 3)
	ZEND_ARG_INFO(0, cf)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_write_batch_class_merge_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_write_batch_class_merge_cf_arginfo, 0, 0, 3)
	ZEND_ARG_INFO(0, cf)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_write_batch_class_delete_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_write_batch_class_delete_cf_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, cf)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

// Data returns the serialized version of this batch.
ZEND_BEGIN_ARG_INFO_EX(rocksdb_write_batch_class_data_arginfo, 0, 0, 0)
ZEND_END_ARG_INFO()

// Count returns the number of updates in the batch.
ZEND_BEGIN_ARG_INFO_EX(rocksdb_write_batch_class_count_arginfo, 0, 0, 0)
ZEND_END_ARG_INFO()

// GetIterator returns a iterator to iterate over the records in the batch.
ZEND_BEGIN_ARG_INFO_EX(rocksdb_write_batch_class_get_iterator_arginfo, 0, 0, 0)
ZEND_END_ARG_INFO()

// Clear removes all the enqueued Put and Deletes.
ZEND_BEGIN_ARG_INFO_EX(rocksdb_write_batch_class_clear_arginfo, 0, 0, 0)
ZEND_END_ARG_INFO()

// Destroy deallocates the WriteBatch object.
ZEND_BEGIN_ARG_INFO_EX(rocksdb_write_batch_class_destroy_arginfo, 0, 0, 0)
ZEND_END_ARG_INFO()

const zend_function_entry rocksdb_write_batch_class_methods[] = {
	PHP_ME(rocksdb_write_batch, __construct, rocksdb_write_batch_class__construct_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdb_write_batch, createFrom, rocksdb_write_batch_class_create_from_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_write_batch, put, rocksdb_write_batch_class_put_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_write_batch, putCf, rocksdb_write_batch_class_put_cf_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_write_batch, merge, rocksdb_write_batch_class_merge_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_write_batch, mergeCf, rocksdb_write_batch_class_merge_cf_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_write_batch, delete, rocksdb_write_batch_class_delete_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_write_batch, deleteCf, rocksdb_write_batch_class_delete_cf_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_write_batch, data, rocksdb_write_batch_class_data_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_write_batch, count, rocksdb_write_batch_class_count_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_write_batch, getIterator, rocksdb_write_batch_class_get_iterator_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_write_batch, clear, rocksdb_write_batch_class_clear_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_write_batch, destroy, rocksdb_write_batch_class_destroy_arginfo, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(rocksdb_write_batch, __construct) {}
PHP_METHOD(rocksdb_write_batch, createFrom) {}
PHP_METHOD(rocksdb_write_batch, put) {}
PHP_METHOD(rocksdb_write_batch, putCf) {}
PHP_METHOD(rocksdb_write_batch, merge) {}
PHP_METHOD(rocksdb_write_batch, mergeCf) {}
PHP_METHOD(rocksdb_write_batch, delete) {}
PHP_METHOD(rocksdb_write_batch, deleteCf) {}
PHP_METHOD(rocksdb_write_batch, data) {}
PHP_METHOD(rocksdb_write_batch, count) {}
PHP_METHOD(rocksdb_write_batch, getIterator) {}
PHP_METHOD(rocksdb_write_batch, clear) {}
PHP_METHOD(rocksdb_write_batch, destroy) {}