--TEST--
rocksdb - iterator
--SKIPIF--
<?php if (!extension_loaded("rocksdb")) print "skip"; ?>
--FILE--
<?php
include "helpers.php";
cleanup_rocksdb_on_shutdown();

$rocksdb_path = dirname(__FILE__) . '/rocksdb-basic.test-db';
$db = new RocksDb\RocksDb($rocksdb_path, ['create_if_missing' => true]);
$db->put('x', '1');
$db->put('y', '2');
$db->put('z', '3');
$it = $db->getIterator([]);
while($it->valid()) {
  var_dump($it->key(), $it->current());
  $it->next();
}
?>
--EXPECTF--
string(1) "x"
string(1) "1"
string(1) "y"
string(1) "2"
string(1) "z"
string(1) "3"
