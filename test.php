<?php

use RocksDb\BackupEngineInfo;

var_dump(
  get_class_methods(new RocksDb()),
  get_class_methods(new BackupEngineInfo())
);
