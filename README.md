# PHP-RocksDb: RocksDb implementation for PHP

The RocksDB library provides a persistent key value store. Keys and values are arbitrary byte arrays. The keys are ordered within the key value store according to a user-specified comparator function.

## Installation

	Clone git@github.com:facebook/rocksdb.git and run make static_lib
	
	Upgrade your gcc to version at least 4.8 to get C++11 support.
	Install gflags. First, try: sudo apt-get install libgflags-dev If this doesn't work and you're using Ubuntu, here's a nice tutorial: (http://askubuntu.com/questions/312173/installing-gflags-12-04)
	Install snappy. This is usually as easy as: sudo apt-get install libsnappy-dev.
	Install zlib. Try: sudo apt-get install zlib1g-dev.
	Install bzip2: sudo apt-get install libbz2-dev.
	Install zstandard: sudo apt-get install libzstd-dev.

	$ git clone https://github.com/phpize7/php-rocksdb.git
	$ cd php-rocksdb
	$ phpize
	$ ./configure --with-rocksdb
	$ make
	$ make install
