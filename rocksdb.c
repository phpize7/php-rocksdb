/*
 * rocksdb.c
 *
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "zend_exceptions.h"

#include "php_rocksdb.h"

zend_class_entry *rocksdb_ce;

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class__construct_arginfo, 0, 0, 9)
  ZEND_ARG_INFO(0, name)
	ZEND_ARG_ARRAY_INFO(0, options, 1)
	ZEND_ARG_ARRAY_INFO(0, read_options, 1)
	ZEND_ARG_ARRAY_INFO(0, write_options, 1)
	ZEND_ARG_INFO(0, num_column_families)
	ZEND_ARG_ARRAY_INFO(0, column_family_names, 1)
	ZEND_ARG_ARRAY_INFO(0, column_family_options, 1)
	ZEND_ARG_ARRAY_INFO(0, column_family_handles, 1)
	ZEND_ARG_INFO(0, error_if_log_file_exist)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_list_column_families_arginfo, 0, 0, 3)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, options)
	ZEND_ARG_INFO(0, lencf)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_create_column_family_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, column_family_name)
	ZEND_ARG_INFO(0, column_family_options)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_drop_column_family_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, handle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_put_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_put_cf_arginfo, 0, 0, 3)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
	ZEND_ARG_INFO(0, column_family)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_delete_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_delete_cf_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, column_family)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_merge_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_merge_cf_arginfo, 0, 0, 3)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
	ZEND_ARG_INFO(0, column_family)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_write_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, batch)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_get_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_get_cf_arginfo, 0, 0, 3)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, column_family)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_get_iterator_cf_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, column_family)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_get_property_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_get_property_cf_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, column_family)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_get_approximate_sizes_arginfo, 0, 0, 4)
	ZEND_ARG_INFO(0, num_ranges)
	ZEND_ARG_INFO(0, start_key)
	ZEND_ARG_INFO(0, limit_key)
	ZEND_ARG_INFO(0, sizes)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_get_approximate_sizes_cf_arginfo, 0, 0, 5)
	ZEND_ARG_INFO(0, num_ranges)
	ZEND_ARG_INFO(0, start_key)
	ZEND_ARG_INFO(0, limit_key)
	ZEND_ARG_INFO(0, sizes)
	ZEND_ARG_INFO(0, column_family)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_flush_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, options)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_delete_file_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_enable_file_deletions_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, force)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_destroy_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_repair_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

const zend_function_entry rocksdb_class_methods[] = {
	PHP_ME(rocksdb, __construct, rocksdb_class__construct_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdb, listColumnFamilies, rocksdb_class_list_column_families_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(rocksdb, createColumnFamily, rocksdb_class_create_column_family_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, dropColumnFamily, rocksdb_class_drop_column_family_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, put, rocksdb_class_put_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, putCf, rocksdb_class_put_cf_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, delete, rocksdb_class_delete_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, deleteCf, rocksdb_class_delete_cf_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, merge, rocksdb_class_merge_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, mergeCf, rocksdb_class_merge_cf_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, write, rocksdb_class_write_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, get, rocksdb_class_get_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, getCf, rocksdb_class_get_cf_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, getIterator, NULL, ZEND_ACC_PUBLIC) // rocksdb_create_iterator
	PHP_ME(rocksdb, getIteratorCf, rocksdb_class_get_iterator_cf_arginfo, ZEND_ACC_PUBLIC) // rocksdb_create_iterator_cf
	PHP_ME(rocksdb, createSnapshot, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, getProperty, rocksdb_class_get_property_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, getPropertyCf, rocksdb_class_get_property_cf_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, getApproximateSizes, rocksdb_class_get_approximate_sizes_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, getApproximateSizesCf, rocksdb_class_get_approximate_sizes_cf_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, flush, rocksdb_class_flush_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, deleteFile, rocksdb_class_delete_file_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, disableFileDeletions, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, enableFileDeletions, rocksdb_class_enable_file_deletions_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, destroy, rocksdb_class_destroy_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, repair, rocksdb_class_repair_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, close, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

/* {{{ Error Handler
*/
static void php_rocksdb_error(php_rocksdb_db_object *db_obj, char *format, ...)
{
	va_list arg;
	char *message;

	va_start(arg, format);
	vspprintf(&message, 0, format, arg);
	va_end(arg);

	if (db_obj && db_obj->exception) {
		zend_throw_exception(zend_ce_exception, message, 0);
	} else {
		php_error_docref(NULL, E_WARNING, "%s", message);
	}

	if (message) {
		efree(message);
	}
}
/* }}} */

PHP_METHOD(rocksdb, __construct) {
  zend_string *name;
  HashTable *args;
  zval *object = getThis();
  php_rocksdb_db_object *db_obj;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &args) == FAILURE) {
    return;
  }

  db_obj = Z_ROCKSDB_DB_P(object);

  if (db_obj->initialised == 1) {
    zend_throw_exception(zend_ce_exception, "Already initialised DB Object", 0);
  }

  rocksdb_options_t *options = rocksdb_options_create();
  rocksdb_options_set_create_if_missing(options, 1);

  char *err = NULL;
  db_obj->db = rocksdb_open(options, (const char *) name, &err);

  rocksdb_options_destroy(options);

  if (err != NULL) {
    zend_throw_exception(zend_ce_exception, err, 0);

    efree(name);
    efree(args);
    efree(db_obj);

    return;
  }

  db_obj->initialised = 1;
}

PHP_METHOD(rocksdb, open) {

}
PHP_METHOD(rocksdb, openReadOnly) {}
PHP_METHOD(rocksdb, openColumnFamilies) {}
PHP_METHOD(rocksdb, openForReadOnlyColumnFamilies) {}
PHP_METHOD(rocksdb, listColumnFamilies) {}
PHP_METHOD(rocksdb, createColumnFamily) {}
PHP_METHOD(rocksdb, dropColumnFamily) {}
PHP_METHOD(rocksdb, put) {}
PHP_METHOD(rocksdb, putCf) {}
PHP_METHOD(rocksdb, delete) {}
PHP_METHOD(rocksdb, deleteCf) {}
PHP_METHOD(rocksdb, merge) {}
PHP_METHOD(rocksdb, mergeCf) {}
PHP_METHOD(rocksdb, write) {}
PHP_METHOD(rocksdb, get) {}
PHP_METHOD(rocksdb, getCf) {}
PHP_METHOD(rocksdb, getIterator) {}
PHP_METHOD(rocksdb, getIteratorCf) {}
PHP_METHOD(rocksdb, createSnapshot) {}
PHP_METHOD(rocksdb, getProperty) {}
PHP_METHOD(rocksdb, getPropertyCf) {}
PHP_METHOD(rocksdb, getApproximateSizes) {}
PHP_METHOD(rocksdb, getApproximateSizesCf) {}
PHP_METHOD(rocksdb, flush) {}
PHP_METHOD(rocksdb, deleteFile) {}
PHP_METHOD(rocksdb, disableFileDeletions) {}
PHP_METHOD(rocksdb, enableFileDeletions) {}
PHP_METHOD(rocksdb, destroy) {}
PHP_METHOD(rocksdb, repair) {}
PHP_METHOD(rocksdb, close) {}
