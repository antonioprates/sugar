#!///usr/local/bin/sugar -dev
#include <sugar.h>

// some basic tests on the sugar script library

void check(string testName, bool pass) {
  // use standard C printf just to make sure pass/fail is not due to
  // changes made on sugar implementation...
  if (!pass) {
    printf("[ FAILED ]  -> %s\n", testName);
    exit(EXIT_FAILURE);
  }
  printf("[ passed ]  -> %s\n", testName);
}

void skip(string testName, bool pass) {
  printf("[ skip.. ]  -> %s\n", testName);
}

void doTests() {
  skip("println",
       // yes, I know it works, but I should think on how to test this
       true);

  check("areSame",
        areSame("yes", "yes") == true && areSame("yes", "no") == false);

  check("ofBool",
        areSame(ofBool(true), "true") && areSame(ofBool(false), "false"));

  check("ofChar",
        areSame(ofChar('c'), "c") && areSame(ofChar('c'), "d") == false);

  check("ofNumber",
        // if we pass a number bigger than NUM_MAX or NUM_MIN we'll get
        // negatives or whatever, but this is expected in C anyway...
        // by the way, this worked on my mac, but could fail on other OS
        areSame(ofNumber(1234567890), "1234567890") &&
            areSame(ofNumber(0), "0") && areSame(ofNumber(-1), "-1"));

  check("ofLong",
        // if we pass a number bigger than LONG_MAX or LONG_MAX we'll get
        // negatives or whatever, but this is expected in C anyway...
        // by the way, this worked on my mac, but could fail on other OS
        areSame(ofLong(1122334455667788990), "1122334455667788990") &&
            areSame(ofLong(0), "0") && areSame(ofLong(-1), "-1"));

  check("ofString",
        // because it is based on C atoi stops interpreting at non-numeric
        // so result is always integer
        ofString("1234567890 US$") == 1234567890 &&
            ofString("100.00km") == 100 && ofString("-1,5 abc") == -1 &&
            ofString("Antonio") == 0);

  string list[3] = {"a", "b", "c"};

  check("mkString", areSame(mkString(3, list), "abc"));

  check("join2s", areSame(join2s("a", "b"), "ab"));

  check("join3s", areSame(join3s("a", "b", "c"), "abc"));

  check("join4s", areSame(join4s("a", "b", "c", "d"), "abcd"));

  check("join5s", areSame(join5s("a", "b", "c", "d", "e"), "abcde"));

  check("joinSep", areSame(joinSep(3, list, ','), "a,b,c"));

  stringList listFromSplit = splitSep("red-green-blue", '-');

  check("splitSep", areSame(listFromSplit[0], "red") &&
                        areSame(listFromSplit[1], "green") &&
                        areSame(listFromSplit[2], "blue"));

  skip("forEach",
       // yes, I know it works, but I should think on how to test this
       true);

  check("startsWith",
        startsWith("abc", "a") == true && startsWith("abc", "c") == false);

  string phrase = "here we have 5 'e' and 3 'a'";

  check("countWord", countWord(phrase, "and") == 1 &&
                         countWord(phrase, "e") == 5 &&
                         countWord(phrase, "a") == 3);

  phrase = replaceWord(phrase, "here", "there");
  phrase = replaceWord(phrase, "we", "you");

  check("replaceWord", areSame(phrase, "there you have 5 'e' and 3 'a'"));

  skip("readKeys",
       // yes, I know it works, but I should think on how to test this
       true);

  string filename = "test.txt";
  bool didSave = writeFile(phrase, filename);

  check("writeFile", writeFile(phrase, filename));

  check("readFile", areSame(readFile(filename), phrase));

  // try to remove the file create during test in mac/linux env
  if (system(join2s("rm ", filename)) != EXIT_SUCCESS) {
    println("[ Info.. ]  -> rm didn't work, try clean up with del (windows?)");
    if (system(join2s("del ", filename)) != EXIT_SUCCESS)
      // else... warn user :/
      println(
          join2s("[ Warn.. ]  -> could not remove file generated during test: ",
                 filename));
  }
}

app({
  println("[   GO   ]  -> running test cases for <sugar.h>...");

  doTests();

  // by using app we are already testing the macro expansion for main function..
  // AND error found with more code: "macro 'app' used with too many args"
  println(
      "[ issue? ]  -> app macro with big body causes: 'app' used with "
      "too many args");

  // still, it's worth the convenience...
  // ...and main functions should not be big anyway!

  println("[   OK   ]  -> <sugar.h> should be good!");
})
