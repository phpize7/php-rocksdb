/*
 * rocksdb_backup.c
 *
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

#include "php_rocksdb.h"

zend_class_entry *rocksdb_backup_engine_ce;

ZEND_BEGIN_ARG_INFO_EX(rocksdb_backup_engine_construct_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(1, path)
	ZEND_ARG_INFO(1, options)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_backup_engine_create_new_backup_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, db)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_backup_engine_restore_db_from_latest_backup_arginfo, 0, 0, 3)
	ZEND_ARG_INFO(0, dir)
	ZEND_ARG_INFO(1, wal)
	ZEND_ARG_INFO(1, options)
ZEND_END_ARG_INFO()

const zend_function_entry rocksdb_backup_engine_class_methods[] = {
	PHP_ME(rocksdb_backup_engine, __construct, rocksdb_backup_engine_construct_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdb_backup_engine, purgeOldBackups, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_backup_engine, createNewBackup, rocksdb_backup_engine_create_new_backup_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_backup_engine, restoreDbFromLatestBackup, rocksdb_backup_engine_restore_db_from_latest_backup_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_backup_engine, getInfoCount, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_backup_engine, getBackupInfo, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_backup_engine, close, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(rocksdb_backup_engine, __construct) {}
PHP_METHOD(rocksdb_backup_engine, purgeOldBackups) {}
PHP_METHOD(rocksdb_backup_engine, createNewBackup) {}
PHP_METHOD(rocksdb_backup_engine, restoreDbFromLatestBackup) {}
PHP_METHOD(rocksdb_backup_engine, getInfoCount) {}
PHP_METHOD(rocksdb_backup_engine, getBackupInfo) {}
PHP_METHOD(rocksdb_backup_engine, close) {}