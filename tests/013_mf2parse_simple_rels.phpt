--TEST--
mf2: parse rels from a, area, and link tags
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?> 
--FILE--
<?php

/* Finds rels in a tags */
var_dump(mf2_parse('<a href="http://example.com/" rel="test"></a>'));
var_dump(mf2_parse('<a href="http://example.com/" rel="test test2"></a>'));
var_dump(mf2_parse('<a href="http://example.com/test/" rel="test"></a><a href="http://example.com/test2/" rel="test2"></a>'));

/* Finds rels in area tags */
var_dump(mf2_parse('<area href="http://example.com/" rel="test">'));
var_dump(mf2_parse('<area href="http://example.com/" rel="test test2">'));
var_dump(mf2_parse('<area href="http://example.com/test/" rel="test" /><area href="http://example.com/test2/" rel="test2"></area>'));

/* Finds rels in link tags*/
var_dump(mf2_parse('<link href="http://example.com/" rel="test">'));
var_dump(mf2_parse('<link href="http://example.com/" rel="test test2">'));
var_dump(mf2_parse('<link href="http://example.com/test/" rel="test"><link href="http://example.com/test2/" rel="test2">'));

/* Does not find rels in tags that are not links */
var_dump(mf2_parse('<dfn rel="test" href="http://example.com/"></dfn>'));
var_dump(mf2_parse('<p rel="test" href="http://example.com/"></dfn>'));

/* Does not find rels in any tag that has rel without href, nor in any tag that has href without rel */
var_dump(mf2_parse('<a rel="test"></a>'));
var_dump(mf2_parse('<a href="http://example.com/"></a>'));

