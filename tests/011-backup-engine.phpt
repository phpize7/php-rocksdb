--TEST--
rocksdb - backup engine
--SKIPIF--
<?php if (!extension_loaded("rocksdb")) print "skip"; ?>
--FILE--
<?php
include "helpers.php";
cleanup_rocksdb_on_shutdown();

$rocksdb_path = dirname(__FILE__) . '/rocksdb-basic.test-db';
$db = new RocksDb\RocksDb($rocksdb_path, ['create_if_missing' => true]);
$db->put('x', 1);
$engine = new RocksDb\BackupEngine($rocksdb_path);
$engine->createNewBackup($db);
$db->delete('x');
$engine->restoreDbFromLatestBackup($rocksdb_path, $rocksdb_path, [
	'set_keep_log_files' => true,
]);
$db->close();
$db = new RocksDb\RocksDb($rocksdb_path, ['create_if_missing' => true]);
var_dump($db->get('x'));
?>
--EXPECTF--
string(1) "1"
