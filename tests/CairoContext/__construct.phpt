--TEST--
new CairoContext [ __construct() method ]
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new CairoImageSurface(CAIRO_FORMAT_ARGB32, 50, 50);
var_dump($surface);

$context = new CairoContext($surface);
var_dump($context);

/* Wrong number args - 1 */
try {
    new CairoContext();
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong number args - 2 */
try {
    new CairoContext($surface, 10);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* Wrong arg type 1 */
try {
    new CairoContext(1);
    trigger_error('We should bomb here');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoContext)#%d (0) {
}
CairoContext::__construct() expects exactly 1 parameter, 0 given
CairoContext::__construct() expects exactly 1 parameter, 2 given
CairoContext::__construct() expects parameter 1 to be CairoSurface, integer given