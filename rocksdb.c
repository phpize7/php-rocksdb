/*
 * rocksdb.c
 *
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "zend_exceptions.h"
 
#include "php_rocksdb.h"

zend_class_entry *rocksdb_ce;

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

const zend_function_entry rocksdb_class_methods[] = {
	PHP_ME(rocksdb, __construct, rocksdb_class__construct_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_FE_END
};

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