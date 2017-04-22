--TEST--
rocksdb - open
--SKIPIF--
<?php if (!extension_loaded("rocksdb")) print "skip"; ?>
--FILE--
<?php
include "helpers.php";
cleanup_rocksdb_on_shutdown();

$rocksdb_path = dirname(__FILE__) . '/rocksdb-basic.test-db';
$db = new RocksDb\RocksDb($rocksdb_path, [
  'read_only' => true,
  'create_if_missing' => true
]);
?>
--EXPECTF--
