/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "ext/spl/spl_iterators.h"
#include "ext/spl/spl_exceptions.h"
#include "rocksdb/c.h"
#include "Zend/zend_types.h"
#include "zend_exceptions.h"
#include "stdbool.h"
#include "php_rocksdb.h"

ZEND_DECLARE_MODULE_GLOBALS(rocksdb);

static zend_object_handlers rocksdb_default_handlers;
static zend_object_handlers rocksdb_iterator_handlers;
static zend_object_handlers rocksdb_backup_engine_info_handlers;

static zend_object* php_rocksdb_object_new(zend_class_entry *ce)
{
  php_rocksdb_db_object *obj;

  obj = emalloc(sizeof(*obj));
  memset(obj, 0, sizeof(*obj));

  zend_object_std_init(&obj->zo, ce);
  obj->zo.handlers = &rocksdb_default_handlers;

  return &obj->zo;
}

static zend_object* php_rocksdb_iterator_object_new(zend_class_entry *ce)
{
  php_rocksdb_iterator_object *obj;

  obj = emalloc(sizeof(*obj));
  memset(obj, 0, sizeof(*obj));

  zend_object_std_init(&obj->zo, ce);
  obj->zo.handlers = &rocksdb_iterator_handlers;

  return &obj->zo;
}

static zend_object* php_rocksdb_backup_engine_info_object_new(zend_class_entry *ce)
{
  php_rocksdb_backup_engine_info_object *obj;

  obj = emalloc(sizeof(*obj));
  memset(obj, 0, sizeof(*obj));

  zend_object_std_init(&obj->zo, ce);
  obj->zo.handlers = &rocksdb_backup_engine_info_handlers;

  return &obj->zo;
}


static void rocksdb_free_storage(zend_object *obj)
{
	php_rocksdb_db_object *object = (php_rocksdb_db_object*) obj;

  if (object->db) {
    rocksdb_close(object->db);
  }
  //efree(object->name);
  efree(object->handles);
}

