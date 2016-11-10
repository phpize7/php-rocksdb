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
#include "php_rocksdb.h"
#include "rocksdb/c.h"
#include "rocksdb_snapshot.h"
#include "Zend/zend_types.h"

#include "zend_exceptions.h"

#include "stdbool.h"

PHP_METHOD(rocksdb, __construct);
PHP_METHOD(rocksdb, open);
PHP_METHOD(rocksdb, open_for_read_only);
PHP_METHOD(rocksdb, backup_engine_open);
PHP_METHOD(rocksdb, rocksdb_backup_engine_purge_old_backups);
PHP_METHOD(rocksdb, rocksdb_restore_options_create);

PHP_METHOD(rocksdb, rocksdb_restore_options_destroy);
PHP_METHOD(rocksdb, rocksdb_backup_engine_restore_db_from_latest_backup);
PHP_METHOD(rocksdb, rocksdb_backup_engine_get_backup_info);
PHP_METHOD(rocksdb, rocksdb_backup_engine_info_count);
PHP_METHOD(rocksdb, rocksdb_backup_engine_info_timestamp);

PHP_METHOD(rocksdb, rocksdb_backup_engine_info_backup_id);
PHP_METHOD(rocksdb, rocksdb_backup_engine_info_size);
PHP_METHOD(rocksdb, rocksdb_backup_engine_info_number_files);
PHP_METHOD(rocksdb, rocksdb_backup_engine_info_destroy);
PHP_METHOD(rocksdb, rocksdb_backup_engine_close);

PHP_METHOD(rocksdb, rocksdb_open_column_families);
PHP_METHOD(rocksdb, rocksdb_open_for_read_only_column_families);
PHP_METHOD(rocksdb, rocksdb_list_column_families);
PHP_METHOD(rocksdb, rocksdb_list_column_families_destroy);
PHP_METHOD(rocksdb, rocksdb_create_column_family);

PHP_METHOD(rocksdb, rocksdb_close);
PHP_METHOD(rocksdb, rocksdb_put);
PHP_METHOD(rocksdb, rocksdb_put_cf);
PHP_METHOD(rocksdb, rocksdb_delete);
PHP_METHOD(rocksdb, rocksdb_delete_cf);

PHP_METHOD(rocksdb, rocksdb_merge);
PHP_METHOD(rocksdb, rocksdb_merge_cf);
PHP_METHOD(rocksdb, rocksdb_write);
PHP_METHOD(rocksdb, rocksdb_get);
PHP_METHOD(rocksdb, rocksdb_get_cf);


PHP_METHOD(rocksdb, rocksdb_multi_get);
PHP_METHOD(rocksdb, rocksdb_multi_get_cf);
PHP_METHOD(rocksdb, rocksdb_create_iterator);
PHP_METHOD(rocksdb, rocksdb_create_iterator_cf);
PHP_METHOD(rocksdb, rocksdb_create_iterators);

PHP_METHOD(rocksdb, rocksdb_release_snapshot);
PHP_METHOD(rocksdb, rocksdb_property_value);
PHP_METHOD(rocksdb, rocksdb_property_value_cf);
PHP_METHOD(rocksdb, rocksdb_approximate_sizes);
PHP_METHOD(rocksdb, rocksdb_approximate_sizes_cf);

PHP_METHOD(rocksdb, rocksdb_compact_range);
PHP_METHOD(rocksdb, rocksdb_compact_range_cf);
PHP_METHOD(rocksdb, rocksdb_delete_file);
PHP_METHOD(rocksdb, rocksdb_flush);
PHP_METHOD(rocksdb, rocksdb_disable_file_deletions);


PHP_METHOD(rocksdb, rocksdb_enable_file_deletions);
PHP_METHOD(rocksdb, rocksdb_destroy_db);
PHP_METHOD(rocksdb, rocksdb_repair_db);
PHP_METHOD(rocksdb, rocksdb_iter_destroy);
PHP_METHOD(rocksdb, rocksdb_iter_valid);

zend_class_entry *php_rocksdb_ce;

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class__construct_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, path)
	ZEND_ARG_ARRAY_INFO(0, options, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_get_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_put_arginfo, 0, 0, 2)
	ZEND_ARG_VARIADIC_INFO(0, args)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_delete_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_DECLARE_MODULE_GLOBALS(rocksdb)

