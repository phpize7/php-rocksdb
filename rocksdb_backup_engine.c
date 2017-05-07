/*
 * rocksdb_backup.c
 *
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "zend_exceptions.h"
#include "Zend/zend_interfaces.h"
#include "php_rocksdb.h"

zend_class_entry *rocksdb_backup_engine_ce;

ZEND_BEGIN_ARG_INFO_EX(rocksdb_backup_engine_construct_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, path)
	ZEND_ARG_INFO(0, options)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_backup_engine_create_new_backup_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, db)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_backup_engine_restore_db_from_latest_backup_arginfo, 0, 0, 3)
	ZEND_ARG_INFO(0, dir)
	ZEND_ARG_INFO(0, wal)
	ZEND_ARG_INFO(0, options)
ZEND_END_ARG_INFO()

const zend_function_entry rocksdb_backup_engine_class_methods[] = {
	PHP_ME(rocksdb_backup_engine, __construct, rocksdb_backup_engine_construct_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdb_backup_engine, purgeOldBackups, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_backup_engine, createNewBackup, rocksdb_backup_engine_create_new_backup_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_backup_engine, restoreDbFromLatestBackup, rocksdb_backup_engine_restore_db_from_latest_backup_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_backup_engine, getBackupInfo, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_backup_engine, close, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(rocksdb_backup_engine, __construct) {
	const char *name = NULL;
	char *err = NULL;
	size_t name_len;
	zval *options_zv = NULL;
	php_rocksdb_backup_engine_object *this = NULL;
	rocksdb_options_t *options = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|a",
			&name, &name_len, &options_zv) == FAILURE) {
			return;
	}

	this = Z_ROCKSDB_BACKUP_ENGINE_P(getThis() TSRMLS_CC);

	options = php_rocksdb_get_open_options(options_zv);
	this->be = rocksdb_backup_engine_open(options, name, &err);
	rocksdb_options_destroy(options);

	if (err != NULL) {
		zend_throw_exception(zend_ce_exception, err, 0);
		return;
	}
}
PHP_METHOD(rocksdb_backup_engine, purgeOldBackups) {
	char *err = NULL;
	zend_ulong num;
	php_rocksdb_backup_engine_object *this;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &num) == FAILURE) {
		return;
	}

	this = Z_ROCKSDB_BACKUP_ENGINE_P(getThis() TSRMLS_CC);
	rocksdb_backup_engine_purge_old_backups(this->be, num, &err);

	if (err != NULL) {
		zend_throw_exception(zend_ce_exception, err, 0);
		return;
	}
}
PHP_METHOD(rocksdb_backup_engine, createNewBackup) {
	char *err = NULL;
	zval *rocks_zv = NULL;
	php_rocksdb_db_object *rocks;
	php_rocksdb_backup_engine_object *this;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O",
			&rocks_zv, rocksdb_ce) == FAILURE) {
			return;
	}

	rocks = Z_ROCKSDB_DB_P(rocks_zv TSRMLS_CC);
	this = Z_ROCKSDB_BACKUP_ENGINE_P(getThis() TSRMLS_CC);

	rocksdb_backup_engine_create_new_backup(this->be, rocks->db, &err);

	if (err != NULL) {
		zend_throw_exception(zend_ce_exception, err, 0);
		return;
	}
}
PHP_METHOD(rocksdb_backup_engine, restoreDbFromLatestBackup) {
	char *db_dir, *wal_dir, *err = NULL;
	size_t db_dir_len, wal_dir_len;
	zval *restore_options_zv = NULL;
	rocksdb_restore_options_t *restore_options;
	php_rocksdb_backup_engine_object *this;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss|a",
			&db_dir, &db_dir_len, &wal_dir, &wal_dir_len, &restore_options_zv) == FAILURE) {
			return;
	}

	restore_options = php_rocksdb_get_restore_options(restore_options_zv);
	this = Z_ROCKSDB_BACKUP_ENGINE_P(getThis() TSRMLS_CC);

	rocksdb_backup_engine_restore_db_from_latest_backup(this->be, (const char *) db_dir, (const char *) wal_dir, restore_options, &err);

	if (err != NULL) {
		zend_throw_exception(zend_ce_exception, err, 0);
		return;
	}
}
PHP_METHOD(rocksdb_backup_engine, getBackupInfo) {
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	object_init_ex(return_value, rocksdb_backup_engine_info_ce);

	zend_call_method_with_1_params(return_value, rocksdb_backup_engine_info_ce,
		&rocksdb_backup_engine_info_ce->constructor, "__construct", NULL, getThis());
}
PHP_METHOD(rocksdb_backup_engine, close) {
	php_rocksdb_backup_engine_object *this;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	this = Z_ROCKSDB_BACKUP_ENGINE_P(getThis() TSRMLS_CC);

	rocksdb_backup_engine_close(this->be);
	this->be = NULL;
}