static void php_rocksdb_register_classes()
{
	zend_class_entry ce,
		ce_backup_info,
		ce_compaction_filter,
		ce_iterator,
		ce_comparator,
		ce_merge_operator,
		ce_snapshot,
		ce_write_batch,
		ce_backup_engine,
		ce_exception;

	memcpy(&rocksdb_default_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
  rocksdb_default_handlers.offset = XtOffsetOf(php_rocksdb_db_object, zo);
	rocksdb_default_handlers.free_obj = rocksdb_free_storage;
	INIT_CLASS_ENTRY(ce, ZEND_NS_NAME("RocksDb", "RocksDb"), rocksdb_class_methods);
  ce.create_object = php_rocksdb_object_new;
	rocksdb_ce = zend_register_internal_class(&ce);

	INIT_CLASS_ENTRY(ce_backup_engine, ZEND_NS_NAME("RocksDb", "BackupEngine"), rocksdb_backup_engine_class_methods);
	rocksdb_backup_engine_ce = zend_register_internal_class(&ce_backup_engine);

  memcpy(&rocksdb_backup_engine_info_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
  rocksdb_backup_engine_info_handlers.offset = XtOffsetOf(php_rocksdb_backup_engine_info_object, zo);
  //rocksdb_beckup_engine_info_handlers.free_obj = rocksdb_free_storage;
	INIT_CLASS_ENTRY(ce_backup_info, ZEND_NS_NAME("RocksDb", "BackupEngineInfo"), rocksdb_backup_engine_info_class_methods);
  ce_backup_info.create_object = php_rocksdb_backup_engine_info_object_new;
	rocksdb_backup_engine_info_ce = zend_register_internal_class(&ce_backup_info);

	INIT_CLASS_ENTRY(ce_snapshot, ZEND_NS_NAME("RocksDb", "Snapshot"), rocksdb_snapshot_class_methods);
	rocksdb_snapshot_ce = zend_register_internal_class(&ce_snapshot);

	INIT_CLASS_ENTRY(ce_write_batch, ZEND_NS_NAME("RocksDb", "WriteBatch"), rocksdb_write_batch_class_methods);
	rocksdb_write_batch_ce = zend_register_internal_class(&ce_write_batch);

  memcpy(&rocksdb_iterator_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
  rocksdb_iterator_handlers.offset = XtOffsetOf(php_rocksdb_iterator_object, zo);
	//rocksdb_iterator_handlers.free_obj = rocksdb_iterator_free_storage;
	INIT_CLASS_ENTRY(ce_iterator, ZEND_NS_NAME("RocksDb", "Iterator"), rocksdb_iterator_class_methods);
  ce_iterator.create_object = php_rocksdb_iterator_object_new;
	rocksdb_iterator_ce = zend_register_internal_class(&ce_iterator);

	zend_class_implements(rocksdb_iterator_ce, 1, spl_ce_SeekableIterator);
	INIT_CLASS_ENTRY(ce_exception, ZEND_NS_NAME("RocksDb", "Exception"), NULL);
	rocksdb_exception_ce = zend_register_internal_class_ex(&ce_exception, spl_ce_RuntimeException);

	// Interfaces
	INIT_CLASS_ENTRY(ce_compaction_filter, ZEND_NS_NAME("RocksDb", "CompactionFilter"), rocksdb_compaction_filter_interface_methods);
	rocksdb_compaction_filter_ce = zend_register_internal_interface(&ce_compaction_filter);
	INIT_CLASS_ENTRY(ce_comparator, ZEND_NS_NAME("RocksDb", "Comparator"), rocksdb_comparator_interface_methods);
	rocksdb_comparator_ce = zend_register_internal_interface(&ce_comparator);
	INIT_CLASS_ENTRY(ce_merge_operator, ZEND_NS_NAME("RocksDb", "MergeOperator"), rocksdb_merge_operator_interface_methods);
	rocksdb_merge_operator_ce = zend_register_internal_interface(&ce_merge_operator);

	PHP_ROCKSDB_REGISTER_CLASS_CONSTANT(rocksdb_ce, "ROCKSDB_TOLERATE_CORRUPTED_TAIL_RECORDS_RECOVERY",  ROCKSDB_TOLERATE_CORRUPTED_TAIL_RECORDS_RECOVERY);
	PHP_ROCKSDB_REGISTER_CLASS_CONSTANT(rocksdb_ce, "ROCKSDB_ABSOLUTE_CONSISTENCY_RECOVERY",  ROCKSDB_ABSOLUTE_CONSISTENCY_RECOVERY);
	PHP_ROCKSDB_REGISTER_CLASS_CONSTANT(rocksdb_ce, "ROCKSDB_POINT_IN_TIME_RECOVERY",  ROCKSDB_POINT_IN_TIME_RECOVERY);
	PHP_ROCKSDB_REGISTER_CLASS_CONSTANT(rocksdb_ce, "ROCKSDB_SKIP_ANY_CORRUPTED_RECORDS_RECOVERY",  ROCKSDB_SKIP_ANY_CORRUPTED_RECORDS_RECOVERY);

	PHP_ROCKSDB_REGISTER_CLASS_CONSTANT(rocksdb_ce, "ROCKSDB_NO_COMPRESSION",  ROCKSDB_NO_COMPRESSION);
	PHP_ROCKSDB_REGISTER_CLASS_CONSTANT(rocksdb_ce, "ROCKSDB_SNAPPY_COMPRESSION",  ROCKSDB_SNAPPY_COMPRESSION);
	PHP_ROCKSDB_REGISTER_CLASS_CONSTANT(rocksdb_ce, "ROCKSDB_ZLIB_COMPRESSION",  ROCKSDB_ZLIB_COMPRESSION);
	PHP_ROCKSDB_REGISTER_CLASS_CONSTANT(rocksdb_ce, "ROCKSDB_BZ2_COMPRESSION",  ROCKSDB_BZ2_COMPRESSION);
	PHP_ROCKSDB_REGISTER_CLASS_CONSTANT(rocksdb_ce, "ROCKSDB_LZ4_COMPRESSION",  ROCKSDB_LZ4_COMPRESSION);
	PHP_ROCKSDB_REGISTER_CLASS_CONSTANT(rocksdb_ce, "ROCKSDB_LZ4HC_COMPRESSION",  ROCKSDB_LZ4HC_COMPRESSION);

	PHP_ROCKSDB_REGISTER_CLASS_CONSTANT(rocksdb_ce, "ROCKSDB_LEVEL_COMPATION",  ROCKSDB_LEVEL_COMPATION);
	PHP_ROCKSDB_REGISTER_CLASS_CONSTANT(rocksdb_ce, "ROCKSDB_UNIVERSAL_COMPACTION",  ROCKSDB_UNIVERSAL_COMPACTION);
	PHP_ROCKSDB_REGISTER_CLASS_CONSTANT(rocksdb_ce, "ROCKSDB_FIFO_COMPACTION",  ROCKSDB_FIFO_COMPACTION);
}

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(rocksdb)
{

	//REGISTER_INI_ENTRIES();
	php_rocksdb_register_classes();

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_GINIT_FUNCTION
*/
PHP_GINIT_FUNCTION(rocksdb)
{
	rocksdb_globals->create_if_missing = 0;
	rocksdb_globals->max_open_files = 0;
	rocksdb_globals->write_buffer_size = 0;
	rocksdb_globals->max_write_buffer_number = 0;
	rocksdb_globals->target_file_size_base = 0;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(rocksdb)
{
	UNREGISTER_INI_ENTRIES();

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(rocksdb)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "rocksdb support", "enabled");
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
/* }}} */

zend_module_entry rocksdb_module_entry = { /* {{{ */
	STANDARD_MODULE_HEADER_EX,
	NULL,
	NULL,
	"rocksdb",
	NULL,
	PHP_MINIT(rocksdb),
	PHP_MSHUTDOWN(rocksdb),
	NULL,
	NULL,
	PHP_MINFO(rocksdb),
	PHP_ROCKSDB_VERSION,
	PHP_MODULE_GLOBALS(rocksdb),
	PHP_GINIT(rocksdb),
	NULL,
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};
/* }}} */

#ifdef COMPILE_DL_ROCKSDB
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE();
#endif
ZEND_GET_MODULE(rocksdb)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
