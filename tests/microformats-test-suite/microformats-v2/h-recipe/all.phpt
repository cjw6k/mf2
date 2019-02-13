--TEST--
mf2: mf-test-suite: v2/h-recipe/all
--SKIPIF--
<?php if (!extension_loaded("mf2")) print "skip"; ?>
--FILE--
<?php

var_dump(mf2_fetch(__DIR__ . '/all.html')->items);

?>
--EXPECT--
array(1) {
  [0]=>
  object(MF2Microformat)#2 (2) {
    ["type"]=>
    array(1) {
      [0]=>
      string(8) "h-recipe"
    }
    ["properties"]=>
    array(10) {
      ["name"]=>
      array(1) {
        [0]=>
        string(18) "Yorkshire Puddings"
      }
      ["summary"]=>
      array(1) {
        [0]=>
        string(63) "Makes 6 good sized Yorkshire puddings, the way my mum taught me"
      }
      ["yield"]=>
      array(1) {
        [0]=>
        string(31) "6 good sized Yorkshire puddings"
      }
      ["photo"]=>
      array(1) {
        [0]=>
        string(62) "http://codebits.glennjones.net/semantic/yorkshire-puddings.jpg"
      }
      ["review"]=>
      array(1) {
        [0]=>
        object(MF2Microformat)#3 (3) {
          ["type"]=>
          array(1) {
            [0]=>
            string(18) "h-review-aggregate"
          }
          ["properties"]=>
          array(3) {
            ["rating"]=>
            array(1) {
              [0]=>
              string(24) "4.5 stars out 5 based on"
            }
            ["average"]=>
            array(1) {
              [0]=>
              string(3) "4.5"
            }
            ["count"]=>
            array(1) {
              [0]=>
              string(2) "35"
            }
          }
          ["value"]=>
          string(49) "4.5 stars out 5 based on 
            35 reviews"
        }
      }
      ["ingredient"]=>
      array(5) {
        [0]=>
        array(2) {
          ["html"]=>
          string(5) "1 egg"
          ["value"]=>
          string(5) "1 egg"
        }
        [1]=>
        array(2) {
          ["html"]=>
          string(15) "75g plain flour"
          ["value"]=>
          string(15) "75g plain flour"
        }
        [2]=>
        array(2) {
          ["html"]=>
          string(9) "70ml milk"
          ["value"]=>
          string(9) "70ml milk"
        }
        [3]=>
        array(2) {
          ["html"]=>
          string(10) "60ml water"
          ["value"]=>
          string(10) "60ml water"
        }
        [4]=>
        array(2) {
          ["html"]=>
          string(13) "Pinch of salt"
          ["value"]=>
          string(13) "Pinch of salt"
        }
      }
      ["instructions"]=>
      array(1) {
        [0]=>
        array(2) {
          ["html"]=>
          string(691) "<ol>
            <li>Pre-heat oven to 230C or gas mark 8. Pour the vegetable oil evenly into 2 x 4-hole 
            Yorkshire pudding tins and place in the oven to heat through.</li> 
            
            <li>To make the batter, add all the flour into a bowl and beat in the eggs until smooth. 
            Gradually add the milk and water while beating the mixture. It should be smooth and 
            without lumps. Finally add a pinch of salt.</li>
            
            <li>Make sure the oil is piping hot before pouring the batter evenly into the tins. 
            Place in the oven for 20-25 minutes until pudding have risen and look golden brown</li>
        </ol>"
          ["value"]=>
          string(631) "Pre-heat oven to 230C or gas mark 8. Pour the vegetable oil evenly into 2 x 4-hole 
            Yorkshire pudding tins and place in the oven to heat through. 
            
            To make the batter, add all the flour into a bowl and beat in the eggs until smooth. 
            Gradually add the milk and water while beating the mixture. It should be smooth and 
            without lumps. Finally add a pinch of salt.
            
            Make sure the oil is piping hot before pouring the batter evenly into the tins. 
            Place in the oven for 20-25 minutes until pudding have risen and look golden brown"
        }
      }
      ["nutrition"]=>
      array(3) {
        [0]=>
        string(13) "Calories: 125"
        [1]=>
        string(9) "Fat: 3.2g"
        [2]=>
        string(17) "Cholesterol: 77mg"
      }
      ["published"]=>
      array(1) {
        [0]=>
        string(10) "2011-10-27"
      }
      ["author"]=>
      array(1) {
        [0]=>
        object(MF2Microformat)#4 (3) {
          ["type"]=>
          array(1) {
            [0]=>
            string(6) "h-card"
          }
          ["properties"]=>
          array(2) {
            ["name"]=>
            array(1) {
              [0]=>
              string(11) "Glenn Jones"
            }
            ["url"]=>
            array(1) {
              [0]=>
              string(21) "http://glennjones.net"
            }
          }
          ["value"]=>
          string(11) "Glenn Jones"
        }
      }
    }
  }
}
