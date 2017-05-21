--TEST--
rocksdb - write batch
--SKIPIF--
<?php if (!extension_loaded("rocksdb")) print "skip"; ?>
--FILE--
<?php
include "helpers.php";
cleanup_rocksdb_on_shutdown();

$rocksdb_path = dirname(__FILE__) . '/rocksdb-basic.test-db';
$db = new RocksDb\RocksDb($rocksdb_path, ['create_if_missing' => true]);
$batch = new RocksDb\WriteBatch();
$batch->put('x', 1);
$batch->put('y', 2);
$db->write($batch);
var_dump($db->get('x'));
var_dump($db->get('y'));
?>
--EXPECTF--
string(1) "1"
string(1) "2"
