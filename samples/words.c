#include <sugar.h>

// simple example of word replacement in a string using sugar.h

app({
  string s = "pizza is alright!";
  string result = replaceWord(s, "alright", "wonderful");
  println(result);
})