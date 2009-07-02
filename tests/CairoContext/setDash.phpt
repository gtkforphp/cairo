--TEST--
CairoContext->setDash() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new CairoImageSurface(CairoFormat::ARGB32, 50, 50);
var_dump($surface);

$context = new CairoContext($surface);
var_dump($context);

$context->setDash(array(1,2,3));
var_dump($context->getDash());

/* Wrong number args - expects 1 or 2 */
try {
    $context->setDash();
    trigger_error('setDash requires 1-2 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - expects 1 or 2 */
try {
    $context->setDash(array(), 1, 1);
    trigger_error('setDash requires 1-2 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}


/* Wrong arg type, expects array of double, double offset */
try {
    $context->setDash(3);
    trigger_error('setDash requires 1-2 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

try {
    $context->setDash(array('foo'));
    trigger_error('setDash requires 1-2 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

try {
    $context->setDash(array(1), 'foo');
    trigger_error('setDash requires 1-2 args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
array(2) {
  ["dashes"]=>
  array(3) {
    [0]=>
    float(1)
    [1]=>
    float(2)
    [2]=>
    float(3)
  }
  ["offset"]=>
  float(0)
}
CairoContext::setDash() expects at least 1 parameter, 0 given
CairoContext::setDash() expects at most 2 parameters, 3 given
CairoContext::setDash() expects parameter 1 to be array, integer given
invalid value for a dash setting
CairoContext::setDash() expects parameter 2 to be double, string given