/*
 * rocksdb_snapshot.c
 *
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

#include "php_rocksdb.h"
#include "rocksdb_snapshot.h"

zend_class_entry *rocksdb_snapshot_ce;

ZEND_BEGIN_ARG_INFO_EX(rocksdb_snapshot_class__construct_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, db)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_snapshot_class_release_arginfo, 0, 0, 0)
ZEND_END_ARG_INFO()

zend_function_entry rocksdb_snapshot_class_methods[] = {
	PHP_ME(rocksdb, __construct, rocksdb_snapshot_class__construct_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdb, release, rocksdb_snapshot_class_release_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_FE_END
};

ZEND_MINIT_FUNCTION(rocksdb_snapshot) {
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "RocksDbSnapshot", rocksdb_snapshot_class_methods);

	rocksdb_snapshot_ce = zend_register_internal_class(&ce);

	return SUCCESS;
}