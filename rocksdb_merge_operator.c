/*
 * rocksdb_iterator.c
 *
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

#include "php_rocksdb.h"

zend_class_entry *rocksdb_merge_operator_ce;

ZEND_BEGIN_ARG_INFO_EX(rocksdb_merge_operator_full_merge_arginfo, 0, 0, 3)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, existing_value)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_merge_operator_partial_merge_arginfo, 0, 0, 3)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, left_operand)
	ZEND_ARG_INFO(0, right_operand)
ZEND_END_ARG_INFO()

const zend_function_entry rocksdb_merge_operator_interface_methods[] = {
	PHP_ABSTRACT_ME(rocksdb_merge_operator, fullMerge, rocksdb_merge_operator_full_merge_arginfo)
	PHP_ABSTRACT_ME(rocksdb_merge_operator, partialMerge, rocksdb_merge_operator_partial_merge_arginfo)
	PHP_ABSTRACT_ME(rocksdb_merge_operator, getName, NULL)
	PHP_FE_END
};
