/*
 * rocksdb_iterator.c
 *
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

#include "php_rocksdb.h"
#include "rockdb_cache.h"

zend_class_entry *rocksdb_cache_ce;

// Data returns the serialized version of this batch.
ZEND_BEGIN_ARG_INFO_EX(rocksdb_cache_class__construct_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, capacity)
ZEND_END_ARG_INFO()

zend_function_entry rocksdb_cache_class_methods[] = {
	PHP_ME(rocksdbcache, __construct, rocksdb_cache_class__construct_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbcache, destroy, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_FE_END
};

ZEND_MINIT_FUNCTION(rocksdb_iterator) {
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "RocksDbCache", rocksdb_cache_class_methods);

	rocksdb_cache_ce = zend_register_internal_class(&ce);

	return SUCCESS;
}