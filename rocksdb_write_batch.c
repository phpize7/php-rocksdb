/*
 * rocksdb_write_batch.c
 *
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

#include "php_rocksdb.h"
#include "rocksdb_write_batch.h"

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

zend_function_entry rocksdb_write_batch_class_methods[] = {
	PHP_ME(rocksdbwritebatch, __construct, rocksdb_write_batch_class__construct_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbwritebatch, createFrom, rocksdb_write_batch_class_create_from_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbwritebatch, put, rocksdb_write_batch_class_put_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbwritebatch, putCf, rocksdb_write_batch_class_put_cf_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbwritebatch, merge, rocksdb_write_batch_class_merge_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbwritebatch, mergeCf, rocksdb_write_batch_class_merge_cf_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbwritebatch, delete, rocksdb_write_batch_class_delete_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbwritebatch, deleteCf, rocksdb_write_batch_class_delete_cf_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbwritebatch, data, rocksdb_write_batch_class_data_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbwritebatch, count, rocksdb_write_batch_class_count_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbwritebatch, getIterator, rocksdb_write_batch_class_get_iterator_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbwritebatch, clear, rocksdb_write_batch_class_get_clear_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbwritebatch, destroy, rocksdb_write_batch_class_get_destroy_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_FE_END
};

ZEND_MINIT_FUNCTION(rocksdb_write_batch) {
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "RocksDbWriteBatch", rocksdb_write_batch_class_methods);

	rocksdb_write_batch_ce = zend_register_internal_class(&ce);

	return SUCCESS;
}