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
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <iostream.h>
#include "vsm.hpp"
#include "DEVKEYS.HPP"

#pragma once

#define EXPORT __declspec(dllexport)
#define VOID   void
typedef float  FLOAT;
typedef double DOUBLE;
typedef char   CHAR;
typedef short  SHORT;
typedef int    INT;
typedef int    BOOL;

////////////////////////////////////////////////////
//  : Flag values for class callback functions :  //
////////////////////////////////////////////////////
#define MAXADC_DATAIN_EN 	    1
#define MAXADC_DATAIN 	        2
#define MAXADC_HOLD		        4
#define MAXADC_CONVERT		    8
#define MAXADC_DOUT_EN 	        16
#define MAXADC_DATAOUT		    32

////////////////////////////////////////////////////
//  : Flag values for other timer functions :     //
////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//1------------------------------------------------------------------------------------------------------------------------------------------------1//
////                                                                                                                                              ////
///////////////////////////////////////////
//  : MODEL CLASS MAX180 DEFINITION :    //
///////////////////////////////////////////
class MAX180 : public IMIXEDMODEL
{
public:
    MAX180 (VOID);
	virtual ~MAX180(VOID);
	virtual INT isanalog (CHAR *pinname);
	virtual INT isdigital (CHAR *pinname);
	virtual VOID runctrl (RUNMODES mode);
	virtual VOID actuate (REALTIME time, ACTIVESTATE newstate);
	virtual BOOL indicate (REALTIME time, ACTIVEDATA *newstate);
	virtual VOID setup (IINSTANCE *instance, ISPICECKT *spiceckt);
	virtual VOID dcload (REALTIME time, SPICEMODES mode, DOUBLE *oldrhs, DOUBLE *newrhs);
	virtual VOID acload (SPICEFREQ omega, DOUBLE *rhs, DOUBLE *irhs);
	virtual VOID trunc  (REALTIME time,  REALTIME *newtimestep);
	virtual VOID accept (REALTIME time, DOUBLE *rhs);
	virtual VOID setup (IINSTANCE *instance, IDSIMCKT *dsimckt);
	virtual VOID simulate (ABSTIME time, DSIMMODES mode);
	virtual VOID callback (ABSTIME time, EVENTID eventid);
    virtual VOID VARWINDOW();
protected:
	IINSTANCE *instance;ISPICECKT *spiceckt; IDSIMCKT *dsimckt; EVENTID *eventid;
    BOOL SDSSW;
	////////////////////////
    CREATEPOPUPSTRUCT * cps;
	ISTATUSPOPUP      * statuspopup;
	INT cwidth, cheight;
	////////////////////


	SPICENODE ain0, ain1, ain2, ain3, ain4, ain5, ain6, ain7, ref, agnd;

    IBUSPIN *D_BUS, *A_BUS;
    IDSIMPIN  *cs, *clkin, *busy, *mode, *hben, *diff, *bip, *rd, *wr;
    IDSIMPIN  *dgnd;

    DWORD controlw;

    BOOL held, interef, intref,shut, SGL_DIF, UNI_BIP;

    LONG conv_reg;

	DOUBLE avin0, avin1, avin2, avin3, avin4, avin5, avin6, avin7;
    DOUBLE input, sample, vref, refV, vain;

    INT c_p_c, sampled;
    INT mode_reg, sdisel;
    INT nbits;

    RELTIME tCONV, tDS, tDV, tDO;
    RELTIME th ,tl, tg;
    RELTIME t;
};
//2------------------------------------------------------------------------------------------------------------------------------------------------2//
///////////////////////////////////////////
//  : MODEL CLASS MAX181 DEFINITION :    //
///////////////////////////////////////////
class MAX181 : public IMIXEDMODEL
{

public:

