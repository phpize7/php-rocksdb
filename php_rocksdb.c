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
#include "rocksdb/c.h"
#include "Zend/zend_types.h"
#include "zend_exceptions.h"
#include "stdbool.h"
#include "php_rocksdb.h"

ZEND_DECLARE_MODULE_GLOBALS(rocksdb)

/* {{{ PHP_INI
 */
PHP_INI_BEGIN()
/*
    STD_PHP_INI_ENTRY("rocksdb.create_if_missing",	    		"1",			PHP_INI_ALL, NULL, create_if_missing,				zend_rocksdb_globals,	rocksdb_globals)
    STD_PHP_INI_ENTRY("rocksdb.max_open_files", 	    		"-1", 			PHP_INI_ALL, NULL, max_open_files, 					zend_rocksdb_globals,	rocksdb_globals)
    STD_PHP_INI_ENTRY("rocksdb.write_buffer_size",       		"67108864", 	PHP_INI_ALL, NULL, write_buffer_size, 				zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.max_write_buffer_number",		"3", 			PHP_INI_ALL, NULL, max_write_buffer_number,			zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.target_file_size_base",			"67108864",		PHP_INI_ALL, NULL, target_file_size_base,			zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.target_file_size_multiplier",	"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.max_background_compactions",		"4",			PHP_INI_ALL, NULL, max_background_compactions,		zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.num_levels",						"4",			PHP_INI_ALL, NULL, num_levels,						zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.max_bytes_for_level_base",		"536870912",	PHP_INI_ALL, NULL, max_bytes_for_level_base,		zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.max_bytes_for_level_multiplier",	"8",			PHP_INI_ALL, NULL, max_bytes_for_level_multiplier,	zend_rocksdb_globals,	rocksdb_globals)

	STD_PHP_INI_ENTRY("rocksdb.paranoid_checks",				"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.error_if_exists",				"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.info_log_level",					"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.db_write_buffer_size",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.max_total_wal_size",				"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)

	STD_PHP_INI_ENTRY("rocksdb.level0_file_num_compaction_trigger",	"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.level0_slowdown_writes_trigger",		"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.level0_stop_writes_trigger",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.level0_file_num_compaction_trigger",	"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	

	STD_PHP_INI_ENTRY("rocksdb.max_mem_compaction_level",	"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.level0_slowdown_writes_trigger",		"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.level0_stop_writes_trigger",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)

	STD_PHP_INI_ENTRY("rocksdb.level_compaction_dynamic_level_bytes",	"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.min_write_buffer_number_to_merge",		"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.max_write_buffer_number_to_maintain",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)

	STD_PHP_INI_ENTRY("rocksdb.max_background_compactions",	"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.base_background_compactions",		"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.max_background_flushes",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.log_file_time_to_roll",	"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.keep_log_file_num",		"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.recycle_log_file_num",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)

	STD_PHP_INI_ENTRY("rocksdb.soft_rate_limit",	"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.hard_rate_limit",		"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.rate_limit_delay_max_milliseconds",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.max_manifest_file_size",	"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.table_cache_numshardbits",		"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.table_cache_remove_scan_count_limit",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)

	STD_PHP_INI_ENTRY("rocksdb.arena_block_size",	"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.set_use_fsync",		"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.db_log_dir",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.wal_dir",	"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.WAL_size_limit_MB",		"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.manifest_preallocation_size",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)

	STD_PHP_INI_ENTRY("rocksdb.purge_redundant_kvs_while_flush",	"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.allow_os_buffer",		"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.allow_mmap_reads",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.allow_mmap_writes",	"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.fd_close_on_exec",		"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.skip_log_error_on_recovery",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)

	STD_PHP_INI_ENTRY("rocksdb.stats_dump_period_sec",	"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.advise_random_on_open",		"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.use_adaptive_mutex",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.access_hint_on_compaction_start",	"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.bytes_per_sync",		"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.allow_concurrent_memtable_write",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)

	STD_PHP_INI_ENTRY("rocksdb.enable_write_thread_adaptive_yield",	"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.verify_checksums_in_compaction",		"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.max_sequential_skip_in_iterations",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.disable_data_sync",	"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.disable_auto_compactions",		"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.delete_obsolete_files_period_micros",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)


	//STD_PHP_INI_ENTRY("rocksdb.memtable_vector_rep",	"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.memtable_prefix_bloom_size_ratio",		"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.max_compaction_bytes",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	//STD_PHP_INI_ENTRY("rocksdb.hash_skip_list_rep",	"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.hash_link_list_rep",		"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	//STD_PHP_INI_ENTRY("rocksdb.plain_table_factory",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)

	STD_PHP_INI_ENTRY("rocksdb.min_level_to_compress",	"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.memtable_huge_page_size",		"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.max_successive_merges",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.min_partial_merge_operands",	"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.bloom_locality",		"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.inplace_update_support",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)

	STD_PHP_INI_ENTRY("rocksdb.inplace_update_num_locks",	"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.report_bg_io_stats",		"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)

	STD_PHP_INI_ENTRY("rocksdb.wal_recovery_mode",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.compression",	"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.compaction_style",		"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.inplace_update_support",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)

	// Read options

	STD_PHP_INI_ENTRY("rocksdb.verify_checksums",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.fill_cache",	"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.snapshot",		"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.iterate_upper_bound",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.read_tier",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.compression",	"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.tailing",		"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.readahead_size",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)

	// Write options
	STD_PHP_INI_ENTRY("rocksdb.set_sync",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	STD_PHP_INI_ENTRY("rocksdb.disable_WAL",	"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)

	// Flush options
	STD_PHP_INI_ENTRY("rocksdb.set_wait",			"0",			PHP_INI_ALL, NULL, paranoid_checks,					zend_rocksdb_globals,	rocksdb_globals)
	*/
