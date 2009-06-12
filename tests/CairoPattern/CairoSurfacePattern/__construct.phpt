--TEST--
new CairoSurfacePattern [ __construct method ]
--SKIPIF--
<?php
if(!extension_loaded('cairo')) die('skip - Cairo extension not available');
?>
--FILE--
<?php
$surface = new CairoImageSurface(CairoFormat::ARGB32, 50, 50);
var_dump($surface);

$pattern = new CairoSurfacePattern($surface);
var_dump($pattern);

/* Total number of args needed = 1 */
try {
    new CairoSurfacePattern();
    trigger_error('CairoSurfacePattern with no args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
try {
    new CairoSurfacePattern($surface, 1);
    trigger_error('CairoSurfacePattern with too many args');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}

/* arg must be instanceof CairoSurface */
try {
    new CairoSurfacePattern(1);
    trigger_error('Arg 1 must be CairoSurface');
} catch (CairoException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
--EXPECTF--
object(CairoImageSurface)#%d (0) {
}
object(CairoSurfacePattern)#%d (0) {
}
CairoSurfacePattern::__construct() expects exactly 1 parameter, 0 given
CairoSurfacePattern::__construct() expects exactly 1 parameter, 2 given
CairoSurfacePattern::__construct() expects parameter 1 to be CairoSurface, integer given