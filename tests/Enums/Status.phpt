--TEST--
Cairo\Status class constants
--EXTENSIONS--
eos_datastructures
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use Cairo\Status;

$enum = new Status(Status::SUCCESS);
var_dump($enum);

var_dump($enum->getMessage());

try {
    $enum->getMessage(1);
} catch(TypeError $e) {
    echo $e->getMessage();
}
?>
--EXPECTF--
object(Cairo\Status)#%d (2) {
  ["__elements"]=>
  array(40) {
    ["SUCCESS"]=>
    long(0)
    ["NO_MEMORY"]=>
    long(1)
    ["INVALID_RESTORE"]=>
    long(2)
    ["INVALID_POP_GROUP"]=>
    long(3)
    ["NO_CURRENT_POINT"]=>
    long(4)
    ["INVALID_MATRIX"]=>
    long(5)
    ["INVALID_STATUS"]=>
    long(6)
    ["NULL_POINTER"]=>
    long(7)
    ["INVALID_STRING"]=>
    long(8)
    ["INVALID_PATH_DATA"]=>
    long(9)
    ["READ_ERROR"]=>
    long(10)
    ["WRITE_ERROR"]=>
    long(11)
    ["SURFACE_FINISHED"]=>
    long(12)
    ["SURFACE_TYPE_MISMATCH"]=>
    long(13)
    ["PATTERN_TYPE_MISMATCH"]=>
    long(14)
    ["INVALID_CONTENT"]=>
    long(15)
    ["INVALID_FORMAT"]=>
    long(16)
    ["INVALID_VISUAL"]=>
    long(17)
    ["FILE_NOT_FOUND"]=>
    long(18)
    ["INVALID_DASH"]=>
    long(19)
    ["INVALID_DSC_COMMENT"]=>
    long(20)
    ["INVALID_INDEX"]=>
    long(21)
    ["CLIP_NOT_REPRESENTABLE"]=>
    long(22)
    ["TEMP_FILE_ERROR"]=>
    long(23)
    ["INVALID_STRIDE"]=>
    long(24)
    ["FONT_TYPE_MISMATCH"]=>
    long(25)
    ["USER_FONT_IMMUTABLE"]=>
    long(26)
    ["USER_FONT_ERROR"]=>
    long(27)
    ["NEGATIVE_COUNT"]=>
    long(28)
    ["INVALID_CLUSTERS"]=>
    long(29)
    ["INVALID_SLANT"]=>
    long(30)
    ["INVALID_WEIGHT"]=>
    long(31)
    ["INVALID_SIZE"]=>
    long(32)
    ["USER_FONT_NOT_IMPLEMENTED"]=>
    long(33)
    ["DEVICE_TYPE_MISMATCH"]=>
    long(34)
    ["DEVICE_ERROR"]=>
    long(35)
    ["INVALID_MESH_CONSTRUCTION"]=>
    long(36)
    ["DEVICE_FINISHED"]=>
    long(37)
    ["JBIG2_GLOBAL_MISSING"]=>
    long(38)
    ["LAST_STATUS"]=>
    long(39)
  }
  ["__value"]=>
  long(0)
}
string(21) "no error has occurred"
Cairo\Status::getMessage() expects exactly 0 parameters, 1 given