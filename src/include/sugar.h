// just some syntactic sugar to make life easier and code look better :D
// 2020, Antonio Prates, <antonioprates@gmail.com>

#ifndef _SUGAR_H
#define _SUGAR_H

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char *string; // declare one string per line or use char *s, *t, *u;
typedef string *stringList;
typedef int number; // use float for float, duh!
typedef number *numberList;

#define STR_END '\0'
#define NUM_MAX INT_MAX
#define NUM_MIN INT_MIN
#define BUF_LEN 4096

// fix eventual problem with <stdbool.h>
#ifndef _Bool
#define _Bool int
#endif

// app -> macro expansion for main function with return 0
// known issue: "error: macro 'app' used with too many args"
#define app(x)                                                                 \
  int main(int argc, char *argv[]) { x return 0; }

// noop -> idiomatic no-op
void noop(){};

// println -> prints a string and adds a new line
void println(string);

// areSame -> strcmp shorthand, if you just want to know it is equal
bool areSame(string, string);

// ofBool -> converts a boolean to string
string ofBool(bool b);

// ofChar -> converts a character to string [USE FREE]
string ofChar(char);

// ofNumber -> converts a number to a new string [USE FREE]
string ofNumber(number);

// ofLong -> converts a long to a new string [USE FREE]
string ofLong(long);

// ofFloat -> converts a long to a new string [USE FREE]
string ofFloat(double f);

// ofString -> atoi shorthand, converts a string to a number
number ofString(string);

// mkString -> join as many strings you like, with no separator [USE FREE]
string mkString(number count, stringList strs);

// join2s -> mkString shorthand, joins 2 strings in a new string [USE FREE]
string join2s(string, string);

// join3s -> mkString shorthand, joins 3 strings in a new string [USE FREE]
string join3s(string, string, string);

// join4s -> mkString shorthand, joins 4 strings in a new string [USE FREE]
string join4s(string, string, string, string);

// join5s -> mkString shorthand, joins 5 strings in a new string [USE FREE]
string join5s(string, string, string, string, string);

// join6s -> mkString shorthand, joins 6 strings in a new string [USE FREE]
string join6s(string, string, string, string, string, string);

// joinSep -> join as many strings you like, with a separator [USE FREE]
string joinSep(number count, stringList strs, char separator);

// splitSep -> split by separator into a list of strings [USE FREE]
stringList splitSep(string str, char separator);

// listCount -> counts valid pointers in stringList provided end is NULL pointer
number listCount(stringList strs);

// forEach -> map over a list of strings and apply string => void function
void forEach(number count, stringList strs, void (*fn)(string));

// startsWith -> checks if word is substring from start of text
bool startsWith(string text, string word);

// countWord -> count occurrences of word in provided text
number countWord(string text, string word);

// replaceWord -> replaces a word with a new word inside a string [USE FREE]
string replaceWord(string text, string oldWord, string newWord);

// readKeys -> reads from keyboard until enter and returns a string [USE FREE]
string readKeys(void);

// writeFile -> writes a string buffer to a filepath
bool writeFile(string buffer, string filepath);

// readFile -> reads text file to a string buffer [USE FREE]
string readFile(string filepath);

// TODO: bellow implementations should be "sugar.c", make this a dynamic lib

void println(string s) { printf("%s\n", s); }

bool areSame(string s1, string s2) {
  if (!s1 && !s2)
    return true;
  if (!s1 || !s2)
    return false;
  return strcmp(s1, s2) == 0 ? true : false;
}

string ofBool(bool b) {
  if (b)
    return "true";
  return "false";
}

string ofChar(char c) {
  string str = (string)malloc(2);
  if (str) { // memory gard
    str[0] = c;
    str[1] = STR_END;
    return str;
  }
  return (string)NULL;
}

string ofNumber(number n) {
  number length = snprintf((string)NULL, 0, "%d", n);
  string result = (string)malloc(length + 1);
  if (result) { // memory gard
    snprintf(result, length + 1, "%d", n);
    return result;
  }
  return (string)NULL;
}

string ofLong(long l) {
  number length = snprintf((string)NULL, 0, "%ld", l);
  string result = (string)malloc(length + 1);
  if (result) { // memory gard
    snprintf(result, length + 1, "%ld", l);
    return result;
  }
  return (string)NULL;
}

string ofFloat(double f) {
  number length = snprintf((string)NULL, 0, "%f", f);
  string result = (string)malloc(length + 1);
  if (result) { // memory gard
    snprintf(result, length + 1, "%f", f);
    return result;
  }
  return (string)NULL;
}

number ofString(string s) { return atoi(s); }

string mkString(number count, stringList strs) {
  number size = 0;
  for (number i = 0; i < count; i++)
    size += strlen(strs[i]);
  string result = (string)malloc(size + 1);
  result[0] = STR_END;
  if (result) { // memory gard
    for (number i = 0; i < count; i++)
      strcat(result, strs[i]);
    return result;
  }
  return (string)NULL;
}

