<?php
$width = 71;
$height = 28;
$sur = new CairoImageSurface(CairoFormat::ARGB32, $width, $height);
$con = new CairoContext($sur);

$dash = array(8.0, 2.0);
$con->setSourceRgb(1, 1, 1);
$con->paint();

$con->setSourceRgb(0., 0., 0);

$con->setLineWidth(2); /* This is vital to reproduce the bug. */

/* First check simple rectangles */
$con->rectangle(2,2,67,24);

$con->setDash($dash, 9.0);
$con->stroke();

$sur->writeToPng(dirname(__FILE__)  . '/leaky-dash.png');