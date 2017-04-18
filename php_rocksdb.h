/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_ROCKSDB_H
#define PHP_ROCKSDB_H

extern zend_module_entry rocksdb_module_entry;

#define phpext_rocksdb_ptr &rocksdb_module_entry

#define PHP_ROCKSDB_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_ROCKSDB_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_ROCKSDB_API __attribute__ ((visibility("default")))
#else
#	define PHP_ROCKSDB_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#ifndef STORAGE_ROCKSDB_INCLUDE_C_H_
#include "rocksdb/c.h"
#endif

#include "rocksdb_ce.h"
#include "rocksdb_fe.h"

#define ROCKSDB_TOLERATE_CORRUPTED_TAIL_RECORDS_RECOVERY 0
#define ROCKSDB_ABSOLUTE_CONSISTENCY_RECOVERY 1
#define ROCKSDB_POINT_IN_TIME_RECOVERY 2
#define ROCKSDB_SKIP_ANY_CORRUPTED_RECORDS_RECOVERY 3

#define ROCKSDB_NO_COMPRESSION 0
#define ROCKSDB_SNAPPY_COMPRESSION 1
#define ROCKSDB_ZLIB_COMPRESSION 2
#define ROCKSDB_BZ2_COMPRESSION 3
#define ROCKSDB_LZ4_COMPRESSION 4
#define ROCKSDB_LZ4HC_COMPRESSION 5

#define ROCKSDB_LEVEL_COMPATION 0
#define ROCKSDB_UNIVERSAL_COMPACTION 1
#define ROCKSDB_FIFO_COMPACTION 2

/* Structure for RocksDb Database object. */
typedef struct _php_rocksdb_db_object {
  int initialised;
  char *name;

  int num_handles;
  char *handle_names[128];

  rocksdb_t *db;
  rocksdb_column_family_handle_t *handles[128];

  zend_bool exception;
  zend_object zo;
} php_rocksdb_db_object;

typedef struct _php_rocksdb_write_batch_object {
	rocksdb_writebatch_t *batch;
	zend_object zo;
} php_rocksdb_write_batch_object;

typedef struct _php_rocksdb_iterator_object {
  zval *db;
	rocksdb_iterator_t *iterator;
	zend_object zo;
} php_rocksdb_iterator_object;

typedef struct _php_rocksdb_snapshot_object {
  zval *db;
	rocksdb_snapshot_t *snapshot;
	zend_object zo;
} php_rocksdb_snapshot_object;

typedef struct _php_rocksdb_backup_engine_object {
	rocksdb_backup_engine_t *be;
	zend_object zo;
} php_rocksdb_backup_engine_object;

typedef struct _php_rocksdb_backup_engine_info_object {
	const rocksdb_backup_engine_info_t *info;
	zend_object zo;
} php_rocksdb_backup_engine_info_object;

typedef struct _php_rocksdb_merge_operator_object {
	rocksdb_mergeoperator_t *op;
  zend_function *fptr_full_merge;
  zend_function *fptr_partial_merge;
	zend_object zo;
} php_rocksdb_merge_operator_object;

#define PHP_ROCKSDB_REGISTER_CLASS_CONSTANT(class_entry, const_name, value) \
  zend_declare_class_constant_long(class_entry, const_name, sizeof(const_name)-1, (zend_long)value);

static inline php_rocksdb_db_object *php_rocksdb_from_obj(zend_object *obj) {
  return (php_rocksdb_db_object*)((char*)(obj) - XtOffsetOf(php_rocksdb_db_object, zo));
}

static inline php_rocksdb_write_batch_object *php_rocksdb_write_batch_from_obj(zend_object *obj) {
	return (php_rocksdb_write_batch_object*)((char*)(obj) - XtOffsetOf(php_rocksdb_write_batch_object, zo));
}

static inline php_rocksdb_iterator_object *php_rocksdb_iterator_from_obj(zend_object *obj) {
	return (php_rocksdb_iterator_object*)((char*)(obj) - XtOffsetOf(php_rocksdb_iterator_object, zo));
}

static inline php_rocksdb_snapshot_object *php_rocksdb_snapshot_from_obj(zend_object *obj) {
	return (php_rocksdb_snapshot_object*)((char*)(obj) - XtOffsetOf(php_rocksdb_snapshot_object, zo));
}

static inline php_rocksdb_backup_engine_object *php_rocksdb_backup_engine_from_obj(zend_object *obj) {
	return (php_rocksdb_backup_engine_object*)((char*)(obj) - XtOffsetOf(php_rocksdb_backup_engine_object, zo));
}

static inline php_rocksdb_backup_engine_info_object *php_rocksdb_backup_engine_info_from_obj(zend_object *obj) {
	return (php_rocksdb_backup_engine_info_object*)((char*)(obj) - XtOffsetOf(php_rocksdb_backup_engine_info_object, zo));
}

static inline php_rocksdb_merge_operator_object *php_rocksdb_merge_operator_info_from_obj(zend_object *obj) {
	return (php_rocksdb_merge_operator_object*)((char*)(obj) - XtOffsetOf(php_rocksdb_merge_operator_object, zo));
}

