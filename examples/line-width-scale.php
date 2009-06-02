<?php
function spline_path ()
{
    global $spline,$con;
    $con->save ();
    {
	$con->moveTo (
		       - $spline, 0);
	$con->curveTo (
			- $spline / 4, - $spline,
			  $spline / 4,   $spline,
			  $spline, 0);
    }
    $con->restore ();
}

function scale_then_set_line_width_and_stroke ()
{
    global $con,$xscale,$yscale,$linewidth;
    $con->scale ( $xscale, $yscale);
    $con->setLineWidth ( $linewidth);
    spline_path ();
    $con->stroke ();
}

function scale_path_and_line_width ()
{
    global $con, $xscale, $yscale,$linewidth;
    $con->save ();
    {
	$con->scale ( $xscale, $yscale);
	spline_path ();
    }
    $con->restore ();

    $con->save ();
    {
	$con->scale ( $xscale, $yscale);
	$con->setLineWidth ( $linewidth);
	$con->stroke ();
    }
    $con->restore ();
}

function set_line_width_then_scale_and_stroke()
{
    global $con, $xscale, $yscale,$linewidth;
    $con->setLineWidth ( $linewidth);
    $con->scale ( $xscale, $yscale);
    spline_path ();
    $con->stroke ();
}

function scale_path_not_line_width ()
{
    global $con, $xscale, $yscale,$linewidth;

    $con->save ();
    {
	$con->scale ( $xscale, $yscale);
	spline_path ();
    }
    $con->restore ();

    $con->save ();
    {
	$con->setLineWidth ( $linewidth);
	$con->stroke ();
    }
    $con->restore ();
}

 $linewidth = 13;
 $spline = 50.0;
 $xscale  = 0.5;
 $yscale  = 2.0;
 $width = ($xscale * $spline * 6.0);
 $height = ($yscale * $spline * 2.0);    
 $sur = new CairoImageSurface(CairoFormat::ARGB32, $width, $height);
 $con = new CairoContext($sur);
 $con->setSourceRgb ( 1.0, 1.0, 1.0); /* white */
 $con->paint ();
 $con->setSourceRgb ( 0.0, 0.0, 0.0); /* black */
 for($i =0 ; $i<4;$i++) {
 	$con->save();
//	$con->translate($width/4 + ($i % 2)*$width/2, $height/4 + ($i/2)*$height/2);
	switch($i) {
	case 0:
 		$con->translate($width/4 , $height/4);
		scale_then_set_line_width_and_stroke();
		break;
	case 1:
 		$con->translate($width/4 + $width/2, $height/4);
		scale_path_and_line_width();
		break;
	case 2:
 		$con->translate($width/4, $height/4 + $height/2);
 		set_line_width_then_scale_and_stroke();
		break;
	case 3:
 		$con->translate($width/4 + $width/2, $height/4 + $height/2);
		scale_path_not_line_width();
		break;
	}
$con->restore();
}
$sur->writeToPng(dirname(__FILE__)  . "/line-width-scale-php.png");
?>



