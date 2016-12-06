/*
 * rocksdb_iterator.c
 *
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

#include "php_rocksdb.h"

zend_class_entry *rocksdb_cache_ce;

ZEND_BEGIN_ARG_INFO_EX(rocksdb_cache_class__construct_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, capacity)
ZEND_END_ARG_INFO()

const zend_function_entry rocksdb_cache_class_methods[] = {
	PHP_ME(rocksdb_cache, __construct, rocksdb_cache_class__construct_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdb_cache, destroy, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(rocksdb_cache, __construct) {}
PHP_METHOD(rocksdb_cache, destroy) {}