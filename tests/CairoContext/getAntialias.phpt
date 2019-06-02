--TEST--
Cairo\Context->getAntialias() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new Cairo\Surface\Image(Cairo\Surface\ImageFormat::ARGB32, 50, 50);
var_dump($surface);

$context = new Cairo\Context($surface);
var_dump($context);

var_dump($context->getAntialias());

/* Wrong number args */
try {
    $context->getAntialias('foobar');
    trigger_error('getAntialias requires no args');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
object(Cairo\Antialias)#3 (2) {
  ["__elements"]=>
  array(7) {
    ["DEFAULT"]=>
    int(0)
    ["NONE"]=>
    int(1)
    ["GRAY"]=>
    int(2)
    ["SUBPIXEL"]=>
    int(3)
    ["FAST"]=>
    int(4)
    ["GOOD"]=>
    int(5)
    ["BEST"]=>
    int(6)
  }
  ["__value"]=>
  int(0)
}
Cairo\Context::getAntialias() expects exactly 0 parameters, 1 given