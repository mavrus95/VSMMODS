#include <string.h>
#include "LCD12232A.h"

extern "C" IDSIMMODEL __declspec(dllexport) * createdsimmodel (CHAR *device, ILICENCESERVER *ils)
{ 
		ils->authorize(0x11111111, 0x11);	
	return new LCD12232A;	
}

extern "C" VOID __declspec(dllexport) deletedsimmodel (IDSIMMODEL *model)
{
	delete (LCD12232A *)model;
}

INT LCD12232A::isdigital (CHAR *pinname)
{
return 1;
}

VOID LCD12232A:: setup(IINSTANCE *inst, IDSIMCKT *dsim)
{
instance=inst;
ckt=dsim;
res = instance->getdsimpin("RES,res",true);
res->setstate(FLT);
cs = instance->getdsimpin("CS,cs",true);
cs->setstate(FLT);
a0 = instance->getdsimpin("RES,res",true);
a0->setstate(FLT);
rw = instance->getdsimpin("RES,res",true);
rw->setstate(FLT);
en = instance->getdsimpin("RES,res",true);
en->setstate(FLT);
d[0] = instance->getdsimpin("RES,res",true);
d[0]->setstate(FLT);
d[1] = instance->getdsimpin("RES,res",true);
d[1]->setstate(FLT);
d[2] = instance->getdsimpin("RES,res",true);
d[2]->setstate(FLT);
d[3] = instance->getdsimpin("RES,res",true);
d[3]->setstate(FLT);
d[4] = instance->getdsimpin("RES,res",true);
d[4]->setstate(FLT);
d[5] = instance->getdsimpin("RES,res",true);
d[5]->setstate(FLT);
d[6] = instance->getdsimpin("RES,res",true);
d[6]->setstate(FLT);
d[7] = instance->getdsimpin("RES,res",true);
d[7]->setstate(FLT);
//линия  данных
databus = instance->getbuspin("LCD_DBUS",d,8);
databus->settiming(100,100,100);
databus->setstates(SHI,SLO,FLT);
//lcd_model
x_addr = 0;
y_addr = 0;
status=0;
new_flag = TRUE;
}
VOID LCD12232A::runctrl(RUNMODES mode)
{
}
VOID LCD12232A::actuate(REALTIME time, ACTIVESTATE newstate)
{
}
BOOL LCD12232A::indicate(REALTIME time, ACTIVEDATA *data)
{
	if (new_flag){
	data->type = ADT_REAL;
	data->realval=(float)time*DSIMTICK;
	}
	return TRUE;
}
VOID LCD12232A::simulate(ABSTIME time, DSIMMODES mode)
{
//BYTE data;

}
VOID LCD12232A::callback(ABSTIME time, EVENTID eventid)
{
}

//-------------------------------------------------------
//Exported constructor for active component models.
extern "C" IACTIVEMODEL __declspec(dllexport) * createactivemodel (CHAR *device, ILICENCESERVER *ils)
{
ils->authorize(0x88888888,0x69);
return new LCD12232A;
}
//Exported destructor for activecomponent models.
extern "C" VOID __declspec(dllexport) deleteactivemodel (IACTIVEMODEL *model)
{
	delete (LCD12232A *)model;
}
VOID LCD12232A::initialize(ICOMPONENT *cpt)
{
	component = cpt;
	component->setpenwidth(0);
	component->setpencolour(BLACK);
	component->setbrushcolour(BLACK);
	component->getsymbolarea(0,&lcdarea);
	//pix_width = (float)(lcdarea.x2-lcdarea.x1-BLANK_WIDTH*2-SYM_LINEWIDTH*2)/LCD_LENGTH;
	//pix_height = (float)(lcdarea.y2-lcdarea.y1-BLANK_WIDTH*2-SYM_LINEWIDTH*2)/LCD_WIDTH;
}
ISPICEMODEL *LCD12232A::getspicemodel(CHAR *)
{
	return NULL;
}
IDSIMMODEL *LCD12232A::getdsimmodel(CHAR *)
{
	return this;
}
VOID LCD12232A::plot(ACTIVESTATE state)
{
component->drawsymbol(-1);
new_flag=TRUE;
animate(0,NULL);
}
VOID LCD12232A::animate(INT element, ACTIVEDATA *data)
{
/*BOX pix;
BYTE dat, block, line;
if(new_flag)
{
	new_flag=FALSE;
	component->begincache (lcdarea);
	component->drawsymbol(1);

	for(block=0; block<LCD_STR_NUM; block++)// переход по страницам
	{
		for(line=0; line<61; line++) // первый кристалл
		{
			
		}
		for(line=61; line<122; line++) // второй кристалл
		{
		}
		component->endcache();
	}*/
}
BOOL LCD12232A::actuate(WORD key, INT x, INT y, DWORD flags)
{
return FALSE;
}