<?php
$sur = new CairoImageSurface(CairoFormat::ARGB32, 120, 100);
$con = new CairoContext($sur);

$con->setSourceRgb ( 1, 1, 1);
$con->paint ();

$con->setSourceRgb ( 0, 0, 0);
$con->setMiterLimit (100000);
for ($xscale = 1; $xscale <= 1000; $xscale += 999)
    for ($yscale = 1; $yscale <= 1000; $yscale += 999)
    {
        //$max_scale = ($xscale > $yscale) ? $xscale : $yscale;
        $max_scale = max($xscale, $yscale);
		$con->save ();
        if ($xscale > 1)
        	$con->translate (50, 0);
        if ($yscale > 1)
        	$con->translate ( 0, 50);
        $con->scale ( $xscale,$yscale);
        $con->setLineWidth ( 10.0 / $max_scale);
        $con->moveTo ( 10.0 / $xscale, 10.0 / $yscale);
        $con->lineTo ( 40.0 / $xscale, 10.0 / $yscale);
        $con->lineTo ( 10.0 / $xscale, 30.0 / $yscale);
        $con->stroke ();
        $con->restore ();
    }
$sur->writeToPng(dirname(__FILE__)  . "/miter-precision-php.png");
?>