string join2s(string s1, string s2) {
  string list[2] = {s1, s2};
  return mkString(2, list);
}

string join3s(string s1, string s2, string s3) {
  string list[3] = {s1, s2, s3};
  return mkString(3, list);
}

string join4s(string s1, string s2, string s3, string s4) {
  string list[4] = {s1, s2, s3, s4};
  return mkString(4, list);
}

string join5s(string s1, string s2, string s3, string s4, string s5) {
  string list[5] = {s1, s2, s3, s4, s5};
  return mkString(5, list);
}

string join6s(string s1, string s2, string s3, string s4, string s5, string s6) {
  string list[6] = {s1, s2, s3, s4, s5, s6};
  return mkString(6, list);
}

string joinSep(number count, stringList strs, char separator) {
  number totalSize = 0;
  number lastIndex = count - 1;
  char strsep[2] = {separator, STR_END};

  for (number i = 0; i < count; i++)
    totalSize += strlen(strs[i]);

  string result = (string)malloc(totalSize + count + 1);
  result[0] = STR_END;

  if (result) { // memory gard
    for (number i = 0; i < count; i++) {
      strcat(result, strs[i]);
      if (i != lastIndex)
        strcat(result, strsep);
    }
    return result;
  }
  return (string)NULL;
}

stringList splitSep(string str, char separator) {
  char strsep[2] = {separator, STR_END};
  number occur = countWord(str, strsep);
  stringList list = (stringList)malloc((occur + 2) * sizeof(string));
  if (list) { // memory gard
    number size = strlen(str);
    string copy = (string)malloc(size + 1);
    if (copy) {          // memory gard
      strcpy(copy, str); // 'cause strtok modifies original string
      number i = 0;
      string word = strtok(copy, strsep);

      while (word != NULL) {
        list[i] = word;
        word = strtok((string)NULL, strsep);
        i++;
      }
      list[i] = NULL;
      return list;
    }
  }
  return (stringList)NULL;
}

number listCount(stringList strs) {
  number i = 0;
  while (strs[i] != NULL)
    i++;
  return i;
}

void forEach(number count, stringList strs, void (*fn)(string)) {
  for (number i = 0; i < count; i++)
    fn(strs[i]);
}

bool startsWith(string text, string word) {
  if (text && word) {
    string occurrence = strstr(text, word);
    if (occurrence && occurrence == text)
      return true;
  }
  return false;
}

number countWord(string text, string word) {
  number occur = 0;
  if (word) {
    number size = strlen(word);
    if (size) {
      number skipsize = size - 1;
      for (number i = 0; text[i] != STR_END; i++) {
        if (startsWith(&text[i], word)) {
          occur++;
          i += skipsize;
        }
      }
    }
  }
  return occur;
}

string replaceWord(string text, string oldWord, string newWord) {
  number i = 0;
  number textSize = strlen(text);
  number oldWordSize = strlen(oldWord);
  number newWordSize = strlen(newWord);
  number occur = countWord(text, oldWord);
  string result =
      (string)malloc(textSize + occur * (newWordSize - oldWordSize) + 1);

  if (result) { // memory gard
    while (*text != STR_END) {
      if (startsWith(text, oldWord)) {
        strcpy(&result[i], newWord);
        i += newWordSize;
        text += oldWordSize;
      } else
        result[i++] = *text++;
    }

    result[i] = STR_END;
    return result;
  }
  return (string)NULL;
}

string readKeys(void) {
  char buffer[BUF_LEN];
  number i;
  for (i = 0; i < BUF_LEN; i++) {
    buffer[i] = getchar();
    if (buffer[i] == '\n' || buffer[i] == '\r') {
      buffer[i] = STR_END;
      break;
    }
  }
  buffer[BUF_LEN - 1] = STR_END; // just in case we used it all

  string result = (string)malloc(i + 1);
  if (result) { // memory gard
    result[0] = STR_END;
    strcat(result, buffer);
    return result;
  }
  return (string)NULL;
}

bool writeFile(string buffer, string filepath) {
  FILE *f = fopen(filepath, "w");
  if (!f) {
    printf("error: could not write file -> %s\n", filepath);
    return false;
  }
  fputs(buffer, f);
  fclose(f);
  return true;
}

string readFile(string filepath) {
  long length;
  string buffer = (string)NULL;
  FILE *f = fopen(filepath, "r");
  if (f) {
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = (string)malloc(length + 1);
    if (buffer) { // memory gard
      fread(buffer, 1, length, f);
      buffer[length] = STR_END;
    }
    fclose(f);
    return buffer;
  }
  printf("error: file not found -> %s\n", filepath);
  return (string)NULL;
}

#endif /* SUGAR_H */
