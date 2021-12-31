#if 0
  /usr/bin/env sugar `basename $0` $@ && exit;
  // above is a shebang hack, so you can run: ./args.c <arg 1> <arg 2> <arg N>
#endif

#include <sugar.h>

// playing around with arguments as a list of strings

app({
  // generate a CSV from input
  string csv = joinSep(argc, argv, ',');
  println(join2s("[ as csv ]  -> ", csv));

  // parse it to back to a list
  stringList list = splitSep(csv, ',');

  // forEach is a simple map apply stringList => void fn
  println("[ mapped ]  -> one per line:");
  forEach(argc, list, &println);
})
