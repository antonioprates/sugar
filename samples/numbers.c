#include <sugar.h>

// just a simple test for the round up of odd division

app({
  // forever 21 :P
  const number x = 21;

  // will round as underneath type is int
  number y = x / 2;

  // expect: 10
  println(ofNumber(y));
})