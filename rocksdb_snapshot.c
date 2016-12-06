/*
 * rocksdb_snapshot.c
 *
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

#include "php_rocksdb.h"

zend_class_entry *rocksdb_snapshot_ce;

ZEND_BEGIN_ARG_INFO_EX(rocksdb_snapshot_class__construct_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, db)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_snapshot_class_release_arginfo, 0, 0, 0)
ZEND_END_ARG_INFO()

const zend_function_entry rocksdb_snapshot_class_methods[] = {
	PHP_ME(rocksdb_snapshot, __construct, rocksdb_snapshot_class__construct_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdb_snapshot, release, rocksdb_snapshot_class_release_arginfo, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(rocksdb_snapshot, __construct) {}
PHP_METHOD(rocksdb_snapshot, release) {}