//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////	          Proteus VSM  ELECTRONICS CIRCUITRY SIMULATOR DLL                   /////
///////////////             DALLAS.DLL: DALLAS DPOTS MODELS dynamic link library                //////
//////////////		                   (C)2000-6 SIMEON DAVID WEBBER MCA   		               ///////
/////////////	                 ALL RIGHTS RESERVED BY SIMEON DAVID WEBBER                   ////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////                 Build: 1.04 BETA ALPHA:  last build date 13_04_2006:           ///////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <windows.h>
#include <math.h>
#include <time.h>
#include "vsm.hpp"
#include "vdm.hpp"
#include "DEVKEYS.HPP"



#define STRICT
#define EXPORT __declspec(dllexport)
#define VOID   void
typedef float  FLOAT;
typedef double DOUBLE;
typedef char   CHAR;
typedef short  SHORT;
typedef int    INT;
typedef int    BOOL;

class DS1267I : public IMIXEDMODEL
{
    public:

        DS1267I (VOID);
	    virtual ~DS1267I(VOID);
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

	    IINSTANCE *instance; ISPICECKT *spiceckt; IDSIMCKT *dsimckt;

	    ABSTIME stime; RELTIME tcc,tplh,tdda;

        CREATEPOPUPSTRUCT *cps; ISTATUSPOPUP *statuspopup;

        SPICENODE Vpot1,Vpot2,vref1,vref2,branch1,branch2;

        IDSIMPIN *dq,*clk,*reset,*sout,*cout;

        STATE data;

        BOOL fifo[17],HOA,SDSSW;

        BYTE potval1,potval2;

        INT ssbval,count,y,cwidth, cheight;

        DWORD vpotid;

        DOUBLE *voutpbnode1,*bvoutpnode1,*voutpbnode2,*bvoutpnode2,*bvrefpnode1,*bvrefpnode2;
        DOUBLE  outval1,outval2,outnext1,outnext2;

        LONG in1,out1,in2,out2;
        // PRIVATE FUNCTIONS

        virtual VOID clockinoutdata(ABSTIME time, BOOL clock, BOOL data);
        virtual VOID VARWINDOW();
};


class DS1666I : public IMIXEDMODEL
{
    public:

        DS1666I (VOID);
	    virtual ~DS1666I(VOID);
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

	    IINSTANCE *instance; ISPICECKT *spiceckt; IDSIMCKT *dsimckt;

        ABSTIME stime; RELTIME tdda;

        CREATEPOPUPSTRUCT *cps; ISTATUSPOPUP *statuspopup;

        SPICENODE Vpot1,vref1,branch1;

        IDSIMPIN *INC,*UD,*CS;

        STATE data;

        BOOL HOA,SDSSW;

        BYTE tot;

        DWORD vpotid;

        INT cwidth, cheight,y;

        DOUBLE *voutpbnode1, *bvoutpnode1, *bvrefpnode1;
        DOUBLE outnext1, outval1;

        LONG in1,out1;
        // PRIVATE FUNCTIONS
        virtual VOID VARWINDOW();
};

class DS1804I : public IMIXEDMODEL
{
    public:

        DS1804I (VOID);
	    virtual ~DS1804I(VOID);
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

	    IINSTANCE *instance;ISPICECKT *spiceckt; IDSIMCKT *dsimckt;
        ABSTIME stime; RELTIME tdda;

        CREATEPOPUPSTRUCT *cps; ISTATUSPOPUP *statuspopup;

        HANDLE file;

        SPICENODE Vpot1,vref1,branch1;

        IDSIMPIN *INC,*UD,*CS;

        STATE data;

        BOOL HOA,SDSSW,SAVE,bResult;

        BYTE eeprom[8], savedata[6], vpotid, tot;

        DWORD timeseed, nBytesRead, savedatadword[2];

        CHAR *filename;

        INT cwidth, cheight,y;

        DOUBLE *voutpbnode1, *bvoutpnode1, *bvrefpnode1, outnext1, outval1;

        LONG in1,out1, runtimes, randomeewrites;

        // PRIVATE FUNCTIONS
        virtual VOID VARWINDOW();
};

class DS1867I : public IMIXEDMODEL
{
    public:

        DS1867I (VOID);
	    virtual ~DS1867I(VOID);
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

	    IINSTANCE *instance; ISPICECKT *spiceckt; IDSIMCKT *dsimckt;
        ABSTIME stime; RELTIME tcc,tplh,tdda;

        CREATEPOPUPSTRUCT *cps; ISTATUSPOPUP *statuspopup;

	    HANDLE file;

        SPICENODE Vpot1,Vpot2,vref1,vref2,branch1,branch2,vpos,vneg;

        IDSIMPIN *dq,*clk,*reset,*sout,*cout;

        STATE data;

        BOOL fifo[17],HOA,SDSSW, bResult,SAVED,LOADED;

        BYTE potval1, potval2, savedata[5];

        INT ssbval, count, y, cwidth, cheight;

        CHAR *filename, eeprom[32];


        DWORD timeseed, savedatadword[2], vpotid, nBytesRead;

        DOUBLE *voutpbnode1, *bvoutpnode1 ,*voutpbnode2, *bvoutpnode2, *bvrefpnode1, *bvrefpnode2;
        DOUBLE outnext1, outval1, outnext2, outval2, value;

        LONG in1, out1, in2, out2, runtimes, randomeewrites;

        // PRIVATE FUNCTIONS
        virtual VOID clockinoutdata(ABSTIME time, BOOL clock, BOOL data);
        virtual VOID VARWINDOW();
};

class DS1868I : public IMIXEDMODEL
{
    public:

        DS1868I (VOID);
	    virtual ~DS1868I(VOID);
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

	    IINSTANCE *instance; ISPICECKT *spiceckt; IDSIMCKT *dsimckt;
        ABSTIME stime; RELTIME tcc,tplh,tdda;
        CREATEPOPUPSTRUCT *cps; ISTATUSPOPUP *statuspopup;

        SPICENODE Vpot1,Vpot2,vref1,vref2,branch1,branch2;

        IDSIMPIN *dq,*clk,*reset,*sout,*cout;

        STATE data;

        BOOL fifo[17],HOA,SDSSW;

        BYTE potval1,potval2;

        INT ssbval,count,y,cwidth, cheight;

        DWORD vpotid;

        DOUBLE *voutpbnode1,*bvoutpnode1,*voutpbnode2,*bvoutpnode2,*bvrefpnode1,*bvrefpnode2;
        DOUBLE  outval1,outval2,outnext1,outnext2;

        LONG in1,out1,in2,out2;

        // PRIVATE FUNCTIONS
        virtual VOID clockinoutdata(ABSTIME time, BOOL clock, BOOL data);
        virtual VOID VARWINDOW();
};
