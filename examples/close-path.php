<?php

use Cairo\Context;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 32, 16);
$context = new Context($surface);

$context->save();
$context->setSourceRgb(1, 1, 1);
$context->paint();
$context->restore();

$context->arc(8, 8, 4, 0, M_PI);
$context->closePath();
$context->arc(8, 8, 4, M_PI, 2 * M_PI);
$context->fill();

$context->translate(16, 0);
$context->moveTo(8, 4);
$context->arcNegative(8, 8, 4, 3 * M_PI / 2, M_PI / 2);
$context->closePath();
$context->curveTo(12, 4, 12, 12, 8, 12);

$path = $context->copyPathFlat();
$context->newPath();
$context->appendPath($path);
$context->fill();

$surface->writeToPng(dirname(__FILE__).'/close-path-php.png');


