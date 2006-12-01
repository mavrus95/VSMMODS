/*****************************************************************
* 文件：LCD19264A.CPP
* 说明：不支持以下特性
* (1) 不支持显示开关控制
* (2) 不支持设置显示起始行
*****************************************************************/

#include <string.h>
#include "LCD19264A.h"

//----------------------------------------------------------------------------
//电气模型的实现

//构造数字电气模型实例
extern "C" IDSIMMODEL __declspec(dllexport) * createdsimmodel (CHAR *device, ILICENCESERVER *ils)
{ 
	//授权认证
	ils->authorize(0x88888888, 0x69);	//版本为6.9
	return new LCD19264A;	//创建模型实例
}


//析构数字电气模型实例
extern "C" VOID __declspec(dllexport) deletedsimmodel (IDSIMMODEL *model)
{
	delete (LCD19264A *)model;	//删除模型实例
}


//数字电路总是返回TRUE
INT LCD19264A::isdigital (CHAR *pinname)
{
	return 1;
}


//当创建模型实例时被调用，做初始化工作
VOID LCD19264A::setup (IINSTANCE *inst, IDSIMCKT *dsim)
{
	instance = inst;	//PROSPICE仿真原始模型
	ckt = dsim;		//DSIM的数字元件

	//获取引脚
	di = instance->getdsimpin("D/I,d/i", true);
	di->setstate(FLT);	//FLOAT
	rw = instance->getdsimpin("R/W,r/w", true);
	rw->setstate(FLT);
	en = instance->getdsimpin("E,e", true);
	en->setstate(FLT);
	cs1 = instance->getdsimpin("CS1,cs1", true);
	cs1->setstate(FLT);
	cs2 = instance->getdsimpin("CS2,cs2", true);
	cs2->setstate(FLT);
	cs3 = instance->getdsimpin("CS3,cs3", true);
	cs3->setstate(FLT);
	d[0] = instance->getdsimpin("D0,d0", true);
	d[0]->setstate(FLT);
	d[1] = instance->getdsimpin("D1,d1", true);
	d[1]->setstate(FLT);
	d[2] = instance->getdsimpin("D2,d2", true);
	d[2]->setstate(FLT);
	d[3] = instance->getdsimpin("D3,d3", true);
	d[3]->setstate(FLT);
	d[4] = instance->getdsimpin("D4,d4", true);
	d[4]->setstate(FLT);
	d[5] = instance->getdsimpin("D5,d5", true);
	d[5]->setstate(FLT);
	d[6] = instance->getdsimpin("D6,d6", true);
	d[6]->setstate(FLT);
	d[7] = instance->getdsimpin("D7,d7", true);
	d[7]->setstate(FLT);

	//为方便操作，将D0~D7映射为8位总线
	databus = instance->getbuspin("LCD_DBUS", d, 8);
	databus->settiming(100,100,100);	//设置时间延迟
	databus->setstates(SHI,SLO,FLT);	//设置总线逻辑为[1,0,三态]时的驱动状态
	
	//lcd model	
	x_addr = 0;	//X地址（见手册）
	y_addr = 0;	//Y地址（见手册）
	status = 0;	//状态（见手册）
	new_flag = TRUE;	//新数据到达标志
}


//仿真运行模式控制，交互仿真中每帧开始时被调用
VOID LCD19264A::runctrl (RUNMODES mode)
{

}


//交互仿真时用户改变按键等的状态时被调用
VOID LCD19264A::actuate (REALTIME time, ACTIVESTATE newstate)
{
	
}


//交互仿真时每帧结束时被调用，通过传递ACTIVEDATA数据与绘图模型通信，从而调用animate()进行绘图
BOOL LCD19264A::indicate (REALTIME time, ACTIVEDATA *data)
{	
	if(new_flag){	//有新数据到达
		data->type = ADT_REAL;	//call back animate() to refresh lcd
		data->realval = (float)time*DSIMTICK;
	}
	return TRUE;
}


