#if 0
  /usr/local/bin/sugar `basename $0` $@ && exit;
  // above is a shebang hack, so you can run with: ./hello.c
#endif

#include <sugar.h>

app({ println("Hello World"); })
