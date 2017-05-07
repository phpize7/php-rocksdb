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

ZEND_BEGIN_ARG_INFO_EX(rocksdb_backup_engine_info__construct_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, db)
ZEND_END_ARG_INFO()

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
	PHP_ME(rocksdb_backup_engine_info, __construct, rocksdb_backup_engine_info__construct_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdb_backup_engine_info, getCount, rocksdb_backup_engine_info_get_count_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_backup_engine_info, getTimestamp, rocksdb_backup_engine_info_get_timestamp_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_backup_engine_info, getBackupId, rocksdb_backup_engine_info_get_backup_id_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_backup_engine_info, getSize, rocksdb_backup_engine_info_get_size_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_backup_engine_info, getNumFiles, rocksdb_backup_engine_info_get_num_files_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_backup_engine_info, destroy, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(rocksdb_backup_engine_info, __construct) {
	zval *be_zv = NULL;
	php_rocksdb_backup_engine_object *backup_engine;
	php_rocksdb_backup_engine_info_object *this;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &be_zv, rocksdb_backup_engine_ce) == FAILURE) {
			return;
	}

	this = Z_ROCKSDB_BACKUP_ENGINE_INFO_P(getThis() TSRMLS_CC);
	backup_engine = Z_ROCKSDB_BACKUP_ENGINE_P(be_zv TSRMLS_CC);

	this->info = rocksdb_backup_engine_get_backup_info(backup_engine->be);
}
PHP_METHOD(rocksdb_backup_engine_info, getCount) {
	php_rocksdb_backup_engine_info_object *this;
	this = Z_ROCKSDB_BACKUP_ENGINE_INFO_P(getThis() TSRMLS_CC);

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	int c = rocksdb_backup_engine_info_count(this->info);

	RETVAL_LONG(c);
}
PHP_METHOD(rocksdb_backup_engine_info, getTimestamp) {
	char *index;
	size_t index_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &index, &index_len) == FAILURE) {
			return;
	}

	php_rocksdb_backup_engine_info_object *this;
	this = Z_ROCKSDB_BACKUP_ENGINE_INFO_P(getThis() TSRMLS_CC);

	int i = atoi(index);
	int64_t retval = rocksdb_backup_engine_info_timestamp(this->info, i);

	RETVAL_LONG(retval);
}
PHP_METHOD(rocksdb_backup_engine_info, getBackupId) {
	char *index;
	size_t index_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &index, &index_len) == FAILURE) {
			return;
	}

	php_rocksdb_backup_engine_info_object *this;
	this = Z_ROCKSDB_BACKUP_ENGINE_INFO_P(getThis() TSRMLS_CC);

	int i = atoi(index);
	int64_t retval = rocksdb_backup_engine_info_backup_id(this->info, i);

	RETVAL_LONG(retval);
}
PHP_METHOD(rocksdb_backup_engine_info, getSize) {
	char *index;
	size_t index_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &index, &index_len) == FAILURE) {
			return;
	}

	php_rocksdb_backup_engine_info_object *this;
	this = Z_ROCKSDB_BACKUP_ENGINE_INFO_P(getThis() TSRMLS_CC);

	int i = atoi(index);
	int64_t retval = rocksdb_backup_engine_info_size(this->info, i);

	RETVAL_LONG(retval);
}
PHP_METHOD(rocksdb_backup_engine_info, getNumFiles) {
	char *index;
	size_t index_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &index, &index_len) == FAILURE) {
			return;
	}

	php_rocksdb_backup_engine_info_object *this;
	this = Z_ROCKSDB_BACKUP_ENGINE_INFO_P(getThis() TSRMLS_CC);

	int i = atoi(index);
	uint32_t retval = rocksdb_backup_engine_info_number_files(this->info, i);

	RETVAL_LONG(retval);
}
PHP_METHOD(rocksdb_backup_engine_info, destroy) {
	if (zend_parse_parameters_none() == FAILURE) {
			return;
	}

	php_rocksdb_backup_engine_info_object *this;
	this = Z_ROCKSDB_BACKUP_ENGINE_INFO_P(getThis() TSRMLS_CC);

	rocksdb_backup_engine_info_destroy(this->info);

	RETURN_TRUE;
}
