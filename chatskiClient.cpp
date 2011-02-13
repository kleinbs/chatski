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
  WINDOW *chat_sub;
	WINDOW *text_win;
  WINDOW *text_sub;
	WINDOW *user_win;
	int startx, starty, width, height;
	int ch;

	initscr();
	cbreak();
  noecho();

	refresh();
	keypad( stdscr, TRUE );

	// Window declarations
	global_win	= create_newwin( 50, 150, 0, 0 );
	chat_win		= create_newwin( 45, 120, 1, 1 );
	text_win		= create_newwin( 3, 120, 46, 1 );
//  text_sub    = subwin( text_win, 1, 119, 1, 1 );
	user_win		= create_newwin( 48, 26, 1, 122 );

  char text[120];
  char queue[120];
  for( int t = 0; t < 120; t++ ) {
    text[t] = ' '; queue[t] = ' '; }

  chat_win = newwin(100,100,0,0);
  chat_sub = subwin( chat_win, 10, 20, 10, 10 ); 
  scrollok( chat_sub, 1 );
  touchwin(chat_win);
  refresh();
  sleep(1);

  int ptr = 1; wmove(text_sub, 1, ptr);
	while((ch = getch()) != KEY_F(1)) { // DO NOTHING
    if( ch != KEY_BACKSPACE && ch != 10 ) {
      /*
         grab user input, key by key, and add it to
         text[][]. print char (advancing cursor)
         refresh, increment pointer (y)
       */
      text[ptr] = ch;
      mvwaddch(text_sub, 2, ptr, text[ptr]);
      wrefresh(text_sub);
      ptr += 1;
    } else if( ch == KEY_BACKSPACE ) {
      /*
         backspace key handler
       */
      if( ptr != 1 ) {
        ptr -= 1; 
        text[ptr] = ' ';
        mvwaddch(text_sub, 0, ptr, text[ptr]);
        wmove(text_sub, 0, ptr);
        wrefresh(text_sub);
      }
    } else if( ch == 10 ) {
      /*
         push data to queue to be processed
          grab all characters out of text and
          push them into the queue, empty text
      */ 
      for( int i = 0; i < ptr; i++ )
        queue[i] = text[i];

      // clear window, redraw border, move the cursor, reset ptr pos, refresh
      werase(text_sub);
      wmove(text_sub, 0, 0);
      ptr = 1;
      wrefresh(text_sub);
  
      wmove(chat_sub, 10, 10);
      scroll(chat_sub);
      wprintw(chat_sub, "%s", queue);
      refresh();
    }
	}
  delwin(chat_sub);
  delwin(text_sub);

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
