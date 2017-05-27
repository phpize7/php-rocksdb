/*
 * rocksdb_iterator.c
 *
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

#include "php_rocksdb.h"

zend_class_entry *rocksdb_iterator_ce;

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class__construct_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, db)
	ZEND_ARG_INFO(0, read_options)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_iterator_class_seek_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

const zend_function_entry rocksdb_iterator_class_methods[] = {
	PHP_ME(rocksdb_iterator, __construct, rocksdb_class__construct_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdb_iterator, current, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_iterator, key, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_iterator, next, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_iterator, rewind, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_iterator, valid, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_iterator, seek, rocksdb_iterator_class_seek_arginfo, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(rocksdb_iterator, __construct) {
	zval *db_zv = NULL;
	php_rocksdb_db_object *db_obj;
	zval *readoptions_zv = NULL;

	php_rocksdb_iterator_object *intern;
	rocksdb_readoptions_t *readoptions;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O|z",
			&db_zv, rocksdb_ce, &readoptions_zv) == FAILURE) {
		return;
	}

	intern = Z_ROCKSDB_ITERATOR_P(getThis() TSRMLS_CC);
	db_obj = Z_ROCKSDB_DB_P(db_zv);

	readoptions = php_rocksdb_get_read_options(readoptions_zv);
	intern->iterator = rocksdb_create_iterator(db_obj->db, readoptions);
	rocksdb_readoptions_destroy(readoptions);

	intern->db = db_zv;

	rocksdb_iter_seek_to_first(intern->iterator);
}
PHP_METHOD(rocksdb_iterator, current) {
	char *value = NULL;
	size_t value_len;
	php_rocksdb_iterator_object *intern;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	intern = Z_ROCKSDB_ITERATOR_P(getThis() TSRMLS_CC);

	if (!rocksdb_iter_valid(intern->iterator) ||
			!(value = (char *)rocksdb_iter_value(intern->iterator, &value_len))) {
		RETURN_FALSE;
	}

	RETVAL_STRINGL(value, value_len);
}
PHP_METHOD(rocksdb_iterator, key) {
	char *key = NULL;
	size_t key_len;
	php_rocksdb_iterator_object *intern;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	intern = Z_ROCKSDB_ITERATOR_P(getThis() TSRMLS_CC);

	if (!rocksdb_iter_valid(intern->iterator) ||
			!(key = (char *)rocksdb_iter_key(intern->iterator, &key_len))) {
		RETURN_FALSE;
	}

	RETVAL_STRINGL(key, key_len);
}
PHP_METHOD(rocksdb_iterator, next) {
	php_rocksdb_iterator_object *intern;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	intern = Z_ROCKSDB_ITERATOR_P(getThis() TSRMLS_CC);

	if (rocksdb_iter_valid(intern->iterator)) {
		rocksdb_iter_next(intern->iterator);
	}
}
PHP_METHOD(rocksdb_iterator, rewind) {
	php_rocksdb_iterator_object *intern;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	intern = Z_ROCKSDB_ITERATOR_P(getThis() TSRMLS_CC);

	if (rocksdb_iter_valid(intern->iterator)) {
		rocksdb_iter_prev(intern->iterator);
	}
}
PHP_METHOD(rocksdb_iterator, valid) {
	php_rocksdb_iterator_object *intern;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	intern = Z_ROCKSDB_ITERATOR_P(getThis() TSRMLS_CC);

	RETVAL_BOOL(rocksdb_iter_valid(intern->iterator));
}
PHP_METHOD(rocksdb_iterator, seek) {
	char *key;
	int key_len;
	php_rocksdb_iterator_object *intern;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &key, &key_len ) == FAILURE) {
		return;
	}

	intern = Z_ROCKSDB_ITERATOR_P(getThis() TSRMLS_CC);

	rocksdb_iter_seek(intern->iterator, key, (size_t) key_len);
}
