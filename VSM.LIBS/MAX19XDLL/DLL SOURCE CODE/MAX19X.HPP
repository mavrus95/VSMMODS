////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////            MAXIM 19X SERIES A-D CONVERTERS            /////////
///////////////////             Construction started 21-11-2004           //////////
//////////////////		     (C)2000-2004 SIMEON DAVID WEBBER MCA        ///////////
/////////////////  	      ALL RIGHTS RESERVED BY SIMEON DAVID WEBBER    ////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
//////////////     Build: 010   last build data 09_12_2004           ///////////////
////////////////////////////////////////////////////////////////////////////////////
//////////// (c)2000-2004 SIMEON WEBBER MCA  ///////////////////////////////////////
///////////       GLASGOW SCOTLAND UK....   ////////////////////////////////////////
//////////      in progress >> ALPHA V1.0  /////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// STAGE 1 COMPLETE:LISA MODELS AND ISIS PARTS WITH SHELL DLL ALL PINS  -- FINISHED/
// STAGE 2 ADD TEST JIGS FOR MODE CONFORMANCE TEST'S                    -- STARTED /
// STAGE 3 ADD SPICE MODEL FRAMEWORK AND COMPLETE TO READY TO USE       -- STARTED /
// STAGE 4 ADD FUNCTIONALITY TO THE DSIMCKT SECTION                     -- STARTED /
// STAGE 5 DEBUG                                                        --         /
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "vsm.hpp"
#include "DEVKEYS.HPP"
////////////
#pragma once
////////////////////////////////////
#define EXPORT __declspec(dllexport)
#define VOID   void
/////////////////////
typedef float  FLOAT;
typedef double DOUBLE;
typedef char   CHAR;
typedef short  SHORT;
typedef int    INT;
typedef int    BOOL;
////////////////////
///////////////////////////////
// SERIAL MODE ORDINAL       //
///////////////////////////////
#define MAX_SERHOLD         1
#define MAX_SERccCONVERT    2
#define MAX_SERcdCONVERT    4
///////////////////////////////
// PARALLEL MODE ORDINAL     //
///////////////////////////////
#define MAX_PARHOLD         1
#define MAX_PARCONVERT      2
#define MAX_PAR8MODE        4
#define MAX_PAR4MODE        8
///////////////////////////////
//                           //
///////////////////////////////
class MAX190_1 : public IMIXEDMODEL
{
public:
    MAX190_1 (VOID);
	virtual ~MAX190_1(VOID);
	// pin ident and typing
	virtual INT isanalog (CHAR *pinname);
	virtual INT isdigital (CHAR *pinname);
	// common functions
	virtual VOID runctrl (RUNMODES mode);
	virtual VOID actuate (REALTIME time, ACTIVESTATE newstate);
	virtual BOOL indicate (REALTIME time, ACTIVEDATA *newstate);
	// spice circuit
	virtual VOID setup (IINSTANCE *instance, ISPICECKT *spice);
	virtual VOID dcload (REALTIME time, SPICEMODES mode, DOUBLE *oldrhs, DOUBLE *newrhs);
	virtual VOID acload (SPICEFREQ omega, DOUBLE *rhs, DOUBLE *irhs);
	virtual VOID trunc  (REALTIME time,  REALTIME *newtimestep);
	virtual VOID accept (REALTIME time, DOUBLE *rhs);
	// dsim events circuit
	virtual VOID setup (IINSTANCE *instance, IDSIMCKT *dsim);
	virtual VOID simulate (ABSTIME time, DSIMMODES mode);
	virtual VOID callback (ABSTIME time, EVENTID eventid);
    // debug data feedback window
    virtual VOID VARWINDOW();
    /////////////////////////

//////////
protected:
	//////////////////////////////////////////////////////////////////////////////
	IINSTANCE *instance; ISPICECKT *spiceckt; IDSIMCKT *dsimckt; EVENTID *eventid;
    ///////////////////////////////////////// :COMMON: ///////////////////////////
    BOOL SDSSW;
    ////////////////////////
    CREATEPOPUPSTRUCT * cps;
	ISTATUSPOPUP      * statuspopup;
	INT cwidth, cheight;
    ///////////////////////////////////////// :SPICECKT://////////////////////////
    SPICENODE  ainP, ainN, ref, agnd;
    //////////////////////////////////////////////////
    BOOL held, interef, intref,shut, SGL_DIF, UNI_BIP;
	///////////////////////
	DOUBLE REFBUF, VREFBUF;
    DOUBLE input, hold;
    ///////////////////////////////////////// :DSIMCKT:///////////////////////////
    IBUSPIN *SER_BUS;  // 1x 3bit port D5-D7
    IBUSPIN *DP_MSW, *DP_LSW; // 2x4bitwords  D0-3 & D4-D8
    //////////////////////
    IDSIMPIN *pd, *bip, *busy;
    IDSIMPIN *rd, *cs, *hben, *par, *clk_sclk;
    IDSIMPIN *dgnd;
    ///////////////
    DWORD controlw;
    //////////////
	LONG conv_reg;
    LONG numbits;
    ///////////////////
    INT c_p_c, sampled;
    INT mode_reg, sdisel;
    INT nbits,donecycles;
    //////////////////////////////////////////////
    RELTIME t1,  t2,  t3,  t4,  t5,  t6,  t7,  t8;
    RELTIME t9,  t10, t11, t12, t13, t14, t15, t16;
    RELTIME t17, t18, t19, t20, t21, t22, t23;
    RELTIME tCONV,tQ;
};
