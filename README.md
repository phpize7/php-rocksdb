# PHP-RocksDb: RocksDb implementation for PHP

The RocksDB library provides a persistent key value store. Keys and values are arbitrary byte arrays. The keys are ordered within the key value store according to a user-specified comparator function.

## Installation

	$ git clone https://github.com/phpize7/php-rocksdb.git
	$ cd php-rocksdb
	$ phpize
	$ ./configure --with-rocksdb
	$ make
	$ make install

## Usage
````php
<?php

use RocksDb\RocksDb;
use RocksDb\CompactionFilter;
use RocksDb\BackupEngine;

$rocks = new RocksDb('/tmp/rocksdb', [
	'set_compaction_filter' => new class extends CompactionFilter {
	   	function filter($level, $key, $existingValue, $newValue, $valueChanged) {
				// do something
		}
	}
]);

$rocks->put('key', 'value);
$rocks->get('key');

$rocks->getSnapshot(); // => RocksDb\Snapshot

$engine = new BackupEngine();
$engine->createNewBackup($rocks);
````