    MAX181 (VOID);
	virtual ~MAX181(VOID);
	virtual INT isanalog (CHAR *pinname);
	virtual INT isdigital (CHAR *pinname);
	virtual VOID runctrl (RUNMODES mode);
	virtual VOID actuate (REALTIME time, ACTIVESTATE newstate);
	virtual BOOL indicate (REALTIME time, ACTIVEDATA *newstate);
	virtual VOID setup (IINSTANCE *instance, ISPICECKT *spiceckt);
	virtual VOID dcload (REALTIME time, SPICEMODES mode, DOUBLE *oldrhs, DOUBLE *newrhs);
	virtual VOID acload (SPICEFREQ omega, DOUBLE *rhs, DOUBLE *irhs);
	virtual VOID trunc  (REALTIME time,  REALTIME *newtimestep);
	virtual VOID accept (REALTIME time, DOUBLE *rhs);
	virtual VOID setup (IINSTANCE *instance, IDSIMCKT *dsimckt);
	virtual VOID simulate (ABSTIME time, DSIMMODES mode);
	virtual VOID callback (ABSTIME time, EVENTID eventid);
    virtual VOID VARWINDOW();
protected:
	IINSTANCE *instance;ISPICECKT *spiceckt; IDSIMCKT *dsimckt; EVENTID *eventid;
	BOOL SDSSW;
	////////////////////////
    CREATEPOPUPSTRUCT * cps;
	ISTATUSPOPUP      * statuspopup;
	INT cwidth, cheight;
	////////////////////
	SPICENODE ain0, ain1, ain2, ain3, ain4, ain5;
	SPICENODE muxout, adcin , ref, agnd;

    IBUSPIN *D_BUS, *A_BUS;
    IDSIMPIN  *cs, *clkin, *busy, *mode, *hben, *diff, *bip, *rd, *wr, *dgnd;

    DWORD controlw;

    BOOL held, interef, intref,shut, SGL_DIF, UNI_BIP;

    LONG conv_reg;


	DOUBLE avin0, avin1, avin2, avin3, avin4, avin5;
    DOUBLE input, sample, vref, refV, vain;

    INT c_p_c, sampled;
    INT mode_reg, sdisel;
    INT nbits;

    RELTIME tCONV, tDS, tDV, tDO;
    RELTIME th ,tl, tg;
    RELTIME t;
};

//3------------------------------------------------------------------------------------------------------------------------------------------------3//

/////////////////////////////////////////
//  : MODEL CLASS MAX182 DEFINITION :  //
/////////////////////////////////////////
class MAX182 : public IMIXEDMODEL
{

public:

    MAX182 (VOID);
	virtual ~MAX182(VOID);
	virtual INT isanalog (CHAR *pinname);
	virtual INT isdigital (CHAR *pinname);
	virtual VOID runctrl (RUNMODES mode);
	virtual VOID actuate (REALTIME time, ACTIVESTATE newstate);
	virtual BOOL indicate (REALTIME time, ACTIVEDATA *newstate);
	virtual VOID setup (IINSTANCE *instance, ISPICECKT *spiceckt);
	virtual VOID dcload (REALTIME time, SPICEMODES mode, DOUBLE *oldrhs, DOUBLE *newrhs);
	virtual VOID acload (SPICEFREQ omega, DOUBLE *rhs, DOUBLE *irhs);
	virtual VOID trunc  (REALTIME time,  REALTIME *newtimestep);
	virtual VOID accept (REALTIME time, DOUBLE *rhs);
	virtual VOID setup (IINSTANCE *instance, IDSIMCKT *dsimckt);
	virtual VOID simulate (ABSTIME time, DSIMMODES mode);
	virtual VOID callback (ABSTIME time, EVENTID eventid);
    virtual VOID VARWINDOW();
protected:
    IINSTANCE *instance;ISPICECKT *spiceckt; IDSIMCKT *dsimckt; EVENTID *eventid;
    BOOL SDSSW;
	////////////////////////
    CREATEPOPUPSTRUCT * cps;
	ISTATUSPOPUP      * statuspopup;
	INT cwidth, cheight;
	////////////////////

	SPICENODE ain0, ain1, ain2, ain3;
	SPICENODE maxout, adcin, ref, agnd;

	IBUSPIN *DB_BUS, *A_BUS;
	IDSIMPIN  *cs, *clk, *busy, *bysl, *rd, *write, *dgnd;

    DWORD controlw;

