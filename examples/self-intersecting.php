<?php
$sur = new CairoImageSurface(CairoFormat::ARGB32, 10 , 20);
$con = new CairoContext($sur);
$con->translate(1.0, 1.0);
$con->setSourceRgb(1, 0, 0); /* red */

/* First draw the desired shape with a fill */
$con->rectangle(0.5, 0.5,  4.0, 4.0);
$con->rectangle(3.5, 3.5,  4.0, 4.0);
$con->rectangle(3.5, 1.5, -2.0, 2.0);
$con->rectangle(6.5, 4.5, -2.0, 2.0);
$con->fill();

/* Then try the same thing with a stroke */
$con->translate(0, 10);
$con->moveTo(1.0, 1.0);
$con->relLineTo( 3.0,  0.0);
$con->relLineTo( 0.0,  6.0);
$con->relLineTo( 3.0,  0.0);
$con->relLineTo( 0.0, -3.0);
$con->relLineTo(-6.0,  0.0);
$con->closePath();

$con->setLineWidth(1.0);
$con->stroke();

$sur->writeToPng(dirname(__FILE__)  . '/self-intersecting.png');