--TEST--
Open database create_if_missing, read_only
--SKIPIF--
<?php if (!extension_loaded("rocksdb")) print "skip"; ?>
--FILE--
<?php
include "helpers.php";
cleanup_rocksdb_on_shutdown();

$rocksdb_path = dirname(__FILE__) . '/rocksdb-basic.test-db';
$db = new RocksDb\RocksDb($rocksdb_path, [
  'create_if_missing' => true
]);
$db->close();
$db = new RocksDb\RocksDb($rocksdb_path, [
  'create_if_missing' => true,
  'read_only' => true
]);
var_dump($db->put('key', 'value'));
?>
--EXPECTF--
Fatal error: Uncaught RocksDb\Exception: Not implemented: Not supported operation in read only mode. in %s
Stack trace:
#0 %s: RocksDb\RocksDb->put('key', 'value')
#1 {main}
  thrown in %s on line %d
