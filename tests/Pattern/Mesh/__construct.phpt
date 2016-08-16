--TEST--
Cairo\Pattern\Mesh->__construct()
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use Cairo\Pattern\Mesh;

$pattern = new Mesh();
var_dump($pattern);

/* Wrong number args - none needed */
try {
    new Mesh(1);
    trigger_error('__construct args should fail');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Pattern\Mesh)#%d (0) {
}
Cairo\Pattern\Mesh::__construct() expects exactly 0 parameters, 1 given