//当引脚状态变化时被调用，主要用来处理数据输入和输出
VOID LCD19264A::simulate (ABSTIME time, DSIMMODES mode)
{	
	BYTE data;

	if(en->isnegedge()){		//E的下降沿到达
		if((rw->istate()==SLO)||(rw->istate()==WLO)){	//R/W为低表示写

			//读块选择
			if((cs1->istate()==SLO)||(cs1->istate()==WLO))
				cur_blk = 0;
			else if((cs2->istate()==SLO)||(cs2->istate()==WLO))
				cur_blk = 1;
			else if((cs3->istate()==SLO)||(cs3->istate()==WLO))
				cur_blk = 2;
			else
				return;	//not select block
			
			data = (BYTE)databus->getbusvalue();	//读数据

			if((di->istate()==SHI)||(di->istate()==WHI)){	//D/I为高表示数据
				DDRAM[cur_blk][x_addr*LCD_BLK_LEN+y_addr] = data;	//写入数据
				new_flag = TRUE;	//新数据到达标志
				y_addr = ((y_addr+1)%LCD_BLK_LEN);		//y地址自动加1
				if(y_addr==0)
					x_addr = ((x_addr+1)%LCD_LINE_NUM);	//自动换行
			}else{		//D/I为低表示命令
				switch(data&CMD_MASK)
				{
				case DISP_ONOFF:	//开关背光
					break;
				case SET_STARTLINE:	//设置起始行
					break;
				case SET_XADDRESS:	//设置X地址
					x_addr = (data&0x07);	//bit2~bit0
					break;
				case SET_YADDRESS:	//设置Y地址
					y_addr = (data&0x3f);	//bit5~bit0
					break;
				default:
					break;
				}
			}
		}else{		//E的下降沿到达,R/W为高表示读结束
			databus->drivetristate(time);	//驱动总线为三态
		}

	}else if(en->isposedge()		//E的上升沿到达
			&& ((rw->istate()==SHI)||(rw->istate()==WHI))){	//R/W为高表示读
		if((di->istate()==SHI)||(di->istate()==WHI)){	//D/I为高表示数据

			//读块选择
			if((cs1->istate()==SLO)||(cs1->istate()==WLO))
				cur_blk = 0;
			else if((cs2->istate()==SLO)||(cs2->istate()==WLO))
				cur_blk = 1;
			else if((cs3->istate()==SLO)||(cs3->istate()==WLO))
				cur_blk = 2;
			else
				return;	//not select block

			data = DDRAM[cur_blk][x_addr*LCD_BLK_LEN+y_addr];
			databus->drivebusvalue(time, data);		//输出数据

			y_addr = ((y_addr+1)%LCD_BLK_LEN);		//y地址自动加1
			if(y_addr==0)
				x_addr = ((x_addr+1)%LCD_LINE_NUM);	//自动换行
		}else{		//D/I为低表示命令
			databus->drivebusvalue(time, status);	//输出状态
		}
	}
}


//可通过setcallback()设置在给定时间调用的回调函数
VOID LCD19264A::callback (ABSTIME time, EVENTID eventid)
{

}


//----------------------------------------------------------------------------
//绘图模型的实现

// Exported constructor for active component models.
extern "C" IACTIVEMODEL __declspec(dllexport) * createactivemodel (CHAR *device, ILICENCESERVER *ils)
{ 
	ils->authorize (0x88888888,0x69);	//6.9
	return new LCD19264A;
}


// Exported destructor for active component models.
extern "C" VOID  __declspec(dllexport) deleteactivemodel (IACTIVEMODEL *model)
{ 
	delete (LCD19264A *)model;
}
 

//当创建模型实例时被调用，做初始化工作
VOID LCD19264A::initialize (ICOMPONENT *cpt)
{ 
	//获取ICOMPONENT接口和初始化
	component = cpt;
	component->setpenwidth(0);
	component->setpencolour(BLACK);
	component->setbrushcolour(BLACK);

	//获取显示区域
	component->getsymbolarea(0,&lcdarea);

	//计算每象素对应矩形的宽和高
	pix_width = (float)(lcdarea.x2-lcdarea.x1-BLANK_WIDTH*2-SYM_LINEWIDTH*2)/LCD_LENGTH;
	pix_height = (float)(lcdarea.y2-lcdarea.y1-BLANK_WIDTH*2-SYM_LINEWIDTH*2)/LCD_WIDTH;
}
 

//被PROSPICE调用，返回模拟电气模型
ISPICEMODEL *LCD19264A::getspicemodel (CHAR *) 
{ 
	return NULL; 
}


//被PROSPICE调用，返回数字电气模型
IDSIMMODEL  *LCD19264A::getdsimmodel (CHAR *) 
{	
	return this; 
}


//当原理图需要重绘时被调用
VOID LCD19264A::plot (ACTIVESTATE state)
{
	//绘制LCD19264A_C元件基本图形
	component->drawsymbol(-1);

	//刷新LCD数据显示
	new_flag = TRUE;
	animate (0, NULL);
}
 

//当相应的电气模型产生活动事件时被调用，常用来更新图形
VOID LCD19264A::animate (INT element, ACTIVEDATA *data)
{ 
	BOX pix;
	BYTE dat,block,line,byte_off,bit_off;

	if(new_flag){	//当有新数据到达
		new_flag = FALSE;

		component->begincache (lcdarea);	//打开缓冲
		component->drawsymbol(1);		//显示LCD19264_1符号

		//显示各点数据
		for(block=0; block<LCD_BLK_NUM; block++){	//block
			for(line=0; line<LCD_LINE_NUM; line++){		//line
				for(byte_off=0; byte_off<LCD_BLK_LEN; byte_off++){	//line off
					dat = DDRAM[block][line*LCD_BLK_LEN+byte_off];	//get byte data
					for(bit_off=0; bit_off<8; bit_off++){
						if(dat&(1<<bit_off)){	//bit=1
							pix.x1 = (int)(BLANK_WIDTH+(block*LCD_BLK_LEN+byte_off)*pix_width+0.5);
							pix.y1 = -(int)(BLANK_WIDTH+(line*8+bit_off)*pix_height+0.5);
							pix.x2 = pix.x1 + (int)(pix_width+0.5);
							pix.y2 = pix.y1 - (int)(pix_height+0.5);
							component->drawbox(pix);	//绘制1个象素点
						}
					}
				}
			}
		}
		component->endcache();	//结束缓冲，显示数据
	}
}


//用来处理键盘和鼠标事件
BOOL LCD19264A::actuate (WORD key, INT x, INT y, DWORD flags)  
{ 
	return FALSE; 
}