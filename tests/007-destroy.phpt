--TEST--
rocksdb - destroy
--SKIPIF--
<?php if (!extension_loaded("rocksdb")) print "skip"; ?>
--FILE--
<?php
$rocksdb_path = dirname(__FILE__) . '/rocksdb-basic.test-db';
$db = new RocksDb\RocksDb($rocksdb_path, ['create_if_missing' => true]);
$db->close();
$db->destroy([]);
?>
--EXPECTF--
