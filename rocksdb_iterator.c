/*
 * rocksdb_iterator.c
 *
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

#include "php_rocksdb.h"
#include "rocksdb_iterator.h"

zend_class_entry *rocksdb_iterator_ce;

// Data returns the serialized version of this batch.
ZEND_BEGIN_ARG_INFO_EX(rocksdb_iterator_class_seek_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

zend_function_entry rocksdb_iterator_class_methods[] = {
	PHP_ME(rocksdbiterator, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbiterator, valid, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbiterator, key, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbiterator, value, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbiterator, next, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbiterator, prev, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbiterator, seekToFirst, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbiterator, seekToLast, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbiterator, seek, rocksdb_iterator_class_seek_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbiterator, error, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdbiterator, close, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_FE_END
};

ZEND_MINIT_FUNCTION(rocksdb_iterator) {
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "RocksDbIterator", rocksdb_iterator_class_methods);

	rocksdb_iterator_ce = zend_register_internal_class(&ce);

	return SUCCESS;
}