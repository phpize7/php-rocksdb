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
#include "rocksdb/c.h"
#include "Zend/zend_types.h"
#include "zend_exceptions.h"
#include "stdbool.h"
#include "php_rocksdb.h"

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


/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(rocksdb)
{
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "RocksDb", rocksdb_class_methods);
	rocksdb_ce = zend_register_internal_class(&ce);

	INIT_CLASS_ENTRY(ce, "RocksDb\\BackupEngineInfo", rocksdb_backup_engine_info_class_methods);
	rocksdb_backup_engine_info_ce = zend_register_internal_class(&ce);

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


static const zend_module_dep rocksdb_deps[] = {
	ZEND_MOD_END
};

zend_module_entry rocksdb_module_entry = { /* {{{ */
	STANDARD_MODULE_HEADER_EX, NULL,
	rocksdb_deps,
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
