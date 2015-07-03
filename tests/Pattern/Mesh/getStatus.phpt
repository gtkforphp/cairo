--TEST--
Cairo\Pattern->getStatus() method [using Solid]
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use Cairo\Pattern\Solid;

$pattern = new Solid(1, 1, 1);
$status = $pattern->getStatus();
var_dump($status == Cairo\Status::SUCCESS);
var_dump($status->getStatusMessage());

try {
    $pattern->getStatus('foo');
    trigger_error('status requires no args');
} catch (TypeError $e) {
    echo $e->getMessage();
}
?>
--EXPECT--
bool(true)
string(21) "no error has occurred"
Cairo\Pattern::getStatus() expects exactly 0 parameters, 1 given