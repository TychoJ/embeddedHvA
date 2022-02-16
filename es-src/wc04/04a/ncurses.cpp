// Basic ncurses Hello World
//
// Compile: g++ -Wall -o ncurses ncurses.cpp  -lncurses
// Run    : ./ncurses

#include <ncurses.h>

int main() {

  WINDOW *pWin = NULL;

  // Start curses mode
  initscr();
  refresh();
  
  // Print the text and refresh to the real screen
  printw("Hello World !!! ");  

  // Create a ncurses window
  pWin = newwin(10, 30, 5, 15);
  wborder(pWin, '|', '|', '-', '-', '+', '+', '+', '+');

  // Print text in window
  mvwprintw(pWin, 3, 1, "Hello Window :-) ");
  wrefresh(pWin);

  // Close the program
  getch();
  delwin(pWin);
  endwin();

 return 0;
}