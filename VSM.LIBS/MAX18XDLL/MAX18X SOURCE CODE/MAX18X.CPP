////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////            MAXIM 18X SERIES A-D CONVERTERS            /////////
///////////////////             Construction started 21-11-2004           //////////
//////////////////		     (C)2000-2004 SIMEON DAVID WEBBER MCA        ///////////
/////////////////  	      ALL RIGHTS RESERVED BY SIMEON DAVID WEBBER    ////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
//////////////     Build: 009   last build data 09_12_2004           ///////////////
////////////////////////////////////////////////////////////////////////////////////
//////////// (c)2000-2004 SIMEON WEBBER MCA  ///////////////////////////////////////
///////////       GLASGOW SCOTLAND UK....   ////////////////////////////////////////
//////////      in progress >> ALPHA V1.0  /////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// STAGE 1 COMPLETE:LISA MODELS AND ISIS PARTS WITH SHELL DLL ALL PINS  -- STARTED /
// STAGE 2 ADD TEST JIGS FOR MODE CONFORMANCE TEST'S                    -- STARTED /
// STAGE 3 ADD SPICE MODEL FRAMEWORK AND COMPLETE TO READY TO USE       -- STARTED /
// STAGE 4 ADD FUNCTIONALITY TO THE DSIMCKT SECTION                     -- STARTED /
// STAGE 5 DEBUG                                                        --         /
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
#include "MAX18X.HPP"

