<?
$width = 247;
$height = 26;
$sur = new CairoImageSurface(FORMAT_ARGB32, $width, $height);
$con = new CairoContext($sur);
$con->selectFontFace("6x13.pcf");
$con->setFontSize(11.5);
$fo = new CairoFontOptions();
$fo->setHintMetrics(HINT_METRICS_ON);
$con->setFontOptions($fo);
$fe = $con->fontExtents();
$con->moveTo(1,$fe["ascent"] - 1);
$con->setSourceRgb(0,0,1);
$fo->setHintStyle(HINT_STYLE_NONE);
$con->setFontOptions($fo);
$con->showText("the ");
$fo->setHintStyle(HINT_STYLE_SLIGHT);
$con->setFontOptions($fo);
$con->showText("quick ");
$fo->setHintStyle(HINT_STYLE_MEDIUM);
$con->setFontOptions($fo);
$con->showText("brown");
$fo->setHintStyle(HINT_STYLE_FULL);
$con->setFontOptions($fo);
$con->showText(" fox");

$con->textPath(" jumps over a lazy dog");
$con->fill();

$con->translate($width, $height);
$con->rotate(M_PI);

$con->moveTo(1, $fe["height"]-$fe["descent"]-1);
$fo->setHintMetrics(HINT_METRICS_OFF);
$fo->setHintStyle(HINT_STYLE_NONE);
$con->setFontOptions($fo);
$con->showText("the ");
$fo->setHintStyle(HINT_STYLE_SLIGHT);
$con->setFontOptions($fo);
$con->showText("quick");
$fo->setHintStyle(HINT_STYLE_MEDIUM);
$con->setFontOptions($fo);
$con->showText(" brown");
$fo->setHintStyle(HINT_STYLE_FULL);
$con->setFontOptions($fo);
$con->showText(" fox");

$con->textPath(" jumps over");
$con->textPath(" a lazy dog");
$con->fill();
$sur->writeToPng("bitmap-font-php.png");
?>

