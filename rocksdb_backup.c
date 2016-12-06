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

ZEND_BEGIN_ARG_INFO_EX(get_count_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(get_timestamp_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(get_backup_id_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(get_size_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(get_num_files_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

const zend_function_entry rocksdb_backup_engine_info_class_methods[] = {
	PHP_ME(rocksdb_backup_engine_info, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdb_backup_engine_info, getCount, get_count_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_backup_engine_info, getTimestamp, get_timestamp_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_backup_engine_info, getBackuoId, get_backup_id_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_backup_engine_info, getSize, get_size_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_backup_engine_info, getNumFiles, get_num_files_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_backup_engine_info, destroy, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(rocksdb_backup_engine_info, __construct) {}
PHP_METHOD(rocksdb_backup_engine_info, getCount) {}
PHP_METHOD(rocksdb_backup_engine_info, getTimestamp) {}
PHP_METHOD(rocksdb_backup_engine_info, getBackuoId) {}
PHP_METHOD(rocksdb_backup_engine_info, getSize) {}
PHP_METHOD(rocksdb_backup_engine_info, getNumFiles) {}
PHP_METHOD(rocksdb_backup_engine_info, destroy) {}