?>
--EXPECT--
object(MF2Parse)#1 (3) {
  ["items"]=>
  array(0) {
  }
  ["rels"]=>
  array(1) {
    ["test"]=>
    array(1) {
      [0]=>
      string(19) "http://example.com/"
    }
  }
  ["rel_urls"]=>
  array(1) {
    ["http://example.com/"]=>
    array(1) {
      ["rels"]=>
      array(1) {
        [0]=>
        string(4) "test"
      }
    }
  }
}
object(MF2Parse)#1 (3) {
  ["items"]=>
  array(0) {
  }
  ["rels"]=>
  array(2) {
    ["test"]=>
    array(1) {
      [0]=>
      string(19) "http://example.com/"
    }
    ["test2"]=>
    array(1) {
      [0]=>
      string(19) "http://example.com/"
    }
  }
  ["rel_urls"]=>
  array(1) {
    ["http://example.com/"]=>
    array(1) {
      ["rels"]=>
      array(2) {
        [0]=>
        string(4) "test"
        [1]=>
        string(5) "test2"
      }
    }
  }
}
object(MF2Parse)#1 (3) {
  ["items"]=>
  array(0) {
  }
  ["rels"]=>
  array(2) {
    ["test"]=>
    array(1) {
      [0]=>
      string(24) "http://example.com/test/"
    }
    ["test2"]=>
    array(1) {
      [0]=>
      string(25) "http://example.com/test2/"
    }
  }
  ["rel_urls"]=>
  array(2) {
    ["http://example.com/test/"]=>
    array(1) {
      ["rels"]=>
      array(1) {
        [0]=>
        string(4) "test"
      }
    }
    ["http://example.com/test2/"]=>
    array(1) {
      ["rels"]=>
      array(1) {
        [0]=>
        string(5) "test2"
      }
    }
  }
}
object(MF2Parse)#1 (3) {
  ["items"]=>
  array(0) {
  }
  ["rels"]=>
  array(1) {
    ["test"]=>
    array(1) {
      [0]=>
      string(19) "http://example.com/"
    }
  }
  ["rel_urls"]=>
  array(1) {
    ["http://example.com/"]=>
    array(1) {
      ["rels"]=>
      array(1) {
        [0]=>
        string(4) "test"
      }
    }
  }
}
object(MF2Parse)#1 (3) {
  ["items"]=>
  array(0) {
  }
  ["rels"]=>
  array(2) {
    ["test"]=>
    array(1) {
      [0]=>
      string(19) "http://example.com/"
    }
    ["test2"]=>
    array(1) {
      [0]=>
      string(19) "http://example.com/"
    }
  }
  ["rel_urls"]=>
  array(1) {
    ["http://example.com/"]=>
    array(1) {
      ["rels"]=>
      array(2) {
        [0]=>
        string(4) "test"
        [1]=>
        string(5) "test2"
      }
    }
  }
}
object(MF2Parse)#1 (3) {
  ["items"]=>
  array(0) {
  }
  ["rels"]=>
  array(2) {
    ["test"]=>
    array(1) {
      [0]=>
      string(24) "http://example.com/test/"
    }
    ["test2"]=>
    array(1) {
      [0]=>
      string(25) "http://example.com/test2/"
    }
  }
  ["rel_urls"]=>
  array(2) {
    ["http://example.com/test/"]=>
    array(1) {
      ["rels"]=>
      array(1) {
        [0]=>
        string(4) "test"
      }
    }
    ["http://example.com/test2/"]=>
    array(1) {
      ["rels"]=>
      array(1) {
        [0]=>
        string(5) "test2"
      }
    }
  }
}
object(MF2Parse)#1 (3) {
  ["items"]=>
  array(0) {
  }
  ["rels"]=>
  array(1) {
    ["test"]=>
    array(1) {
      [0]=>
      string(19) "http://example.com/"
    }
  }
  ["rel_urls"]=>
  array(1) {
    ["http://example.com/"]=>
    array(1) {
      ["rels"]=>
      array(1) {
        [0]=>
        string(4) "test"
      }
    }
  }
}
object(MF2Parse)#1 (3) {
  ["items"]=>
  array(0) {
  }
  ["rels"]=>
  array(2) {
    ["test"]=>
    array(1) {
      [0]=>
      string(19) "http://example.com/"
    }
    ["test2"]=>
    array(1) {
      [0]=>
      string(19) "http://example.com/"
    }
  }
  ["rel_urls"]=>
  array(1) {
    ["http://example.com/"]=>
    array(1) {
      ["rels"]=>
      array(2) {
        [0]=>
        string(4) "test"
        [1]=>
        string(5) "test2"
      }
    }
  }
}
object(MF2Parse)#1 (3) {
  ["items"]=>
  array(0) {
  }
  ["rels"]=>
  array(2) {
    ["test"]=>
    array(1) {
      [0]=>
      string(24) "http://example.com/test/"
    }
    ["test2"]=>
    array(1) {
      [0]=>
      string(25) "http://example.com/test2/"
    }
  }
  ["rel_urls"]=>
  array(2) {
    ["http://example.com/test/"]=>
    array(1) {
      ["rels"]=>
      array(1) {
        [0]=>
        string(4) "test"
      }
    }
    ["http://example.com/test2/"]=>
    array(1) {
      ["rels"]=>
      array(1) {
        [0]=>
        string(5) "test2"
      }
    }
  }
}
object(MF2Parse)#1 (3) {
  ["items"]=>
  array(0) {
  }
  ["rels"]=>
  array(0) {
  }
  ["rel_urls"]=>
  array(0) {
  }
}
object(MF2Parse)#1 (3) {
  ["items"]=>
  array(0) {
  }
  ["rels"]=>
  array(0) {
  }
  ["rel_urls"]=>
  array(0) {
  }
}
object(MF2Parse)#1 (3) {
  ["items"]=>
  array(0) {
  }
  ["rels"]=>
  array(0) {
  }
  ["rel_urls"]=>
  array(0) {
  }
}
object(MF2Parse)#1 (3) {
  ["items"]=>
  array(0) {
  }
  ["rels"]=>
  array(0) {
  }
  ["rel_urls"]=>
  array(0) {
  }
}