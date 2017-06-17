<?php

use Cairo\Context;
use Cairo\Surface\Image;
use Cairo\Surface\ImageFormat;

$surface = new Image(ImageFormat::ARGB32, 2, 2);
$context = new Context($surface);
$s = new Image(ImageFormat::ARGB32, 2, 2);
$file = fopen(dirname(__FILE__).'/create-from-png-ref.png', 'r');
$s->createFromPng($file);
$context->setSurface($s);
$context->paint();

$surface->writeToPng(dirname(__FILE__).'/create-from-png-stream-php.png');
