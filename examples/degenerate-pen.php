<?php

use Cairo\Context;
use Cairo\LineJoin;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::RGB24, 165, 30);
$context = new Context($surface);
$context->moveTo(0, 0);

$context->setSourceRgb(1, 1, 1);
$context->paint();

$context->setSourceRgb(0, 0, 0);
$context->moveTo(0, 0);
$context->translate(5, 5);

/* First compress the pen to a vertical line. */
$context->rectangle(0, 0, 20, 20);
$context->curveTo(20 / 2, 0, 20, 20 / 2, 20, 20);
$context->save();

$context->scale(0.00001, 1.0);
$context->stroke();

$context->restore();
$context->translate(5 + 20, 0);

/* Then compress the pen to a horizontal line. */
$context->rectangle(0, 0, 20, 20);
$context->curveTo(20 / 2, 0, 20, 20 / 2, 20, 20);
$context->save();

$context->scale(1.0, 0.00001);
$context->stroke();

$context->restore();

$context->translate(5 + 20, 0);

/* Finally a line at an angle. */
$context->rectangle(0, 0, 20, 20);
$context->curveTo(20 / 2, 0, 20, 20 / 2, 20, 20);
$context->save();

$context->rotate(M_PI / 4.0);
$context->scale(0.00001, 1.0);
$context->stroke();

$context->restore();
$context->setSourceRgb(1, 1, 1);
$context->paint();

$context->setSourceRgb(0, 0, 0);
$context->setLineJoin(LineJoin::ROUND);

$context->translate(5, 5);

/* First compress the pen to a vertical line. */
$context->rectangle(0, 0, 20, 20);
$context->curveTo(20 / 2, 0, 20, 20 / 2, 20, 20);
$context->save();

$context->scale(0.00001, 1.0);
$context->stroke();

$context->restore();

$context->translate(5 + 20, 0);

/* Then compress the pen to a horizontal line. */
$context->rectangle(0, 0, 20, 20);
$context->curveTo(20 / 2, 0, 20, 20 / 2, 20, 20);
$context->save();

$context->scale(1.0, 0.00001);
$context->stroke();

$context->restore();

$context->translate(5 + 20, 0);

/* Finally a line at an angle. */
$context->rectangle(0, 0, 20, 20);
$context->curveTo(20 / 2, 0, 20, 20 / 2, 20, 20);
$context->save();

$context->rotate(M_PI / 4.0);
$context->scale(0.00001, 1.0);
$context->stroke();

$context->restore();
$surface->writeToPng(dirname(__FILE__).'/degenerate-pen-php.png'); 

