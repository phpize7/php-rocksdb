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

ZEND_BEGIN_ARG_INFO_EX(rocksdb_iterator_class_seek_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

const zend_function_entry rocksdb_iterator_class_methods[] = {
	PHP_ME(rocksdb_iterator, current, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_iterator, key, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_iterator, next, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_iterator, rewind, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_iterator, valid, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb_iterator, seek, rocksdb_iterator_class_seek_arginfo, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(rocksdb_iterator, current) {}
PHP_METHOD(rocksdb_iterator, key) {}
PHP_METHOD(rocksdb_iterator, next) {}
PHP_METHOD(rocksdb_iterator, rewind) {}
PHP_METHOD(rocksdb_iterator, valid) {}
PHP_METHOD(rocksdb_iterator, seek) {}