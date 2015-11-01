
//  A game fragment adapted from Andre La Mothe's book
//  Ported by Antonello Dettori

//	The Black Art of 3D Games Programming

//  Modified by CJM 24/9/'08 to run without error or warnings:

//	1.  hconsole - called TEXT( ) for parameter 1
//	2.  added _ as prefix to deprecated kbhit() function
//	3.  added _ as prefix to deprecated getch() function

//	Note: this is very old-fashioned code originally written for 16-bit PCs



// INCLUDES ///////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ncurses.h>
#include <time.h>
#include <string>
#include <unistd.h>


// DEFINES ////////////////////////////////////////////////

#define MAX_X        80  // maximum x position for player
#define SCROLL_POS   24  // the point that scrolling occurs

// PROTOTYPES /////////////////////////////////////////////

void Init_Graphics();
void Set_Color(int fcolor, int bcolor);
void Draw_String(int x, int y, char *string);

// GLOBALS ////////////////////////////////////////////////

int    game_running = 1; // state of game, 0=done, 1=run

// FUNCTIONS //////////////////////////////////////////////

void Init_Graphics()
{
	// this function initializes the console graphics engine

	setlocale(LC_ALL,"uk");

	initscr();

	cbreak();			/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */

	start_color();

	init_pair(1, COLOR_RED, COLOR_BLACK);

	// seed the random number generator with time
	srand((unsigned)time(NULL));

} // end Init_Graphics

///////////////////////////////////////////////////////////

//void Set_Color(int fcolor, int bcolor = 0)
//{
	// this function sets the color of the console output
//	SetConsoleTextAttribute(hconsole, (WORD)((bcolor << 4) |
//		fcolor));
//
//} // Set_Color

///////////////////////////////////////////////////////////

void Draw_String(int x, int y, char *string)
{
	// this function draws a string at the given x,y

	int cursor_pos_x = x;
	int cursor_pos_y = y;

	// print the string in current color and position
	mvaddstring(cursor_pos_y, cursor_pos_x, string);

} // end Draw_String

///////////////////////////////////////////////////////////

void Clear_Screen(void)
{
	// this function clears the screen

	// set color to white on black
//	Set_Color(15, 0);

//	color_set(COLOR_PAIR(1));

	// clear the screen
	for (int index = 0; index <= SCROLL_POS; index++)
		Draw_String(0, SCROLL_POS, "\n");

} // end Clear_Screen


// MAIN GAME LOOP /////////////////////////////////////////
using namespace std;
int main()
{
	char key;            // player input data
	int  player_x = 40;  // player's x 

	// SECTION: initialization

	// set up the console text graphics system
	Init_Graphics();
	
	// clear the screen
//	Clear_Screen();

	// SECTION: main event loop, this is where all the action  
	// takes place, the general loop is erase-move-draw

	while (game_running)
	{
		// SECTION: erase all the objects or clear screen

		// nothing to erase in our case   

		// SECTION: get player input
		if (getch())
		{
			// get keyboard data, and filter it
			key = getch();

			// is player trying to exit, if so exit
			if (key == 'q' || key == 27)
				game_running = 0;

			// is player moving left        
			if (key == 'a')
				player_x--;

			// is player moving right
			if (key == 's')
				player_x++;

		} // end if   

		// SECTION: game logic and further processing

		// make sure player stays on screen 
		if (++player_x > MAX_X)
			player_x = MAX_X;

		if (--player_x < 0)
			player_x = 0;

		// SECTION: draw everything

		// draw next star at random position
//		Set_Color(15, 0);
		Draw_String(rand() % MAX_X, SCROLL_POS, ".\n");

		// draw player 
//		Set_Color(rand() % 15, 0);
		Draw_String(player_x, 0, "<--*-->");
//		Draw_String(0, 0, "");

		refresh();

		// SECTION: synchronize to a constant frame rate
		usleep(100);

	} // end while

	// SECTION: shutdown and bail
//	Clear_Screen();

	refresh();

	printf("\nG A M E  O V E R \n\n");

	endwin();

	return 0;
} // end main
