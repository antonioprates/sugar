#!//usr/local/bin/sugar
#include <sugar.h>

// HTML 2 TXT
// simple utility: extracts unformatted text from
// html file and prints result to console
// (no html validation, any fragment should work)
//
// limitation: if the text contains '<' (open tag simbol)
// this part will be considered a tag until '>' (closing)
// is found...
//
// by Antonio Prates, 2021

string readHtmlFile(number argc, stringList argv) {
  if (argc != 2) {
    println("bad arguments! should be: ./html2txt.c [FILE]");
    exit(EXIT_FAILURE);  // crash!
  }

  string html = readFile(argv[1]);
  if (html == NULL)      // error would be printed by readFile method...
    exit(EXIT_FAILURE);  // so just crash!

  return html;
}

bool isBlank(char c) {
  return c == ' ' || c == '\n' || c == '\r' || c == '\b' || c == '\t';
}

bool startsWithText(string html) {
  number i = 0;
  while (html[i] != STR_END) {
    if (html[i] == '<')
      return true;  // found open tag first
    if (html[i] == '>')
      return false;  // found close tag first (start is in the middle of a tag)
    i++;
  }
  return true;  // only contains text (no html)
}

string extractText(string html) {
  number i = 0;
  number chunksCount = 0;
  number maxChunks = strlen(html) / 2 + 1;
  stringList textChunks = (stringList)malloc((maxChunks) * sizeof(string));
  bool isTrimming = isBlank(html[0]);
  bool isText = startsWithText(html);

  if (isText && !isBlank(html[0]) && html[0] != '<' && html[0] != STR_END) {
    textChunks[chunksCount] = &html[0];  // point next string
    chunksCount++;
  }

  while (html[i] != STR_END) {
    if (isText) {
      // convert new lines to simple space
      if (isBlank(html[i]))
        html[i] = ' ';

      // if new tag found...
      if (html[i] == '<') {  // html[i] == '<'
        html[i] = STR_END;   // mark the end of the string
        isText = false;
      } else {
        if (isTrimming) {
          if (!isBlank(html[i])) {
            textChunks[chunksCount] = &html[i];  // point next string
            chunksCount++;
            isTrimming = false;
          }
        } else if (isBlank(html[i]) &&
                   (isBlank(html[i + 1]) || html[i + 1] == '<')) {
          html[i] = STR_END;  // mark the end of the string
          isTrimming = true;
        }
      }
    } else {
      if (html[i] == '>') {  // if end of tag...
        isText = true;
        if (isBlank(html[i + 1])) {
          isTrimming = true;
        } else if (html[i + 1] != STR_END) {
          if (html[i + 1] != '<') {
            textChunks[chunksCount] = &html[i + 1];  // point next string
            chunksCount++;
            i++;  // move index forward as nothing left to check here
            isTrimming = false;
          } else
            isText = false;  // found tag opening right after last closed
        }
      }
    }
    i++;  // move index forward
  }
  return joinSep(chunksCount, textChunks, ' ');
}

app({ println(extractText(readHtmlFile(argc, argv))); })
