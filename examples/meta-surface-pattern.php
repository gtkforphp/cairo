<?php

$patwidth = 120;
$patheight =120;
$size =($patwidth*2);
$pad =2;
$width =($pad + $size + $pad);
$height =$width;

$sur = new CairoImageSurface(CairoFormat::ARGB32, $width, $height);
$con = new CairoContext($sur);
//$s = new CairoImageSurface(FORMATARGB32, $width, $height);


    $con->translate ( $pad, $pad);

    $pat_surface = $sur->createSimilar (
						CairoContent::COLOR_ALPHA,
						$patwidth, $patheight);

    $cr2 = new CairoContext($pat_surface);

    $cr2->setSourceRgba (1, 0, 1, 0.5);
    $cr2->rectangle ($patwidth/6.0, $patheight/6.0, $patwidth/4.0, $patheight/4.0);
    $cr2->fill ();

    $cr2->setSourceRgba (0, 1, 1, 0.5);
    $cr2->rectangle ($patwidth/2.0, $patheight/2.0, $patwidth/4.0, $patheight/4.0);
    $cr2->fill ();

    $cr2->setLineWidth (1);
    $cr2->moveTo ($patwidth/6.0, 0);
    $cr2->lineTo (0, 0);
    $cr2->lineTo (0, $patheight/6.0);
    $cr2->setSourceRgb (1, 0, 0);
    $cr2->stroke ();
    $cr2->moveTo ($patwidth/6.0, $patheight);
    $cr2->lineTo (0, $patheight);
    $cr2->lineTo (0, 5*$patheight/6.0);
    $cr2->setSourceRgb (0, 1, 0);
    $cr2->stroke ();
    $cr2->moveTo (5*$patwidth/6.0, 0);
    $cr2->lineTo ($patwidth, 0);
    $cr2->lineTo ($patwidth, $patheight/6.0);
    $cr2->setSourceRgb (0, 0, 1);
    $cr2->stroke ();
    $cr2->moveTo (5*$patwidth/6.0, $patheight);
    $cr2->lineTo ($patwidth, $patheight);
    $cr2->lineTo ($patwidth, 5*$patheight/6.0);
    $cr2->setSourceRgb (1, 1, 0);
    $cr2->stroke ();

    $cr2->setSourceRgb (0.5, 0.5, 0.5);
    $cr2->setLineWidth ($patwidth/10.0);

    $cr2->moveTo (0,         $patheight/4.0);
    $cr2->lineTo ($patwidth, $patheight/4.0);
    $cr2->stroke ();

    $cr2->moveTo ($patwidth/4.0,         0);
    $cr2->lineTo ($patwidth/4.0, $patwidth);
    $cr2->stroke ();

    $pattern = new CairoSurfacePattern ($pat_surface);

    $mat = new CairoMatrix();
    $mat->scale ( 2, 1.5);
    $mat->rotate ( 1);
    $mat->translate ( -$patwidth/4.0, -$patwidth/2.0);
    $pattern->setMatrix ( $mat);
    $pattern->setExtend ( CairoExtend::NONE);

    $con->setSource ( $pattern);
    $con->paint ();
	$sur->writeToPng(dirname(__FILE__)  . "/meta-surface-pattern-php.png");
?>
