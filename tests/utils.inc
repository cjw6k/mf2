<?php

function testSuiteFormat(MF2Parse $parse) {
    $arr = json_decode(json_encode($parse), true);
    sortByKeys($arr);

    // the jsonSerialize method does this, but it's lost in the test after the encode/decode above
    if (empty($arr['rel-urls'])) {
        $arr['rel-urls'] = (object)[];
    }
    if (empty($arr['rels'])) {
        $arr['rels'] = (object)[];
    }

    return json_encode($arr, JSON_PRETTY_PRINT|JSON_UNESCAPED_SLASHES|JSON_UNESCAPED_UNICODE);
}

function sortByKeys(array &$arr) {
    foreach ($arr as $key => &$value) {
        if (! is_array($value)) {
            continue;
        }
        sortByKeys($value);
    }
    ksort($arr);
}