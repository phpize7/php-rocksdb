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

ZEND_BEGIN_ARG_INFO_EX(rocksdb_snapshot_class__construct_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, db)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_snapshot_class_release_arginfo, 0, 0, 0)
ZEND_END_ARG_INFO()

const zend_function_entry rocksdb_snapshot_class_methods[] = {
	PHP_ME(rocksdb_snapshot, __construct, rocksdb_snapshot_class__construct_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdb_snapshot, release, rocksdb_snapshot_class_release_arginfo, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(rocksdb_snapshot, __construct) {
	zval *db_zv = NULL;
	php_rocksdb_db_object *db_obj;
	php_rocksdb_snapshot_object *intern;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O",
			&db_zv, rocksdb_ce) == FAILURE) {
		return;
	}

	intern = Z_ROCKSDB_SNAPSHOT_P(getThis() TSRMLS_CC);
	db_obj = Z_ROCKSDB_DB_P(db_zv TSRMLS_CC);

	intern->snapshot = (rocksdb_snapshot_t *)rocksdb_create_snapshot(db_obj->db);

	intern->db = db_zv;
}
PHP_METHOD(rocksdb_snapshot, release) {
	php_rocksdb_snapshot_object *intern;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	intern = Z_ROCKSDB_SNAPSHOT_P(getThis() TSRMLS_CC);

	if (!intern->db) {
		return;
	}

	php_rocksdb_db_object *db = Z_ROCKSDB_DB_P(intern->db TSRMLS_CC);
	rocksdb_release_snapshot(db->db, intern->snapshot);

	intern->snapshot = NULL;
	intern->db = NULL;
}
