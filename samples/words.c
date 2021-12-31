#if 0
  /usr/bin/env sugar `basename $0` $@ && exit;
  // above is a shebang hack, so you can run with: ./words.c
#endif

#include <sugar.h>

// simple example of word replacement in a string using sugar.h

string improve(string s) { return replaceWord(s, "alright", "wonderful"); }

app({
  string s = "pizza is alright!";
  println(improve(s));
})
