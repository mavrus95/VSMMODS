#include "mareadout.h"

extern "C" EXPORT IACTIVEMODEL * createactivemodel (CHAR *device, ILICENCESERVER *ils)
{ device=device; MAREADOUT *model = new MAREADOUT(); ils->authorize(PRO_KEY); return (MAREADOUT *) model; }
extern "C" EXPORT  VOID deleteactivemodel (IACTIVEMODEL *model){ delete (MAREADOUT *) model; }
MAREADOUT::MAREADOUT (VOID){}
MAREADOUT::~MAREADOUT() {}

VOID MAREADOUT::initialize (ICOMPONENT *cpt)  // insitialise non active state symbol
 {
	component = cpt;
	BOX textbox;   // fill text box  copy over string to it  as symbol 1 is the  sim state
	cpt->getsymbolarea(1, &textbox);
	textorg.x = (textbox.x1+textbox.x2)/2;
	textorg.y = (textbox.y1+textbox.y2)/2;
	textstyle = cpt->createtextstyle("ACTIVE MAREADOUT");
}
ISPICEMODEL *MAREADOUT::getspicemodel (CHAR *) { return NULL; }  // check for spice model
IDSIMMODEL  *MAREADOUT::getdsimmodel (CHAR *) { return NULL; }  // check for a digital model

// plot  symbol c "in our case  then plot symbol 1 symbol 0 is the writing
VOID MAREADOUT::plot (ACTIVESTATE state)
{
	state=state;
	component->drawsymbol(-1);
	component->drawsymbol(1);
	component->drawtext(textorg.x, textorg.y, 0, TXJ_CENTRE|TXJ_MIDDLE, rout);
}
VOID MAREADOUT::animate (INT element, ACTIVEDATA *data)
{
	element=element;
	CHAR sign;
	CHAR result[19]; // -> modified
	if (data->type == ADT_REAL)
	{
	        DOUBLE absval = fabs(data->realval);
		    if  (data->realval > 0.0000001)
			    sign = '+';
		    else if
			    (data->realval < -0.0000001)
			    sign = '-';
		    else { sign = ' '; sprintf_s(result, "        0.0      ");}
		    if (absval > 999999999.9999999)
			    sprintf_s(result, "%cOPEN_LIMIT 1G", sign);
		    else if (absval <= 999999999.9999999)
			{sprintf_s(result, "%c%9.7f", sign, absval); }
			strcpy_s( rout,_countof(rout),result);
	}
	component->drawsymbol(1);
	component->drawtext(textorg.x, textorg.y, 0, TXJ_CENTRE|TXJ_MIDDLE, rout);
}
// setup  for  any  interactive  parts / not used here
BOOL MAREADOUT::actuate (WORD key, INT x, INT y, DWORD flags)
{ key=key; x=x;y=y;flags=flags; return FALSE; };







