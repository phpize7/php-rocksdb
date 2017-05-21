/*
 * rocksdb.c
 *
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "zend_exceptions.h"
#include "Zend/zend_hash.h"
#include "Zend/zend_types.h"
#include "Zend/zend_interfaces.h"

#include "php_rocksdb.h"

zend_class_entry *rocksdb_ce;

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class__construct_arginfo, 0, 0, 1)
  ZEND_ARG_INFO(0, name)
  ZEND_ARG_INFO(0, options)
  ZEND_ARG_INFO(0, read_options)
  ZEND_ARG_INFO(0, write_options)
  ZEND_ARG_INFO(0, cf_names)
  ZEND_ARG_INFO(0, cf_options)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_list_column_families_arginfo, 0, 0, 3)
  ZEND_ARG_INFO(0, name)
  ZEND_ARG_INFO(0, options)
  ZEND_ARG_INFO(0, lencf)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_create_column_family_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, column_family_name)
	ZEND_ARG_INFO(0, column_family_options)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_drop_column_family_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, handle)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_put_arginfo, 0, 0, 3)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
	ZEND_ARG_INFO(0, options)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_put_cf_arginfo, 0, 0, 3)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
	ZEND_ARG_INFO(0, column_family)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_delete_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_delete_cf_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, column_family)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_merge_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_merge_cf_arginfo, 0, 0, 3)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
	ZEND_ARG_INFO(0, column_family)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_write_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, batch)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_get_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_get_cf_arginfo, 0, 0, 3)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, column_family)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_get_iterator_cf_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, column_family)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_get_property_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_get_property_cf_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, column_family)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_get_approximate_sizes_arginfo, 0, 0, 4)
	ZEND_ARG_INFO(0, num_ranges)
	ZEND_ARG_INFO(0, start_key)
	ZEND_ARG_INFO(0, limit_key)
	ZEND_ARG_INFO(0, sizes)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_get_approximate_sizes_cf_arginfo, 0, 0, 5)
	ZEND_ARG_INFO(0, num_ranges)
	ZEND_ARG_INFO(0, start_key)
	ZEND_ARG_INFO(0, limit_key)
	ZEND_ARG_INFO(0, sizes)
	ZEND_ARG_INFO(0, column_family)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_flush_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, options)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_delete_file_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_enable_file_deletions_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, force)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(rocksdb_class_repair_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

const zend_function_entry rocksdb_class_methods[] = {
	PHP_ME(rocksdb, __construct, rocksdb_class__construct_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(rocksdb, listColumnFamilies, rocksdb_class_list_column_families_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(rocksdb, createColumnFamily, rocksdb_class_create_column_family_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, dropColumnFamily, rocksdb_class_drop_column_family_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, put, rocksdb_class_put_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, putCf, rocksdb_class_put_cf_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, delete, rocksdb_class_delete_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, deleteCf, rocksdb_class_delete_cf_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, merge, rocksdb_class_merge_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, mergeCf, rocksdb_class_merge_cf_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, write, rocksdb_class_write_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, get, rocksdb_class_get_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, getCf, rocksdb_class_get_cf_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, getIterator, NULL, ZEND_ACC_PUBLIC) // rocksdb_create_iterator
	PHP_ME(rocksdb, getIteratorCf, rocksdb_class_get_iterator_cf_arginfo, ZEND_ACC_PUBLIC) // rocksdb_create_iterator_cf
	PHP_ME(rocksdb, createSnapshot, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, getProperty, rocksdb_class_get_property_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, getPropertyCf, rocksdb_class_get_property_cf_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, getApproximateSizes, rocksdb_class_get_approximate_sizes_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, getApproximateSizesCf, rocksdb_class_get_approximate_sizes_cf_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, flush, rocksdb_class_flush_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, deleteFile, rocksdb_class_delete_file_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, disableFileDeletions, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, enableFileDeletions, rocksdb_class_enable_file_deletions_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, destroy, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, repair, rocksdb_class_repair_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(rocksdb, close, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_METHOD(rocksdb, __construct) {
  char *name, *err = NULL;
  size_t name_len;

  zval *options_zv = NULL,
      *readoptions_zv = NULL,
      *writeoptions_zv = NULL,
      *cfnames_zv = NULL,
      *cfoptions_zv = NULL,
      *ro = NULL,
      *entry;

  zval *object = getThis();
  php_rocksdb_db_object *db_obj;
  HashTable *htoptions, *htcfnames;
  zend_ulong index;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|aaaaa",
  			&name, &name_len, &options_zv, &readoptions_zv, &writeoptions_zv, &cfnames_zv, &cfoptions_zv) == FAILURE) {
  		return;
  }

  db_obj = Z_ROCKSDB_DB_P(object);

  if (db_obj->initialised == 1) {
    zend_throw_exception(zend_ce_exception, "Already initialised DB Object", 0);
  }

  rocksdb_options_t *options = php_rocksdb_get_open_options(options_zv);

  htoptions = Z_ARRVAL_P(options_zv);
  ro = zend_hash_str_find(htoptions, "read_only", sizeof("read_only")-1);

  if (cfnames_zv != NULL) {
    htcfnames = Z_ARRVAL_P(cfnames_zv);
    if (htcfnames->nNumOfElements > 0) {
      const char *cfnames[htcfnames->nNumOfElements];
      const rocksdb_options_t *cfopts[htcfnames->nNumOfElements];

      ZEND_HASH_FOREACH_NUM_KEY_VAL(htcfnames, index, entry) {
        if (Z_TYPE_P(entry) != IS_STRING) {
          zend_error(E_ERROR, "Expected string for frame " ZEND_ULONG_FMT, index);
          break;
        }
        cfnames[index] = (char *) Z_STRVAL(*entry);
        cfopts[index] = (rocksdb_options_t *) options;

        db_obj->handle_names[index] = (char *) cfnames[index];
      } ZEND_HASH_FOREACH_END();

      if (NULL != ro && zend_is_true(ro)) {
        db_obj->db = rocksdb_open_for_read_only_column_families(
          options, (const char*) name, htcfnames->nNumOfElements, (const char **) cfnames, (const rocksdb_options_t **) cfopts, db_obj->handles, 0, &err);
      } else {
        db_obj->db = rocksdb_open_column_families(
          options, (const char*) name, htcfnames->nNumOfElements, (const char **) cfnames, (const rocksdb_options_t **) cfopts, db_obj->handles, &err);
      }
      db_obj->num_handles = htcfnames->nNumOfElements;
    } else {
      if (NULL != ro && zend_is_true(ro)) {
        db_obj->db = rocksdb_open_for_read_only(options, (const char*) name, 0, &err);
      } else {
        db_obj->db = rocksdb_open(options, (const char*) name, &err);
      }
      db_obj->num_handles = 0;
    }
  } else {
    if (NULL != ro && zend_is_true(ro)) {
      db_obj->db = rocksdb_open_for_read_only(options, (const char*) name, 0, &err);
    } else {
      db_obj->db = rocksdb_open(options, (const char*) name, &err);
    }
  }

  rocksdb_options_destroy(options);

  ROCKSDB_CHECK_FOR_ERRORS(err);

  db_obj->name = name;
  db_obj->initialised = 1;
}

PHP_METHOD(rocksdb, listColumnFamilies) {
  char *err, *cf = NULL;
  const char *name;
  char **column_families;
  size_t lencf, name_len;
  zval val;
  zval *options_zv = NULL;

  rocksdb_options_t *options;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|a",
  		&name, &name_len, &options_zv) == FAILURE) {
  	return;
  }

  options = php_rocksdb_get_open_options(options_zv);
  column_families = rocksdb_list_column_families(options, name, &lencf, &err);
  rocksdb_options_destroy(options);

  HashTable *ht;
  ALLOC_HASHTABLE(ht);
  zend_hash_init(ht, 0, NULL, ZVAL_PTR_DTOR, 0);

  cf = *column_families;
  for (int i = 0; i < lencf; i = i + 1) {
    ZVAL_STRING(&val, cf);

    zend_hash_next_index_insert_new(ht, &val);
    cf = *++column_families;
  }

  rocksdb_list_column_families_destroy(column_families, lencf);

  RETVAL_ARR(ht);
}
PHP_METHOD(rocksdb, createColumnFamily) {
  char *err = NULL;
  const char *name;
  size_t name_len;
  zval *object = getThis();
  zval *options_zv = NULL;
  rocksdb_options_t *options;
  php_rocksdb_db_object *db_obj;
  db_obj = Z_ROCKSDB_DB_P(object);

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|a",
  		&name, &name_len, &options_zv) == FAILURE) {
  	return;
  }

  options = php_rocksdb_get_open_options(options_zv);
  db_obj->handles[db_obj->num_handles] = rocksdb_create_column_family(db_obj->db, (const rocksdb_options_t *) options, name, &err);
  db_obj->handle_names[db_obj->num_handles] = (char *) name;
  db_obj->num_handles++;
  rocksdb_options_destroy(options);

  RETURN_TRUE;
}
PHP_METHOD(rocksdb, dropColumnFamily) {
  char *err = NULL;
  char *name = NULL;
  size_t name_len;
  php_rocksdb_db_object *this = Z_ROCKSDB_DB_P(getThis() TSRMLS_CC);

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s",
  		&name, &name_len) == FAILURE) {
  	return;
  }

  int i = 0;
  while((i < this->num_handles) && (this->handle_names[i] != name)) i++;
  int h = (i < this->num_handles) ? (i) : (-1);

  if (h == -1) {
    RETURN_FALSE;
  }

  rocksdb_drop_column_family(this->db, this->handles[h], &err);

  if (err != NULL) {
    zend_throw_exception(zend_ce_exception, err, 0);
  }

  RETURN_TRUE;
}

PHP_METHOD(rocksdb, put) {
  char *key, *value;
  size_t key_len, value_len;
  zval *object = getThis();
  zval *options_zv = NULL;
  php_rocksdb_db_object *db_obj;
  db_obj = Z_ROCKSDB_DB_P(object);
  char *err = NULL;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss|a",
  		&key, &key_len, &value, &value_len, &options_zv) == FAILURE) {
  	return;
  }

  rocksdb_writeoptions_t *options = php_rocksdb_get_write_options(options_zv);
  rocksdb_put(db_obj->db, options, key, key_len, value, value_len, &err);
  rocksdb_writeoptions_destroy(options);

  ROCKSDB_CHECK_FOR_ERRORS(err);

  RETURN_TRUE;
}

PHP_METHOD(rocksdb, putCf) {
  char *key, *value, *cf;
  size_t key_len, value_len, cf_len;
  zval *object = getThis();
  php_rocksdb_db_object *db_obj;
  db_obj = Z_ROCKSDB_DB_P(object);
  char *err = NULL;

  rocksdb_writeoptions_t *writeoptions;
  writeoptions = rocksdb_writeoptions_create();

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sss",
  		&key, &key_len, &value, &value_len, &cf, &cf_len) == FAILURE) {
  	return;
  }

  int i=0;
  while((i<db_obj->num_handles) && (db_obj->handle_names[i] != cf)) i++;
  int h = (i<db_obj->num_handles) ? (i) : (-1);

  if (h == -1) {
    RETURN_FALSE;
  }

  rocksdb_put_cf(db_obj->db, writeoptions, db_obj->handles[h], key, key_len, value, value_len, &err);
  rocksdb_writeoptions_destroy(writeoptions);

  RETURN_TRUE;
}

PHP_METHOD(rocksdb, delete) {
  char *key;
  size_t key_len;
  zval *object = getThis();
  zval *options_zv = NULL;
  php_rocksdb_db_object *db_obj;
  db_obj = Z_ROCKSDB_DB_P(object);
  char *err = NULL;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|a",
      &key, &key_len, &options_zv) == FAILURE) {
    return;
  }

  rocksdb_writeoptions_t *options = php_rocksdb_get_write_options(options_zv);
  rocksdb_delete(db_obj->db, options, key, key_len, &err);
  rocksdb_writeoptions_destroy(options);

  ROCKSDB_CHECK_FOR_ERRORS(err);

  RETURN_TRUE;
}


PHP_METHOD(rocksdb, deleteCf) {
  char *key, *cf;
  size_t key_len, cf_len;
  zval *object = getThis();
  zval *options_zv = NULL;
  php_rocksdb_db_object *db_obj;
  db_obj = Z_ROCKSDB_DB_P(object);
  char *err = NULL;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss|a",
      &key, &key_len, &cf, &cf_len, &options_zv) == FAILURE) {
    return;
  }

  int i = 0;
  while((i < db_obj->num_handles) && (db_obj->handle_names[i] != cf)) i++;
  int h = (i < db_obj->num_handles) ? (i) : (-1);

  if (h == -1) {
    RETURN_FALSE;
  }

  rocksdb_writeoptions_t *options = php_rocksdb_get_write_options(options_zv);
  rocksdb_delete_cf(db_obj->db, options, db_obj->handles[h], key, key_len, &err);
  rocksdb_writeoptions_destroy(options);

  if (err != NULL) {
    RETURN_FALSE;
  }

  RETURN_TRUE;
}
PHP_METHOD(rocksdb, merge) {
  char *key, *value;
  size_t key_len, value_len;
  char *err = NULL;
  zval *options_zv = NULL;
  php_rocksdb_db_object *db_obj;
  db_obj = Z_ROCKSDB_DB_P(getThis());

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss|a",
      &key, &key_len, &value, &value_len, &options_zv) == FAILURE) {
    return;
  }

  rocksdb_writeoptions_t *options = php_rocksdb_get_write_options(options_zv);
  rocksdb_merge(db_obj->db, options, (const char *) key, key_len, (const char *) value, value_len, &err);
  rocksdb_writeoptions_destroy(options);

  RETURN_TRUE;
}
PHP_METHOD(rocksdb, mergeCf) {
}


PHP_METHOD(rocksdb, write) {
  zval *write_batch;
  char *err = NULL;
  zval *object = getThis();
  zval *options_zv = NULL;
  php_rocksdb_db_object *db_obj;
  db_obj = Z_ROCKSDB_DB_P(object);
  php_rocksdb_write_batch_object *write_batch_object;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O|a",
      &write_batch, rocksdb_write_batch_ce, &options_zv) == FAILURE) {
    return;
  }

  write_batch_object = Z_ROCKSDB_WRITE_BATCH_P(write_batch TSRMLS_CC);

  rocksdb_writeoptions_t *options = php_rocksdb_get_write_options(options_zv);
  rocksdb_write(db_obj->db, options, write_batch_object->batch, &err);
  rocksdb_writeoptions_destroy(options);

  RETURN_TRUE;
}


PHP_METHOD(rocksdb, get) {
  char *key, *value;
  size_t key_len, value_len;
  zval *object = getThis();
  zval *options_zv = NULL;
  php_rocksdb_db_object *db_obj;
  db_obj = Z_ROCKSDB_DB_P(object);
  char *err = NULL;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|a",
      &key, &key_len, &options_zv) == FAILURE) {
    return;
  }

  rocksdb_readoptions_t *options = php_rocksdb_get_read_options(options_zv);
  value = rocksdb_get(db_obj->db, options, key, key_len, &value_len, &err);
  rocksdb_readoptions_destroy(options);

  if (value == NULL) {
    RETURN_FALSE;
  }

  RETVAL_STRINGL(value, value_len);
  free(value);
}


PHP_METHOD(rocksdb, getCf) {
  char *key, *value, *cf;
  size_t key_len, value_len, cf_len;
  zval *options_zv = NULL;
  php_rocksdb_db_object *this = Z_ROCKSDB_DB_P(getThis());
  char *err = NULL;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss|a",
      &key, &key_len, &cf, &cf_len, &options_zv) == FAILURE) {
    return;
  }

  int i = 0;
  while((i < this->num_handles) && (this->handle_names[i] != cf)) i++;
  int h = (i < this->num_handles) ? (i) : (-1);

  if (h == -1) {
    RETURN_FALSE;
  }

  rocksdb_readoptions_t *options = php_rocksdb_get_read_options(options_zv);
  value = rocksdb_get_cf(this->db, options, this->handles[h], key, key_len, &value_len, &err);
  rocksdb_readoptions_destroy(options);

  if (value == NULL) {
    RETURN_FALSE;
  }

  RETVAL_STRINGL(value, value_len);
  free(value);
}

PHP_METHOD(rocksdb, getIterator) {
  zval *readoptions_zv = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|a", &readoptions_zv) == FAILURE) {
		return;
	}

	object_init_ex(return_value, rocksdb_iterator_ce);

  zend_call_method_with_2_params(return_value, rocksdb_iterator_ce,
    &rocksdb_iterator_ce->constructor, "__construct", NULL, getThis(), readoptions_zv TSRMLS_CC);
}


PHP_METHOD(rocksdb, getIteratorCf) {

}
PHP_METHOD(rocksdb, createSnapshot) {
  if (zend_parse_parameters_none() == FAILURE) {
    return;
  }

  object_init_ex(return_value, rocksdb_snapshot_ce);

  zend_call_method_with_1_params(return_value, rocksdb_snapshot_ce,
    &rocksdb_snapshot_ce->constructor, "__construct", NULL, getThis());
}
PHP_METHOD(rocksdb, getProperty) {
  char *prop;
  size_t prop_len;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s",
      &prop, &prop_len) == FAILURE) {
    return;
  }

  php_rocksdb_db_object *db_obj = Z_ROCKSDB_DB_P(getThis() TSRMLS_CC);

  char *value = rocksdb_property_value(db_obj->db, (const char *) prop);

  if (NULL == value) {
    RETURN_FALSE;
  }

  RETURN_STRING(value);
}
PHP_METHOD(rocksdb, getPropertyCf) {
  char *prop, *cf;
  size_t prop_len, cf_len;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss",
      &prop, &prop_len, &cf, &cf_len) == FAILURE) {
    return;
  }

  php_rocksdb_db_object *this = Z_ROCKSDB_DB_P(getThis() TSRMLS_CC);

  int i = 0;
  while((i < this->num_handles) && (this->handle_names[i] != cf)) i++;
  int h = (i < this->num_handles) ? (i) : (-1);

  if (h == -1) {
    RETURN_FALSE;
  }

  char *value = rocksdb_property_value_cf(this->db, this->handles[h], (const char *) prop);

  RETURN_STRING(value);
}
PHP_METHOD(rocksdb, getApproximateSizes) {

}
PHP_METHOD(rocksdb, getApproximateSizesCf) {}
PHP_METHOD(rocksdb, flush) {
  zval *flushoptions_zv = NULL;
  rocksdb_flushoptions_t *flushoptions;
  php_rocksdb_db_object *this;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|a", &flushoptions_zv) == FAILURE) {
    return;
  }

  char *err = NULL;
  this = Z_ROCKSDB_DB_P(getThis() TSRMLS_CC);

  flushoptions = php_rocksdb_get_flush_options(flushoptions_zv);
  rocksdb_flush(this->db, flushoptions, &err);
  rocksdb_flushoptions_destroy(flushoptions);

  if (err != NULL) {
    zend_throw_exception(zend_ce_exception, err, 0);
    return;
  }
}
PHP_METHOD(rocksdb, deleteFile) {
  char *name;
  size_t name_len;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s",
      &name, &name_len) == FAILURE) {
    return;
  }

  php_rocksdb_db_object *this = Z_ROCKSDB_DB_P(getThis() TSRMLS_CC);

  rocksdb_delete_file(this->db, (const char *) name);

  RETURN_TRUE;
}
PHP_METHOD(rocksdb, disableFileDeletions) {
  if (zend_parse_parameters_none() == FAILURE) {
    return;
  }

  char *err = NULL;
  php_rocksdb_db_object *this = Z_ROCKSDB_DB_P(getThis() TSRMLS_CC);

  rocksdb_disable_file_deletions(this->db, &err);

  if (err != NULL) {
    zend_throw_exception(zend_ce_exception, err, 0);
  }
}
PHP_METHOD(rocksdb, enableFileDeletions) {
  char *err = NULL;
  zend_bool *force_zv;
  php_rocksdb_db_object *this = Z_ROCKSDB_DB_P(getThis() TSRMLS_CC);

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "b", &force_zv) == FAILURE) {
    return;
  }

  rocksdb_enable_file_deletions(this->db, *force_zv, &err);

  if (err != NULL) {
    zend_throw_exception(zend_ce_exception, err, 0);
    return;
  }
}
PHP_METHOD(rocksdb, destroy) {
  char *err = NULL;
  zval *options_zv = NULL;
  php_rocksdb_db_object *this = NULL;
  this = Z_ROCKSDB_DB_P(getThis() TSRMLS_CC);

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &options_zv) == FAILURE) {
    return;
  }

  rocksdb_options_t *options = php_rocksdb_get_open_options(options_zv);
  rocksdb_destroy_db(options, this->name, &err);
  rocksdb_options_destroy(options);

  RETURN_TRUE;
}
PHP_METHOD(rocksdb, repair) {
  char *name;
  size_t name_len;
  zval *options_zv = NULL;
  rocksdb_options_t *options;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|a",
    &name, &name_len, &options_zv) == FAILURE) {
    return;
  }

  char *err = NULL;

  options = php_rocksdb_get_open_options(options_zv);
  rocksdb_repair_db(options, (const char *) name, &err);

  if (err != NULL) {
    zend_throw_exception(zend_ce_exception, err, 0);
    return;
  }
}
PHP_METHOD(rocksdb, close) {
  php_rocksdb_db_object *this;

  if (zend_parse_parameters_none() == FAILURE) {
    return;
  }

  this = Z_ROCKSDB_DB_P(getThis() TSRMLS_CC);

  if (this->db) {
    rocksdb_close(this->db);
    this->db = NULL;
  }

  RETURN_TRUE;
}
