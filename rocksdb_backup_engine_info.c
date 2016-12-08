/*
 * rocksdb_backup.c
 *
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

#include "php_rocksdb.h"

zend_class_entry *rocksdb_backup_engine_info_ce;

ZEND_BEGIN_ARG_INFO_EX(rocksdb_backup_engine_info_get_count_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_backup_engine_info_get_timestamp_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_backup_engine_info_get_backup_id_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_backup_engine_info_get_size_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_backup_engine_info_get_num_files_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

const zend_function_entry rocksdb_backup_engine_info_class_methods[] = {
	PHP_ME(rocksdb_backup_engine_info, getCount, rocksdb_backup_engine_info_get_count_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_backup_engine_info, getTimestamp, rocksdb_backup_engine_info_get_timestamp_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_backup_engine_info, getBackupId, rocksdb_backup_engine_info_get_backup_id_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_backup_engine_info, getSize, rocksdb_backup_engine_info_get_size_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_backup_engine_info, getNumFiles, rocksdb_backup_engine_info_get_num_files_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_backup_engine_info, destroy, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(rocksdb_backup_engine_info, getCount) {}
PHP_METHOD(rocksdb_backup_engine_info, getTimestamp) {}
PHP_METHOD(rocksdb_backup_engine_info, getBackupId) {}
PHP_METHOD(rocksdb_backup_engine_info, getSize) {}
PHP_METHOD(rocksdb_backup_engine_info, getNumFiles) {}
PHP_METHOD(rocksdb_backup_engine_info, destroy) {}