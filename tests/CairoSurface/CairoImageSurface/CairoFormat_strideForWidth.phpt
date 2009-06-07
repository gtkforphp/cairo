--TEST--
CairoFormat::strideForWidth() method
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
if(!method_exists('CairoFormat', 'strideForWidth')) die('skip - CairoFormat::strideForWidth not available');
?>
--FILE--
<?php
echo CairoFormat::strideForWidth(1, 5);

/* Wrong number args */
CairoFormat::strideForWidth();

/* Wrong number args 2 */
CairoFormat::strideForWidth(1);

/* Wrong number args 3 */
CairoFormat::strideForWidth(1, 1, 1);

/* Wrong arg type */
CairoFormat::strideForWidth(array(), 1);

/* Wrong arg type */
CairoFormat::strideForWidth(1, array());
?>
--EXPECTF--
20
Warning: CairoFormat::strideForWidth() expects exactly 2 parameters, 0 given in %s on line %d

Warning: CairoFormat::strideForWidth() expects exactly 2 parameters, 1 given in %s on line %d

Warning: CairoFormat::strideForWidth() expects exactly 2 parameters, 3 given in %s on line %d

Warning: CairoFormat::strideForWidth() expects parameter 1 to be long, array given in %s on line %d

Warning: CairoFormat::strideForWidth() expects parameter 2 to be long, array given in %s on line %d