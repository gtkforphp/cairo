<?php

use Cairo\Context;
use Cairo\FillRule;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$starsize = 20;

$surface = new Image(ImageFormat::ARGB32, $starsize * 2 + 2, $starsize + 2);
$context = new Context($surface);
$context->setSourceRgb(1, 0, 0);
$context->translate(1, 1);
$context->save();

$context->moveTo(10, 0);
$context->relLineTo(6, 20);
$context->relLineTo(-16, -12);
$context->relLineTo(20, 0);
$context->relLineTo(-16, 12);

$context->setFillRule(FillRule::WINDING);
$context->clip();
$context->paint();

$context->restore();
$context->translate($starsize + 1, 0);
$context->save();

$context->moveTo(10, 0);
$context->relLineTo(6, 20);
$context->relLineTo(-16, -12);
$context->relLineTo(20, 0);
$context->relLineTo(-16, 12);

$context->setFillRule(FillRule::EVEN_ODD);
$context->clip();
$context->paint();

$context->restore();
$surface->writeToPng(dirname(__FILE__).'/clip-fill-rule-php.png');


