<?php
$sur = new CairoImageSurface(FORMAT_ARGB32, 2, 2);
$con = new CairoContext($sur);

$pat = new CairoLinearGradient(0,0,1,1);
$con->setSource($pat);
$con->paint();

unset($pat);

$pat = new CairoRadialGradient(0,0,0,1,1,1);
$con->setSource($pat);
$con->paint();

$sur->writeToPng("gradient-zero-stops-php.png");
?>

