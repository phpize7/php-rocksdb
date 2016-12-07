<?php

namespace App;

use RocksDb\Snapshot;
use RocksDb\Iterator;
use RocksDb\BackupEngine;

// Create instance
$d = new RocksDb('/tmp/rocksdb');

// Purge old backups and create new backup from current RocksDb instance
$b = new BackupEngine($options, $path);
$b->purgeOldBackups();
$b->createNewBackup($db);
$b->restoreDbFromLatestBackup($dir, $wal, $options);
$b->getInfoCount();
$i = $b->getBackupInfo(); // => RocksDb\BackupEngineInfo
$b->close();

//RocksDb\BackupEngineInfo
$i->count();
$i->getTimestamp();
$i->getBackupId();
$i->getSize();
$i->getNumberFiles();
$i->destroy();

//RocksDb\Snapshot
$snapshot = new Snapshot($db);
$snapshot->release();


//RocksDb\Iterator

$it = new Iterator($db);

use RocksDb\RocksDb;
use RocksDb\CompactionFilter; // Abstract Class

$rocks = new RocksDb('/tmp/rocksdb', [
	'set_compaction_filter' => new class extends CompactionFilter {
		function filter($level, $key, $keyLength, $existingValue, $valueLength, $newValue, $newValueLength, $valueChanged) {
			// do something
		}
	}
]);
