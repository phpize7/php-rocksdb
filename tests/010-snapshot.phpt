--TEST--
rocksdb - snapshot
--SKIPIF--
<?php if (!extension_loaded("rocksdb")) print "skip"; ?>
--FILE--
<?php
include "helpers.php";
cleanup_rocksdb_on_shutdown();

$rocksdb_path = dirname(__FILE__) . '/rocksdb-basic.test-db';
$db = new RocksDb\RocksDb($rocksdb_path, ['create_if_missing' => true]);
$db->put('x', 1);
$snapshot = $db->createSnapshot();
$db->delete('x');
var_dump($db->get('x', [
  'snapshot' => $snapshot,
]));
?>
--EXPECTF--
string(1) "1"