    BOOL held, interef, intref,shut;

    LONG conv_reg;

	DOUBLE avin0, avin1, avin2, avin3;
    DOUBLE input, sample, vref, refV;

    INT c_p_c, sampled;
    INT mode_reg, sdisel;
    INT nbits;

    RELTIME tCONV, tDS, tDV, tDO;
    RELTIME th ,tl, tg;
    RELTIME t;
};
//4------------------------------------------------------------------------------------------------------------------------------------------------4//
//////////////////////////////////////////////
//  : MODEL CLASS MAX183_4_5 DEFINITION :   //
//////////////////////////////////////////////
class MAX183_4_5 : public IMIXEDMODEL
{

public:

	MAX183_4_5 (VOID);
	virtual ~MAX183_4_5(VOID);
	virtual INT isanalog (CHAR *pinname);
	virtual INT isdigital (CHAR *pinname);
    virtual VOID runctrl  (RUNMODES mode);
    virtual VOID actuate  (REALTIME time, ACTIVESTATE newstate);
    virtual BOOL indicate (REALTIME time, ACTIVEDATA *newstate);
    virtual VOID setup (IINSTANCE *instance, ISPICECKT *spiceckt);
	virtual VOID dcload (REALTIME time, SPICEMODES mode, DOUBLE *oldrhs, DOUBLE *newrhs);
	virtual VOID acload (SPICEFREQ omega, DOUBLE *rhs, DOUBLE *irhs);
	virtual VOID trunc  (REALTIME time,  REALTIME *newtimestep);
	virtual VOID accept (REALTIME time, DOUBLE *rhs);
    virtual VOID setup (IINSTANCE *instance, IDSIMCKT *dsimckt);
    virtual VOID simulate (ABSTIME time, DSIMMODES mode);
    virtual VOID callback (ABSTIME time, EVENTID eventid);
    virtual VOID VARWINDOW();
protected:
    IINSTANCE *instance;ISPICECKT *spiceckt; IDSIMCKT *dsimckt; EVENTID *eventid;
    BOOL SDSSW;
	////////////////////////
    CREATEPOPUPSTRUCT * cps;
	ISTATUSPOPUP      * statuspopup;
	INT cwidth, cheight;
	////////////////////
	SPICENODE ain0, ain1;
	SPICENODE ref, agnd;

	IDSIMPIN  *cs, *clkin, *clkout, *rd, *busy, *dgnd;
    IBUSPIN *D_BUS;

    DWORD controlw;

    BOOL held, interef, intref, shut, FIXEDFC;

    LONG conv_reg;

	DOUBLE avin0, avin1;
    DOUBLE input, sample, vref, refV, vain , CLOCK , convt ;

    INT c_p_c, sampled;
    INT mode_reg, sdisel;
    INT nbits, i;

    RELTIME tCONV, t2, t9;
    RELTIME th, tl, tg;
    RELTIME t;

};
//5------------------------------------------------------------------------------------------------------------------------------------------------5//
///////////////////////////////////////////
//  : MODEL CLASS MAX186_8 DEFINITION :  //
///////////////////////////////////////////
class MAX186_8 : public IMIXEDMODEL
{
public:

    MAX186_8 (VOID);
	virtual ~MAX186_8(VOID);
	virtual INT isanalog (CHAR *pinname);
	virtual INT isdigital (CHAR *pinname);
	virtual VOID runctrl (RUNMODES mode);
	virtual VOID actuate (REALTIME time, ACTIVESTATE newstate);
	virtual BOOL indicate (REALTIME time, ACTIVEDATA *newstate);
	virtual VOID setup (IINSTANCE *instance, ISPICECKT *spiceckt);
	virtual VOID dcload (REALTIME time, SPICEMODES mode, DOUBLE *oldrhs, DOUBLE *newrhs);
	virtual VOID acload (SPICEFREQ omega, DOUBLE *rhs, DOUBLE *irhs);
	virtual VOID trunc  (REALTIME time,  REALTIME *newtimestep);
	virtual VOID accept (REALTIME time, DOUBLE *rhs);
	virtual VOID setup (IINSTANCE *instance, IDSIMCKT *dsimckt);
	virtual VOID simulate (ABSTIME time, DSIMMODES mode);
	virtual VOID callback (ABSTIME time, EVENTID eventid);
    virtual VOID VARWINDOW();
protected:
    IINSTANCE *instance;ISPICECKT *spiceckt; IDSIMCKT *dsimckt; EVENTID *eventid;
    BOOL SDSSW;
	////////////////////////
    CREATEPOPUPSTRUCT * cps;
	ISTATUSPOPUP      * statuspopup;
	INT cwidth, cheight;
	////////////////////
	SPICENODE ain0, ain1, ain2, ain3, ain4, ain5, ain6, ain7, ref, agnd;
    SPICENODE branch1, branch2;

