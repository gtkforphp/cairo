--TEST--
Cairo\FontFace\Toy::__construct() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
// Test with all parameters
$c = new Cairo\FontFace\Toy("sans-serif", Cairo\FontSlant::NORMAL, Cairo\FontWeight::NORMAL);
var_dump($c);

// Test with 1 param
$c = new Cairo\FontFace\Toy("sans-serif");
var_dump($c);

// test with 2 params
$c = new Cairo\FontFace\Toy("sans-serif", Cairo\FontSlant::NORMAL);
var_dump($c);

// test with 3 params, 1 null
$c = new Cairo\FontFace\Toy("sans-serif", null, Cairo\FontWeight::NORMAL);
var_dump($c);

// We shouldn't accept 0 args
try {
    $c = new Cairo\FontFace\Toy();
} catch (TypeError $e) {
    var_dump($e->getMessage());
}
var_dump($c);

// Test with 1 param
$c = new Cairo\FontFace\Toy("NotARealFont");
var_dump($c);

// Test with a silly param
$o = array();
try {
    $c = new Cairo\FontFace\Toy($o);
} catch (TypeError $e) {
    var_dump($e->getMessage());
}
var_dump($c);
?>
--EXPECTF--
object(Cairo\FontFace\Toy)#%d (0) {
}
object(Cairo\FontFace\Toy)#%d (0) {
}
object(Cairo\FontFace\Toy)#%d (0) {
}
object(Cairo\FontFace\Toy)#%d (0) {
}
string(69) "Cairo\FontFace\Toy::__construct() expects at least 1 parameter, 0 given"
object(Cairo\FontFace\Toy)#2 (0) {
}
object(Cairo\FontFace\Toy)#1 (0) {
}
string(77) "Cairo\FontFace\Toy::__construct() expects parameter 1 to be string, array given"
object(Cairo\FontFace\Toy)#1 (0) {
}
