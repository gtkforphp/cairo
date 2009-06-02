<?php
$sur = new CairoImageSurface(CairoFormat::ARGB32, 1, 1);
$con = new CairoContext($sur);

$con2 = new CairoContext($sur);
$s = new CairoImageSurface(CairoFormat::ARGB32, 0, 0);
$s->createFromPng('__THIS_FILE_DOES_NOT_EXIST');

$pat = new CairoSurfacePattern($s);
$con2->setSource($pat);
$con2->paint();

$con2=$con->getTarget();
$pat = new CairoSurfacePattern(NULL);
$con2->setSource($pat);
$con2->paint();

$sur->writeToPng(dirname(__FILE__)  . '/nil-surface-php.png');