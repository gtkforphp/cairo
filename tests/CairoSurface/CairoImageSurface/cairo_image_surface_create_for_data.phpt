--TEST--
cairo_image_surface_create_for_data() function
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = cairo_image_surface_create_for_data('', CAIRO_FORMAT_ARGB32, 50, 50);
var_dump($surface);

/* Wrong number args - 1 */
cairo_image_surface_create_for_data();

/* Wrong number args - 2 */
cairo_image_surface_create_for_data('');

/* Wrong number args - 3 */
cairo_image_surface_create_for_data('', CAIRO_FORMAT_ARGB32);

/* Wrong number args - 4 */
cairo_image_surface_create_for_data('', CAIRO_FORMAT_ARGB32, 1);

/* Wrong number args - 5 */
cairo_image_surface_create_for_data('', CAIRO_FORMAT_ARGB32, 1, 1, 1);

/* Wrong arg type 1 */
cairo_image_surface_create_for_data(array(), 1, 1, 1);

/* Wrong arg type 2 */
cairo_image_surface_create_for_data('', array(), 1, 1);

/* Wrong arg type 3 */
cairo_image_surface_create_for_data('', 1, array(), 1);

/* Wrong arg type 4 */
cairo_image_surface_create_for_data('', 1, 1, array());
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}

Warning: cairo_image_surface_create_for_data() expects exactly 4 parameters, 0 given in %s on line %d

Warning: cairo_image_surface_create_for_data() expects exactly 4 parameters, 1 given in %s on line %d

Warning: cairo_image_surface_create_for_data() expects exactly 4 parameters, 2 given in %s on line %d

Warning: cairo_image_surface_create_for_data() expects exactly 4 parameters, 3 given in %s on line %d

Warning: cairo_image_surface_create_for_data() expects exactly 4 parameters, 5 given in %s on line %d

Warning: cairo_image_surface_create_for_data() expects parameter 1 to be string, array given in %s on line %d

Warning: cairo_image_surface_create_for_data() expects parameter 2 to be long, array given in %s on line %d

Warning: cairo_image_surface_create_for_data() expects parameter 3 to be long, array given in %s on line %d

Warning: cairo_image_surface_create_for_data() expects parameter 4 to be long, array given in %s on line %d
