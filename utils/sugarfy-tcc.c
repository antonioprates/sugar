#!///usr/local/bin/sugar -run
#include <sugar.h>

// C script by Antonio Prates, 2020
// part of utility to patch sugar with tcc repo

app({
  if (argc < 2) {
    println("error: missing filepath");
    return EXIT_FAILURE;
  };

  string s = readFile(argv[1]);
  if (!s)
    return EXIT_FAILURE;

  s = replaceWord(s, "tcc", "sugar");
  s = replaceWord(s, "TCC", "SUGAR");
  s = replaceWord(s, "TINYC", "SUGARC");
  s = replaceWord(s, "tinycc", "sugarc");
  s = replaceWord(s, "TinyCC", "SugarC");
  s = replaceWord(s, "Tiny C", "Sugar C");

  writeFile(s, argv[1]);

  printf("■");
})