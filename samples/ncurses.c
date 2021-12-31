#if 0
  /usr/bin/env sugar -lncurses -run `basename $0` $@ && exit;
  // above is a shebang hack, so you can run as ./ncurses.c
#endif

#include <curses.h>
#include <sugar.h>

app({
  initscr();             // start curses mode
  printw("Hello World"); // print Hello World to screen buffer
  refresh();             // render buffer to the real screen
  getch();               // wait for user input
  endwin();              // end curses mode
})