// Basic ncurses Hello World
//
// Compile: g++ -Wall -o ncurses ncurses.cpp  -lncurses
// Run    : ./ncurses

#include <ncurses.h>

int main() {

  WINDOW *pWin = NULL;
  WINDOW *win2 = NULL;

  // Start curses mode
  initscr();
  refresh();
  
  // Print the text and refresh to the real screen
  printw("Hello World !!! ");  

  // Create a ncurses window
  pWin = newwin(5, 25, 0, 10);
  wborder(pWin, '|', '|', '-', '-', '+', '+', '+', '+');

  win2 = newwin(10, 30, 5, 15);
  wborder(win2, '|', '|', '-', '-', '+', '+', '+', '+');

  // Print text in window
  mvwprintw(pWin, 3, 1, "Hello Window :-) ");
  wrefresh(pWin);

  mvwprintw(win2, 3, 1, "Hello Window :-) ");
  wrefresh(win2);

  // Close the program
  getch();
  delwin(pWin);
  endwin();

 return 0;
}