#define Z_ROCKSDB_DB_P(zv) php_rocksdb_from_obj(Z_OBJ_P((zv)))
#define Z_ROCKSDB_WRITE_BATCH_P(zv) php_rocksdb_write_batch_from_obj(Z_OBJ_P((zv)))
#define Z_ROCKSDB_ITERATOR_P(zv) php_rocksdb_iterator_from_obj(Z_OBJ_P((zv)))
#define Z_ROCKSDB_SNAPSHOT_P(zv) php_rocksdb_snapshot_from_obj(Z_OBJ_P((zv)))
#define Z_ROCKSDB_BACKUP_ENGINE_P(zv) php_rocksdb_backup_engine_from_obj(Z_OBJ_P((zv)))
#define Z_ROCKSDB_BACKUP_ENGINE_INFO_P(zv) php_rocksdb_backup_engine_info_from_obj(Z_OBJ_P((zv)))
#define Z_ROCKSDB_MERGE_OPERATOR_P(zv) php_rocksdb_merge_operator_info_from_obj(Z_OBJ_P((zv)))

#define ROCKSDB_CHECK_FOR_ERRORS(err) \
	if ((err) != NULL) { \
		zend_throw_exception(rocksdb_exception_ce, err, 0 TSRMLS_CC); \
		free(err); \
		return; \
	}

static inline rocksdb_flushoptions_t* php_rocksdb_get_flush_options(zval *options_zv)
{
  HashTable *ht;
  zval *val;

  rocksdb_flushoptions_t *options = rocksdb_flushoptions_create();

  if (options_zv == NULL) {
  	return options;
  }

  ht = Z_ARRVAL_P(options_zv);

  if (NULL != (val = zend_hash_str_find(ht, "wait", sizeof("wait")-1))) {
    rocksdb_flushoptions_set_wait(options, zend_is_true(val));
  }

	return options;
}

static inline rocksdb_restore_options_t* php_rocksdb_get_restore_options(zval *options_zv)
{
  HashTable *ht;
  zval *val;

  rocksdb_restore_options_t *options = rocksdb_restore_options_create();

  if (options_zv == NULL) {
  	return options;
  }

  ht = Z_ARRVAL_P(options_zv);

  if (NULL != (val = zend_hash_str_find(ht, "keep_log_files", sizeof("keep_log_files")-1))) {
    rocksdb_restore_options_set_keep_log_files(options, 1);
  }

  return options;
}

static inline rocksdb_writeoptions_t* php_rocksdb_get_write_options(zval *options_zv)
{
  HashTable *ht;
  zval *val;

  rocksdb_writeoptions_t *options = rocksdb_writeoptions_create();

  if (options_zv == NULL) {
  	return options;
  }

  ht = Z_ARRVAL_P(options_zv);

  if (NULL != (val = zend_hash_str_find(ht, "sync", sizeof("sync")-1))) {
    rocksdb_writeoptions_set_sync(options, (unsigned char) zend_is_true(val));
  }

  if (NULL != (val = zend_hash_str_find(ht, "disable_wal", sizeof("disable_wal")-1))) {
    rocksdb_writeoptions_set_sync(options, i_zend_is_true(val));
  }

  return options;
}

static inline rocksdb_readoptions_t* php_rocksdb_get_read_options(zval *options_zv)
{
  HashTable *ht;
  zval *val;

  rocksdb_readoptions_t *options = rocksdb_readoptions_create();

  if (options_zv == NULL) {
  	return options;
  }

  ht = Z_ARRVAL_P(options_zv);

  if (NULL != (val = zend_hash_str_find(ht, "verify_checksums", sizeof("verify_checksums")-1))) {
    rocksdb_readoptions_set_verify_checksums(options, (unsigned char) zend_is_true(val));
  }

  if (NULL != (val = zend_hash_str_find(ht, "fill_cache", sizeof("fill_cache")-1))) {
    rocksdb_readoptions_set_fill_cache(options, (unsigned char) zend_is_true(val));
  }


  if (NULL != (val = zend_hash_str_find(ht, "tailing", sizeof("tailing")-1))) {
    rocksdb_readoptions_set_tailing(options, (unsigned char) zend_is_true(val));
  }

  if (NULL != (val = zend_hash_str_find(ht, "pin_data", sizeof("pin_data")-1))) {
    rocksdb_readoptions_set_pin_data(options, (unsigned char) zend_is_true(val));
  }

  if (NULL != (val = zend_hash_str_find(ht, "order_seek", sizeof("order_seek")-1))) {
    rocksdb_readoptions_set_total_order_seek(options, (unsigned char) zend_is_true(val));
  }

  if (NULL != (val = zend_hash_str_find(ht, "snapshot", sizeof("snapshot")-1))) {
    php_rocksdb_snapshot_object *obj = Z_ROCKSDB_SNAPSHOT_P(val);
    rocksdb_readoptions_set_snapshot(options, obj->snapshot);
  }

  return options;
}

