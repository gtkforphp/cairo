<?php

use Cairo\Context;
use Cairo\Extend;
use Cairo\Operator;
use Cairo\Pattern\Surface as PatternSurface;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 100, 100);
$context = new Context($surface);

$s = new Image(ImageFormat::ARGB32, 20, 20);
$con2 = new Context($s);

$con2->setSourceRgba(1, 0, 0, 1);
$con2->rectangle(0, 0, 10, 10);
$con2->fill();
$con2->setSourceRgba(0, 1, 0, 1);
$con2->rectangle(10, 0, 10, 10);
$con2->fill();
$con2->setSourceRgba(0, 0, 1, 1);
$con2->rectangle(0, 10, 10, 10);
$con2->fill();
$con2->setSourceRgba(1, 1, 0, 1);
$con2->rectangle(10, 10, 10, 10);
$con2->fill();

$pat = new PatternSurface($s);
$pat->setExtend(Extend::REPEAT);
$context->setSourceRgba(0, 0, 0, 1);
$context->rectangle(0, 0, 100, 100);
$context->fill();
$context->translate(10, 10);
$context->setOperator(Operator::OVER);
$context->setPattern($pat);
$context->rectangle(0, 0, 90, 90);
$context->fill();
$surface->writeToPng(dirname(__FILE__).'/composite-integer-translate-over-repeat-php.png');
