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

// Data returns the serialized version of this batch.
ZEND_BEGIN_ARG_INFO_EX(rocksdb_iterator_class_seek_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

const zend_function_entry rocksdb_iterator_class_methods[] = {
	PHP_ME(rocksdb_iterator, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdb_iterator, valid, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_iterator, key, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_iterator, value, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_iterator, next, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_iterator, prev, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_iterator, seekToFirst, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_iterator, seekToLast, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_iterator, seek, rocksdb_iterator_class_seek_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_iterator, error, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_iterator, close, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(rocksdb_iterator, __construct) {}
PHP_METHOD(rocksdb_iterator, valid) {}
PHP_METHOD(rocksdb_iterator, key) {}
PHP_METHOD(rocksdb_iterator, value) {}
PHP_METHOD(rocksdb_iterator, next) {}
PHP_METHOD(rocksdb_iterator, prev) {}
PHP_METHOD(rocksdb_iterator, seekToFirst) {}
PHP_METHOD(rocksdb_iterator, seekToLast) {}
PHP_METHOD(rocksdb_iterator, seek) {}
PHP_METHOD(rocksdb_iterator, error) {}
PHP_METHOD(rocksdb_iterator, close) {}