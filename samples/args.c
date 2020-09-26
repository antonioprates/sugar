#!///usr/local/bin/sugar
#include <sugar.h>

// playing around with arguments as a list of strings

app({
  // simple apply string => void
  forEach(argc, argv, &println);

  // generate a CSV from input
  string csv = joinSep(argc, argv, ',');
  println(csv);

  // undo it to back to a list
  stringList list = splitSep(csv, ',');

  // expect same result from the first map
  forEach(argc, list, &println);
})
