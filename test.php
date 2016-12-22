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


use RocksDb\RocksDb;

$rocks = new RocksDb('/tmp/rocks.db', ['create_if_missing' => true]);
$rocks->put('counter', 0);
$rocks->get('counter');


use RocksDb\RocksDb;
use RocksDb\WriteBatch;

$rocks = new RocksDb('/tmp/rocks.db', ['create_if_missing' => true]);
$batch = new WriteBatch();

for ($i = 0; $i < 10; $i++) {
	$batch->put('user_' . $i, json_encode([]))
}

$rocks->write($batch);





use RocksDb\RocksDb;
use RocksDb\MergeOperator;

$mergeOperator = new class implements MergeOperator {
		function fullMerge($key, $existingValue, &$value): boolval {
			if ($existingValue) {
				$value = $existingValue + $value;
			}

			return true;
		}

		function partialMerge(): bool {
			return true;
		}

		function name(): string {
			return 'AssocCounter';
		}
};

$rocks = new RocksDb('/tmp/rocks.db', [
	'create_if_missing' => true,
	'merge_operator' => $mergeOperator
]);
$rocks->merge('x', 1);
$rocks->merge('x', 1);

print $rocks->get('x'); // prints 2


use RocksDb\RocksDb;
use RocksDb\BackupEngine;

$rocks = new RocksDb('/tmp/rocks.db', [
	'create_if_missing' => true
]);
$rocks->put('a', 'v1');
$rocks->put('b', 'v2');
$rocks->put('c', 'v3');

$backup = new BackupEngine('/tmp/backups');
$backup->createBackup($rocks, [
	'flush_before_backup' => true
]);

$backup->restoreLatestBackup('rocks.db', 'rocks.db');




use RocksDb\WriteBatch;

$batch = new WriteBatch();
for ($i = 0; $i < 10; $i++) {
	$batch->put('user_' . $i, json_encode([]))
}
$iterator = $batch->getIterator();

foreach ($iterator as $key => $value) {
	print $key, $value;
}
