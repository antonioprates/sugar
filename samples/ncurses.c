#!//usr/local/bin/sugar -lncurses -dev

#include <curses.h>
#include <sugar.h>

app({
  initscr();              // Start curses mode
  printw("Hello World");  // Print Hello World
  refresh();              // Print it on to the real screen
  getch();                // Wait for user input
  endwin();               // End curses mode
})