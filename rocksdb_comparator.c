/*
 * rocksdb_iterator.c
 *
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

#include "php_rocksdb.h"

zend_class_entry *rocksdb_comparator_ce;

ZEND_BEGIN_ARG_INFO_EX(rocksdb_comparator_compare_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, a)
	ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

const zend_function_entry rocksdb_comparator_interface_methods[] = {
	PHP_ABSTRACT_ME(rocksdb_comparator, compare, rocksdb_comparator_compare_arginfo)
	PHP_ABSTRACT_ME(rocksdb_comparator, getName, NULL)
	PHP_FE_END
};