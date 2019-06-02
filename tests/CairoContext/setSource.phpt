--TEST--
Cairo\Context->setSource() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new Cairo\Surface\Image(CAIRO_FORMAT_ARGB32, 50, 50);
var_dump($surface);

$context = new Cairo\Context($surface);
var_dump($context);

$pattern = new Cairo\Pattern\Solid(0.3, 0.3, 0.3);
var_dump($pattern);

$context->setSource($pattern);

var_dump($context->getSource()->getRGBA());

$pattern = new Cairo\Pattern\Solid(0.3, 0.3, 0.3);
var_dump($pattern);

$context->setSource($pattern);

var_dump($context->getSource()->getRGBA());

/* Wrong number args */
try {
    $context->setSource();
    trigger_error('setSource requires only one arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args */
try {
    $context->setSource($pattern, 1);
    trigger_error('setSource requires only one arg');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type */
try {
    $context->setSource(array());
    trigger_error('setSource expects instanceof CairoPattern');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

// DO NOT REMOVE: workaround for GC-related bug in 5.3
die;
?>
--EXPECTF--
object(Cairo\Surface\Image)#%d (0) {
}
object(Cairo\Context)#%d (0) {
}
object(Cairo\Pattern\Solid)#%d (0) {
}
array(4) {
  ["red"]=>
  float(0.3)
  ["green"]=>
  float(0.3)
  ["blue"]=>
  float(0.3)
  ["alpha"]=>
  float(1)
}
object(Cairo\Pattern\Solid)#%d (0) {
}
array(4) {
  ["red"]=>
  float(0.3)
  ["green"]=>
  float(0.3)
  ["blue"]=>
  float(0.3)
  ["alpha"]=>
  float(1)
}
Cairo\Context::setSource() expects exactly 1 parameter, 0 given
Cairo\Context::setSource() expects exactly 1 parameter, 2 given
Cairo\Context::setSource() expects parameter 1 to be CairoPattern, array given
