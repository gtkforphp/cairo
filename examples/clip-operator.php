<?php
$width = 16;
$height = 16;
$pad = 2;
$noperator = 1 + CairoOperator::SATURATE - CairoOperator::CLEAR;
$imagewidth = $noperator * ($width + $pad) + $pad;
$imageheight = 4 * ($height + $pad) + $pad; 
$sur = new CairoImageSurface(CairoFormat::ARGB32, $imagewidth, $imageheight);
$con = new CairoContext($sur);
$con->selectFontFace("Bitstream Vera Sans");
$con->setFontSize(0.9 * $height);

for($i=0; $i < 4; $i++) {
	for($op = CairoOperator::CLEAR; $op < $noperator; $op++) {
		$x = $op *($width + $pad) + $pad;
		$y = $i * ($height + $pad) + $pad;

		$con->save();
		$pat = new CairoLinearGradient($x + $width, $y, $x, $y + $height);
		$pat->addColorStopRgba(0.2,0,0,1,1);
        $pat->addColorStopRgba(0.8,0,0,1,0);

		$con->setSource($pat);
		$con->rectangle($x, $y, $width, $height);
		$con->fill();
		$con->setOperator($op);
		$con->setSourceRgb(1,0,0);
		$con->moveTo($x,$y);
		$con->lineTo($x+$width, $y);
		$con->lineTo($x, $y+$height);
		$con->clip();

		switch($i) {
		case 0:
			$wi = floor($width * 0.9);
			$he = floor($height * 0.9);
			$x += 0.05 * $width;
			$y += 0.05 * $height;
			
			//$stemp = $con->get_group_target();
			$msur = $sur->createSimilar(CairoContent::ALPHA, $wi, $he);
			
			$c2 = new CairoContext($msur);
			$c2->save();
			$c2->setSourceRgba(0,0,0,0);
			$c2->setOperator(CairoOperator::SOURCE);
			$c2->paint();
			$c2->restore();

			$c2->setSourceRgb(1,1,1);
			$c2->arc(0.5 * $wi, 0.5 * $he, 0.45 * $he, 0, 2 * M_PI);
			$c2->fill();
			//unset($c2);
			
			$con->maskSurface($msur, $x, $y);
			//unset($msur);
			//unset($stemp);
			break;
		
		case 1:
			$con->setFontSize(0.9 * $height);
			$ext = $con->textExtents("FG");
			$con->moveTo($x + floor(($width - $ext["width"])/2 + 0.5) - $ext["x_bearing"], $y + floor(($height - $ext["height"])/2 + 0.5) - $ext["y_bearing"]);
			$con->showText("FG");
			break;
		
		case 2:
            $wi = floor($width * 9 / 10);
            $he = floor($height * 9 / 10);
            $x += 0.05 * $width;
            $y += 0.05 * $height;
			$con->newPath();
			$con->moveTo($x, $y);
			$con->lineTo($x, $y + $he);
			$con->lineTo($x + $wi/2, $y + 3 * $he/4);
			$con->lineTo($x + $wi, $y + $he);
			$con->lineTo($x+$wi, $y);
			$con->lineTo($x + $wi/2, $y + $he/4);
			$con->closePath();
			$con->fill();
			break;

		case 3:
			$bw = floor(0.33 * $width + 0.5);
			$bh = floor(0.33 * $height + 0.5);

			for($t1 = 0; $t1 < 3; $t1++) 
				for($t2 = 0; $t2 < 3; $t2++) 
					if (($t1 + $t2) % 2 == 0)
						$con->rectangle($x + $bw*$t1, $y + $bh*$t2, $bw, $bh);
				$con->fill();
				
			
			break;
		}
		$con->restore();
	}
}
$sur->writeToPng(dirname(__FILE__)  . "/clip-operator-php.png");
?>		
		

