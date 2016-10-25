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
   | Authors: Justinas Petrulis <justinas.petrulis@gmail.com>             |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_SQLITE_STRUCTS_H
#define PHP_SQLITE_STRUCTS_H

#include <sqlite3.h>

/* Structure for RocksDb Database object. */
typedef struct _php_rocksdb_db_object {
  int initialized;
  rocksdb_t *db;

  zend_bool exception;
  zend_object zo;
} php_rocksdb_db_object;

static inline php_rocksdb_db_object *php_rocksdb_db_from_obj(zend_object *obj) {
	return (php_sqlite3_db_object*)((char*)(obj) - XtOffsetOf(php_sqlite3_db_object, zo));
}

#define Z_ROCKSDB_DB_P(zv) php_rocksdb_db_from_obj(Z_OBJ_P((zv)))

#endif


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */
