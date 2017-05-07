<?php

use RocksDb\RocksDb;
use RocksDb\BackupEngine;

$name = '/tmp/rocksdb.db';

$rocks = new RocksDb($name, ['create_if_missing' => true]);
$rocks->put('version', '1.0');

$engine = new BackupEngine($name);
$engine->createNewBackup($rocks);

$rocks->delete('version');

$engine->restoreDbFromLatestBackup($name, $name, [
  'set_keep_log_files' => true,
]);
$rocks->close();

$rocks = new RocksDb($name, ['create_if_missing' => true]);

die(var_dump(
  $rocks->get('version')
));
