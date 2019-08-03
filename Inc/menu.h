#ifndef __MENU_H__
#define __MENU_H__

//=============================引用头文件=========================================================
#include "display.h"

//=============================宏定义=============================================================

#define MENU_NUM 4
#define OPT_NUM_1 3
#define OPT_NUM_2 6
#define OPT_NUM_3 2
#define OPT_NUM_4 1


//=============================菜单结构体=========================================================

//菜单界面
typedef struct MenuStruct
{
		unsigned char menuNum;//菜单编号
		unsigned char subOptNum;//子项目数量
		struct subOptionStruct *subOpt;//子项目指针
}MenuItem;

//项目
//主页面子项目最多就6个！！多了不想写判断了！！！（暴躁）
typedef struct subOptionStruct
{
		MenuItem *menu;//位于菜单
		unsigned char optNum;//项目编号
		char *optName;//项目名称
		void (*display)();//主页面显示函数（在display.h里调用这个显示每个选项）
		void (*KeyCallbackPlus)();//按键回调函数(+键)
		void (*KeyCallbackMinus)();//按键回调函数(-键)
		void (*KeyCallbackConfirm)();//按键回调函数(确认键)
	
}SubOption;

//=============================结构体声明=========================================================

static SubOption Menu_1[OPT_NUM_1];
	
static SubOption Menu_2[OPT_NUM_2];
	
static SubOption Menu_3[OPT_NUM_3];

static SubOption Menu_4[OPT_NUM_4];

//======================callback函数声明===========================================================

//display
void CallbackDisplay1_1(void);
void CallbackDisplay1_2(void);
void CallbackDisplay1_3(void);

void CallbackDisplay2_1(void);
void CallbackDisplay2_2(void);
void CallbackDisplay2_3(void);
void CallbackDisplay2_4(void);
void CallbackDisplay2_5(void);
void CallbackDisplay2_6(void);

void CallbackDisplay3_1(void);
void CallbackDisplay3_2(void);

void CallbackDisplay4_1(void);

//plus
void KeyCallbackPlus1_1(void);
void KeyCallbackPlus1_2(void);
void KeyCallbackPlus1_3(void);

void KeyCallbackPlus2_1(void);
void KeyCallbackPlus2_2(void);
void KeyCallbackPlus2_3(void);
void KeyCallbackPlus2_4(void);
void KeyCallbackPlus2_5(void);
void KeyCallbackPlus2_6(void);

void KeyCallbackPlus3_1(void);
void KeyCallbackPlus3_2(void);

void KeyCallbackPlus4_1(void);

//minus
void KeyCallbackMinus1_1(void);
void KeyCallbackMinus1_2(void);
void KeyCallbackMinus1_3(void);

void KeyCallbackMiuns2_1(void);
void KeyCallbackMinus2_2(void);
void KeyCallbackMinus2_3(void);
void KeyCallbackMinus2_4(void);
void KeyCallbackMinus2_5(void);
void KeyCallbackMinus2_6(void);

void KeyCallbackMinus3_1(void);
void KeyCallbackMinus3_2(void);

void KeyCallbackMinus4_1(void);

//confirm
void KeyCallbackConfirm1_1(void);
void KeyCallbackConfirm1_2(void);
void KeyCallbackConfirm1_3(void);

void KeyCallbackConfirm2_1(void);
void KeyCallbackConfirm2_2(void);
void KeyCallbackConfirm2_3(void);
void KeyCallbackConfirm2_4(void);
void KeyCallbackConfirm2_5(void);
void KeyCallbackConfirm2_6(void);

void KeyCallbackConfirm3_1(void);
void KeyCallbackConfirm3_2(void);

void KeyCallbackConfirm4_1(void);

//==============================各个菜单定义======================================================


static MenuItem menu[MENU_NUM]=
{
	{1,3,Menu_1},
	{2,6,Menu_2},
	{3,2,Menu_3},
	{4,1,Menu_4}
};


//========================各个页面下项目定义======================================================

static SubOption Menu_1[OPT_NUM_1]=//第一个页面下项目
{
	{menu,1,"opt1",CallbackDisplay1_1,KeyCallbackPlus1_1,KeyCallbackMinus1_1,KeyCallbackConfirm1_1},//第一个项目
	{menu,2,"opt2",CallbackDisplay1_2,KeyCallbackPlus1_2,KeyCallbackMinus1_2,KeyCallbackConfirm1_2},//第二个项目
	{menu,3,"opt3",CallbackDisplay1_3,KeyCallbackPlus1_3,KeyCallbackMinus1_3,KeyCallbackConfirm1_3}//第三个项目
};
	
static SubOption Menu_2[OPT_NUM_2]=//第二个页面下项目
{
	{menu+1,1,"opt1",CallbackDisplay2_1,KeyCallbackPlus2_1,KeyCallbackMiuns2_1,KeyCallbackConfirm2_1},//第一个项目
	{menu+1,2,"opt2",CallbackDisplay2_2,KeyCallbackPlus2_2,KeyCallbackMinus2_2,KeyCallbackConfirm2_2},//第二个项目
	{menu+1,3,"opt3",CallbackDisplay2_3,KeyCallbackPlus2_3,KeyCallbackMinus2_3,KeyCallbackConfirm2_3},//第三个项目
	{menu+1,4,"opt4",CallbackDisplay2_4,KeyCallbackPlus2_4,KeyCallbackMinus2_4,KeyCallbackConfirm2_4},//第四个项目
	{menu+1,5,"opt5",CallbackDisplay2_5,KeyCallbackPlus2_5,KeyCallbackMinus2_5,KeyCallbackConfirm2_5},//第五个项目
	{menu+1,6,"opt6",CallbackDisplay2_6,KeyCallbackPlus2_6,KeyCallbackMinus2_6,KeyCallbackConfirm2_6}//第六个项目
};	

static SubOption Menu_3[OPT_NUM_3]=//第三个页面下项目
{
	{menu+2,1,"opt1",CallbackDisplay3_1,KeyCallbackPlus3_1,KeyCallbackMinus3_1,KeyCallbackConfirm3_1},//第一个项目
	{menu+2,2,"opt2",CallbackDisplay3_2,KeyCallbackPlus3_2,KeyCallbackMinus3_2,KeyCallbackConfirm3_2}//第二个项目
};

static SubOption Menu_4[OPT_NUM_4]=//第四个页面下项目
{
	{menu+3,1,"opt1",CallbackDisplay4_1,KeyCallbackPlus4_1,KeyCallbackMinus4_1,KeyCallbackConfirm4_1}//第一个项目
};		


#endif


