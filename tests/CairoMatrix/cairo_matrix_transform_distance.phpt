--TEST--
cairo_matrix_transform_distance function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$matrix = cairo_matrix_init();
var_dump($matrix);

var_dump(cairo_matrix_transform_distance($matrix, 1.0, 1.0));

// bad type hint is an E_RECOVERABLE_ERROR, so let's hook a handler
function bad_class($errno, $errstr) {
	echo 'CAUGHT ERROR: ' . $errstr, PHP_EOL;
}
set_error_handler('bad_class', E_RECOVERABLE_ERROR);

// check number of args - should accept ONLY 3
cairo_matrix_transform_distance();
cairo_matrix_transform_distance($matrix);
cairo_matrix_transform_distance($matrix, 1);
cairo_matrix_transform_distance($matrix, 1, 1, 1);

// check arg types, should be matrix object, scalar (casts to float), scalar (casts to float)
cairo_matrix_transform_distance(1, 1, 1);
cairo_matrix_transform_distance($matrix, array(), 1);
cairo_matrix_transform_distance($matrix, 1, array());
?>
--EXPECTF--
object(CairoMatrix)#%d (0) {
}
array(2) {
  ["x"]=>
  float(%f)
  ["y"]=>
  float(%f)
}

Warning: cairo_matrix_transform_distance() expects exactly 3 parameters, 0 given in %s on line %d

Warning: cairo_matrix_transform_distance() expects exactly 3 parameters, 1 given in %s on line %d

Warning: cairo_matrix_transform_distance() expects exactly 3 parameters, 2 given in %s on line %d

Warning: cairo_matrix_transform_distance() expects exactly 3 parameters, 4 given in %s on line %d
CAUGHT ERROR: Argument 1 passed to cairo_matrix_transform_distance() must be an instance of CairoMatrix, integer given

Warning: cairo_matrix_transform_distance() expects parameter 1 to be CairoMatrix, integer given in %s on line %d

Warning: cairo_matrix_transform_distance() expects parameter 2 to be double, array given in %s on line %d

Warning: cairo_matrix_transform_distance() expects parameter 3 to be double, array given in %s on line %d