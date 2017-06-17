<?php

use Cairo\Context;
use Cairo\Filter;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$size = 20;
$pad = 2;
$surfaceSize = sqrt(($size - 2 * $pad) * ($size - 2 * $pad) / 2);

$surface = new Image(ImageFormat::ARGB32, $size, $size);
$context = new Context($surface);

$s = new Image(ImageFormat::RGB24, $surfaceSize, $surfaceSize);
$con2 = new Context($s);

$con2->setSourceRgb(1, 1, 1);
$con2->rectangle(0, 0, $surfaceSize / 2, $surfaceSize / 2);
$con2->fill();
$con2->setSourceRgb(1, 0, 0);
$con2->rectangle($surfaceSize / 2, 0, $surfaceSize / 2, $surfaceSize / 2);
$con2->fill();
$con2->setSourceRgb(0, 1, 0);
$con2->rectangle(0, $surfaceSize / 2, $surfaceSize / 2, $surfaceSize / 2);
$con2->fill();
$con2->setSourceRgb(0, 0, 1);
$con2->rectangle($surfaceSize / 2, $surfaceSize / 2, $surfaceSize / 2, $surfaceSize / 2);
$con2->fill();

/* First paint opaque background (black) so we don't need separate
 * ARGB32 and RGB24 reference images. */
$context->setSourceRgb(0, 0, 0); /* black */
$context->paint();

$context->translate($size / 2, $size / 2);
$context->rotate(M_PI / 4.0);
$context->translate(-$surfaceSize / 2, -$surfaceSize / 2);

$context->setSurface($s, 0, 0);
$pat = $context->getPattern();

$pat->setFilter(Filter::NEAREST);
$context->setPattern($pat);
$context->paint();

$surface->writeToPng(dirname(__FILE__).'/rotate-image-surface-paint-php.png');
