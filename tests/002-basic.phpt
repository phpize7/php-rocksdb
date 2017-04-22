--TEST--
rocksdb - basic: get(), put(), delete()
--SKIPIF--
<?php if (!extension_loaded("rocksdb")) print "skip"; ?>
--FILE--
<?php
include "helpers.php";
cleanup_rocksdb_on_shutdown();

$rocksdb_path = dirname(__FILE__) . '/rocksdb-basic.test-db';
$db = new RocksDb\RocksDb($rocksdb_path, ['create_if_missing' => true]);
var_dump($db->put('key', 'value'));
var_dump($db->get('key'));
var_dump($db->get('non-exists-key'));
var_dump($db->put('name', 'justinas'));
var_dump($db->get('name'));
var_dump($db->delete('name'));
var_dump($db->get('name'));
?>
--EXPECTF--
bool(true)
string(5) "value"
bool(false)
bool(true)
string(8) "justinas"
bool(true)
bool(false)
