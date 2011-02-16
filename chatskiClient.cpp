#include <ncurses.h>
#include <iostream>
#include <string.h>

#define chat_win_x 39
#define chat_win_y 120
#define text_win_x 9
#define text_win_y 120
#define user_win_x 48
#define user_win_y 26

WINDOW	*create_newwin( int height, int width, int starty, int startx);
void		destroy_win( WINDOW *local_win );

int main( int argc, char* argv[] ) {
  /*if( argv[1] != NULL )
    char *username[15] = { argv[1] };*/

	WINDOW *global_win, *chat_win, *chat_sub, *text_win, *text_sub, *user_win;
  int startx, starty, width, height, ch;

	initscr();
	cbreak();
//  noecho();

	keypad( stdscr, TRUE );

	// Window declarations
  // global
	global_win = newwin( 50, 150, 0, 0 );
  box( global_win, 0, 0 );
  wrefresh( global_win );
  // chat
	chat_win = subwin( global_win, 43, 120, 1, 1 );
  box( chat_win, 0, 0 ); wrefresh( chat_win );
  chat_sub = subwin( chat_win, 41, 118, 2, 2 );
  box( chat_sub, 0, 0 ); wrefresh( chat_sub );
  // text
	text_win = subwin( global_win, 5, 120, 44, 1 );
  box( text_win, 0, 0 ); wrefresh( text_win );
  text_sub = subwin( text_win, 3, 118, 45, 2 );
  wrefresh( text_sub );
  // user
	user_win = subwin( global_win, 48, 26, 1, 122 );
  box( user_win, 0, 0 ); wrefresh( user_win );

  touchwin( stdscr );
  werase( text_sub );
  mvwaddch( text_sub, 0, 0, '>' );
//  mvwprintw( text_sub, 0, 2, "%s", "x" );
  wrefresh( text_sub );
  sleep( 1 );

  int x = 2;
  move( 46, 3 );
  while( (ch = getch()) != KEY_F(1) ) {
    mvwaddch( text_sub, 0, x, ch );
    touchwin( text_win );
    touchwin( global_win );
    touchwin( stdscr );
//    wrefresh( text_win );
//    sleep(1);
    wrefresh( global_win );
//    wrefresh( stdscr );
//    sleep(1);
//    wrefresh( text_sub );
//    sleep(1);
  }

  delwin(chat_sub);
  delwin(text_sub);

	endwin();
	return 0;
}