    IDSIMPIN *sclk, *cs, *din, *sstrb, *dout, *shdn, *dgnd;

    DWORD controlw;
    BOOL held, interef, intref,shut, SGL_DIF, UNI_BIP;
    LONG conv_reg;

	DOUBLE avin0, avin1, avin2, avin3, avin4, avin5, avin6, avin7, vc;
    DOUBLE *node11, *node12, *node21, *node22;
    DOUBLE input, sample, vref, refV, vain;

    INT c_p_c, sampled;
    INT mode_reg, sdisel;
    INT nbits;

    RELTIME tCONV, tDS, tDV, tDO;
    RELTIME th ,tl, tg;
    RELTIME t;
};
//6------------------------------------------------------------------------------------------------------------------------------------------------6//
/////////////////////////////////////////
/////////////< COMPLETED >///////////////
/////////////////////////////////////////
// : MODEL CLASS MAX187_9 DEFINITION : //
/////////////////////////////////////////
class MAX187_9 : public IMIXEDMODEL
{
public:
	MAX187_9 (VOID);
	virtual ~MAX187_9(VOID);
	virtual INT isanalog (CHAR *pinname);
	virtual INT isdigital (CHAR *pinname);
    virtual VOID runctrl  (RUNMODES mode);
    virtual VOID actuate  (REALTIME time, ACTIVESTATE newstate);
    virtual BOOL indicate (REALTIME time, ACTIVEDATA *newstate);
	virtual VOID setup (IINSTANCE *instance, ISPICECKT *spiceckt);
	virtual VOID dcload (REALTIME time, SPICEMODES mode, DOUBLE *oldrhs, DOUBLE *newrhs);
	virtual VOID acload (SPICEFREQ omega, DOUBLE *rhs, DOUBLE *irhs);
	virtual VOID trunc  (REALTIME time,  REALTIME *newtimestep);
	virtual VOID accept (REALTIME time, DOUBLE *rhs);
    virtual VOID setup (IINSTANCE *instance, IDSIMCKT *dsimckt);
    virtual VOID simulate (ABSTIME time, DSIMMODES mode);
    virtual VOID callback (ABSTIME time, EVENTID eventid);
    virtual VOID VARWINDOW();
protected:
	//////////////////////////////////////////////////////////////////////////////////////
	IINSTANCE *instance;ISPICECKT *spiceckt; IDSIMCKT *dsimckt; EVENTID *eventid;
	///////////
	BOOL SDSSW;
	////////////////////////
    CREATEPOPUPSTRUCT * cps;
	ISTATUSPOPUP      * statuspopup;
	INT cwidth, cheight;
	////////////////////
	SPICENODE ain, ref;
    ////////////////////////////////////
    IDSIMPIN *shdn, *sclk, *cs, *dout;
    //////////////////////////////////////
    BOOL held, interef, intref, shut, eoc;
    //////////////
    LONG conv_reg;
    ///////////////////////////////////////
    DOUBLE input, sample, vref, refV, vain;
    //////////////////////////////
    INT c_p_c, sampled; INT nbits;
    ///////////////////////////////////
    RELTIME tCONV, tACQ, tDO, tCQ, tCS;
    RELTIME th ,tl, tg;
    RELTIME t;
    //////////
    //////////
};
//end------------------------------------------------------------------------------------------------------------------------------------------------end//
