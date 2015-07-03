--TEST--
Cairo\Pattern\Solid [__construct() method ] with extended class
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use Cairo\Pattern\Solid;
use Cairo\Exception;

class Bad extends Solid {
    public function __construct() {
    }
}

$fail = new Bad();

try {
    $fail->getStatus();
} catch (Exception $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECT--
Internal pattern object missing in Bad, you must call parent::__construct in extended classes