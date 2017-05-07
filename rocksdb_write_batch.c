/*
 * rocksdb_write_batch.c
 *
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

#include "php_rocksdb.h"

zend_class_entry *rocksdb_write_batch_ce;

ZEND_BEGIN_ARG_INFO_EX(rocksdb_write_batch_class_create_from_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, bytes)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_write_batch_class_put_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_write_batch_class_put_cf_arginfo, 0, 0, 3)
	ZEND_ARG_INFO(0, cf)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_write_batch_class_merge_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_write_batch_class_merge_cf_arginfo, 0, 0, 3)
	ZEND_ARG_INFO(0, cf)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_write_batch_class_delete_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_write_batch_class_delete_cf_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, cf)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

const zend_function_entry rocksdb_write_batch_class_methods[] = {
	PHP_ME(rocksdb_write_batch, __construct, NULL,  ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdb_write_batch, createFrom, rocksdb_write_batch_class_create_from_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_write_batch, put, rocksdb_write_batch_class_put_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_write_batch, putCf, rocksdb_write_batch_class_put_cf_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_write_batch, merge, rocksdb_write_batch_class_merge_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_write_batch, mergeCf, rocksdb_write_batch_class_merge_cf_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_write_batch, delete, rocksdb_write_batch_class_delete_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_write_batch, deleteCf, rocksdb_write_batch_class_delete_cf_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_write_batch, data, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_write_batch, count, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_write_batch, getIterator, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_write_batch, clear, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_write_batch, destroy, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(rocksdb_write_batch, __construct) {
	php_rocksdb_write_batch_object *this;
	rocksdb_writebatch_t *batch;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	this = Z_ROCKSDB_WRITE_BATCH_P(getThis() TSRMLS_CC);
	batch = rocksdb_writebatch_create();

	this->batch = batch;
}
PHP_METHOD(rocksdb_write_batch, createFrom) {}
PHP_METHOD(rocksdb_write_batch, put) {
	char *key, *value;
	size_t key_len, value_len;

	php_rocksdb_write_batch_object *this;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss",
			&key, &key_len, &value, &value_len) == FAILURE) {
		return;
	}

	this = Z_ROCKSDB_WRITE_BATCH_P(getThis() TSRMLS_CC);
	rocksdb_writebatch_put(this->batch, key, key_len, value, value_len);

	RETURN_TRUE;
}
PHP_METHOD(rocksdb_write_batch, putCf) {
}
PHP_METHOD(rocksdb_write_batch, merge) {
	char *key, *value;
	size_t key_len, value_len;

	php_rocksdb_write_batch_object *this;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss",
			&key, &key_len, &value, &value_len) == FAILURE) {
		return;
	}

	this = Z_ROCKSDB_WRITE_BATCH_P(getThis() TSRMLS_CC);
	rocksdb_writebatch_merge(this->batch, (const char *) key, key_len, (const char *) value, value_len);

	RETURN_TRUE;
}
PHP_METHOD(rocksdb_write_batch, mergeCf) {

}
PHP_METHOD(rocksdb_write_batch, delete) {
	char *key;
	size_t key_len;

	php_rocksdb_write_batch_object *this;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &key, &key_len) == FAILURE) {
		return;
	}

	this = Z_ROCKSDB_WRITE_BATCH_P(getThis() TSRMLS_CC);
	rocksdb_writebatch_delete(this->batch, key, key_len);
}
PHP_METHOD(rocksdb_write_batch, deleteCf) {}
PHP_METHOD(rocksdb_write_batch, data) {
	const char *value;
	size_t *size, size_len;
	php_rocksdb_write_batch_object *this;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &size, &size_len) == FAILURE) {
		return;
	}

	this = Z_ROCKSDB_WRITE_BATCH_P(getThis() TSRMLS_CC);
	value = rocksdb_writebatch_data(this->batch, size);

	RETVAL_STRINGL(value, size_len);
}
PHP_METHOD(rocksdb_write_batch, count) {}
PHP_METHOD(rocksdb_write_batch, getIterator) {}
PHP_METHOD(rocksdb_write_batch, clear) {
	php_rocksdb_write_batch_object *this;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	this = Z_ROCKSDB_WRITE_BATCH_P(getThis() TSRMLS_CC);
	rocksdb_writebatch_clear(this->batch);

	RETURN_TRUE;
}
PHP_METHOD(rocksdb_write_batch, destroy) {
	php_rocksdb_write_batch_object *this;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	this = Z_ROCKSDB_WRITE_BATCH_P(getThis() TSRMLS_CC);
	rocksdb_writebatch_destroy(this->batch);

	RETURN_TRUE;
}
