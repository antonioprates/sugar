#include <sugar.h>
#include <sys/types.h>
#include <unistd.h>

// stupid script to make use of all CPU cores, follow in top/htop
// be carefull, this is a fork-bomb and can hang your system!

app({
  println("how many cores has your machine?  (max = 64)");
  string response = readKeys();
  number corecount = 0;
  if (response && (corecount = ofString(response)) > 64)
    corecount = 64; // limit! remove this limit at your own risk

  println("hit CTRL+C to end this madness");
  number i = 1;
  while (i < corecount) {
    i = i * 2;
    fork();
  }

  number x = 0;
  do { // some dummy math
    x = x + 32;
    x = 32 - x;
  } while (true);
})
