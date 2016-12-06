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
#ifndef ROCKSDB_FE_H
#define ROCKSDB_FE_H

extern const zend_function_entry rocksdb_class_methods[];
extern const zend_function_entry rocksdb_backup_engine_info_class_methods[];
extern const zend_function_entry rocksdb_cache_class_methods[];
extern const zend_function_entry rocksdb_iterator_class_methods[];
extern const zend_function_entry rocksdb_snapshot_class_methods[];
extern const zend_function_entry rocksdb_write_batch_class_methods[];


// RocksDb class methods
PHP_METHOD(rocksdb, __construct);

// RocksDbBackupEngineInfo class methods
PHP_METHOD(rocksdb_backup_engine_info, __construct);
PHP_METHOD(rocksdb_backup_engine_info, getCount);
PHP_METHOD(rocksdb_backup_engine_info, getTimestamp);
PHP_METHOD(rocksdb_backup_engine_info, getBackuoId);
PHP_METHOD(rocksdb_backup_engine_info, getSize);
PHP_METHOD(rocksdb_backup_engine_info, getNumFiles);
PHP_METHOD(rocksdb_backup_engine_info, destroy);

// RocksDbCache class methods
PHP_METHOD(rocksdb_cache, __construct);
PHP_METHOD(rocksdb_cache, destroy);

// RocksDbIterator class methods
PHP_METHOD(rocksdb_iterator, __construct);
PHP_METHOD(rocksdb_iterator, valid);
PHP_METHOD(rocksdb_iterator, key);
PHP_METHOD(rocksdb_iterator, value);
PHP_METHOD(rocksdb_iterator, next);
PHP_METHOD(rocksdb_iterator, prev);
PHP_METHOD(rocksdb_iterator, seekToFirst);
PHP_METHOD(rocksdb_iterator, seekToLast);
PHP_METHOD(rocksdb_iterator, seek);
PHP_METHOD(rocksdb_iterator, error);
PHP_METHOD(rocksdb_iterator, close);

// RocksDbSnapshot class methods
PHP_METHOD(rocksdb_snapshot, __construct);
PHP_METHOD(rocksdb_snapshot, release);

// rocksdb_write_batch class methods
PHP_METHOD(rocksdb_write_batch, __construct);
PHP_METHOD(rocksdb_write_batch, createFrom);
PHP_METHOD(rocksdb_write_batch, put);
PHP_METHOD(rocksdb_write_batch, putCf);
PHP_METHOD(rocksdb_write_batch, merge);
PHP_METHOD(rocksdb_write_batch, mergeCf);
PHP_METHOD(rocksdb_write_batch, delete);
PHP_METHOD(rocksdb_write_batch, deleteCf);
PHP_METHOD(rocksdb_write_batch, data);
PHP_METHOD(rocksdb_write_batch, count);
PHP_METHOD(rocksdb_write_batch, getIterator);
PHP_METHOD(rocksdb_write_batch, clear);
PHP_METHOD(rocksdb_write_batch, destroy);

#endif /* ROCKSDB_FE_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
