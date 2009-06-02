<?php
$width = 50;
$height = 50;
$sur = new CairoImageSurface(CairoFormat::ARGB32, $width, $height);
$con = new CairoContext($sur);

$con->setSourceRgb ( 0.5, 0.5, 0.5);
$con->paint ();
$con->save ();
$pattern = new CairoLinearGradient(0, 0, 10.0, 0);
$pattern->addColorStopRgb ( 0.0, 0.0, 0.0, 1.0);
$pattern->addColorStopRgb ( 1.0,1.0, 0.0, 0.0);
$pattern->setExtend (CairoExtend::REFLECT);
$con->setSource ($pattern);
$con->rectangle ( 0.0, 0.0, $width, $height);
$con->fill ();
$con->restore ();

$sur->writeToPng(dirname(__FILE__)  . "/linear-gradient-reflect-php.png");
?>

