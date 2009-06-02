<?php
$char = 'Cairo';
$sur = new CairoImageSurface(0,500,500);
$con = new CairoContext($sur);

$con->selectFontFace('Sans');
$con->setFontSize(100);
$ext = $con->textExtents($char);

$x = 25.0;
$y = 150.0;
$con->moveTo($x, $y);
$con->showText($char);

$con->setSourceRgba(1,0.2,0.2,0.6);
$con->setLineWidth(6.0);
$con->arc($x, $y, 10, 0, 2*3.14);
$con->fill();
$con->moveTo($x, $y);
$con->relLineTo(0, -1*$ext['height']);
$con->relLineTo($ext['width'], 0);
$con->relLineTo($ext['x_bearing'], -1*$ext['y_bearing']);
$con->stroke();
$sur->writeToPng(dirname(__FILE__) . '/text-extents.png');