/* {{{ PHP_INI
 */
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("rocksdb.create_if_missing", "true", PHP_INI_ALL, OnUpdateString, create_if_missing, zend_rocksdb_globals, rocksdb_globals)
    STD_PHP_INI_ENTRY("rocksdb.max_open_files", "300000", PHP_INI_ALL, OnUpdateLong, max_open_files, zend_rocksdb_globals, rocksdb_globals)
    STD_PHP_INI_ENTRY("rocksdb.write_buffer_size", "67108864", PHP_INI_ALL, OnUpdateLong, write_buffer_size, zend_rocksdb_globals, rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.max_write_buffer_number", "3", PHP_INI_ALL, OnUpdateLong, max_write_buffer_number, zend_rocksdb_globals, rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.target_file_size_base", "67108864", PHP_INI_ALL, OnUpdateLong, target_file_size_base, zend_rocksdb_globals, rocksdb_globals)
PHP_INI_END()
/* }}} */

/**
 * Define module class methods
 */
zend_function_entry rocksdb_class_methods[] = {
	PHP_ME(rocksdb, __construct, rocksdb_class__construct_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_FE_END
};

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(rocksdb)
{
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "RocksDb", rocksdb_class_methods);

	php_rocksdb_ce = zend_register_internal_class(&ce);

	REGISTER_INI_ENTRIES();

	/* Define compression related constants */
	PHP_ROCKSDB_REGISTER_CONSTANT("ROCKSDB_NO_COMPRESSION",  ROCKSDB_NO_COMPRESSION);
	PHP_ROCKSDB_REGISTER_CONSTANT("ROCKSDB_SNAPPY_COMPRESSION",  ROCKSDB_SNAPPY_COMPRESSION);
	PHP_ROCKSDB_REGISTER_CONSTANT("ROCKSDB_ZLIB_COMPRESSION",  ROCKSDB_ZLIB_COMPRESSION);
	PHP_ROCKSDB_REGISTER_CONSTANT("ROCKSDB_BZ2_COMPRESSION",  ROCKSDB_BZ2_COMPRESSION);
	PHP_ROCKSDB_REGISTER_CONSTANT("ROCKSDB_LZ4_COMPRESSION",  ROCKSDB_LZ4_COMPRESSION);
	PHP_ROCKSDB_REGISTER_CONSTANT("ROCKSDB_LZ4HC_COMPRESSION",  ROCKSDB_LZ4HC_COMPRESSION);

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


/* {{{ rocksdb_module_entry
 */
zend_module_entry rocksdb_module_entry = {
	STANDARD_MODULE_HEADER,
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



/* {{{ Error Handler
*/
static void php_rocksdb_error(php_rocksdb_db_object *db_obj, char *format, ...)
{
	va_list arg;
	char 	*message;

	va_start(arg, format);
	vspprintf(&message, 0, format, arg);
	va_end(arg);

	if (db_obj && db_obj->exception) {
		zend_throw_exception(zend_ce_exception, message, 0);
	} else {
		php_error_docref(NULL, E_WARNING, "%s", message);
	}

	if (message) {
		efree(message);
	}
}
/* }}} */

PHP_METHOD(rocksdb, __construct) {
	char *path = NULL;
	zval *args;
	zval *object = getThis();
	php_rocksdb_db_object *db_obj;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sa", &path, &args) == FAILURE) {
		return;
	}

	db_obj = Z_ROCKSDB_DB_P(object);

	if (db_obj->initialised) {
		zend_throw_exception(zend_ce_exception, "Already initialised DB Object", 0);
	}

	rocksdb_options_t *options = rocksdb_options_create();

	/*
	rocksdb_options_increase_parallelism(options, ROCKSDB_G(increase_parallelism));
	rocksdb_options_optimize_for_point_lookup(options, (uint64_t) ROCKSDB_G(optimize_for_point_lookup));
	rocksdb_options_optimize_level_style_compaction(options, (uint64_t) ROCKSDB_G(optimize_level_style_compaction));
	rocksdb_options_optimize_universal_style_compaction(options, (uint64_t) ROCKSDB_G(memtable_memory_budget));


	rocksdb_options_set_create_if_missing(options, (int) ROCKSDB_G(create_if_missing));
	rocksdb_options_set_max_open_files(options, (int) ROCKSDB_G(max_open_files));
	rocksdb_options_set_write_buffer_size(options, (int) ROCKSDB_G(write_buffer_size));
	rocksdb_options_set_max_write_buffer_number_to_maintain(options, (int) ROCKSDB_G(max_write_buffer_number));
	rocksdb_options_set_target_file_size_base(options, (int) ROCKSDB_G(target_file_size_base));
	*/

	char *err = NULL;
	db_obj->db = rocksdb_open(options, path, &err);

	if (err) {
		rocksdb_options_destroy(options);

		zend_throw_exception_ex(zend_ce_exception, 0, "Unable to open database: %s", err);

		if (path) {
			efree(path);
		}

		return;
	}

	db_obj->initialised = 1;

	rocksdb_options_destroy(options);
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
