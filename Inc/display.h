#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "menu.h"

#define KEY_UP				1
#define KEY_DOWN      5
#define KEY_LEFT			9
#define KEY_RIGHT			13
#define KEY_PLUS			3
#define KEY_MINUS			4
#define KEY_CONFIRM		12
#define KEY_ESC				16

typedef struct MenuStruct MenuItem;
typedef struct subOptionStruct SubOption;

void displayOled(unsigned char key);

//这里有个warning不知道怎么消除
void displayMenu(MenuItem *menuNow);
void displayOption(SubOption *optNow,unsigned char mode);

#endif

