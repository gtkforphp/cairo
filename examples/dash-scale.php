<?php

use Cairo\Context;
use Cairo\LineCap;
use Cairo\LineJoin;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$linewidth = 8.0;
$size = 5 * $linewidth;
$pad = 2 * $linewidth;
$dash = [1.5 * $linewidth];

$imwidth = 3 * ($pad + $size) + $pad;
$imheight = ($size * 5) + (6 * $pad);

$surface = new Image(ImageFormat::ARGB32, $imwidth, $imheight);
$context = new Context($surface);


$context->save();
$context->setSourceRgb(1, 1, 1);
$context->paint();
$context->restore();

$context->translate($pad, $pad);

$context->setDash($dash, -2 * $linewidth);
$context->setLineWidth($linewidth);

$context->save();

$context->moveTo(0, 0);
$context->relLineTo(0, $size);
$context->relLineTo($size, 0);
$context->closePath();
$context->moveTo(2 * $linewidth, 0);
$context->relLineTo(3 * $linewidth, 0);
$context->relLineTo(0, 3 * $linewidth);

$context->setLineCap(LineCap::BUTT);
$context->setLineJoin(LineJoin::BEVEL);
$context->stroke();
$context->translate($size + $pad, 0);

$context->moveTo(0, 0);
$context->relLineTo(0, $size);
$context->relLineTo($size, 0);
$context->closePath();
$context->moveTo(2 * $linewidth, 0);
$context->relLineTo(3 * $linewidth, 0);
$context->relLineTo(0, 3 * $linewidth);

$context->setLineCap(LineCap::ROUND);
$context->setLineJoin(LineJoin::ROUND);
$context->stroke();
$context->translate($size + $pad, 0);

$context->moveTo(0, 0);
$context->relLineTo(0, $size);
$context->relLineTo($size, 0);
$context->closePath();
$context->moveTo(2 * $linewidth, 0);
$context->relLineTo(3 * $linewidth, 0);
$context->relLineTo(0, 3 * $linewidth);

$context->setLineCap(LineCap::SQUARE);
$context->setLineJoin(LineJoin::MITER);
$context->stroke();
$context->restore();

$context->translate(0, $size + 2 * $pad);

$context->save();
$context->scale(1, 2);
$context->moveTo(0, 0);
$context->relLineTo(0, $size);
$context->relLineTo($size, 0);
$context->closePath();
$context->moveTo(2 * $linewidth, 0);
$context->relLineTo(3 * $linewidth, 0);
$context->relLineTo(0, 3 * $linewidth);

$context->setLineCap(LineCap::BUTT);
$context->setLineJoin(LineJoin::BEVEL);
$context->stroke();
$context->translate($size + $pad, 0);

$context->moveTo(0, 0);
$context->relLineTo(0, $size);
$context->relLineTo($size, 0);
$context->closePath();
$context->moveTo(2 * $linewidth, 0);
$context->relLineTo(3 * $linewidth, 0);
$context->relLineTo(0, 3 * $linewidth);

$context->setLineCap(LineCap::ROUND);
$context->setLineJoin(LineJoin::ROUND);
$context->stroke();
$context->translate($size + $pad, 0);

$context->moveTo(0, 0);
$context->relLineTo(0, $size);
$context->relLineTo($size, 0);
$context->closePath();
$context->moveTo(2 * $linewidth, 0);
$context->relLineTo(3 * $linewidth, 0);
$context->relLineTo(0, 3 * $linewidth);

$context->setLineCap(LineCap::SQUARE);
$context->setLineJoin(LineJoin::MITER);
$context->stroke();
$context->restore();

$context->translate(0, 2 * $size + 2 * $pad);
$context->save();
$context->scale(1, 2);
$context->moveTo(0, 0);
$context->relLineTo(0, $size);
$context->relLineTo($size, 0);
$context->closePath();
$context->moveTo(2 * $linewidth, 0);
$context->relLineTo(3 * $linewidth, 0);
$context->relLineTo(0, 3 * $linewidth);

$context->setLineCap(LineCap::BUTT);
$context->setLineJoin(LineJoin::BEVEL);
$context->stroke();
$context->translate($size + $pad, 0);

$context->moveTo(0, 0);
$context->relLineTo(0, $size);
$context->relLineTo($size, 0);
$context->closePath();
$context->moveTo(2 * $linewidth, 0);
$context->relLineTo(3 * $linewidth, 0);
$context->relLineTo(0, 3 * $linewidth);

$context->setLineCap(LineCap::ROUND);
$context->setLineJoin(LineJoin::ROUND);
$context->stroke();
$context->translate($size + $pad, 0);

$context->moveTo(0, 0);
$context->relLineTo(0, $size);
$context->relLineTo($size, 0);
$context->closePath();
$context->moveTo(2 * $linewidth, 0);
$context->relLineTo(3 * $linewidth, 0);
$context->relLineTo(0, 3 * $linewidth);
$context->setLineCap(LineCap::SQUARE);
$context->setLineJoin(LineJoin::MITER);
$context->stroke();
$context->restore();

$surface->writeToPng(dirname(__FILE__).'/dash-scale-php.png');

