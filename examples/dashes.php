<?php

use Cairo\Context;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$dashes = [
	50.0,  // ink
	10.0,  // skip
	10.0,  // ink
	10.0,  // skip
];

$ndash = count($dashes);
$offset = -50.0;

$surface = new Image(0, 500, 500);
$context = new Context($surface);
$context->setDash($dashes, $offset);
$context->setLineWidth(10.0);
$context->moveTo(128.0, 25.6);
$context->lineTo(230.4, 230.4);
$context->relLineTo(-102.4, 0.0);
$context->curveTo(51.2, 230.4, 51.2, 128.0, 128.0, 128.0);
$context->stroke();

$surface->writeToPng(dirname(__FILE__).'/dashes-php.png');
