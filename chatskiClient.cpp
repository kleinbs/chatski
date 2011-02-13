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

	WINDOW *global_win;
	WINDOW *chat_win;
	WINDOW *text_win;
	WINDOW *user_win;
	int startx, starty, width, height;
	int ch;

	initscr();
	cbreak();
  noecho();

	keypad( stdscr, TRUE );

	refresh();

	// Window declarations
	global_win	= create_newwin( 50, 150, 0, 0 );
	chat_win		= create_newwin( 39, 120, 1, 1 );
	text_win		= create_newwin( 9, 120, 40, 1 );
	user_win		= create_newwin( 48, 26, 1, 122 );

	char chat_text[39][120];
  char text_text[9][120];
	for( int i = 0; i < 39; i++ )
		for( int j = 0; j < 120; j++ )
			chat_text[i][j] = 'a';

  char mesg[] = "just a string";

  for( int i = 5; i < 30; i++ )
    for( int j = 5; j < 30; j++ )
      mvwaddch(chat_win,i,j,chat_text[i][j]);
  wrefresh(chat_win);

  /*for( int i = 0; *username[i] != '\0'; i++ ) {
    mvwaddch(user_win, 1, i, *username[i]);
  }
  wrefresh(user_win);*/

  int x = 1;
  int y = 1;
	while((ch = getch()) != KEY_F(1)) { // DO NOTHING
    if( ch != KEY_BACKSPACE ) {
      text_text[x][y] = ch;
      mvwaddch(text_win, x, y, text_text[x][y]);
      wrefresh(text_win);
      y += 1;
    } else {
      if( y != 1 ) {
        y -= 1; 
        text_text[x][y] = ' ';
        mvwaddch(text_win, x, y, text_text[x][y]);
        wmove(text_win, x, y);
        wrefresh(text_win);
      }
    }
	}

	endwin();
	return 0;
}

void *monitor_chat() {
  // wait for response back from server
}

void *monitor_input( void *input_win ) {
  // watch for user input
  // wait for '\n'
  // send data to queue
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
