<?php

use Cairo\Context;
use Cairo\Extend;
use Cairo\Matrix;
use Cairo\Pattern\Surface as PatternSurface;
use Cairo\Surface\Content;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$patternWidth = 120;
$patternHeight = 120;
$size = ($patternWidth * 2);
$pad = 2;
$width = ($pad + $size + $pad);
$height = $width;

$surface = new Image(ImageFormat::ARGB32, $width, $height);
$context = new Context($surface);
$context->translate($pad, $pad);

$patternSurface = $surface->createSimilar(Content::COLOR_ALPHA, $patternWidth, $patternHeight);

$cr2 = new Context($patternSurface);

$cr2->setSourceRgba(1, 0, 1, 0.5);
$cr2->rectangle($patternWidth / 6.0, $patternHeight / 6.0, $patternWidth / 4.0, $patternHeight / 4.0);
$cr2->fill();

$cr2->setSourceRgba(0, 1, 1, 0.5);
$cr2->rectangle($patternWidth / 2.0, $patternHeight / 2.0, $patternWidth / 4.0, $patternHeight / 4.0);
$cr2->fill();

$cr2->setLineWidth(1);
$cr2->moveTo($patternWidth / 6.0, 0);
$cr2->lineTo(0, 0);
$cr2->lineTo(0, $patternHeight / 6.0);
$cr2->setSourceRgb(1, 0, 0);
$cr2->stroke();
$cr2->moveTo($patternWidth / 6.0, $patternHeight);
$cr2->lineTo(0, $patternHeight);
$cr2->lineTo(0, 5 * $patternHeight / 6.0);
$cr2->setSourceRgb(0, 1, 0);
$cr2->stroke();
$cr2->moveTo(5 * $patternWidth / 6.0, 0);
$cr2->lineTo($patternWidth, 0);
$cr2->lineTo($patternWidth, $patternHeight / 6.0);
$cr2->setSourceRgb(0, 0, 1);
$cr2->stroke();
$cr2->moveTo(5 * $patternWidth / 6.0, $patternHeight);
$cr2->lineTo($patternWidth, $patternHeight);
$cr2->lineTo($patternWidth, 5 * $patternHeight / 6.0);
$cr2->setSourceRgb(1, 1, 0);
$cr2->stroke();

$cr2->setSourceRgb(0.5, 0.5, 0.5);
$cr2->setLineWidth($patternWidth / 10.0);

$cr2->moveTo(0, $patternHeight / 4.0);
$cr2->lineTo($patternWidth, $patternHeight / 4.0);
$cr2->stroke();

$cr2->moveTo($patternWidth / 4.0, 0);
$cr2->lineTo($patternWidth / 4.0, $patternWidth);
$cr2->stroke();

$pattern = new PatternSurface($patternSurface);

$matrix = new Matrix();
$matrix->scale(2, 1.5);
$matrix->rotate(1);
$matrix->translate(-$patternWidth / 4.0, -$patternWidth / 2.0);
$pattern->setMatrix($matrix);
$pattern->setExtend(Extend::NONE);

$context->setPattern($pattern);
$context->paint();

$surface->writeToPng(dirname(__FILE__).'/meta-surface-pattern-php.png');
