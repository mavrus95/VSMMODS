//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////// 	          Proteus VSM  ELECTRONICS CIRCUITRY SIMULATOR DLL                    ////
////////////////                MIXED MODEL Construction started 06-05-2006                      /////
///////////////      DP_POT.DLL: DIGITAL PROGRAMMABLE POTENTIOMETERS dynamic link library       //////
//////////////		                  (C)2005-6 SIMEON DAVID WEBBER MCA   		               ///////
/////////////	                 ALL RIGHTS RESERVED BY SIMEON DAVID WEBBER                   ////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////               Build: 1.052 BETA: LAST BUILD:21_08_2006 10.00 HRS-BST           ///////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <math.h>
#include <stdio.h>
#include "vsm.hpp"
#include "DEVKEYS.H"
//#include "DEVKEYS1.H"



#define EXPORT __declspec(dllexport)
#define VOID   void
typedef float  FLOAT;
typedef double DOUBLE;
typedef char   CHAR;
typedef short  SHORT;
typedef int    INT;
typedef int    BOOL;


// ordinal
#define DP_POT_UPDATE  1
#define DP_POT_RESET   2

class DP_POT : public IMIXEDMODEL
{
    public:

        DP_POT (VOID);
	    virtual ~DP_POT(VOID);
	    virtual INT isanalog (CHAR *pinname);
	    virtual INT isdigital (CHAR *pinname);
	    virtual VOID runctrl (RUNMODES mode);
	    virtual VOID actuate (REALTIME time, ACTIVESTATE newstate);
	    virtual BOOL indicate (REALTIME time, ACTIVEDATA *newstate);
	    virtual VOID setup (IINSTANCE *, ISPICECKT *spice);
	    virtual VOID dcload (REALTIME time, SPICEMODES mode, DOUBLE *oldrhs, DOUBLE *newrhs);
	    virtual VOID acload (SPICEFREQ omega, DOUBLE *rhs, DOUBLE *irhs);
	    virtual VOID trunc  (REALTIME time,  REALTIME *newtimestep);
	    virtual VOID accept (REALTIME time, DOUBLE *rhs);
	    virtual VOID setup (IINSTANCE *, IDSIMCKT *dsim);
	    virtual VOID simulate (ABSTIME time, DSIMMODES mode);
	    virtual VOID callback (ABSTIME time, EVENTID eventid);

    private:

        ////////////////////////
        /// : MODEL HANDLES : //
        ////////////////////////////////////////////////////////////
        IINSTANCE *instance; ISPICECKT *spiceckt; IDSIMCKT *dsimckt;
        ////////////////////////////////////////////////////////////

        ///////////////////////
	    /// : TIME VECTERS : //
	    ////////////////////////////
	    RELTIME tcc,tdda,bdel,ddel,sdel,abdel,addel,asdel;
	    ABSTIME stime;
	    //////////////
        ///////////////////////
        /// : STATUS POPUP : //
        ///////////////////////
        CREATEPOPUPSTRUCT *cpd;
        ISTATUSPOPUP *statuspopup;
        //////////////////////////
        HANDLE file;
        /////////////////////
        /// : SPICE PINS : //
        //////////////////////////////
        SPICENODE W1[16],W2[16], L[16], H[16];
        ////////////////
        /// DSIM PINS //
        //////////////////////////////////
        IDSIMPIN *clk, *rst, *hold, *load, *SHDN, *EEPS, *EEPR;
        /////////////////////////////////
        IBUSPIN *B_BUS, *D_BUS, *SEL_BUS;
        /////////////////////////////////

        ////////////////
        /// VARIABLES //
        ///////////////////////////////////////////////////////
        BOOL CRM, HOA, SDSSW, UPDATESTATE, ebus, updatestatus,SHDNPOTS,bResult, SAVE,ESEE,LOAD;
        ///////////////////////////////////////////////////////

        ///////////////////
        CHAR *filename;
        CHAR STATTITLE[20];
        ///////////////////////////

        /////////////////////
        INT x, y, width, height;
        INT Xpots, Xpotssp, BTE;
        ////////////////////////
        BYTE tot;
        BYTE G;
        ////////////////////////
        DWORD savedatadword[16],eeprom[16];
        DWORD in[16], out[16],start[16],savep[16];
        DWORD fifo[16];
        DWORD vpotid, w, INITVAL[16],nBytesRead,GLOBALINIT;
        ////////////////////////////////////////////////////////////
        DOUBLE *nodeLW[16], *nodeLL[16], *nodeLLW[16], *nodeLWL[16];
        DOUBLE *nodeHW[16], *nodeHH[16], *nodeHHW[16], *nodeHWH[16];

        DOUBLE POTVAL[16], out1[16], out2[16];
        //////////////////////////////////////

		////////////////////////////
		/// : PRIVATE FUNCTIONS : //
		//////////////////////////////////////////////////////
        virtual VOID clockindata(ABSTIME time, BOOL clock);
        virtual VOID STATUSPOPUP();
};