#!//usr/local/bin/sugar -lncurses -run
#include <curses.h>
#include <sugar.h>

app({
  initscr();              // start curses mode
  printw("Hello World");  // print Hello World to screen buffer
  refresh();              // render buffer to the real screen
  getch();                // wait for user input
  endwin();               // end curses mode
})