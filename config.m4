dnl
dnl $Id$
dnl

PHP_ARG_ENABLE(rocksdb, whether to enable RocksDb support,
[  --disable-rocksdb          Disable RocksDb support], yes)

if test "$PHP_ROCKSDB" != "no"; then
  AC_DEFINE([HAVE_ROCKSDB],1 ,[whether to enable RocksDb support])
  AC_HEADER_STDC

PHP_ADD_LIBRARY_WITH_PATH("rocksdb", "/usr/local/lib", ROCKSDB_SHARED_LIBADD)
PHP_SUBST(ROCKSDB_SHARED_LIBADD)

PHP_NEW_EXTENSION(rocksdb,
    php_rocksdb.c \
    rocksdb.c \
    rocksdb_backup_engine_info.c \
    rocksdb_cache.c \
    rocksdb_backup_engine.c \
    rocksdb_iterator.c \
    rocksdb_snapshot.c \
    rocksdb_write_batch.c \
    rocksdb_compaction_filter.c \
    rocksdb_comparator.c \
    rocksdb_merge_operator.c \
    rocksdb_exception.c,
    $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)

  PHP_INSTALL_HEADERS([ext/rocksdb], [php_rocksdb.h])
  PHP_ADD_MAKEFILE_FRAGMENT()
fi
