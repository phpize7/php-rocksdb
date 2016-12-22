/*
 * rocksdb_iterator.c
 *
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

#include "php_rocksdb.h"

zend_class_entry *rocksdb_compaction_filter_ce;

ZEND_BEGIN_ARG_INFO_EX(rocksdb_compaction_filter_filter_arginfo, 0, 0, 8)
	ZEND_ARG_INFO(0, level)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, key_length)
	ZEND_ARG_INFO(0, existing_value)
	ZEND_ARG_INFO(0, value_length)
	ZEND_ARG_INFO(0, new_value)
	ZEND_ARG_INFO(0, new_value_length)
	ZEND_ARG_INFO(0, value_changes)
ZEND_END_ARG_INFO()

const zend_function_entry rocksdb_compaction_filter_interface_methods[] = {
	PHP_ABSTRACT_ME(rocksdb_compaction_filter, filter, rocksdb_compaction_filter_filter_arginfo)
	PHP_ABSTRACT_ME(rocksdb_compaction_filter, getName, NULL)
	PHP_FE_END
};
