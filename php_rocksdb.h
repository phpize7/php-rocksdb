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
  rocksdb_t *db;

  zend_bool exception;
  zend_object zo;
} php_rocksdb_db_object;

#define PHP_ROCKSDB_REGISTER_CLASS_CONSTANT(class_entry, const_name, value) \
  zend_declare_class_constant_long(class_entry, const_name, sizeof(const_name)-1, (zend_long)value);

static inline php_rocksdb_db_object *php_rocksdb_db_from_obj(zend_object *obj) {
  return (php_rocksdb_db_object*)((char*)(obj) - XtOffsetOf(php_rocksdb_db_object, zo));
}

#define Z_ROCKSDB_DB_P(zv) php_rocksdb_db_from_obj(Z_OBJ_P((zv)))

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
