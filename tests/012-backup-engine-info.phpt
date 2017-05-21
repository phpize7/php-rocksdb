--TEST--
rocksdb - backup engine info
--SKIPIF--
<?php if (!extension_loaded("rocksdb")) print "skip"; ?>
--FILE--
<?php
include "helpers.php";
cleanup_rocksdb_on_shutdown();

$rocksdb_path = dirname(__FILE__) . '/rocksdb-basic.test-db';
$db = new RocksDb\RocksDb($rocksdb_path, ['create_if_missing' => true]);
$engine = new RocksDb\BackupEngine($rocksdb_path);
$engine->purgeOldBackups(0);
$engine->createNewBackup($db);
$info = $engine->getBackupInfo();
var_dump($info->getCount());
?>
--EXPECTF--
int(1)
