#include <ncurses.h>
#include <iostream>
#include <string.h>

WINDOW	*create_newwin( int height, int width, int starty, int startx);
void		destroy_win( WINDOW *local_win );

int main( int argc, char* argv[] ) {
	WINDOW *global_win;
	WINDOW *chat_win;
	WINDOW *text_win;
	WINDOW *user_win;
	int startx, starty, width, height;
	int ch;

	initscr();
	cbreak();

	keypad( stdscr, TRUE );

	refresh();

	// Window declarations
	global_win	= create_newwin( 50, 150, 0, 0 );
	chat_win		= create_newwin( 39, 120, 1, 1 );
	text_win		= create_newwin( 9, 120, 40, 1 );
	user_win		= create_newwin( 48, 26, 1, 122 );

	char chat_text[39][120];
	for( int i = 0; i < 39; i++ )
		for( int j = 0; j < 120; j++ )
			chat_text[i][j] = 'a';

  char mesg[] = "just a string";

  for( int i = 5; i < 30; i++ )
    for( int j = 5; j < 30; j++ )
      mvwaddch(chat_win,i,j,chat_text[i][j]);
  wrefresh(chat_win);
//  refresh();

/*	const char *x = "blah blah blah";

	for( int i = 0; i < 14; i++ ) {
		chat_text[0][i] = x[i];
	}

	for( int i = 0; i < 14; i++ ) {
		mvwaddch( chat_win, 0, i, chat_text[0][i] );
	}
*/
//	mvwaddch(chat_win, 2, 2, "blah blah blah");
	//printw("blah blah blah");
	//move(2,123);
	//printw("droops");
//	refresh();

	while((ch = getch()) != KEY_F(1)) { // DO NOTHING
		
	}

	endwin();
	return 0;
}

WINDOW *create_newwin( int height, int width, int starty, int startx ) {
	WINDOW *local_win;

	local_win = newwin( height, width, starty, startx );
	box( local_win, 0, 0 );

	wrefresh( local_win );
	return local_win;
}

void destroy_win( WINDOW *local_win ) {
	wborder( local_win, ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ' );
	wrefresh( local_win );
	delwin( local_win );
}
