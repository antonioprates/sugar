#!///usr/local/bin/sugar
#include <sugar.h>

app({
  string s = "pizza is alright!";
  string result = replaceWord(s, "alright", "wonderful");
  println(result);
})