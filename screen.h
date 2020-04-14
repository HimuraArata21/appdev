// usually in a header file we have 2 part
// 1. function declarations
// 2. constant definitions

// constant definitions
#define ESC 27	// or using hex 0x1B

//make enumeration for fg colors
enum FG {BLACK=30,RED,GREEN,YELLOW,BLUE,MAGENTA,CYAN,WHITE};
#define bg(c)	(c+10)

#define UNICODE
#define BAR "\u2590"

#define DEBUG
// the following is the information of cursor position, 
//this information will be decoded by escape sequence ESC[6n, 
//and query reply should be a string consisting row and col numbers of cursor.
typedef struct{
	int row;
	int col;
}Position;
//making a constant in a name will make your program more meaningful/readable
//now we can use color names in function setfgcolor()

// function declarations
void setfgcolor(int);
void setbgcolor(int);
void setcolors(int, int);
void resetcolors(void);
void clearscreen(void);
void gotoXY(int, int);
void setcursor(int, int);
void drawbar(int, int);
void drawrect(int, int, int, int);
Position getscreensize(void);
int devicestatus(void);
