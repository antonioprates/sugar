// just some syntactic sugar to make live easier and code look better :D
// 2020, Antonio Prates, <antonioprates@gmail.com>

#ifndef _SUGAR_h
#define _SUGAR_h

#include <limits.h>

#define null NULL
typedef char* string;
typedef string* stringList;
typedef int number;  // use float for float, duh!
typedef number* numberList;
typedef enum { false, true } boolean;
typedef enum { _success, _failure } excode;  // exit code
const char _strend = '\0';
const number _nmax = INT_MAX;
const number _nmin = INT_MIN;

#define app(x) \
  int main(int argc, char* argv[]) { x return 0; }

// println -> prints a string and adds a new line
void println(string);

// ofBoolean -> converts a boolean to a string
string ofBoolean(boolean);

// ofNumber -> converts a number to a new string [USE FREE]
string ofNumber(number);

// ofLong -> converts a long to a new string [USE FREE]
string ofLong(long);

// ofString -> atoi shorthand, converts a string to a number
number ofString(string);

// round -> gets the approximation of float to number
number round(float);

// mkString -> join as many strings you like with a list of strings [USE FREE]
string mkString(number count, stringList strs);

// join2s -> mkString shorthand, joins 2 strings in a new string [USE FREE]
string join2s(string, string);

// join3s -> mkString shorthand, joins 3 strings in a new string [USE FREE]
string join3s(string, string, string);

// join4s -> mkString shorthand, joins 4 strings in a new string [USE FREE]
string join4s(string, string, string, string);

// join5s -> mkString shorthand, joins 5 strings in a new string [USE FREE]
string join5s(string, string, string, string, string);

// mapVS -> maps over a list of strings with a (void => string) function
void mapVS(number count, stringList s, void (*fn)(string));

// startsWith -> checks if word is substring from start of s
boolean startsWith(string s, string word);

// countWord -> count occurrences of old word in the string
number countWord(string s, string word);

// replaceWord -> replaces a word with a new word inside a string [USE FREE]
string replaceWord(string text, string oldWord, string newWord);

// readKeys -> reads from keyboard until enter and returns a string [USE FREE]
string readKeys(void);

// readFile -> reads all text content of a filepath to a string
string readFile(string filepath);

// writeFile -> writes a string as text to a filepath
void writeFile(string s, string filepath);

// include "sugar.c"  // TODO: make sugar as a dynamic lib

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

void println(string s) {
  printf("%s\n", s);
}

string ofBoolean(boolean b) {
  return b ? "true" : "false";
}

string ofNumber(number n) {
  number length = snprintf(NULL, 0, "%d", n);
  string result = malloc(length + 1);
  snprintf(result, length + 1, "%d", n);
  return result;
}

string ofLong(long l) {
  number length = snprintf(NULL, 0, "%ld", l);
  string result = malloc(length + 1);
  snprintf(result, length + 1, "%ld", l);
  return result;
}

number ofString(string s) {
  return atoi(s);
}

number round(float f) {
  return (number)(f + 0.5);
}

string mkString(number count, stringList strs) {
  number size = 0;
  for (number i = 0; i < count; i++)
    size += strlen(strs[i]);
  string result = malloc(size + 1);
  for (number i = 0; i < count; i++)
    strcat(result, strs[i]);
  return result;
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

void mapVS(number count, stringList s, void (*fn)(string)) {
  for (number i = 0; i < count; i++)
    fn(s[i]);
}

boolean startsWith(string s, string word) {
  number i;
  for (i = 0; s[i] != _strend; i++) {
    if (word[i] == _strend)
      return true;
    if (word[i] != s[i])
      return false;
  }
  return false;
}

number countWord(string s, string word) {
  number occur = 0;
  number size = strlen(word);

  for (number i = 0; s[i] != '\0'; i++) {
    if (startsWith(&s[i], word)) {
      occur++;
      i += size - 1;
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
  string result;

  result = malloc(textSize + occur * (newWordSize - oldWordSize) + 1);

  while (*text != _strend) {
    if (startsWith(text, oldWord)) {
      strcpy(&result[i], newWord);
      i += newWordSize;
      text += oldWordSize;
    } else
      result[i++] = *text++;
  }

  result[i] = _strend;
  return result;
}

string readKeys(void) {
  const number bufsize = 4096;
  char buffer[bufsize];
  fgets(buffer, bufsize, stdin);
  string result = malloc(strlen(buffer) + 1);
  strcpy(result, buffer);
  string head = result;
  while (*head != _strend) {
    if (head[0] == '\n' || head[0] == '\r') {
      head[0] = _strend;
      break;
    }
    *head++;
  }
  return result;
}

string readFile(string filepath) {
  number length;
  number maxbuffer = _nmax - 1;
  string buffer = null;
  FILE* f = fopen(filepath, "r");
  if (f) {
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    if (length > maxbuffer) {
      println("error: file too big!");
      return null;
    }
    fseek(f, 0, SEEK_SET);
    buffer = malloc(length + 1);
    if (buffer) {
      fread(buffer, 1, length, f);
      buffer[length] = _strend;
    }
    fclose(f);
    return buffer;
  }
  println(join2s("file not found: ", filepath));
  return null;
}

void writeFile(string s, string filepath) {
  FILE* f = fopen(filepath, "w");
  if (f)
    fputs(s, f);
  else
    println(join2s("could not write: ", filepath));
  fclose(f);
}

#endif