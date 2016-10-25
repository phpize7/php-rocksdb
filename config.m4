dnl $Id$
dnl config.m4 for extension rocksdb

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(rocksdb, for rocksdb support,
dnl Make sure that the comment is aligned:
dnl [  --with-rocksdb             Include rocksdb support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(rocksdb, whether to enable rocksdb support,
dnl Make sure that the comment is aligned:
dnl [  --enable-rocksdb           Enable rocksdb support])

if test "$PHP_ROCKSDB" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-rocksdb -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/rocksdb.h"  # you most likely want to change this
  dnl if test -r $PHP_ROCKSDB/$SEARCH_FOR; then # path given as parameter
  dnl   ROCKSDB_DIR=$PHP_ROCKSDB
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for rocksdb files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       ROCKSDB_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$ROCKSDB_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the rocksdb distribution])
  dnl fi

  dnl # --with-rocksdb -> add include path
  dnl PHP_ADD_INCLUDE($ROCKSDB_DIR/include)

  dnl # --with-rocksdb -> check for lib and symbol presence
  dnl LIBNAME=rocksdb # you may want to change this
  dnl LIBSYMBOL=rocksdb # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $ROCKSDB_DIR/$PHP_LIBDIR, ROCKSDB_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_ROCKSDBLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong rocksdb lib version or lib not found])
  dnl ],[
  dnl   -L$ROCKSDB_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(ROCKSDB_SHARED_LIBADD)

  PHP_NEW_EXTENSION(rocksdb, rocksdb.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