PHP_INI_END()
/* }}} */

static void php_rocksdb_register_classes()
{
	zend_class_entry ce, ce_backup_info, ce_compaction_filter, ce_iterator, ce_comparator, ce_merge_operator, ce_snapshot, ce_rocksdb_write_batch;

	INIT_CLASS_ENTRY(ce, ZEND_NS_NAME("RocksDb", "RocksDb"), rocksdb_class_methods);
	rocksdb_ce = zend_register_internal_class(&ce);
	INIT_CLASS_ENTRY(ce_backup_info, ZEND_NS_NAME("RocksDb", "BackupEngineInfo"), rocksdb_backup_engine_info_class_methods);
	rocksdb_backup_engine_info_ce = zend_register_internal_class(&ce_backup_info);
	INIT_CLASS_ENTRY(ce_backup_info, ZEND_NS_NAME("RocksDb", "BackupEngineInfo"), rocksdb_backup_engine_info_class_methods);
	rocksdb_backup_engine_info_ce = zend_register_internal_class(&ce_backup_info);
	INIT_CLASS_ENTRY(ce_snapshot, ZEND_NS_NAME("RocksDb", "Snapshot"), rocksdb_snapshot_class_methods);
	rocksdb_snapshot_ce = zend_register_internal_class(&ce_snapshot);
	INIT_CLASS_ENTRY(ce_rocksdb_write_batch, ZEND_NS_NAME("RocksDb", "WriteBatch"), rocksdb_write_batch_class_methods);
	rocksdb_write_batch_ce = zend_register_internal_class(&ce_rocksdb_write_batch);
	// Abstract classes
	INIT_CLASS_ENTRY(ce_iterator, ZEND_NS_NAME("RocksDb", "Iterator"), rocksdb_iterator_class_methods);
	rocksdb_iterator_ce = zend_register_internal_class(&ce_iterator);
	zend_class_implements(rocksdb_iterator_ce, 1, spl_ce_SeekableIterator);
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

	REGISTER_INI_ENTRIES();
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
