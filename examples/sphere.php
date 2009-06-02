<?php
$Surface = new CairoImageSurface(0,256,256);
$ctx = new CairoContext($Surface);
$ctx->setAntialias(0);
$ctx->setFillRule(0);
$ctx->scale(256/1.0, 256/1.0);

$pat = new CairoLinearGradient(0.0, 0.0, 0.0, 1.0);
$pat->addColorStopRgba(1, 0, 0, 0, 1);
$pat->addColorStopRgba(0, 1, 1, 1, 1);
$ctx->rectangle(0,0,1,1);
$ctx->setSource($pat);
$ctx->fill();

$pat = new CairoRadialGradient(0.45, 0.4, 0.1, 0.4, 0.4, 0.5);
$pat->addColorStopRgba(0, 1, 1, 1, 1);
$pat->addColorStopRgba(1, 0, 0, 0, 1);
$ctx->setSource($pat);
$ctx->arc(.5, .5, .3, 0, 2*3.14);
$ctx->fill();

$check = $ctx->getTarget();
$check->writeToPng(dirname(__FILE__) . '/sphere.png');