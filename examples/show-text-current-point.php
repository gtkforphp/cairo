<?php
$sur = new CairoImageSurface(CairoFormat::ARGB32, 300, 16);
$con = new CairoContext($sur);
$con->save();
$con->setSourceRgb ( 1.0, 1.0, 1.0); /* white */
$con->paint();
$con->restore();

$con->selectFontFace('Bitstream Vera Sans',
            CairoFontSlant::NORMAL,
            CairoFontWeight::NORMAL);
$con->setFontSize(12);
$con->setSourceRgb( 0, 0, 0); /* black */

$con->moveTo(0, 12);
$con->showText('Hello from the ');
$con->showText('show-text-current-point-php');
$con->showText(' test.');
$sur->writeToPng(dirname(__FILE__)  . '/show-text-current-point.png');