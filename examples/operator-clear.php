<?php

$width = 16;
$height = 16;
$pad = 2;

function set_solid_pattern ($x, $y)
{
    global $con;
    $con->setSourceRgb (1.0, 0, 0.0);
}

function set_gradient_pattern ($x, $y)
{
    global $con,$width,$height;

    $pat = new CairoLinearGradient ($x, $y, $x + $width, $y + $height);
    $pat->addColorStopRgba (0.2, 1, 0, 0, 1);
    $pat->addColorStopRgba ( 0.8, 1, 0, 0, 0.0);
    $con->setSource ($pat);
    
}

function draw_mask ($x, $y)
{
    
    global $con,$width,$height,$sur;
    $wi = floor(0.9 * $width);
    $he = floor(0.9 * $height);
    $x += 0.05 * $width;
    $y += 0.05 * $height;
    //$s = new CairoImageSurface(FORMATARGB32, 1, 1);
    $s = $sur->createSimilar (
						 CairoContent::ALPHA,
						 $wi, $he);
    $con2 = new CairoContext($s);

    $con2->setSourceRgb (1, 1, 1); /* white */

    $con2->arc (0.5 * $wi, 0.5 * $he, 0.45 * $he, 0, 2 * M_PI);
    $con2->fill ();


    $con->maskSurface ($s, $x, $y);

   
}

function draw_glyphs ($x, $y)
{
    
    global $con,$width,$height;
    $con->setFontSize (0.8 * $height);

    $extents = $con->textExtents ("FG");
    $con->moveTo (
		   $x + floor (($width - $extents["width"]) / 2 + 0.5) - $extents["x_bearing"],
		   $y + floor (($height - $extents["height"]) / 2 + 0.5) - $extents["y_bearing"]);
    $con->showText ("FG");
}

function draw_polygon ($x, $y)
{
    global $con,$width,$height;
    
    $wi = floor(0.9 * $width);
    $he = floor(0.9 * $height);
    $x += 0.05 * $width;
    $y += 0.05 * $height;

    $con->newPath ();
    $con->moveTo ($x, $y);
    $con->lineTo ($x, $y + $he);
    $con->lineTo ($x + $wi / 2, $y + 3 * $he / 4);
    $con->lineTo ($x + $wi, $y + $he);
    $con->lineTo ($x + $wi, $y);
    $con->lineTo ($x + $wi / 2, $y + $he / 4);
    $con->closePath ();
    $con->fill ();
}

function draw_rects ($x, $y)
{
    global $con,$width,$height;
  
    $block_width = floor(0.33 * $width + 0.5);
    $block_height = floor(0.33 * $height + 0.5);
    

    for ($i = 0; $i < 3; $i++)
	for ($j = 0; $j < 3; $j++)
	    if (($i + $j) % 2 == 0)
		$con->rectangle (
				 $x + $block_width * $i, $y + $block_height * $j,
				 $block_width,         $block_height);

    $con->fill ();
}

$imwidth = 2*($width+$pad) + $pad;
$imheight = 4*($height+$pad) + $pad;

$sur = new CairoImageSurface(CairoFormat::ARGB32, $imwidth, $imheight);
$con = new CairoContext($sur);

    $con->selectFontFace ( "Bitstream Vera Sans",
			    CairoFontSlant::NORMAL,
			    CairoFontWeight::NORMAL);

    for ($j = 0; $j < 4; $j++) {
	for ($i = 0; $i < 2; $i++) {
	    $x = $i * ($width + $pad) + $pad;
	    $y = $j * ($height + $pad) + $pad;

	    $con->save ();

	    $pat = new CairoLinearGradient ($x + $width, $y,
						   $x,         $y + $height);
	    $pat->addColorStopRgba (0.2,
					       0.0, 0.0, 1.0, 1.0); /* Solid blue */
	    $pat->addColorStopRgba ( 0.8,
					       0.0, 0.0, 1.0, 0.0); /* Transparent blue */
	    $con->setSource ($pat);
	    

	    $con->rectangle ($x, $y, $width, $height);
	    $con->fillPreserve ();
	    $con->clip ();

	    $con->setOperator (CairoOperator::CLEAR);
	    //pattern_funcs[i] ($x, $y);
	    switch($i) {
		case 0: 
			set_solid_pattern($x,$y);
			break;
		case 1:
			set_gradient_pattern($x,$y);
			break;
		}
		
        //draw_funcs[j] (cr, x, y);
	    switch($j) {
		case 0:
			draw_mask($x,$y);
			break;
		case 1:
			draw_glyphs($x,$y);
			break;
		case 2:
			draw_polygon($x,$y);
			break;
		case 3:
			draw_rects($x,$y);
			break;
		}
	    $con->restore ();
	}
    }

$sur->writeToPng(dirname(__FILE__) . "/operator-clear-php.png");
?>
