// in this file we are going to define a number of functions for screen
// manipulation. These functions include erase screen, set color attributes,
// set cursor location, etc.. using VT100 escape sequences.

#include <stdio.h>
#include "screen.h"

//function defination
int devicestatus(void)	{
	printf("%c[5n", ESC);
	char status[40];
	scanf("%s", status);
	int ret;
	char dum;
	scanf(status, "%c%c%d%C", &dum, &dum, &ret, &dum);
	return ret;
}
void setfgcolor(int fg)	{
	printf("%c[1;%dm", ESC, fg);
}

void setbgcolor(int bg)	{
	printf("%c[1;%dm", ESC, bg);
}

void setcolors(int f, int b)	{
	setfgcolor(f);
	setbgcolor(bg(b));
}

void resetcolors(void) {
	printf("%c[0m", ESC);
}

void clearscreen(void)	{
	printf("%c[2J", ESC);
}

void gotoXY(int row, int col)	{
	printf("%c[%d;%dH", ESC, row, col);
}

void setcursor(int row, int col)	{
	printf("%c[d;%dH", ESC, row, col);
}

void drawbar(int col, int height)	{
	int i;
	for(i=1; i<=height; i++)	{
		gotoXY(35-i, col);
#ifdef UNICODE
		printf("%s", BAR);
#else
		printf("%c", '#');
#endif
	}
}

void drawrect(int row, int col, int height, int width)	{
	int i, j;	//loop control variables
	for (i = row; i<row+height; i++)	{
		for(j=col; j<col+width; j++)	{
			gotoXY(i, j);
#ifdef UNICODE
			printf("%s", BAR);
#else
			printf("%c", '#');
#endif
		}
		printf("\n");
	}
}

Position getscreensize(void)	{
	Position p;
	char ret[100] = "\0";	//make an empty string for query return
	int r, c;
	gotoXY(999, 999);
	printf("%c[6n", ESC);
	scanf("%s", ret);
#ifdef DEBUG
	printf("%s\n", ret);
#endif
#include <string.h>
	if (strlen(ret)>0)	{
		char dum;
		scanf(ret, "%c%c%d%c%d%c", &dum, &dum, &r, &dum, &c, &dum);
		p.row = r;
		p.col = c;
	}
	else	{
		p.row = 0;
		p.col = 0;
	}
	return p;
}