/* }}} */

/*
static inline void mergeoperator_destructor(void* v) {
  zval *callable = (zval *) v;
  zval_ptr_dtor(callable);
}

static inline char* mergeoperator_full_merge(
  void* v,
  const char* key,
  size_t key_length,
  const char* existing_value,
  size_t existing_value_length,
  const char* const* operands_list,
  const size_t* operands_list_length,
  int num_operands,
  unsigned char* success,
  size_t* new_value_length) {

  char *value = NULL;
  value = "Justinas";
  zval fname, result, params[2];

  zval *val = (zval *) v;

  ZVAL_STRINGL(&fname, "fullMerge", sizeof("fullMerge") - 1);
  ZVAL_STRINGL(&params[0], key, key_length);
  ZVAL_STRINGL(&params[1], existing_value, existing_value_length);


  if (call_user_function(NULL, val, &fname , &result, 3, params TSRMLS_CC) == SUCCESS) {
  }

  *new_value_length = sizeof(value);
  *success = 1;

  return value;
}

static inline char* mergeoperator_partial_merge(
  void* v,
  const char* key,
  size_t key_length,
  const char* const* operands_list,
  const size_t* operands_list_length,
  int num_operands,
  unsigned char* success,
  size_t* new_value_length) {

    char *c = "A";

    return c;
}

static inline void mergeoperator_delete_value(
  void* v,
  const char* value,
  size_t value_length) {

}

static inline const char* mergeoperator_name() {
  const char* c = "MergeOperator2";

  return c;
}
*/

static inline rocksdb_options_t* php_rocksdb_get_open_options(zval *options_zv)
{
  HashTable *ht;
  zval *val;

  rocksdb_options_t *options = rocksdb_options_create();

  if (options_zv == NULL) {
  	return options;
  }

  ht = Z_ARRVAL_P(options_zv);

  if (NULL != (val = zend_hash_str_find(ht,
      "create_if_missing", sizeof("create_if_missing")-1))) {
    rocksdb_options_set_create_if_missing(options, zend_is_true(val));
  }
  if (NULL != (val = zend_hash_str_find(ht,
      "error_if_exists", sizeof("error_if_exists")-1))) {
    rocksdb_options_set_error_if_exists(options, zend_is_true(val));
  }
  if (NULL != (val = zend_hash_str_find(ht,
      "paranoid_checks", sizeof("paranoid_checks")-1))) {
    rocksdb_options_set_error_if_exists(options, zend_is_true(val));
  }
  if (NULL != (val = zend_hash_str_find(ht,
      "write_buffer_size", sizeof("write_buffer_size")-1))) {
    convert_to_long(val);
  	rocksdb_options_set_write_buffer_size(options, Z_LVAL_P(val));
  }
  if (NULL != (val = zend_hash_str_find(ht,
      "max_open_files", sizeof("max_open_files")-1))) {
    convert_to_long(val);
  	rocksdb_options_set_max_open_files(options, Z_LVAL_P(val));
  }
  if (NULL != (val = zend_hash_str_find(ht,
      "compression", sizeof("compression")-1))) {
    convert_to_long(val);
  	if (Z_LVAL_P(val) != rocksdb_no_compression && Z_LVAL_P(val) != rocksdb_snappy_compression) {
  		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid compression type");
  	} else {
  		rocksdb_options_set_compression(options, Z_LVAL_P(val));
  	}
  }
  /*
  if (NULL != (val = zend_hash_str_find(ht,
      "set_merge_operator", sizeof("set_merge_operator")-1))) {

    php_rocksdb_merge_operator_object *merge_operator;

    merge_operator = Z_ROCKSDB_MERGE_OPERATOR_P(val TSRMLS_CC);

    merge_operator->fptr_full_merge = zend_hash_str_find_ptr(&merge_operator->zo.ce->function_table, "fullMerge", sizeof("fullMerge") - 1);
    merge_operator->fptr_partial_merge = zend_hash_str_find_ptr(&merge_operator->zo.ce->function_table, "partialMerge", sizeof("partialMerge") - 1);

    merge_operator->op = rocksdb_mergeoperator_create(val, mergeoperator_destructor, mergeoperator_full_merge, mergeoperator_partial_merge, mergeoperator_delete_value, mergeoperator_name);

    rocksdb_options_set_merge_operator(options, merge_operator->op);
  }
  */
	return options;
}

ZEND_BEGIN_MODULE_GLOBALS(rocksdb)
  zend_bool  create_if_missing;
  zend_long  max_open_files;
  zend_long  write_buffer_size;
  zend_long  max_write_buffer_number;
  zend_long  target_file_size_base;
ZEND_END_MODULE_GLOBALS(rocksdb)

#define ROCKSDB_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(rocksdb, v)

#if defined(ZTS) && defined(COMPILE_DL_ROCKSDB)
ZEND_TSRMLS_CACHE_EXTERN();
#endif

#endif	/* PHP_ROCKSDB_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
