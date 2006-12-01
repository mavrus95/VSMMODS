/*****************************************************************
* 文件：LCD19264A.H
* 说明：不支持以下特性
* (1) 不支持显示开关控制
* (2) 不支持设置显示起始行
*****************************************************************/

#include "vsm.hpp"


//LCD常量
#define LCD_BLK_NUM		3		//lcd block number
#define LCD_BLK_LEN		64		//lcd block length
#define LCD_LINE_NUM	8		//lcd line number
#define LCD_LENGTH		(LCD_BLK_LEN*LCD_BLK_NUM)		//lcd length
#define LCD_WIDTH		64		//lcd width
#define BLANK_WIDTH		50		//the width of blank
#define SYM_LINEWIDTH	28		//the width of symbol line

//LCD命令掩码
#define CMD_MASK		0xc0

//LCD命令
#define DISP_ONOFF		0x00	//开关背光
#define SET_STARTLINE	0xc0	//设置起始行
#define SET_XADDRESS	0x80	//设置X地址
#define SET_YADDRESS	0x40	//设置Y地址

//延时常量
#define DELAY_1s  1000000000000
#define DELAY_1ms 1000000000
#define DELAY_1us 1000000
#define DELAY_1ns 1000
#define DELAY_1ps 1


/*
	LCD元件既有数字电气特性，也有绘图特性，所以要继承IACTIVEMODEL和IDSIMMODEL
*/
class LCD19264A : public IACTIVEMODEL,public IDSIMMODEL
{
public:
	/* 电气模型成员函数 */

	//数字电路总是返回TRUE
	INT isdigital (CHAR *pinname);

	//当创建模型实例时被调用，做初始化工作
	VOID setup (IINSTANCE *inst, IDSIMCKT *dsim);

	//仿真运行模式控制，交互仿真中每帧开始时被调用
	VOID runctrl (RUNMODES mode);
	
	//交互仿真时用户改变按键等的状态时被调用
	VOID actuate (REALTIME time, ACTIVESTATE newstate);

	//交互仿真时每帧结束时被调用，通过传递ACTIVEDATA数据与绘图模型通信，从而调用animate()进行绘图
	BOOL indicate (REALTIME time, ACTIVEDATA *data);

	//当引脚状态变化时被调用，主要用来处理数据输入和输出
	VOID simulate (ABSTIME time, DSIMMODES mode);

	//可通过setcallback()设置在给定时间调用的回调函数
	VOID callback (ABSTIME time, EVENTID eventid);


	/* 绘图模型成员函数 */

	//当创建模型实例时被调用，做初始化工作
	VOID initialize (ICOMPONENT *cpt);

	//被PROSPICE调用，返回模拟电气模型
	ISPICEMODEL *getspicemodel (CHAR *device);

	//被PROSPICE调用，返回数字电气模型
	IDSIMMODEL *getdsimmodel (CHAR *device);

	//当原理图需要重绘时被调用
	VOID plot (ACTIVESTATE state);

	//当相应的电气模型产生活动事件时被调用，常用来更新图形
	VOID animate (INT element, ACTIVEDATA *newstate);

	//用来处理键盘和鼠标事件
	BOOL actuate (WORD key, INT x, INT y, DWORD flags);

private:
	IINSTANCE *instance;	//PROSPICE仿真原始模型
	IDSIMCKT *ckt;			//DSIM的数字元件
	ICOMPONENT *component;	//ISIS内部一个活动组件对象

	//引脚定义
	IDSIMPIN *di;	//D/I
	IDSIMPIN *rw;	//R/W
	IDSIMPIN *en;	//E
	IDSIMPIN *cs1;	//CS1
	IDSIMPIN *cs2;	//CS2
	IDSIMPIN *cs3;	//CS3
	IDSIMPIN *d[8];	//D0~D7
	IBUSPIN *databus;	//D[0..7]

	//LCD参数
	BYTE x_addr;	//X地址（见手册）
	BYTE y_addr;	//Y地址（见手册）
	BYTE status;	//状态（见手册）
	BYTE cur_blk;	//当前块号（总共分3块，见手册）
	BYTE DDRAM[LCD_BLK_NUM][LCD_BLK_LEN*LCD_WIDTH/8];	//LCD显示RAM
	BOOL new_flag;	//新数据到达标志

	//显示参数
	BOX lcdarea;	//LCD显示区域
	float pix_width, pix_height;	//每象素对应矩形的宽和高
};