extern "C"  EXPORT IMIXEDMODEL * createmixedmodel (CHAR *device, ILICENCESERVER *ils)
{
	IMIXEDMODEL * model = NULL;
	if (strnicmp(device, "MAX180", 6) == 0) model = new MAX180        ();
	if (strnicmp(device, "MAX181", 6) == 0) model = new MAX181        ();
	if (strnicmp(device, "MAX182", 6) == 0) model = new MAX182        ();
	if (strnicmp(device, "MAX183", 6) == 0) model = new MAX183_4_5    ();
	if (strnicmp(device, "MAX184", 6) == 0) model = new MAX183_4_5    ();
	if (strnicmp(device, "MAX185", 6) == 0) model = new MAX183_4_5    ();
	if (strnicmp(device, "MAX186", 6) == 0) model = new MAX186_8      ();
	if (strnicmp(device, "MAX187", 6) == 0) model = new MAX187_9      ();
	if (strnicmp(device, "MAX188", 6) == 0) model = new MAX186_8      ();
	if (strnicmp(device, "MAX189", 6) == 0) model = new MAX187_9      ();
	if (model != NULL) { ils->authorize(DEV_KEY20); } return (IMIXEDMODEL *) model;
}
extern "C" EXPORT VOID deletemixedmodel (IMIXEDMODEL * model) { delete  (IMIXEDMODEL *) model; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//1------------------------------------------------------------------------------------------------------------------------------------------------1//
///////////////////////////////////////////////////////////////////////////
///////////////         !!basic shell!!                 ///////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
//                         : CLASS MAX180 :                              //
///////////////////////////////////////////////////////////////////////////
///////////////////////////
// : CLASS CONSTRUCTOR : //
///////////////////////////
MAX180::MAX180 (VOID)
{ instance = NULL; spiceckt = NULL; dsimckt = NULL;
    cs              =               NULL;
	clkin           =               NULL;
    dgnd            =               NULL;

	busy            =               NULL;
	mode            =               NULL;
	hben            =               NULL;

	diff            =               NULL;
	bip             =               NULL;
	rd              =               NULL;
	wr              =               NULL;

    ain0            =               NULL;
    ain1            =               NULL;
    ain2            =               NULL;
    ain3            =               NULL;
    ain4            =               NULL;
    ain5            =               NULL;
    ain6            =               NULL;
    ain7            =               NULL;

	SGL_DIF         =               NULL;      // single ended differential  mode switch
    UNI_BIP         =               NULL;      // uni or bipolar mode switch

    held            =               NULL;      // ? is sample there to convert
    shut            =               NULL;      // check if shdn is inactive
    intref          =               NULL;      // choose internal referance or  external {by refpin} input to vref stage
    interef         =               NULL;      // flag to  make choice in spice section for internal or external volts ref trimmer

    refV            =                  5;      // internal zener -5v{5v}
    vref            =                  0;      // voltage referance pin/internal value
    sample          =                  0;      // held result for dsim section
    input           =                  0;      // input a double of a sampled v+ from spice section
    nbits           =                 12;      // number of  data bits  to store = 12

    tCONV           =    dsimtime(55e-7);      // Conversion Time
    tDS             =     dsimtime(1e-7);      // Acquisition Time
    tDV             =     dsimtime(1e-7);      // CS Fall to Output Enable
    tDO             =    dsimtime(20e-9);      // Setupo Delay till DATA OUTPUT VALID
    th              =    dsimtime(10e-9);      //    10n
    tl              =    dsimtime(10e-9);      //    10n
    tg              =     dsimtime(5e-9);      //     5n
}
MAX180::~MAX180() {}
INT MAX180::isanalog (CHAR *pinname)
{
	if (strnicmp(pinname,   "AIN",      3) == 0)
	    return TRUE;
	if (strnicmp(pinname,   "REFIN",    5) == 0)
	    return TRUE;
    if (strnicmp(pinname,   "REFOUT",   6) == 0)
        return TRUE;
	if (strnicmp(pinname,   "REFADJ",   6) == 0)
        return TRUE;
	if (strnicmp(pinname,   "OFFADJ",   6) == 0)
        return TRUE;
	if (strnicmp(pinname,   "AGND",     4) == 0)
        return TRUE;
    else
	    return FALSE;
}
INT MAX180::isdigital (CHAR *pinname)
{
    if (strnicmp(pinname,   "$CS",      3) == 0)
	    return TRUE;
	if (strnicmp(pinname,   "CLKIN",    5) == 0)
	    return TRUE;
	if (strnicmp(pinname,   "DGND",     4) == 0)
	    return TRUE;
	if (strnicmp(pinname,   "D",        1) == 0)
	    return TRUE;
	if (strnicmp(pinname,   "A",        1) == 0)
        return TRUE;
	if (strnicmp(pinname,   "$BUSY$",   5) == 0)
	    return TRUE;
    if (strnicmp(pinname,   "MODE",     4) == 0)
        return TRUE;
	if (strnicmp(pinname,   "HBEN",     4) == 0)
	    return TRUE;
    if (strnicmp(pinname,   "DIFF",     4) == 0)
        return TRUE;
	if (strnicmp(pinname,   "BIP",      3) == 0)
        return TRUE;
    if (strnicmp(pinname,   "$RD$",     3) == 0)
        return TRUE;
	if (strnicmp(pinname,   "$WR$",     3) == 0)
        return TRUE;
	if (strnicmp(pinname,   "CLOCK",    5) == 0)
	    return TRUE;
	else
	    return FALSE;
}
VOID MAX180::runctrl (RUNMODES mode)
{

    if ((mode == RM_SUSPEND) && (SDSSW == TRUE))
	{
		cheight = statuspopup->getcharheight();
		cwidth  = statuspopup->getcharwidth();
		VARWINDOW();
		statuspopup->repaint();
	}
}

VOID MAX180::actuate (REALTIME time, ACTIVESTATE newstate) {}
BOOL MAX180::indicate (REALTIME time, ACTIVEDATA *newstate){ return FALSE; };
VOID MAX180::setup (IINSTANCE *iinstance, ISPICECKT *ispiceckt)
{ instance = iinstance; spiceckt = ispiceckt;

	ain0            =   instance->getspicenode        ("AIN0,ain0",    TRUE);
	ain1            =   instance->getspicenode        ("AIN1,ain1",    TRUE);
	ain2            =   instance->getspicenode        ("AIN2,ain2",    TRUE);
	ain3            =   instance->getspicenode        ("AIN3,ain3",    TRUE);
	ain4            =   instance->getspicenode        ("AIN4,ain4",    TRUE);
	ain5            =   instance->getspicenode        ("AIN5,ain5",    TRUE);
	ain6            =   instance->getspicenode        ("AIN6,ain6",    TRUE);
	ain7            =   instance->getspicenode        ("AIN7,ain7",    TRUE);
    ref             =   instance->getspicenode        ("REF,ref",   TRUE);
    agnd            =   instance->getspicenode        ("AGND",    TRUE);
}
VOID MAX180::accept (REALTIME time, DOUBLE *rhs)
{
    DOUBLE vref         = (ref != -1) ? rhs[ref]:1.0;
    DOUBLE ag           = rhs[agnd];
    DOUBLE asample      = 0;

    ///////////////////////////////////////
    // attain a sample of  each  channel //
    ///////////////////////////////////////
    DOUBLE avin0 = rhs[ain0];
	DOUBLE avin1 = rhs[ain1];
	DOUBLE avin2 = rhs[ain2];
	DOUBLE avin3 = rhs[ain3];
	DOUBLE avin4 = rhs[ain4];
	DOUBLE avin5 = rhs[ain5];
	DOUBLE avin6 = rhs[ain6];
	DOUBLE avin7 = rhs[ain7];

    /////////////////////////////////
    // 8 channel single-ended mode //
	/////////////////////////////////
	if (SGL_DIF)
	{
	    if (sdisel == 0)
		    asample = avin0 - ag;       // CH0+
	    if (sdisel == 1)
		    asample = avin1 - ag;       // CH1+
	    if (sdisel == 2)
		    asample = avin2 - ag;       // CH2+
	    if (sdisel == 3)
		    asample = avin3 - ag;       // CH3+
	    if (sdisel == 4)
		    asample = avin4 - ag;       // CH4+
	    if (sdisel == 5)
		    asample = avin5 - ag;       // CH5+
	    if (sdisel == 6)
    		asample = avin6 - ag;       // CH6+
	    if (sdisel == 7)
		    asample = avin7 - ag;       // CH7+
	}
    /////////////////////////////////
	//     differential mode       //
	/////////////////////////////////
	if (!SGL_DIF)
	{
	    if (sdisel == 0)
		    asample = avin0 - avin1;    // CH0+ CH1-
	    if (sdisel == 1)
		    asample = avin2 - avin3;    // CH2+ CH3-
	    if (sdisel == 2)
		    asample = avin4 - avin5;    // CH4+ CH5-
	    if (sdisel == 3)
		    asample = avin6 - avin7;    // CH6+ CH7-
	    if (sdisel == 4)
		    asample = avin1 - avin0;    // CH1+ CH0-
	    if (sdisel == 5)
		    asample = avin3 - avin2;    // CH3+ CH2-
	    if (sdisel == 6)
		    asample = avin5 - avin4;    // CH5+ CH4-
	    if (sdisel == 7)
		    asample = avin7 - avin6;    // CH7+ CH6-
	}
}
VOID MAX180::dcload (REALTIME time, SPICEMODES mode, DOUBLE *oldrhs, DOUBLE *newrhs) {}
VOID MAX180::acload (SPICEFREQ omega, DOUBLE *rhs, DOUBLE *irhs) {}
VOID MAX180::trunc  (REALTIME time,  REALTIME *newtimestep) {}
VOID MAX180::setup (IINSTANCE *iinstance, IDSIMCKT *idsimckt)
{ instance = iinstance; dsimckt = idsimckt;
    ////////////////////////////////////////////////////////////////////////
    SDSSW               =   instance->getboolval    ("SDSSW",            0); // switch debug window off
    ////////////////////////////////////////////////////////////////////////
	//                   :: DEBUG POPUP STRUCTURE ::                      //
	////////////////////////////////////////////////////////////////////////
	if (SDSSW ==TRUE)
	{
	    cps                 =   new CREATEPOPUPSTRUCT;
	    cps->type           =   PWT_STATUS;
	    cps->caption        =   "MAX 191 STATUS WINDOW";
	    cps->flags          =   PWF_HIDEONANIMATE | PWF_VISIBLE;
	    cps->height         =   30;
	    cps->width          =   45;
	    statuspopup         =   (ISTATUSPOPUP *)instance->createpopup(cps);
	}
	////////////////////////////////////////////////////////////////////////
	cs              =   instance->getdsimpin          ("$CS",     TRUE);
	clkin           =   instance->getdsimpin          ("CLKIN",   TRUE);
    busy            =   instance->getdsimpin          ("$BUSY$",  TRUE);
	mode            =   instance->getdsimpin          ("MODE",    TRUE);
	hben            =   instance->getdsimpin          ("HBEN",    TRUE);
	diff            =   instance->getdsimpin          ("DIFF",    TRUE);
	bip             =   instance->getdsimpin          ("BIP",     TRUE);
	rd              =   instance->getdsimpin          ("$RD$",    TRUE);
	wr              =   instance->getdsimpin          ("$WR$",    TRUE);
    dgnd            =   instance->getdsimpin          ("CLKIN",   TRUE);

	/////////////////////////////////////////////////////////////////
    D_BUS		    =   instance->getbuspin("D,d",0,11, TRUE);
	D_BUS->setstates(SHI,SLO,FLT);
	//D_BUS->settiming(/2);
	/////////////////////////////////////////////////////////////////
    A_BUS		    =   instance->getbuspin("A,a",0,3, TRUE);
	A_BUS->setstates(SHI,SLO,FLT);
	//A_BUS->settiming(/2);
	/////////////////////////////////////////////////////////////////

}
VOID MAX180::simulate (ABSTIME time, DSIMMODES dmode)
{
	if (dmode == DSIMBOOT )
	{
	}
	else if (dmode == DSIMSETTLE)
	{

	}
	else
	{
		EVENTID eventid = 0 ;
	}
}
VOID MAX180::callback (ABSTIME time, EVENTID eventid)
{
}
VOID MAX180::VARWINDOW()
{
}


//2------------------------------------------------------------------------------------------------------------------------------------------------2//
///////////////////////////////////////////////////////////////////////////
///////////////         !!basic shell!!                 ///////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
//                         : CLASS MAX181 :                              //
///////////////////////////////////////////////////////////////////////////
///////////////////////////
// : CLASS CONSTRUCTOR : //
///////////////////////////
MAX181::MAX181 (VOID)
{ instance = NULL; spiceckt = NULL; dsimckt = NULL;
    cs              =               NULL;
	clkin           =               NULL;
	busy            =               NULL;
	mode            =               NULL;
	hben            =               NULL;

	diff            =               NULL;
	bip             =               NULL;
	rd              =               NULL;
	wr              =               NULL;
    dgnd            =               NULL;

    ain0            =               NULL;
    ain1            =               NULL;
    ain2            =               NULL;
    ain3            =               NULL;
    ain4            =               NULL;
    ain5            =               NULL;


	SGL_DIF         =               NULL;      // single ended differential  mode switch
    UNI_BIP         =               NULL;      // uni or bipolar mode switch

    held            =               NULL;      // ? is sample there to convert
    shut            =               NULL;      // check if shdn is inactive
    intref          =               NULL;      // choose internal referance or  external {by refpin} input to vref stage
    interef         =               NULL;      // flag to  make choice in spice section for internal or external volts ref trimmer

    refV            =             246e-2;      // the referance preset for internal voltage gen value
    ref            =                  0;      // voltage referance pin/internal value
    sample          =                  0;      // held result for dsim section
    input           =                  0;      // input a double of a sampled v+ from spice section
    nbits           =                 12;      // number of  data bits  to store = 12


    tCONV           =    dsimtime(55e-7);      // Conversion Time
    tDS             =     dsimtime(1e-7);      // Acquisition Time
    tDV             =     dsimtime(1e-7);      // CS Fall to Output Enable
    tDO             =    dsimtime(20e-9);      // Setupo Delay till DATA OUTPUT VALID
    th              =    dsimtime(10e-9);      //    10n
    tl              =    dsimtime(10e-9);      //    10n
    tg              =     dsimtime(5e-9);      //     5n
}
MAX181::~MAX181() {}
INT MAX181::isanalog (CHAR *pinname)
{
	if (strnicmp(pinname,  "AIN",      3) == 0)
	    return TRUE;
	if (strnicmp(pinname,  "MUXOUT",   6) == 0)
	    return TRUE;
	if (strnicmp(pinname,  "ADCIN",    5) == 0)
	    return TRUE;
	if (strnicmp(pinname,  "REF",    5) == 0)
	    return TRUE;
	if (strnicmp(pinname,  "AGND",     4) == 0)
        return TRUE;
	else
	    return FALSE;
}
INT MAX181::isdigital (CHAR *pinname)
{
    if (strnicmp(pinname,  "$CS",      3) == 0)
	    return TRUE;
	if (strnicmp(pinname,  "CLKIN",    5) == 0)
	    return TRUE;
	if (strnicmp(pinname,  "DGND",     4) == 0)
	    return TRUE;
	if (strnicmp(pinname,  "D",        1) == 0)
	    return TRUE;
	if (strnicmp(pinname,  "A",        1) == 0)
        return TRUE;
	if (strnicmp(pinname,  "$BUSY$",   5) == 0)
	    return TRUE;
    if (strnicmp(pinname,  "MODE",     4) == 0)
        return TRUE;
	if (strnicmp(pinname,  "HBEN",     4) == 0)
	    return TRUE;
    if (strnicmp(pinname,  "DIFF",     4) == 0)
        return TRUE;
	if (strnicmp(pinname,  "BIP",      3) == 0)
        return TRUE;
    if (strnicmp(pinname,  "$RD$",     3) == 0)
        return TRUE;
	if (strnicmp(pinname,  "$WR$",     3) == 0)
        return TRUE;
	else
	    return FALSE;
}
VOID MAX181::runctrl (RUNMODES mode)
{

    if ((mode == RM_SUSPEND) && (SDSSW == TRUE))
	{
		cheight = statuspopup->getcharheight();
		cwidth  = statuspopup->getcharwidth();
		VARWINDOW();
		statuspopup->repaint();
	}
}
VOID MAX181::actuate (REALTIME time, ACTIVESTATE newstate) {}
BOOL MAX181::indicate (REALTIME time, ACTIVEDATA *newstate){ return FALSE; };
VOID MAX181::setup (IINSTANCE *iinstance, ISPICECKT *ispiceckt)
{ instance = iinstance; spiceckt = ispiceckt;
	ain0            =   instance->getspicenode        ("AIN0",    TRUE);
	ain1            =   instance->getspicenode        ("AIN1",    TRUE);
	ain2            =   instance->getspicenode        ("AIN2",    TRUE);
	ain3            =   instance->getspicenode        ("AIN3",    TRUE);
	ain4            =   instance->getspicenode        ("AIN4",    TRUE);
	ain5            =   instance->getspicenode        ("AIN5",    TRUE);
	muxout          =   instance->getspicenode        ("MUXOUT",  TRUE);
	adcin           =   instance->getspicenode        ("ADCIN",   TRUE);
	ref             =   instance->getspicenode        ("REFIN",   TRUE);
    agnd            =   instance->getspicenode        ("AGND",    TRUE);
}
VOID MAX181::accept (REALTIME time, DOUBLE *rhs)
{
    DOUBLE vref         = (ref!=-1) ? rhs[ref]:1.0;
    DOUBLE ag           = rhs[agnd];
    DOUBLE asample      = 0;
    ///////////////////////////////////////
    // attain a sample of  each  channel //
    ///////////////////////////////////////
    DOUBLE avin0 = rhs[ain0];
	DOUBLE avin1 = rhs[ain1];
	DOUBLE avin2 = rhs[ain2];
	DOUBLE avin3 = rhs[ain3];
	DOUBLE avin4 = rhs[ain4];
	DOUBLE avin5 = rhs[ain5];
    /////////////////////////////////
    // 5 channel single-ended mode //
	/////////////////////////////////
	if (SGL_DIF)
	{
	    if (sdisel == 0)
		    asample = avin0 - ag;       // CH0+
	    if (sdisel == 1)
		    asample = avin1 - ag;       // CH1+
	    if (sdisel == 2)
		    asample = avin2 - ag;       // CH2+
	    if (sdisel == 3)
		    asample = avin3 - ag;       // CH3+
	    if (sdisel == 4)
		    asample = avin4 - ag;       // CH4+
	    if (sdisel == 5)
		    asample = avin5 - ag;       // CH5+

	}
    /////////////////////////////////
	//     differential mode       //
	/////////////////////////////////
	if (!SGL_DIF)
	{
	    if (sdisel == 0)
		    asample = avin0 - avin1;    // CH0- CH1+
	    if (sdisel == 1)
		    asample = avin2 - avin3;    // CH2- CH3+
	    if (sdisel == 2)
		    asample = avin4 - avin5;    // CH4- CH5+

	    if (sdisel == 4)
		    asample = avin1 - avin0;    // CH1+ CH0-
	    if (sdisel == 5)
		    asample = avin3 - avin2;    // CH3+ CH2-
	    if (sdisel == 6)
		    asample = avin5 - avin4;    // CH5+ CH4-
	}
}
VOID MAX181::dcload (REALTIME time, SPICEMODES mode, DOUBLE *oldrhs, DOUBLE *newrhs) {}
VOID MAX181::acload (SPICEFREQ omega, DOUBLE *rhs, DOUBLE *irhs) {}
VOID MAX181::trunc  (REALTIME time,  REALTIME *newtimestep) {}
VOID MAX181::setup (IINSTANCE *iinstance, IDSIMCKT *idsimckt)
{ instance = iinstance; dsimckt = idsimckt;
    ////////////////////////////////////////////////////////////////////////
    SDSSW               =   instance->getboolval    ("SDSSW",            0); // switch debug window off
    ////////////////////////////////////////////////////////////////////////
	//                   :: DEBUG POPUP STRUCTURE ::                      //
	////////////////////////////////////////////////////////////////////////
	if (SDSSW ==TRUE)
	{
	    cps                 =   new CREATEPOPUPSTRUCT;
	    cps->type           =   PWT_STATUS;
	    cps->caption        =   "MAX 191 STATUS WINDOW";
	    cps->flags          =   PWF_HIDEONANIMATE | PWF_VISIBLE;
	    cps->height         =   30;
	    cps->width          =   45;
	    statuspopup         =   (ISTATUSPOPUP *)instance->createpopup(cps);
	}
	////////////////////////////////////////////////////////////////////////

	cs              =   instance->getdsimpin          ("$CS",     TRUE);
	clkin           =   instance->getdsimpin          ("CLKIN",   TRUE);
    busy            =   instance->getdsimpin          ("$BUSY$",  TRUE);
	mode            =   instance->getdsimpin          ("MODE",    TRUE);
	hben            =   instance->getdsimpin          ("HBEN",    TRUE);

	diff            =   instance->getdsimpin          ("DIFF",    TRUE);
	bip             =   instance->getdsimpin          ("BIP",     TRUE);
	rd              =   instance->getdsimpin          ("$RD$",    TRUE);
	wr              =   instance->getdsimpin          ("$WR$",    TRUE);
    dgnd            =   instance->getdsimpin          ("DGND",    TRUE);

	/////////////////////////////////////////////////////////////////
    D_BUS		    =   instance->getbuspin("D,d",0,11, TRUE);
	D_BUS->setstates(SHI,SLO,FLT);
	//D_BUS->settiming(/2);
	/////////////////////////////////////////////////////////////////
    A_BUS		    =   instance->getbuspin("A,a",0,3, TRUE);
	A_BUS->setstates(SHI,SLO,FLT);
	//A_BUS->settiming(/2);
	/////////////////////////////////////////////////////////////////
}
VOID MAX181::simulate (ABSTIME time, DSIMMODES dmode)
{
	if (dmode == DSIMBOOT )
	{
	}
	else if (dmode == DSIMSETTLE)
	{
	}
	else
	{
		EVENTID eventid = 0 ;
	}
}
VOID MAX181::callback (ABSTIME time, EVENTID eventid)
{
}
VOID MAX181::VARWINDOW()
{
}

//3------------------------------------------------------------------------------------------------------------------------------------------------3//
///////////////////////////////////////////////////////////////////////////
///////////////         !!basic shell!!                 ///////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
//                         : CLASS MAX182 :                              //
///////////////////////////////////////////////////////////////////////////
///////////////////////////
// : CLASS CONSTRUCTOR : //
///////////////////////////
MAX182::MAX182 (VOID)
{ instance = NULL; spiceckt = NULL; dsimckt = NULL;

    cs              =               NULL;
	clk             =               NULL;
	rd              =               NULL;
    busy            =               NULL;
    bysl            =               NULL;
    dgnd            =               NULL;

    held            =               NULL;      // ? is sample there to convert
    shut            =               NULL;      // check if shdn is inactive
    intref          =               NULL;      // choose internal referance or  external {by refpin} input to vref stage
    interef         =               NULL;      // flag to  make choice in spice section for internal or external volts ref trimmer

    ain0            =               NULL;
    ain1            =               NULL;
    ain2            =               NULL;
    ain3            =               NULL;

    refV            =             246e-2;      // the referance preset for internal voltage gen value
    vref            =                  0;      // voltage referance pin/internal value
    sample          =                  0;      // held result for dsim section
    input           =                  0;      // input a double of a sampled v+ from spice section
    nbits           =                 12;      // number of  data bits  to store = 12


    tCONV           =    dsimtime(55e-7);      // Conversion Time
    tDS             =     dsimtime(1e-7);      // Acquisition Time
    tDV             =     dsimtime(1e-7);      // CS Fall to Output Enable
    tDO             =    dsimtime(20e-9);      // Setupo Delay till DATA OUTPUT VALID
    th              =    dsimtime(10e-9);      //    10n
    tl              =    dsimtime(10e-9);      //    10n
    tg              =     dsimtime(5e-9);      //     5n
}
MAX182::~MAX182() {}
INT MAX182::isanalog (CHAR *pinname)
{
	if (strnicmp(pinname,  "AIN",      3) == 0)
	    return TRUE;
	if (strnicmp(pinname,  "CAZ",      3) == 0)
	    return TRUE;
	if (strnicmp(pinname,  "REF",    5) == 0)
	    return TRUE;
	if (strnicmp(pinname,  "AGND",     4) == 0)
        return TRUE;
	else
	    return FALSE;
}
INT MAX182::isdigital (CHAR *pinname)
{
	if (strnicmp(pinname,  "DB",       2) == 0)
	    return TRUE;
	if (strnicmp(pinname,  "A",        1) == 0)
	    return TRUE;
	if (strnicmp(pinname,  "DGND",     4) == 0)
	    return TRUE;
	if (strnicmp(pinname,  "$CS",      3) == 0)
	    return TRUE;
	if (strnicmp(pinname,  "CLK",      3) == 0)
	    return TRUE;
	if (strnicmp(pinname,  "$RD$",     3) == 0)
	    return TRUE;
	if (strnicmp(pinname,  "$WRITE$",  6) == 0)
	    return TRUE;
	if (strnicmp(pinname,  "$BUSY$",   5) == 0)
	    return TRUE;
    if (strnicmp(pinname,  "BYSL",     4) == 0)
        return TRUE;
	else
	    return FALSE;
}
VOID MAX182::runctrl (RUNMODES mode) {

    if ((mode == RM_SUSPEND) && (SDSSW == TRUE))
	{
		cheight = statuspopup->getcharheight();
		cwidth  = statuspopup->getcharwidth();
		VARWINDOW();
		statuspopup->repaint();
	}
}
VOID MAX182::actuate (REALTIME time, ACTIVESTATE newstate) {}
BOOL MAX182::indicate (REALTIME time, ACTIVEDATA *newstate){ return FALSE; };
VOID MAX182::setup (IINSTANCE *iinstance, ISPICECKT *ispiceckt)
{ instance = iinstance; spiceckt = ispiceckt;

	ain0 = instance->getspicenode("AIN0,ain0",     TRUE);
	ain1 = instance->getspicenode("AIN1,ain1",     TRUE);
	ain2 = instance->getspicenode("AIN2,ain2",     TRUE);
	ain3 = instance->getspicenode("AIN3,ain3",     TRUE);
	ref  = instance->getspicenode("REF,ref",       TRUE);
    agnd = instance->getspicenode("AGND,agnd",     TRUE);
}
VOID MAX182::accept (REALTIME time, DOUBLE *rhs)
{

    DOUBLE vref         = (ref  != -1) ? rhs[ref] : 1.0;
    DOUBLE ag           = rhs[agnd];
    DOUBLE asample      = 0;

    ///////////////////////////////////////
    // attain a sample of  each  channel //
    ///////////////////////////////////////
    DOUBLE avin0 = rhs[ain0];
	DOUBLE avin1 = rhs[ain1];
	DOUBLE avin2 = rhs[ain2];
	DOUBLE avin3 = rhs[ain3];
    /////////////////////////////////
    // 4 channel single-ended mode //
	/////////////////////////////////
	if (sdisel == 0)
	    asample = avin0 - ag;       // CH0+
	if (sdisel == 1)
		asample = avin1 - ag;       // CH1+
	if (sdisel == 2)
		asample = avin2 - ag;       // CH2+
	if (sdisel == 3)
		asample = avin3 - ag;       // CH3+
}
VOID MAX182::dcload (REALTIME time, SPICEMODES mode, DOUBLE *oldrhs, DOUBLE *newrhs) {}
VOID MAX182::acload (SPICEFREQ omega, DOUBLE *rhs, DOUBLE *irhs) {}
VOID MAX182::trunc  (REALTIME time,  REALTIME *newtimestep) {}
VOID MAX182::setup (IINSTANCE *iinstance, IDSIMCKT *idsimckt)
{ instance = iinstance; dsimckt = idsimckt;
    ////////////////////////////////////////////////////////////////////////
    SDSSW               =   instance->getboolval    ("SDSSW",            0); // switch debug window off
    ////////////////////////////////////////////////////////////////////////
	//                   :: DEBUG POPUP STRUCTURE ::                      //
	////////////////////////////////////////////////////////////////////////
	if (SDSSW ==TRUE)
	{
	    cps                 =   new CREATEPOPUPSTRUCT;
	    cps->type           =   PWT_STATUS;
	    cps->caption        =   "MAX 191 STATUS WINDOW";
	    cps->flags          =   PWF_HIDEONANIMATE | PWF_VISIBLE;
	    cps->height         =   30;
	    cps->width          =   45;
	    statuspopup         =   (ISTATUSPOPUP *)instance->createpopup(cps);
	}
	////////////////////////////////////////////////////////////////////////

	cs              =   instance->getdsimpin          ("$CS",     TRUE);
	clk             =   instance->getdsimpin          ("CLK",     TRUE);
	rd              =   instance->getdsimpin          ("$RD$",    TRUE);
	write           =   instance->getdsimpin          ("$WRITE$", TRUE);
    busy            =   instance->getdsimpin          ("$BUSY$",  TRUE);
    bysl            =   instance->getdsimpin          ("BYSL",    TRUE);
    dgnd            =   instance->getdsimpin          ("DGND",    TRUE);

    /////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////
    DB_BUS		    =   instance->getbuspin("D,d",0,11, TRUE);
	DB_BUS->setstates(SHI,SLO,FLT);
	//D_BUS->settiming(/2);
	/////////////////////////////////////////////////////////////////
    A_BUS		    =   instance->getbuspin("A,a",0,3, TRUE);
	A_BUS->setstates(SHI,SLO,FLT);
	//A_BUS->settiming(/2);
	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////
}
VOID MAX182::simulate (ABSTIME time, DSIMMODES dmode)
{
	if (dmode == DSIMBOOT )
	{
	}
	else if (dmode == DSIMSETTLE)
	{

	}
	else
	{
		EVENTID eventid = 0 ;
	}
}
VOID MAX182::callback (ABSTIME time, EVENTID eventid)
{
}

VOID MAX182::VARWINDOW()
{
}


























//4------------------------------------------------------------------------------------------------------------------------------------------------4//
///////////////////////////////////////////////////////////////////////////
///////////////         !!basic shell!!                 ///////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
//                         : CLASS MAX183_4_5 :                          //
///////////////////////////////////////////////////////////////////////////
///////////////////////////
// : CLASS CONSTRUCTOR : //
///////////////////////////
MAX183_4_5::MAX183_4_5 (VOID)
{ instance = NULL; spiceckt = NULL; dsimckt = NULL;
	cs              =               NULL;

	busy            =               NULL;
	rd              =               NULL;
    clkin           =               NULL;
	clkout          =               NULL;
    dgnd            =               NULL;


    ain0            =               NULL;
    ain1            =               NULL;

    held            =               NULL;      // ? is sample there to convert
    shut            =               NULL;      // check if shdn is inactive
    intref          =               NULL;      // choose internal referance or  external {by refpin} input to vref stage
    interef         =               NULL;      // flag to  make choice in spice section for internal or external volts ref trimmer
    sample          =                  0;
    refV            =             246e-2;      // the referance preset for internal voltage gen value
    vref            =                  0;      // voltage referance pin/internal value
    input           =                  0;      // input a double of a sampled v+ from spice section
    nbits           =                 12;      // number of  data bits  to store = 12
    i               =                  0;      // array's  variable

    t2              =    dsimtime(10e-9);      //    50n
    t9              =    dsimtime(10e-9);      //   100n
    th              =     dsimtime(1e-9);      //    10n
    tl              =     dsimtime(1e-9);      //    10n
    tg              =    dsimtime(5e-10);      //     5n
}
MAX183_4_5::~MAX183_4_5() {}
INT MAX183_4_5::isanalog (CHAR *pinname)
{
	if (strnicmp(pinname, "AIN",       3) == 0)
	    return TRUE;
	if (strnicmp(pinname, "VREF",      4) == 0)
        return TRUE;
    if (strnicmp(pinname, "AGND",      4) == 0)
        return TRUE;
	else
	    return FALSE;
}
INT MAX183_4_5::isdigital (CHAR *pinname)
{
    if (strnicmp(pinname, "$CS",       3) == 0)
	    return TRUE;
	if (strnicmp(pinname, "CLKIN",     5) == 0)
	    return TRUE;
    if (strnicmp(pinname, "CLKOUT",    6) == 0)
	    return TRUE;
    if (strnicmp(pinname, "DGND",      4) == 0)
        return TRUE;
    if (strnicmp(pinname, "D",         1) == 0)
        return TRUE;
    if (strnicmp(pinname, "$RD$",      3) == 0)
        return TRUE;
    if (strnicmp(pinname, "$BUSY$",    5) == 0)
	    return TRUE;
	else
	    return FALSE;
}
VOID MAX183_4_5::runctrl (RUNMODES mode)
{
    if ((mode == RM_SUSPEND) && (SDSSW == TRUE))
	{
		cheight = statuspopup->getcharheight();
		cwidth  = statuspopup->getcharwidth();
		VARWINDOW();
		statuspopup->repaint();
	}
}
VOID MAX183_4_5::actuate (REALTIME time, ACTIVESTATE newstate) {}
BOOL MAX183_4_5::indicate (REALTIME time, ACTIVEDATA *newstate) { return FALSE; };
VOID MAX183_4_5::setup (IINSTANCE *iinstance, ISPICECKT *ispiceckt)
{ instance = iinstance; spiceckt = ispiceckt;
    ain0                =   instance->getspicenode          ("AIN1",     TRUE);
	ain1                =   instance->getspicenode          ("AIN2",     TRUE);
	ref                 =   instance->getspicenode          ("VREF",     TRUE);
    agnd                =   instance->getspicenode          ("AGND",     TRUE);
    tCONV               =   instance->getdelay              ("tCONV",       0);
}
VOID MAX183_4_5::accept (REALTIME time, DOUBLE *rhs)
{
    DOUBLE vref         = (ref != -1) ? rhs[ref]   :  1.0;
    DOUBLE ag           =                       rhs[agnd];
    DOUBLE asample      =                               0;
    ///////////////////////////////////////
    // attain a sample of  each  channel //
    ///////////////////////////////////////
    DOUBLE avin0 = rhs[ain0];
	DOUBLE avin1 = rhs[ain1];
	asample = (((avin0+avin1)+(avin0-avin1))-ag);        // CH0 +-  CH1 +-
    input = (asample/vref);
}
VOID MAX183_4_5::dcload (REALTIME time, SPICEMODES mode, DOUBLE *oldrhs, DOUBLE *newrhs) {}
VOID MAX183_4_5::acload (SPICEFREQ omega, DOUBLE *rhs, DOUBLE *irhs) {}
VOID MAX183_4_5::trunc  (REALTIME time,  REALTIME *newtimestep) {}
VOID MAX183_4_5::setup (IINSTANCE * iinstance, IDSIMCKT *idsimckt)
{ instance = iinstance; dsimckt = idsimckt;
    ////////////////////////////////////////////////////////////////////////
    SDSSW               =   instance->getboolval    ("SDSSW",            0); // switch debug window off
    ////////////////////////////////////////////////////////////////////////
	//                   :: DEBUG POPUP STRUCTURE ::                      //
	////////////////////////////////////////////////////////////////////////
	if (SDSSW ==TRUE)
	{
	    cps                 =   new CREATEPOPUPSTRUCT;
	    cps->type           =   PWT_STATUS;
	    cps->caption        =   "MAX 191 STATUS WINDOW";
	    cps->flags          =   PWF_HIDEONANIMATE | PWF_VISIBLE;
	    cps->height         =   30;
	    cps->width          =   45;
	    statuspopup         =   (ISTATUSPOPUP *)instance->createpopup(cps);
	}
	////////////////////////////////////////////////////////////////////////

	cs              =   instance->getdsimpin          ("$CS",     TRUE);
	busy            =   instance->getdsimpin          ("$BUSY$",  TRUE);
	rd              =   instance->getdsimpin          ("$RD$",    TRUE);
    clkin           =   instance->getdsimpin          ("CLKIN",   TRUE);
	clkout          =   instance->getdsimpin          ("CLKOUT",  TRUE);
    dgnd            =   instance->getdsimpin          ("DGND",    TRUE);
    /////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////
    D_BUS		    =   instance->getbuspin("D,d",0,11, TRUE);
	D_BUS->setstates(SHI,SLO,FLT);
	//D_BUS->settiming(/2);
	////////////////////////////////////////////////////////////////
    FIXEDFC         =   instance->getboolval          ("FIXED",   FALSE);
    convt           =   instance->getdelay            ("tCONV",     10);
    tCONV           =    dsimtime(convt);      // Conversion Time 183-3us 184-5us 185-10us
}
VOID MAX183_4_5::simulate (ABSTIME time, DSIMMODES dmode)
{

	if ((dmode == DSIMBOOT ) || (dmode == DSIMSETTLE))
	{}
	else
	{
	    EVENTID eventid = 0;
	}


}

VOID MAX183_4_5::callback (ABSTIME time, EVENTID eventid)
{
}

VOID MAX183_4_5::VARWINDOW()
{
}

















































//5------------------------------------------------------------------------------------------------------------------------------------------------5//

///////////////////////////////////////////////////////////////////////////
///////////////         !!WORK IN PROGRESS!!            ///////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
//                         : CLASS MAX186_8 :                            //
///////////////////////////////////////////////////////////////////////////
///////////////////////////
// : CLASS CONSTRUCTOR : //
///////////////////////////
MAX186_8::MAX186_8 (VOID)
{ instance = NULL; spiceckt = NULL; dsimckt = NULL;
    cs		        =               NULL;      // the clear to send input
	sclk			=               NULL;      // the serial clock input
	shdn			=               NULL;      // the shutdown pin
	din             =               NULL;
	dout			=               NULL;      // the digital output pin
    sstrb           =               NULL;      // sstrb
    dgnd            =               NULL;      // digital ground pin

    ain0            =               NULL;
    ain1            =               NULL;
    ain2            =               NULL;
    ain3            =               NULL;
    ain4            =               NULL;
    ain5            =               NULL;
    ain6            =               NULL;
    ain7            =               NULL;


    SGL_DIF         =               NULL;      // single ended differential  mode switch
    UNI_BIP         =               NULL;      // uni or bipolar mode switch

    held            =               NULL;      // ? is sample there to convert
    shut            =               NULL;      // check if shdn is inactive
    intref          =               NULL;      // choose internal referance or  external {by refpin} input to vref stage
    interef         =               NULL;      // flag to  make choice in spice section for internal or external volts ref trimmer
    vref            =                  0;      // voltage referance pin/internal value
    sample          =                  0;      // held result for dsim section
    input           =                  0;      // input a double of a sampled v+ from spice section
    nbits           =                 12;      // number of  data bits  to store = 12

    tCONV           =    dsimtime(55e-7);      // Conversion Time
    tDS             =     dsimtime(1e-7);      // Acquisition Time
    tDV             =     dsimtime(1e-7);      // CS Fall to Output Enable
    tDO             =    dsimtime(20e-9);      // Setupo Delay till DATA OUTPUT VALID
    th              =    dsimtime(10e-9);      //    10n
    tl              =    dsimtime(10e-9);      //    10n
    tg              =     dsimtime(5e-9);      //     5n

}
MAX186_8::~MAX186_8() {}
INT MAX186_8::isanalog (CHAR *pinname)
{
	if (strnicmp(pinname, "AIN0",       3) == 0)
	    return TRUE;
	else if (strnicmp(pinname, "AIN1",       3) == 0)
	    return TRUE;
	else if (strnicmp(pinname, "AIN2",       3) == 0)
	    return TRUE;
	else if (strnicmp(pinname, "AIN3",       3) == 0)
	    return TRUE;
	else if (strnicmp(pinname, "AIN4",       3) == 0)
	    return TRUE;
	else if (strnicmp(pinname, "AIN5",       3) == 0)
	    return TRUE;
	else if (strnicmp(pinname, "AIN6",       3) == 0)
	    return TRUE;
	else if (strnicmp(pinname, "AIN7",       3) == 0)
	    return TRUE;
	else if (strnicmp(pinname, "REF",      4) == 0)
	    return TRUE;
	else if (strnicmp(pinname, "AGND",      4) == 0)
        return TRUE;
	else
	    return FALSE;
}
INT MAX186_8::isdigital (CHAR *pinname)
{
	if (strnicmp(pinname, "$CS",       3) == 0)
	    return TRUE;
	else if (strnicmp(pinname, "SCLK",      4) == 0)
	    return TRUE;
	else if (strnicmp(pinname, "DIN",       3) == 0)
	    return TRUE;
	else if (strnicmp(pinname, "DOUT",      4) == 0)
	    return TRUE;
	else if (strnicmp(pinname, "DGND",      4) == 0)
	    return TRUE;
	else if (strnicmp(pinname, "$SHDN$",    5) == 0)
	    return TRUE;
    else if (strnicmp(pinname, "SSTRB",     5) == 0)
        return TRUE;
	else
	    return FALSE;
}
VOID MAX186_8::runctrl (RUNMODES mode)
{
    if ((mode == RM_SUSPEND) && (SDSSW == TRUE))
	{
		cheight = statuspopup->getcharheight();
		cwidth  = statuspopup->getcharwidth();
		VARWINDOW();
		statuspopup->repaint();
	}
}
VOID MAX186_8::actuate (REALTIME time, ACTIVESTATE newstate) {}
BOOL MAX186_8::indicate (REALTIME time, ACTIVEDATA *newstate){ return FALSE; };
VOID MAX186_8::setup (IINSTANCE *iinstance, ISPICECKT *ispiceckt)
{ instance = iinstance; spiceckt = ispiceckt;

	ain0                =       instance->getspicenode        ("AIN0,ain0",    TRUE);
	ain1                =       instance->getspicenode        ("AIN1,ain1",    TRUE);
	ain2                =       instance->getspicenode        ("AIN2,ain2",    TRUE);
	ain3                =       instance->getspicenode        ("AIN3,ain3",    TRUE);
	ain4                =       instance->getspicenode        ("AIN4,ain4",    TRUE);
	ain5                =       instance->getspicenode        ("AIN5,ain5",    TRUE);
	ain6                =       instance->getspicenode        ("AIN6,ain6",    TRUE);
	ain7                =       instance->getspicenode        ("AIN7,ain7",    TRUE);

	ref                 =       instance->getspicenode        ("REF,ref",    TRUE);
    agnd                =       instance->getspicenode        ("AGND,agnd",    TRUE);
    intref              =       instance->getboolval          ("INTREF,intref", FALSE);
}
VOID MAX186_8::accept (REALTIME time, DOUBLE *rhs)
{
    DOUBLE vref         = (ref      != -1) ? rhs[ref]    :    1.0;
    DOUBLE ag           =                               rhs[agnd];
    DOUBLE asample      =                                       0;

    ///////////////////////////////////////
    // attain a sample of  each  channel //
    ///////////////////////////////////////
    DOUBLE avin0 = rhs[ain0];
	DOUBLE avin1 = rhs[ain1];
	DOUBLE avin2 = rhs[ain2];
	DOUBLE avin3 = rhs[ain3];
	DOUBLE avin4 = rhs[ain4];
	DOUBLE avin5 = rhs[ain5];
	DOUBLE avin6 = rhs[ain6];
	DOUBLE avin7 = rhs[ain7];
    /////////////////////////////////
    // 8 channel single-ended mode //
	/////////////////////////////////
	if (SGL_DIF)
	{
	    if (sdisel == 0)
		    asample = avin0 - ag;       // CH0+
	    if (sdisel == 4)
		    asample = avin1 - ag;       // CH1+
	    if (sdisel == 1)
		    asample = avin2 - ag;       // CH2+
	    if (sdisel == 5)
		    asample = avin3 - ag;       // CH3+
	    if (sdisel == 2)
		    asample = avin4 - ag;       // CH4+
	    if (sdisel == 6)
		    asample = avin5 - ag;       // CH5+
	    if (sdisel == 3)
    		asample = avin6 - ag;       // CH6+
	    if (sdisel == 7)
		    asample = avin7 - ag;       // CH7+
	}
    /////////////////////////////////
	//     differential mode       //
	/////////////////////////////////
	if (!SGL_DIF)
	{
	    if (sdisel == 0)
		    asample = avin0 - avin1;    // CH0+ CH1-
	    if (sdisel == 1)
		    asample = avin2 - avin3;    // CH2+ CH3-
	    if (sdisel == 2)
		    asample = avin4 - avin5;    // CH4+ CH5-
	    if (sdisel == 3)
		    asample = avin6 - avin7;    // CH6+ CH7-

	    if (sdisel == 4)
		    asample = avin1 - avin0;    // CH1+ CH0-
	    if (sdisel == 5)
		    asample = avin3 - avin2;    // CH3+ CH2-
	    if (sdisel == 6)
		    asample = avin5 - avin4;    // CH5+ CH4-
	    if (sdisel == 7)
		    asample = avin7 - avin6;    // CH7+ CH6-
	}
	/////////////////////////////////
	//        unipolar mode        //
	/////////////////////////////////
    if (UNI_BIP)
	{
	}
    /////////////////////////////////
	//        bipolar mode         //
	/////////////////////////////////
	if (!UNI_BIP)
	{
	}
}
VOID MAX186_8::dcload (REALTIME time, SPICEMODES mode, DOUBLE *oldrhs, DOUBLE *newrhs)
{

}
VOID MAX186_8::acload (SPICEFREQ omega, DOUBLE *rhs, DOUBLE *irhs) {}
VOID MAX186_8::trunc  (REALTIME time,  REALTIME *newtimestep) {}
VOID MAX186_8::setup (IINSTANCE * iinstance, IDSIMCKT *idsimckt)
{ instance = iinstance; dsimckt = idsimckt;
    ////////////////////////////////////////////////////////////////////////
    SDSSW               =   instance->getboolval    ("SDSSW",            0); // switch debug window off
    ////////////////////////////////////////////////////////////////////////
	//                   :: DEBUG POPUP STRUCTURE ::                      //
	////////////////////////////////////////////////////////////////////////
	if (SDSSW ==TRUE)
	{
	    cps                 =   new CREATEPOPUPSTRUCT;
	    cps->type           =   PWT_STATUS;
	    cps->caption        =   "MAX 191 STATUS WINDOW";
	    cps->flags          =   PWF_HIDEONANIMATE | PWF_VISIBLE;
	    cps->height         =   30;
	    cps->width          =   45;
	    statuspopup         =   (ISTATUSPOPUP *)instance->createpopup(cps);
	}
	////////////////////////////////////////////////////////////////////////

	cs                  =       instance->getdsimpin          ("$CS,$cs",       TRUE);
	dgnd                =       instance->getdsimpin          ("DGND,dgnd",     TRUE);
	dout                =       instance->getdsimpin          ("DOUT,dout",     TRUE);
	din                 =       instance->getdsimpin          ("DIN,din",       TRUE);
	sclk                =       instance->getdsimpin          ("SCLK,sclk",     TRUE);
    shdn                =       instance->getdsimpin          ("$SHDN$,$shdn$", TRUE);
    sstrb               =       instance->getdsimpin          ("SSTRB,sstrb",   TRUE);

}
VOID MAX186_8::simulate (ABSTIME time, DSIMMODES dmode)
{
	if (dmode == DSIMBOOT)
    {
	    if (intref == 1)
		{
		    instance->log("MAX186 model is running ");

		}
	    if (intref == 0)
		{
	        instance->log("MAX188 model is running ");
	    }
	}
	if (dmode == DSIMSETTLE)
	{
	    c_p_c = 0;
	    conv_reg = 0;
	    din->setstate (FLT);
	    dout->setstate (FLT);
	    sstrb->setstate (FLT);
	}
	else
	{
	    EVENTID eventid = 0;

        if (shdn->isinactive())
        {
            dout->setstate(FLT);
            sstrb->setstate (SHI);
            c_p_c = 0;
			conv_reg = 0;
			shut=TRUE;
        }
        else if (shdn->isposedge())
        {
            dout->setstate(FLT);
            sstrb->setstate (SHI);
            c_p_c = 0;
			conv_reg = 0;
			shut=FALSE;
        }
        else
        {
            EVENTID eventid =0;
            shut=FALSE;
            //////////////////////////////////////////////////////////////////
            // select referance input to use  by chip type and shdn state   //
            //////////////////////////////////////////////////////////////////
            if (intref == TRUE)
            {
                if ((shdn->isposedge()) || (shdn->isactive()))  interef = TRUE;
                else if (isfloating(shdn->istate()))            interef = FALSE;
            }
            // as cs goes low for the din setup period  set inital states of dout and sstrb
            else if (cs->isnegedge())
            {
                sstrb->setstate (FSTATE);
                dout->setstate  (FSTATE);
            }
            // is din start bit presant.. enable control word data in
            else if (cs->isinactive() && din->isposedge() && (c_p_c < 1 ))
            {
                eventid |= MAXADC_DATAIN_EN;
            }
            // if datain is active  clock in 7 bits of data msb first to control word
            else if (cs->isinactive() && sclk->isposedge() && din->isposedge() && (c_p_c > 1 ))
            {
                eventid |= MAXADC_DATAIN;
            }
            // by this point we should have  loaded the control  word  ready for a sample to be taken
            else if (cs->isinactive() && (held == TRUE))
            {
                eventid |= MAXADC_CONVERT;
                c_p_c = 0;  // after a convertion reset clock pulse counter to zero
            }
            // after a  convertion using preset by control word method  at this point we  enable the output if  cs is fstate
            else if (cs->isinactive() && sclk->isposedge() && (c_p_c <1  ))
            {
                eventid |= MAXADC_DOUT_EN;
	        }
	        else if (cs->isinactive() && sclk->isnegedge() && (c_p_c >1  ))
	        {
	            eventid |= MAXADC_DATAOUT;
		    }
		    // we need to add an extra  clocked  out databit here  to accomadated 16 and 15 bit clocking modes
		    if (eventid != 0) dsimckt->setcallback(time + (eventid & MAXADC_CONVERT)? (t): 1, this, eventid);
        }
	}
}
VOID MAX186_8::callback (ABSTIME time, EVENTID eventid)
{
    LONG min, max;
	if (eventid & MAXADC_DATAIN_EN)
    {
        c_p_c++;// << ranges from 0 - 1
        // use up the control word  start bit and enable recieve  by adding one to the previous zero'd clock
    }
    else if (eventid & MAXADC_DATAIN)
    {
        // load control word msb first on rising edge of the clock
        // whilst spliting control word into  3bit seldata  2bit pd{powerdown}data   UNI_BIP   SGL_DIF
        c_p_c++; // << ranges from 1 to 7
    }
	else if (eventid & MAXADC_HOLD)
    {
		sample = input;
		held = TRUE;
	}
	else if (eventid & MAXADC_CONVERT)
    {
        min = 0;
        max = (1<<nbits)-1;
        conv_reg = (long) ceil(sample * max);
        if (conv_reg < min) conv_reg = min;
        if (conv_reg > max) conv_reg = max;
		held = FALSE;
	}
	else if (eventid & MAXADC_DOUT_EN)
	{
	    // use up the first dout clock pulse
		dout->setstate(time, tDO+th, tDO+tl, tg, TSTATE);
	    c_p_c++;          // << ranges from 0 - 1
	}
    else if (eventid & MAXADC_DATAOUT)
	{
	    // clock out dout data  12 bits msb first
		if (c_p_c < (nbits + 1))
		dout->setstate(time, tDO+th, tDO+tl, tg, (conv_reg & ((1<<nbits) >> c_p_c))? TSTATE: FSTATE);
		else dout->setstate(time, tDO+th, tDO+tl, tg, FSTATE);
		c_p_c++;          // << ranges from 1 - 7;
	}
}

VOID MAX186_8::VARWINDOW()
{
}
























//6------------------------------------------------------------------------------------------------------------------------------------------------6//
///////////////////////////
///////////////////////////
////// < COMPLETED > //////
///////////////////////////
///////////////////////////
//   : CLASS MAX187_9 :  //
///////////////////////////
///////////////////////////
// : CLASS CONSTRUCTOR : //
///////////////////////////
MAX187_9::MAX187_9 (VOID)
{  instance = NULL; spiceckt = NULL; dsimckt = NULL;
    ain = NULL; ref = NULL;
	shdn = NULL; sclk = NULL; cs = NULL; dout = NULL;
    held = NULL; interef = NULL; intref = NULL;shut = NULL; eoc = NULL;
    conv_reg = 0;
    vref = 0; sample = 0; input = 0; vref = 0; refV = 4096e-3; vain = 0;
    c_p_c = 0; sampled = 0;
    nbits = 12;
    t  = 0; tCONV = dsimtime(55e-7); tACQ = dsimtime(15e-7); tDO = dsimtime(20e-9);
    tCQ = dsimtime(5e-7); tCS = dsimtime(5e-7);
    th = dsimtime(1e-9); tl = dsimtime(1e-9); tg = dsimtime(5e-10); }
MAX187_9::~MAX187_9() {}
INT MAX187_9::isanalog (CHAR *pinname)
{ if (strnicmp(pinname,  "AIN",      3) == 0)
	    return TRUE;
    if (strnicmp(pinname,  "REF",      3) == 0)
        return TRUE;
	else
	    return FALSE; }
INT MAX187_9::isdigital (CHAR *pinname)
{ if (strnicmp(pinname,  "$CS",      3) == 0)
	    return TRUE;
	if (strnicmp(pinname,  "SCLK",     4) == 0)
	    return TRUE;
    if (strnicmp(pinname,  "DOUT",     4) == 0)
        return TRUE;
    if (strnicmp(pinname,  "$SHDN$",   5) == 0)
	    return TRUE;
	else
	    return FALSE; }
VOID MAX187_9::runctrl (RUNMODES mode)
{
    if ((mode == RM_SUSPEND) && (SDSSW == TRUE))
	{
		cheight = statuspopup->getcharheight();
		cwidth  = statuspopup->getcharwidth();
		VARWINDOW();
		statuspopup->repaint();
	}
}
VOID MAX187_9::actuate (REALTIME time, ACTIVESTATE newstate) {}
BOOL MAX187_9::indicate (REALTIME time, ACTIVEDATA *newstate){ return FALSE; };
VOID MAX187_9::setup (IINSTANCE *iinstance, ISPICECKT *ispiceckt)
{ instance =       iinstance; spiceckt = ispiceckt;
	ain             =       instance->getspicenode        ("AIN",     TRUE);
    ref             =       instance->getspicenode        ("REF",     TRUE);
    intref          =       instance->getboolval          ("INTREF", FALSE); }
VOID MAX187_9::accept (REALTIME time, DOUBLE *rhs)
{ if (interef == FALSE)
    { vain        =       rhs[ain];
        vref        =       (ref != -1) ? rhs[ref] : 1.0;
        input       =       (vain / vref); }
    if (interef == TRUE)
    { vref        =       refV;
        vain        =       rhs[ain];
        input       =       (vain / vref); }
    if ((shut == FALSE) && (vref <= 2.5)) instance->error("VREF PIN must be greater than 2.5 volt's rms."); }
VOID MAX187_9::dcload (REALTIME time, SPICEMODES mode, DOUBLE *oldrhs, DOUBLE *newrhs) {}
VOID MAX187_9::acload (SPICEFREQ omega, DOUBLE *rhs, DOUBLE *irhs) {}
VOID MAX187_9::trunc  (REALTIME time,  REALTIME *newtimestep) {}
VOID MAX187_9::setup (IINSTANCE * iinstance, IDSIMCKT *idsimckt)
{ instance = iinstance; dsimckt = idsimckt;
    ////////////////////////////////////////////////////////////////////////
    SDSSW               =   instance->getboolval    ("SDSSW",            0); // switch debug window off
    ////////////////////////////////////////////////////////////////////////
	//                   :: DEBUG POPUP STRUCTURE ::                      //
	////////////////////////////////////////////////////////////////////////
	if (SDSSW ==TRUE)
	{
	    cps                 =   new CREATEPOPUPSTRUCT;
	    cps->type           =   PWT_STATUS;
	    cps->caption        =   "MAX 191 STATUS WINDOW";
	    cps->flags          =   PWF_HIDEONANIMATE | PWF_VISIBLE;
	    cps->height         =   30;
	    cps->width          =   45;
	    statuspopup         =   (ISTATUSPOPUP *)instance->createpopup(cps);
	}
	////////////////////////////////////////////////////////////////////////
	dout            =       instance->getdsimpin          ("DOUT",    TRUE);
	sclk            =       instance->getdsimpin          ("SCLK",    TRUE);
	cs              =       instance->getdsimpin          ("$CS",     TRUE);
	shdn            =       instance->getdsimpin          ("$SHDN$",  TRUE); }
VOID MAX187_9::simulate (ABSTIME time, DSIMMODES dmode)
{ if (dmode == DSIMBOOT)
    { if (intref == 1)
		{ instance->log("MAX187 model is running "); }
	    else if (intref == 0)
		{ instance->log("MAX189 model is running "); }
	}
	if (dmode == DSIMSETTLE)
	{ c_p_c = 0;
	    conv_reg = 0;
	    dout->setstate(FLT); }
	else
	{ EVENTID eventid = 0;
        if (intref == TRUE)
        { if ((shdn->isposedge()) || (shdn->isactive())) interef = TRUE;
            else if (isfloating(shdn->istate())) interef = FALSE; }
        else if (intref == FALSE) interef = FALSE;
        if ((shdn->isnegedge()) || (shdn->isinactive()))
        { dout->setstate(FLT);
            c_p_c = 0;
			conv_reg = 0;
			shut=TRUE; }
        else
        { shut = FALSE;
            if ((cs->isposedge()) && (islow(sclk->istate())))
            { t = time + tCONV;
			    dout->setstate(time+tCQ ,0, FLT);
			    c_p_c = 0; }
		    if ((cs->isnegedge()) && (islow(sclk->istate())))
		    { dout->setstate(time,0,SLO);
			    dsimckt->setbreak(time);
			    eventid |= MAXADC_HOLD; }
		    if (cs->isinactive() && (held == TRUE))     eventid |= MAXADC_CONVERT;
		    if (cs->isinactive() && sclk->isposedge() && (c_p_c < 1 ))    eventid |= MAXADC_DOUT_EN;
	        if (cs->isinactive() && sclk->isnegedge() && (c_p_c > 0 ))    eventid |= MAXADC_DATAOUT;
		    if ((ishigh(cs->istate()) && (islow(sclk->istate()))))
            { dout->setstate(time+tCS ,0, FLT);
			    c_p_c = 0; }
		    if (eventid != 0) dsimckt->setcallback(time + (eventid & MAXADC_CONVERT)? (t): 1, this, eventid); } } }
VOID MAX187_9::callback (ABSTIME time, EVENTID eventid)
{ LONG min, max;
	if (eventid & MAXADC_HOLD)
    { dout->setstate(tCONV ,0, TSTATE);
		sample = input;
		held = TRUE; }
	else if (eventid & MAXADC_CONVERT)
    { min = 0;
        max = (1<<nbits)-1;  conv_reg = (long) ceil(sample * max);
        if (conv_reg < min) conv_reg = min; if (conv_reg > max) conv_reg = max; held = FALSE; }
	if (eventid & MAXADC_DOUT_EN) { dout->setstate(time, tDO+th, tDO+tl, tg, TSTATE); c_p_c++; }
	else if (eventid & MAXADC_DATAOUT)
	{ if (c_p_c < (nbits + 1)) dout->setstate(time, tDO+th, tDO+tl, tg, (conv_reg & ((1<<nbits) >> c_p_c))? TSTATE: FSTATE);
	else dout->setstate(time, tDO+th, tDO+tl, tg, FSTATE); c_p_c++; } }
VOID MAX187_9::VARWINDOW()
{
}


//end-------------------------------------------------------------------------------------------------------------------------------------------end//
