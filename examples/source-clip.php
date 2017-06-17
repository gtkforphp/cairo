<?php

use Cairo\Context;
use Cairo\Surface\Content;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 12, 12);
$context = new Context($surface);
$source = $surface->createSimilar(Content::COLOR_ALPHA, 12, 12);
$con2 = new Context($source);

/* Fill the source surface with green */
$con2->setSourceRgb(0, 1, 0);
$con2->paint();

/* Draw a blue square in the middle of the source with clipping,
 * and leave the clip there. */
$con2->rectangle(12 / 4, 12 / 4, 12 / 2, 12 / 2);
$con2->clip();
$con2->setSourceRgb(0, 0, 1);
$con2->paint();

/* Fill the destination surface with solid red (should not appear
 * in final result) */
$context->setSourceRgb(1, 0, 0);
$context->paint();

/* Now draw the source surface onto the destination surface */
$context->setSurface($source, 0, 0);
$context->paint();

$surface->writeToPng(dirname(__FILE__).'/source-clip-php.png');
