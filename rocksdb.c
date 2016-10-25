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
#include "Zend/zend_types.h"


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

zend_class_entry *php_rocksdb_ce;

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class__construct_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, path)
	ZEND_ARG_ARRAY_INFO(0, options, 1)
ZEND_END_ARGS_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_get_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARGS_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_put_arginfo, 0, 0, 2)
	ZEND_ARG_VARIADIC_INFO(0, args)
ZEND_END_ARGS_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_delete_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARGS_INFO()

/**
 * Define module class methods
 */
zend_function_entry rocksdb_class_methods[] = {
	PHP_ME(rocksdb, __construct, rocksdb_class__construct_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdb, get,         rocksdb_class_get_arginfo,          ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, put,         rocksdb_class_put_arginfo,          ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, delete,      rocksdb_class_delete_arginfo,       ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, close,       NULL,     						     ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

PHP_METHOD(rocksdb, __construct) {
	char *path = NULL;
	zval *options;
	zval *object = getThis();
	php_rocksdb_db_object *db_obj;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sa", &path, &options) == FAILURE) {
		return;
	}

	db_obj = Z_ROCKSDB_DB_P(object);

	if (db_obj->initialised) {
		zend_throw_exception(zend_ce_exception, "Already initialised DB Object", 0);
	}

	rocksdb_options_t *options = rocksdb_options_create();

	// Set options
	rocksdb_options_increase_parallelism(options, ROCKSDB_G(increase_parallelism));
	rocksdb_options_optimize_for_point_lookup(options, (uint64_t) ROCKSDB_G(optimize_for_point_lookup));
	rocksdb_options_optimize_level_style_compaction(options, (uint64_t) ROCKSDB_G(optimize_level_style_compaction));
	rocksdb_options_optimize_universal_style_compaction(options, (uint64_t) ROCKSDB_G(memtable_memory_budget))


	rocksdb_options_set_create_if_missing(options, (int) ROCKSDB_G(create_if_missing));
	rocksdb_options_set_max_open_files(options, (int) ROCKSDB_G(max_open_files));
	rocksdb_options_set_write_buffer_size(options, (int) ROCKSDB_G(write_buffer_size))
	rocksdb_options_set_max_write_buffer_number_to_maintain(options, (int) ROCKSDB_G(max_write_buffer_number))
	rocksdb_options_set_target_file_size_base(options, (int) ROCKSDB_G(target_file_size_base))

	char *err = NULL;
	db_obj->db = rocksdb_open(options, path, &err);

	if (err) {
		rocksdb_options_destroy(options);

		zend_throw_exception_ex(zend_ce_exception, 0, "Unable to open database: %s", err);

		if (fullpath) {
			efree(path);
		}

		return;
	}

	db_obj->initialised = 1;

	rocksdb_options_destroy(options);
}

PHP_METHOD(rocksdb, close)
{
	php_rocksdb_db_object *db_obj;
	zval *object = getThis();
	int errcode;
	db_obj = Z_ROCKSDB_DB_P(object);

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	if (db_obj->initialised) {
		if(db_obj->db) {
            rocksdb_close(db_obj->db);
        }
		db_obj->initialised = 0;
	}

	RETURN_TRUE;
}

PHP_METHOD(rocksdb, put)
{
	zval *object = getThis();
	db_obj = Z_ROCKSDB_DB_P(object);

	char *k, *v;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "ss", &k, &v) == FAILURE) {
		RETURN_FALSE;
	}

	if (strlen(k) == 0) {
		php_rocksdb_error(db_obj->db, "Cannot set parameter with key `%s` and value %s", k, v)
	}

	char *err = NULL;
	rocksdb_writeoptions_t *writeoptions = rocksdb_writeoptions_create();
	rocksdb_put(obj->db, writeoptions, k, strlen(k), v, strlen(v), &err);
	rocksdb_writeoptions_destroy(writeoptions);
	if (err != NULL) {
		RETURN_FALSE;
	}

	RETURN_TRUE;
}


ZEND_DECLARE_MODULE_GLOBALS(rocksdb)

/* {{{ PHP_INI
 */
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("rocksdb.create_if_missing",      "true", PHP_INI_ALL, OnUpdateString, create_if_missing, zend_rocksdb_globals, rocksdb_globals);
    STD_PHP_INI_ENTRY("rocksdb.max_open_files", "300000", PHP_INI_ALL, OnUpdateLong, max_open_files, zend_rocksdb_globals, rocksdb_globals);
    STD_PHP_INI_ENTRY("rocksdb.write_buffer_size", "67108864", PHP_INI_ALL, OnUpdateLong, write_buffer_size, zend_rocksdb_globals, rocksdb_globals);
	STD_PHP_INI_ENTRY("rocksdb.max_write_buffer_number", "3", PHP_INI_ALL, OnUpdateLong, max_write_buffer_number, zend_rocksdb_globals, rocksdb_globals);
	STD_PHP_INI_ENTRY("rocksdb.target_file_size_base", "67108864", PHP_INI_ALL, OnUpdateLong, target_file_size_base, zend_rocksdb_globals, rocksdb_globals);
PHP_INI_END()
/* }}} */


/* {{{ php_rocksdb_init_globals
 */
static void php_rocksdb_init_globals(zend_rocksdb_globals *rocksdb_globals)
{
	rocksdb_globals->create_if_missing = true;
	rocksdb_globals->max_open_files = 0;
	rocksdb_globals->write_buffer_size = 0;
	rocksdb_globals->max_write_buffer_number = 0;
	rocksdb_globals->target_file_size_base = 0;
}
/* }}} */


/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(rocksdb)
{
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "RocksDb", rocksdb_class_methods);

	php_rocksdb_ce = zend_register_internal_class(&ce, TSRMLS_CC);

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
1}
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
	STANDARD_MODULE_PROPERTIES
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
