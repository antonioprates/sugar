#!///usr/local/bin/sugar
#include <sugar.h>
#include <sys/types.h>
#include <unistd.h>

// stupid script to make use of all CPUs

app({
  println("hit CTRL+C to end this madness");

  int corecount = 8;

  int i = 1;
  while (i < corecount) {
    i = i * 2;
    fork();
  }

  int x = 0;
  do {
    // some dummy math
    x = x + 32;
    x = 32 - x;
  } while (true);
})