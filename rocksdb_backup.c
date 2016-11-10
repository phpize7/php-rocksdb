/*
 * rocksdb_backup.c
 *
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

#include "php_rocksdb.h"
#include "rocksdb_backup.h"

zend_class_entry *rocksdb_backup_engine_info_ce;

ZEND_BEGIN_ARG_INFO_EX(get_count_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, index)
ZEND

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

zend_function_entry rocksdb_backup_engine_info_class_methods[] = {
	PHP_ME(rocksdbbackupengine_info, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbbackupengineinfo, getCount, get_count_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbbackupengineinfo, getTimestamp, get_timestamp_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbbackupengineinfo, getBackuoId, get_backuo_id_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbbackupengineinfo, getSize, get_size_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbbackupengineinfo, getNumFiles, get_num_files_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbbackupengineinfo, destroy, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_FE_END
}

ZEND_MINIT_FUNCTION(rocksdb_iterator) {
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "RocksDbBackupEngineInfo", rocksdb_backup_engine_info_class_methods);

	rocksdb_backup_engine_info_ce = zend_register_internal_class(&ce);

	return SUCCESS;
}