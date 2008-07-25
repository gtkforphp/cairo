<?php
$sur = new CairoImageSurface(FORMAT_ARGB32, 76,76);
$con = new CairoContext($sur);

$con->setSourceRgb ( 1, 1, 1);
$con->paint ();
$con->setAntialias (ANTIALIAS_NONE);
$con->setSourceRgb ( 0, 0, 0);

$con->translate( -300, -300);
$con->scale( 677.0/26, 677.0/26);
$con->translate( 1, 1);
$con->rectangle( 11, 11, 1, 1);
$con->rectangle( 11, 12, 1, 1);
$con->rectangle( 12, 11, 1, 1);
$con->rectangle( 12, 12, 1, 1);
$con->setSourceRgb( 0, 0, 0);
$con->fill();

$sur->writeToPng("rectangle-rounding-error-php.png");
?>

