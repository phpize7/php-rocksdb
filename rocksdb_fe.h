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
extern const zend_function_entry rocksdb_backup_engine_class_methods[];
extern const zend_function_entry rocksdb_backup_engine_info_class_methods[];
extern const zend_function_entry rocksdb_cache_class_methods[];
extern const zend_function_entry rocksdb_iterator_class_methods[];
extern const zend_function_entry rocksdb_snapshot_class_methods[];
extern const zend_function_entry rocksdb_write_batch_class_methods[];
extern const zend_function_entry rocksdb_compaction_filter_interface_methods[];
extern const zend_function_entry rocksdb_comparator_interface_methods[];
extern const zend_function_entry rocksdb_merge_operator_interface_methods[];

// RocksDb class methods
PHP_METHOD(rocksdb, __construct);
PHP_METHOD(rocksdb, open);
PHP_METHOD(rocksdb, openReadOnly);
PHP_METHOD(rocksdb, openColumnFamilies);
PHP_METHOD(rocksdb, openForReadOnlyColumnFamilies);
PHP_METHOD(rocksdb, listColumnFamilies);
PHP_METHOD(rocksdb, createColumnFamily);
PHP_METHOD(rocksdb, dropColumnFamily);
PHP_METHOD(rocksdb, put);
PHP_METHOD(rocksdb, putCf);
PHP_METHOD(rocksdb, delete);
PHP_METHOD(rocksdb, deleteCf);
PHP_METHOD(rocksdb, merge);
PHP_METHOD(rocksdb, mergeCf);
PHP_METHOD(rocksdb, write);
PHP_METHOD(rocksdb, get);
PHP_METHOD(rocksdb, getCf);
PHP_METHOD(rocksdb, getIterator);
PHP_METHOD(rocksdb, getIteratorCf);
PHP_METHOD(rocksdb, createSnapshot);
PHP_METHOD(rocksdb, getProperty);
PHP_METHOD(rocksdb, getPropertyCf);
PHP_METHOD(rocksdb, getApproximateSizes);
PHP_METHOD(rocksdb, getApproximateSizesCf);
PHP_METHOD(rocksdb, flush);
PHP_METHOD(rocksdb, deleteFile);
PHP_METHOD(rocksdb, disableFileDeletions);
PHP_METHOD(rocksdb, enableFileDeletions);
PHP_METHOD(rocksdb, destroy);
PHP_METHOD(rocksdb, repair);
PHP_METHOD(rocksdb, close);

// RocksDb\BackupEngine
PHP_METHOD(rocksdb_backup_engine, __construct);
PHP_METHOD(rocksdb_backup_engine, purgeOldBackups);
PHP_METHOD(rocksdb_backup_engine, createNewBackup);
PHP_METHOD(rocksdb_backup_engine, restoreDbFromLatestBackup);
PHP_METHOD(rocksdb_backup_engine, getInfoCount);
PHP_METHOD(rocksdb_backup_engine, getBackupInfo);
PHP_METHOD(rocksdb_backup_engine, close);

// RocksDb\BackupEngineInfo class methods
PHP_METHOD(rocksdb_backup_engine_info, __construct);
PHP_METHOD(rocksdb_backup_engine_info, getCount);
PHP_METHOD(rocksdb_backup_engine_info, getTimestamp);
PHP_METHOD(rocksdb_backup_engine_info, getBackupId);
PHP_METHOD(rocksdb_backup_engine_info, getSize);
PHP_METHOD(rocksdb_backup_engine_info, getNumFiles);
PHP_METHOD(rocksdb_backup_engine_info, destroy);

// RocksDbCache class methods
PHP_METHOD(rocksdb_cache, __construct);
PHP_METHOD(rocksdb_cache, destroy);

// RocksDb\Iterator class methods
PHP_METHOD(rocksdb_iterator, current);
PHP_METHOD(rocksdb_iterator, key);
PHP_METHOD(rocksdb_iterator, next);
PHP_METHOD(rocksdb_iterator, rewind);
PHP_METHOD(rocksdb_iterator, valid);
PHP_METHOD(rocksdb_iterator, seek);

// RocksDb\Snapshot class methods
PHP_METHOD(rocksdb_snapshot, __construct);
PHP_METHOD(rocksdb_snapshot, release);

// Rocksdb\WriteBatch class methods
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
