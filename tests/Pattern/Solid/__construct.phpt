--TEST--
new Cairo\Pattern\Solid [__construct() method ]
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use Cairo\Pattern\Solid;

$red = 0.8;
$green = 0.6;
$blue = 0.5;
$alpha = 0.7;

$pattern = new Solid($red, $green, $blue);
var_dump($pattern);

$values =$pattern->getRGBA();
var_dump($values);
var_dump($red === $values['red']);
var_dump($green === $values['green']);
var_dump($blue === $values['blue']);

$pattern = new Solid($red, $green, $blue, $alpha);
var_dump($pattern);

$values =$pattern->getRGBA();
var_dump($values);
var_dump($red === $values['red']);
var_dump($green === $values['green']);
var_dump($blue === $values['blue']);
var_dump($alpha === $values['alpha']);

/* Wrong number args - at least 3, no more than 4 */
try {
    new Solid();
    trigger_error('__construct with no args should fail');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - at least 3, no more than 4 */
try {
    new Solid(1);
    trigger_error('__construct with 1 arg should fail');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - at least 3, no more than 4 */
try {
    new Solid(1, 1);
    trigger_error('__construct with 2 args should fail');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - at least 3, no more than 4 */
try {
    new Solid(1, 1, 1, 1, 1);
    trigger_error('__construct with 5 args should fail');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    new Solid(array(), 1, 1, 1);
    trigger_error('__construct requires all doubles');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 2 */
try {
    new Solid(1, array(), 1, 1);
    trigger_error('__construct requires all doubles');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 3 */
try {
    new Solid(1, 1, array(), 1);
    trigger_error('__construct requires all doubles');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 4 */
try {
    new Solid(1, 1, 1, array());
    trigger_error('__construct requires all doubles');
} catch (TypeError $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(Cairo\Pattern\Solid)#%d (0) {
}
array(4) {
  ["red"]=>
  float(0.8)
  ["green"]=>
  float(0.6)
  ["blue"]=>
  float(0.5)
  ["alpha"]=>
  float(1)
}
bool(true)
bool(true)
bool(true)
object(Cairo\Pattern\Solid)#%d (0) {
}
array(4) {
  ["red"]=>
  float(0.8)
  ["green"]=>
  float(0.6)
  ["blue"]=>
  float(0.5)
  ["alpha"]=>
  float(0.7)
}
bool(true)
bool(true)
bool(true)
bool(true)
Cairo\Pattern\Solid::__construct() expects at least 3 parameters, 0 given
Cairo\Pattern\Solid::__construct() expects at least 3 parameters, 1 given
Cairo\Pattern\Solid::__construct() expects at least 3 parameters, 2 given
Cairo\Pattern\Solid::__construct() expects at most 4 parameters, 5 given
Cairo\Pattern\Solid::__construct() expects parameter 1 to be float, array given
Cairo\Pattern\Solid::__construct() expects parameter 2 to be float, array given
Cairo\Pattern\Solid::__construct() expects parameter 3 to be float, array given
Cairo\Pattern\Solid::__construct() expects parameter 4 to be float, array given