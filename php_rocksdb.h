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

/* Register constant for options and errors */
#define PHP_ROCKSDB_REGISTER_CONSTANT(_name, _value) \
  REGISTER_LONG_CONSTANT(_name,  _value, CONST_CS | CONST_PERSISTENT);


ZEND_BEGIN_MODULE_GLOBALS(rocksdb)
  char       *create_if_missing;
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
