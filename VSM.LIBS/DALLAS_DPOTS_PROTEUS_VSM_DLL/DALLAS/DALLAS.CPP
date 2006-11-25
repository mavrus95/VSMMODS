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


#include "DALLAS.HPP"


extern "C"  EXPORT IMIXEDMODEL * createmixedmodel (CHAR *device, ILICENCESERVER *ils)
{
    ///////////////////////////
	IMIXEDMODEL * model = NULL;
    ///////////////////////////////////////////////////////////////
	if (strnicmp(device, "DS1267I", 7) == 0) model = new DS1267I();

	if (strnicmp(device, "DS1666I", 7) == 0) model = new DS1666I();


	// obsolite if (strnicmp(device, "DS1668I", 7) == 0) model = new DS1668I();
	//if (strnicmp(device, "DS1669I", 7) == 0) model = new DS1669I();

	// DS18XX series digital pot chips
	//if (strnicmp(device, "DS1801I", 7) == 0) model = new DS1801I();
	//if (strnicmp(device, "DS1802I", 7) == 0) model = new DS1802I();
	//if (strnicmp(device, "DS1803I", 7) == 0) model = new DS1803I();

	if (strnicmp(device, "DS1804I", 7) == 0) model = new DS1804I();

	//if (strnicmp(device, "DS1805I", 7) == 0) model = new DS1805I();
	//if (strnicmp(device, "DS1806I", 7) == 0) model = new DS1806I();
	//if (strnicmp(device, "DS1807I", 7) == 0) model = new DS1807I();
	//if (strnicmp(device, "DS1808I", 7) == 0) model = new DS1808I();
	//if (strnicmp(device, "DS1809I", 7) == 0) model = new DS1809I();
	//if (strnicmp(device, "DS1810I", 7) == 0) model = new DS1810I();


    ///////////////////////////////////////////////////////////////
	if (strnicmp(device, "DS1867I", 7) == 0) model = new DS1867I();
	if (strnicmp(device, "DS1868I", 7) == 0) model = new DS1868I();
	///////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (model != NULL) { ils->authorize(PRO_KEY) || ils->authorize(LITE_KEY); } return (IMIXEDMODEL *) model;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
}
extern "C" EXPORT VOID deletemixedmodel (IMIXEDMODEL * model) { delete(IMIXEDMODEL *) model; }

///////////////////////////
// : CLASS CONSTRUCTOR : //
///////////////////////////
DS1267I::DS1267I (VOID)
{
    //DIRECTOR'S NULLS
    instance = NULL; spiceckt = NULL; dsimckt = NULL;
    // TIMING CONSTANTS
    tdda = dsimtime(1e-9); tcc = dsimtime(50e-9); tplh = dsimtime(25e-9);
    //NODE'S
    Vpot1=Vpot2=vref1=vref2=branch1=branch2=NULL;
    //LONGS {SPICE}
     outval1=outval2=0;
    //LONGS {DSIM/SPICE/MIXEDMODE}
    in1=out1=in2=out2=0;
    //BOOL
    SDSSW =FALSE; HOA = FALSE;
    //INTS
    count=y=0; cwidth=cheight=0;
    //BYTE'S
    potval1=potval2=0x00;
    //DWORDS
    vpotid=0x0000;
}
DS1267I::~DS1267I() {}
INT DS1267I::isanalog (CHAR *pinname)
{
         if (strnicmp(pinname, "VPOT1", 5) == 0) return TRUE;
	else if (strnicmp(pinname, "VPOT2", 5) == 0) return TRUE;
	else if (strnicmp(pinname, "VREF",  4) == 0) return TRUE;
	else return FALSE;
}
INT DS1267I::isdigital (CHAR *pinname)
{
         if (strnicmp(pinname, "DQ",    2) == 0) return TRUE;
	else if (strnicmp(pinname, "CLK",   3) == 0) return TRUE;
	else if (strnicmp(pinname, "$RST$", 5) == 0) return TRUE;
	else if (strnicmp(pinname, "COUT",  4) == 0) return TRUE;
	else if (strnicmp(pinname, "SOUT",  4) == 0) return TRUE;
    else return FALSE;
}
VOID DS1267I::runctrl (RUNMODES mode)
{
    if ((mode == RM_ANIMATE)|(RM_STEPTIME)|(mode == RM_SUSPEND))
    { if(SDSSW) { cheight = statuspopup->getcharheight(); cwidth  = statuspopup->getcharwidth(); VARWINDOW(); } }
}
VOID DS1267I::actuate (REALTIME stime, ACTIVESTATE newstate) {}
BOOL DS1267I::indicate (REALTIME stime, ACTIVEDATA *newstate){ return FALSE; };
VOID DS1267I::setup (IINSTANCE *iinstance, ISPICECKT *ispiceckt)
{
    instance = iinstance; spiceckt = ispiceckt;
    SDSSW    = instance->getboolval("SDSSW", 0);
	HOA      = instance->getboolval("HOA",   0);
	if (SDSSW ==TRUE)
	{
	    cps                  =   new CREATEPOPUPSTRUCT;
	    cps->type            =   PWT_STATUS;
	    cps->caption         =   "DS1267 STATUS..";
	    if (HOA) cps->flags  =   PWF_VISIBLE | PWF_AUTOREFRESH | PWF_HIDEONANIMATE;
	    if (!HOA) cps->flags =   PWF_VISIBLE | PWF_AUTOREFRESH;
	    cps->height          =   3;
	    cps->width           =   18;
	    statuspopup          =   (ISTATUSPOPUP *)instance->createpopup(cps);
	}
    Vpot1  = instance->getspicenode("VPOT1", TRUE);
    Vpot2  = instance->getspicenode("VPOT2", TRUE);
    vref1  = instance->getspicenode("VREF",  TRUE);
    vref2  = instance->getspicenode("VREF",  TRUE);
    branch1 = spiceckt->newcurnode(instance->id(), "branch1");
    voutpbnode1 = spiceckt->allocsmp(Vpot1, branch1);
    bvoutpnode1 = spiceckt->allocsmp(branch1, Vpot1);
    bvrefpnode1 = spiceckt->allocsmp(branch1, vref1);
    branch2 = spiceckt->newcurnode(instance->id(), "branch2");
    voutpbnode2 = spiceckt->allocsmp(Vpot2, branch2);
    bvoutpnode2 = spiceckt->allocsmp(branch2, Vpot2);
    bvrefpnode2 = spiceckt->allocsmp(branch2, vref2);
}
VOID DS1267I::dcload (REALTIME stime, SPICEMODES mode, DOUBLE *oldrhs, DOUBLE *newrhs)
{
    // Load the values:
	*voutpbnode1 += 1.0; *bvoutpnode1 += 1.0; *bvrefpnode1 -= outnext1;
	// Load the values:
	*voutpbnode2 += 1.0; *bvoutpnode2 += 1.0; *bvrefpnode2 -= outnext2;
}
VOID DS1267I::acload (SPICEFREQ omega, DOUBLE *rhs, DOUBLE *irhs) {}
VOID DS1267I::trunc  (REALTIME stime,  REALTIME *newtimestep) {}
VOID DS1267I::accept (REALTIME stime, DOUBLE *rhs )
{
    if ( in1 != out1 ) outnext1 = DOUBLE(in1) / ( (1<<8) - 1 );
    if ( in2 != out2 ) outnext2 = DOUBLE(in2) / ( (1<<8) - 1 );
	out1 = in1; out2 = in2;
}
VOID DS1267I::setup (IINSTANCE *iinstance, IDSIMCKT *idsimckt)
{
    instance = iinstance; dsimckt = idsimckt;
	dq    = instance->getdsimpin("DQ,dq",          TRUE);
	clk   = instance->getdsimpin("CLK,clk",        TRUE);
	reset = instance->getdsimpin("$RST$,$rst$",    TRUE);
	sout  = instance->getdsimpin("Sout,SOUT,sout", TRUE);
	cout  = instance->getdsimpin("Cout,COUT,cout", TRUE);
	cout->setstate(FLT); sout->setstate(FLT); dq->setstate(FLT); clk->setstate(FLT); reset->setstate(FLT);
}
VOID DS1267I::simulate (ABSTIME stime, DSIMMODES dmode)
{
	if ( dmode == DSIMBOOT   )
	{
	    instance->log("**********************************************************");
	    instance->log("*     DALLAS DS1267  Dual Digital Potentiometer Chip     *");
		instance->log("*  COPYRIGHT(c)2005-6 Simeon Webber ALL RIGHTS RESERVED. *");
		instance->log("**********************************************************");
		instance->log("*         You can use this product as you like,          *");
	    instance->log("*            HOWEVER THE RIGHTS REMAIN MINE              *");
	    instance->log("*               EMAIL vsmlibs@yahoo.co.uk                *");
	    instance->log("*      site address  http://uk.geocities.com/vsmlibs/    *");
	    instance->log("*            V1.04 ALPHA LAST BUILT :13/04/06:           *");
	    instance->log("**********************************************************");
	}
	if ( dmode == DSIMSETTLE ) {}
	else
	{
	    vpotid = 0;
		if (ishigh(reset->istate()))
		{
		    if (clk->isposedge() | clk->isnegedge()) clockinoutdata(stime+tcc, clk->isposedge(), ishigh(dq->istate()));
		}
		if (islow(reset->istate()))
		{
		    // FILL THE POTVALS WITH FIFO STATES
		    // POTVAL 2
		    (fifo[0])?    ssbval = 0x01 : ssbval = 0x00;
		    (fifo[1])?  potval2 |= 0x80 : potval2 &= ~0x80;
            (fifo[2])?  potval2 |= 0x40 : potval2 &= ~0x40;
            (fifo[3])?  potval2 |= 0x20 : potval2 &= ~0x20;
            (fifo[4])?  potval2 |= 0x10 : potval2 &= ~0x10;
            (fifo[5])?  potval2 |= 0x08 : potval2 &= ~0x08;
            (fifo[6])?  potval2 |= 0x04 : potval2 &= ~0x04;
            (fifo[7])?  potval2 |= 0x02 : potval2 &= ~0x02;
            (fifo[8])?  potval2 |= 0x01 : potval2 &= ~0x01;
            // POTVAL 1
            (fifo[9])?  potval1 |= 0x80 : potval1 &= ~0x80;
            (fifo[10])? potval1 |= 0x40 : potval1 &= ~0x40;
            (fifo[11])? potval1 |= 0x20 : potval1 &= ~0x20;
            (fifo[12])? potval1 |= 0x10 : potval1 &= ~0x10;
            (fifo[13])? potval1 |= 0x08 : potval1 &= ~0x08;
            (fifo[14])? potval1 |= 0x04 : potval1 &= ~0x04;
            (fifo[15])? potval1 |= 0x02 : potval1 &= ~0x02;
            (fifo[16])? potval1 |= 0x01 : potval1 &= ~0x01;
            // LOAD THE POTS
            dsimckt->setcallback(stime + tdda + 1, this, vpotid);
    		dsimckt->setbreak(stime + tdda + 1);
		}
	}
}
VOID DS1267I::callback (ABSTIME stime, EVENTID vpotid) { in1 = potval1; in2 = potval2; }
VOID DS1267I::clockinoutdata(ABSTIME stime, BOOL clock, BOOL data)
{
    if (clock)
    {
        //CHECK FOR DATA LEVEL AND STORE IN FIFO
             if (data)  fifo[count] =  TRUE;
        else if (!data) fifo[count] = FALSE;
        // SET THE COUT PIN STATE
        cout->setstate(stime,1,(fifo[count]) ? TSTATE: FSTATE);
        // MUX SETUP
        if ((fifo[0]==TRUE)&(count>=1))
        {
            if (count<=8) sout->setstate(stime+tplh,0,(fifo[count]) ? TSTATE: FSTATE);
        }
        if ((fifo[0]==FALSE)&(count>=9))
        {
            sout->setstate(stime+tplh,0,(fifo[count]) ? TSTATE: FSTATE);
        }
        count++;
        if (count>=17) count=0;
    }
}
VOID DS1267I::VARWINDOW()
{
    y=0;
    statuspopup->setcursorto(cwidth,cheight * (y));
	statuspopup->print(1 ,1,RED,        ":POTVAL 1: 0x%.2X", potval1);
    statuspopup->setcursorto(cwidth,cheight * (y+=1));
    statuspopup->print(1 ,1,DARKYELLOW, ":POTVAL 2: 0x%.2X", potval2);
    statuspopup->setcursorto(cwidth,cheight * (y+=1));
    statuspopup->print(1 ,1,BLACK,      ":SS BIT  : %d    ", ssbval);
    statuspopup->setcursorto(cwidth,cheight * (y+=1));
	statuspopup->print(1 ,1,BLACK," ");
    y=0;
}



///////////////////////////
// : CLASS CONSTRUCTOR : //
///////////////////////////
DS1666I::DS1666I (VOID)
{
    //DIRECTOR'S NULLS
    instance = NULL; spiceckt = NULL; dsimckt = NULL;
    // TIMING CONSTANTS
    tdda = dsimtime(1e-9);
    //NODE'S
    Vpot1=vref1=branch1=NULL;
    //LONGS {SPICE}
    outval1=0;
    //LONGS {DSIM/SPICE /MIXEDMODE}
    in1=out1=0;
    //BOOL
    SDSSW =FALSE; HOA = FALSE;
    cwidth=cheight=0;
    //BYTE's
    tot=0x00;
    //DWORDS
    vpotid=0x0000;
}
DS1666I::~DS1666I() {}
INT DS1666I::isanalog (CHAR *pinname)
{
         if (strnicmp(pinname, "VPOT1", 5) == 0) return TRUE;
	else if (strnicmp(pinname, "VREF",  4) == 0) return TRUE;
	else return FALSE;
}
INT DS1666I::isdigital (CHAR *pinname)
{
         if (strnicmp(pinname, "U/$D$", 5) == 0) return TRUE;
	else if (strnicmp(pinname, "$INC$", 5) == 0) return TRUE;
	else if (strnicmp(pinname, "$CS$",  4) == 0) return TRUE;
    else return FALSE;
}
VOID DS1666I::runctrl (RUNMODES mode)
{
    if ((mode == RM_ANIMATE)|(RM_STEPTIME)|(mode == RM_SUSPEND))
    { if(SDSSW) { cheight = statuspopup->getcharheight(); cwidth  = statuspopup->getcharwidth(); VARWINDOW();} }
}
VOID DS1666I::actuate (REALTIME stime, ACTIVESTATE newstate) {}
BOOL DS1666I::indicate (REALTIME stime, ACTIVEDATA *newstate){ return FALSE; };
VOID DS1666I::setup (IINSTANCE *iinstance, ISPICECKT *ispiceckt)
{
    instance = iinstance; spiceckt = ispiceckt;
    SDSSW = instance->getboolval("SDSSW", 0);
	HOA   = instance->getboolval("HOA",   0);
	if (SDSSW ==TRUE)
	{
	    cps                  =   new CREATEPOPUPSTRUCT;
	    cps->type            =   PWT_STATUS;
	    cps->caption         =   "DS1666 STATUS..";
	    if (HOA) cps->flags  =   PWF_VISIBLE | PWF_AUTOREFRESH | PWF_HIDEONANIMATE;
	    if (!HOA) cps->flags =   PWF_VISIBLE | PWF_AUTOREFRESH;
	    cps->height          =   1;
	    cps->width           =   18;
	    statuspopup          =   (ISTATUSPOPUP *)instance->createpopup(cps);
	}
    Vpot1 = instance->getspicenode("VPOT1", TRUE);
    vref1 = instance->getspicenode("VREF",  TRUE);
    branch1 = spiceckt->newcurnode(instance->id(), "branch1");
    voutpbnode1 = spiceckt->allocsmp(Vpot1, branch1);
    bvoutpnode1 = spiceckt->allocsmp(branch1, Vpot1);
    bvrefpnode1 = spiceckt->allocsmp(branch1, vref1);
}
VOID DS1666I::dcload (REALTIME stime, SPICEMODES mode, DOUBLE *oldrhs, DOUBLE *newrhs)
{
    // Load the values:
	*voutpbnode1 += 1.0; *bvoutpnode1 += 1.0; *bvrefpnode1 -= outnext1;
}
VOID DS1666I::acload (SPICEFREQ omega, DOUBLE *rhs, DOUBLE *irhs) {}
VOID DS1666I::trunc  (REALTIME stime,  REALTIME *newtimestep) {}
VOID DS1666I::accept (REALTIME stime, DOUBLE *rhs ) { if ( in1 != out1 ) outnext1 = DOUBLE(in1) / ( (1<<8) - 1 ); out1 = in1; }
VOID DS1666I::setup (IINSTANCE *iinstance, IDSIMCKT *idsimckt)
{
    instance = iinstance; dsimckt = idsimckt;
	UD      = instance->getdsimpin("U/$D$,u/$d$", TRUE);
	INC     = instance->getdsimpin("$INC$,$inc$", TRUE);
	CS      = instance->getdsimpin("$CS$,$cs$",   TRUE);
	UD->setstate(FLT); INC->setstate(FLT); CS->setstate(FLT);
}
VOID DS1666I::simulate (ABSTIME stime, DSIMMODES dmode)
{
	if ( dmode == DSIMBOOT   )
	{
	    instance->log("**********************************************************");
	    instance->log("*           DALLAS DS1666 Audio Digital Resistor         *");
		instance->log("*  COPYRIGHT(c)2005-6 Simeon Webber ALL RIGHTS RESERVED. *");
		instance->log("**********************************************************");
		instance->log("*          You can use this product as you like,         *");
	    instance->log("*             HOWEVER THE RIGHTS REMAIN MINE             *");
	    instance->log("*               EMAIL vsmlibs@yahoo.co.uk                *");
	    instance->log("*     site address  http://uk.geocities.com/vsmlibs/     *");
	    instance->log("*            V1.04 ALPHA LAST BUILT :13/04/06:           *");
	    instance->log("**********************************************************");
	    tot=0x0D;
	    dsimckt->setcallback(stime + tdda + 1, this, vpotid);
        dsimckt->setbreak(stime + tdda + 1);
	}
	if ( dmode == DSIMSETTLE ) {}
	else
	{
	    vpotid = 0;
		if (islow(CS->istate()))
		{
		    if(islow(UD->istate()))
		    {
		        if (INC->isnegedge())
		        {
		            if (tot >= 0x01)
		            {
		                tot--;
		                dsimckt->setcallback(stime + tdda + 1, this, vpotid);
        		        dsimckt->setbreak(stime + tdda + 1);
		            }
		            if (tot < 0x01)
		            {
		                tot = 0;
		                dsimckt->setcallback(stime + tdda + 1, this, vpotid);
        		        dsimckt->setbreak(stime + tdda + 1);
		            }
		        }
		    }
		    if(ishigh(UD->istate()))
		    {
		        if (INC->isnegedge())
		        {
		            if (tot <= 126)
		            {
		                tot++;
		                dsimckt->setcallback(stime + tdda + 1, this, vpotid);
    		            dsimckt->setbreak(stime + tdda + 1);
    		        }
    		        if (tot > 126)
		            {
		                tot = 127;
		                dsimckt->setcallback(stime + tdda + 1, this, vpotid);
    		            dsimckt->setbreak(stime + tdda + 1);
		            }
		        }
		    }
		}
    }
}
VOID DS1666I::callback (ABSTIME stime, EVENTID vpotid) { in1 = tot; }
VOID DS1666I::VARWINDOW()
{
    y=0;
    statuspopup->setcursorto(cwidth,cheight * (y));
	statuspopup->print(1 ,1,RED, ":POSITION: 0x%.2X", tot);
    statuspopup->setcursorto(cwidth,cheight * (y+=1));
	statuspopup->print(1 ,1,BLACK," ");
    y=0;
}


///////////////////////////
// : CLASS CONSTRUCTOR : //
///////////////////////////
DS1804I::DS1804I (VOID)
{
    //DIRECTOR'S NULLS
    instance = NULL; spiceckt = NULL; dsimckt = NULL;
    // TIMING CONSTANTS
    tdda = dsimtime(1e-9);
    //NODE'S
    Vpot1=vref1=branch1=NULL;
    //LONGS {SPICE}
    outval1=0;
    //LONGS {DSIM/SPICE /MIXEDMODE}
    in1=out1=0;
    //BOOL
    SDSSW = FALSE;
    HOA   = FALSE;
    SAVE  = FALSE;
    cwidth=cheight=0;
    //BYTE's
    tot=0x00;
    savedata[0]=0x00;
    savedata[1]=0x00;
    savedata[2]=0x00;
    savedata[3]=0x00;
    savedata[4]=0x00;
    savedata[5]=0x00;
    //DWORDS
    vpotid=0x0000;

    savedatadword[0]=0x0000;
    savedatadword[1]=0x0000;
}
DS1804I::~DS1804I() {}
INT DS1804I::isanalog (CHAR *pinname)
{
         if (strnicmp(pinname, "VPOT1", 5) == 0) return TRUE;
	else if (strnicmp(pinname, "VREF",  4) == 0) return TRUE;
	else return FALSE;
}
INT DS1804I::isdigital (CHAR *pinname)
{
         if (strnicmp(pinname, "U/$D$", 5) == 0) return TRUE;
	else if (strnicmp(pinname, "$INC$", 5) == 0) return TRUE;
	else if (strnicmp(pinname, "$CS$",  4) == 0) return TRUE;
    else return FALSE;
}
VOID DS1804I::runctrl (RUNMODES mode)
{
    if ((mode == RM_ANIMATE)|(RM_STEPTIME)|(mode == RM_SUSPEND))
    {
        if(SDSSW) { cheight = statuspopup->getcharheight(); cwidth  = statuspopup->getcharwidth(); VARWINDOW(); }
        if(SAVE == TRUE)
        {
            eeprom[0] = savedata[0];
            eeprom[1] = savedata[1];
            eeprom[2] = savedata[2];
            eeprom[3] = savedata[3];
            eeprom[4] = savedata[4];
            eeprom[5] = savedata[5];

            filename = instance->getstrval("EPROM");
		    file = CreateFile(filename, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL);
		    bResult = WriteFile(file, &eeprom, 8, &nBytesRead, NULL);
		    if (!bResult) instance->fatal("Could not write EEPROM file");
    		CloseHandle(file);
		    instance->log("eeprom save was triggered");
		    SAVE = FALSE;
        }
    }
}
VOID DS1804I::actuate (REALTIME stime, ACTIVESTATE newstate) {}
BOOL DS1804I::indicate (REALTIME stime, ACTIVEDATA *newstate){ return FALSE; };
VOID DS1804I::setup (IINSTANCE *iinstance, ISPICECKT *ispiceckt)
{
    instance = iinstance; spiceckt = ispiceckt;
    SDSSW = instance->getboolval("SDSSW", 0);
	HOA   = instance->getboolval("HOA",   0);
	if (SDSSW ==TRUE)
	{
	    cps                  =   new CREATEPOPUPSTRUCT;
	    cps->type            =   PWT_STATUS;
	    cps->caption         =   "DS1804 STATUS..";
	    if (HOA) cps->flags  =   PWF_VISIBLE | PWF_AUTOREFRESH | PWF_HIDEONANIMATE;
	    if (!HOA) cps->flags =   PWF_VISIBLE | PWF_AUTOREFRESH;
	    cps->height          =   3;
	    cps->width           =   42;
	    statuspopup          =   (ISTATUSPOPUP *)instance->createpopup(cps);
	}
    Vpot1 = instance->getspicenode("VPOT1", TRUE);
    vref1 = instance->getspicenode("VREF",  TRUE);
    branch1 = spiceckt->newcurnode(instance->id(), "branch1");
    voutpbnode1 = spiceckt->allocsmp(Vpot1, branch1);
    bvoutpnode1 = spiceckt->allocsmp(branch1, Vpot1);
    bvrefpnode1 = spiceckt->allocsmp(branch1, vref1);
}
VOID DS1804I::dcload (REALTIME stime, SPICEMODES mode, DOUBLE *oldrhs, DOUBLE *newrhs)
{
    // Load the values:
	*voutpbnode1 += 1.0; *bvoutpnode1 += 1.0; *bvrefpnode1 -= outnext1;
}
VOID DS1804I::acload (SPICEFREQ omega, DOUBLE *rhs, DOUBLE *irhs) {}
VOID DS1804I::trunc  (REALTIME stime,  REALTIME *newtimestep) {}
VOID DS1804I::accept (REALTIME stime, DOUBLE *rhs ) { if ( in1 != out1 ) outnext1 = DOUBLE(in1) / ( (1<<8) - 1 ); out1 = in1; }
VOID DS1804I::setup (IINSTANCE *iinstance, IDSIMCKT *idsimckt)
{
    instance = iinstance; dsimckt = idsimckt;
	filename = instance->getstrval("EPROM");
	file = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	bResult = ReadFile(file, &eeprom, 8, &nBytesRead, NULL) ;

	// Check for the end of the file.
	if (!bResult) {
		instance->log("EEPROM FILE NOT PRESENT DEFAULTS IN USE");
		file = CreateFile(filename, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL);
		bResult = WriteFile(file, &eeprom, 8, &nBytesRead, NULL);
		if (!bResult) instance->fatal("Could not create EEPROM file");
	}
	CloseHandle(file);

    tot = eeprom[0]; // load the previously saved pot position value 0x00-0xFF

    savedatadword[0] = (DWORD) eeprom[1] + ((eeprom[2])<<8); // move the lsb BYTES to DWORD 1
    savedatadword[1] = (DWORD) eeprom[3] + ((eeprom[4])<<8); // move the msb BYTES to DWORD 2
    runtimes = (LONG) savedatadword[0] + ((savedatadword[1])<<16);  // move DWORD 0 and 1 to LONG

    srand ( time(NULL) );  //  set sudo random seed from system time clock mseconds
	randomeewrites = (LONG) (((rand()%RAND_MAX) + (rand()%RAND_MAX))+0xC350); // add two random values in the range 0-32768 and add this to 0XC350 {50000 flashes guarantee}

	savedata[5] = eeprom[5]; // load the has eeprom failed flag

	UD      = instance->getdsimpin("U/$D$,u/$d$", TRUE);
	INC     = instance->getdsimpin("$INC$,$inc$", TRUE);
	CS      = instance->getdsimpin("$CS$,$cs$",   TRUE);
	UD->setstate(FLT); INC->setstate(FLT); CS->setstate(FLT);
}
VOID DS1804I::simulate (ABSTIME stime, DSIMMODES dmode)
{
	if (dmode == DSIMBOOT)
	{
	    instance->log("*************************************************************");
	    instance->log("*            DALLAS DS1804 NV Trimmer Potentiometer         *");
		instance->log("*   COPYRIGHT(c)2005-6 Simeon Webber ALL RIGHTS RESERVED.   *");
		instance->log("*************************************************************");
		instance->log("*           You can use this product as you like,           *");
	    instance->log("*              HOWEVER THE RIGHTS REMAIN MINE               *");
	    instance->log("*                EMAIL vsmlibs@yahoo.co.uk                  *");
	    instance->log("*      site address  http://uk.geocities.com/vsmlibs/       *");
	    instance->log("*              V1.04 ALPHA LAST BUILT :13/04/06:            *");
	    instance->log("*************************************************************");
	    dsimckt->setcallback(stime + tdda + 1, this, vpotid);
        dsimckt->setbreak(stime + tdda + 1);
	}
	if ( dmode == DSIMSETTLE ) {}
	else
	{
	    vpotid = 0;
		if(ishigh(INC->istate()))
		{
		    if (CS->isposedge())
		    {
		        if ((runtimes >= randomeewrites)||(savedata[5]==0x01))
		        {
		            instance->log("chip eeprom has failed 50000+ flash expired");
		            savedata[0] = 0; savedata[5] = 1; SAVE = TRUE;
		        }
		        else
		        {
		            SAVE = TRUE; runtimes++;
		            savedata[0] = tot;
		            savedata[1] = (BYTE) (runtimes);
                    savedata[2] = (BYTE) (runtimes>>8);
	                savedata[3] = (BYTE) (runtimes>>16);
                    savedata[4] = (BYTE) (runtimes>>24);
		            savedata[5] = 0;
		        }
		    }
		}
		if (islow(CS->istate()))
		{
		    if(islow(UD->istate()))
		    {
		        if (INC->isnegedge())
		        {
		            if (tot >= 0x01)
		            {
		                tot--;
		                dsimckt->setcallback(stime + tdda + 1, this, vpotid);
        		        dsimckt->setbreak(stime + tdda + 1);
		            }
		            if (tot < 0x01)
		            {
		                tot = 0;
		                dsimckt->setcallback(stime + tdda + 1, this, vpotid);
        		        dsimckt->setbreak(stime + tdda + 1);
		            }
		        }
		    }
		    if(ishigh(UD->istate()))
		    {
		        if (INC->isnegedge())
		        {
		            if (tot <= 99)
		            {
		                tot++;
		                dsimckt->setcallback(stime + tdda + 1, this, vpotid);
    		            dsimckt->setbreak(stime + tdda + 1);
    		        }
    		        if (tot > 99)
		            {
		                tot = 100;
		                dsimckt->setcallback(stime + tdda + 1, this, vpotid);
    		            dsimckt->setbreak(stime + tdda + 1);
		            }
		        }
		    }
		}
    }
}
VOID DS1804I::callback (ABSTIME stime, EVENTID vpotid) { in1 = tot; }
VOID DS1804I::VARWINDOW()
{
    y=0;
    statuspopup->setcursorto(cwidth,cheight * (y));
	    statuspopup->print(1 ,1,RED,    ":POT POSITION: %.3d   0x%.2X           ", tot, tot);
    if (savedata[5]==1)
    {
        statuspopup->setcursorto(cwidth,cheight * (y+=2));
	    statuspopup->print(1 ,1,DARKRED, ":NV EEPROM HAS FAILED AT:        %#.5X ", runtimes);
	}
	else
	{
	    statuspopup->setcursorto(cwidth,cheight * (y+=1));
	    statuspopup->print(1 ,1,BLUE,    ":EEPROM SAVE VAL(17BIT):         %#.5X ", runtimes);
	    statuspopup->setcursorto(cwidth,cheight * (y+=1));
	    statuspopup->print(1 ,1,BLACK,   ":SRANDOM EEPROM FAIL VAL(17BIT): %#.5X ", randomeewrites);
	}
	statuspopup->setcursorto(cwidth,cheight * (y+=1));
	statuspopup->print(1 ,1,BLACK," ");
    y=0;
}
///////////////////////////
// : CLASS CONSTRUCTOR : //
///////////////////////////
DS1867I::DS1867I (VOID)
{
    //DIRECTOR'S NULLS
    instance = NULL; spiceckt = NULL; dsimckt = NULL;
    // TIMING CONSTANTS
    tdda = dsimtime(1e-9); tcc = dsimtime(50e-9); tplh = dsimtime(35e-9);
    //NODE'S
    Vpot1=Vpot2=vref1=vref2=branch1=branch2=NULL;
    //LONGS {SPICE}
     outval1=outval2=0;
    //LONGS {DSIM/SPICE /MIXEDMODE}
    in1=out1=in2=out2=0;
    //BOOL
    SDSSW  = FALSE;
    HOA    = FALSE;
    SAVED  = FALSE;
    LOADED = FALSE;
    //INTS
    count=y=0; cwidth=cheight=0;
    //BYTE'S
    potval1=potval2=0x00;
    savedata[0]=0x00;
    savedata[1]=0x00;
    savedata[2]=0x00;
    savedata[3]=0x00;
    savedata[4]=0x00;
    //DWORDS
    vpotid=0x0000;
    value = 5;
    savedatadword[0]=0x0000;
    savedatadword[1]=0x0000;
}
DS1867I::~DS1867I() {}
INT DS1867I::isanalog (CHAR *pinname)
{
    if      (strnicmp(pinname, "VPOT1", 5) == 0) return TRUE;
	else if (strnicmp(pinname, "VPOT2", 5) == 0) return TRUE;
	else if (strnicmp(pinname, "VREF",  4) == 0) return TRUE;
	else if (strnicmp(pinname, "VPOS",  4) == 0) return TRUE;
	else if (strnicmp(pinname, "VNEG",  4) == 0) return TRUE;
	else return FALSE;
}
INT DS1867I::isdigital (CHAR *pinname)
{
         if (strnicmp(pinname, "DQ",    2) == 0) return TRUE;
	else if (strnicmp(pinname, "CLK",   3) == 0) return TRUE;
	else if (strnicmp(pinname, "$RST$", 5) == 0) return TRUE;
	else if (strnicmp(pinname, "COUT",  4) == 0) return TRUE;
	else if (strnicmp(pinname, "SOUT",  4) == 0) return TRUE;
    else return FALSE;
}
VOID DS1867I::runctrl (RUNMODES mode)
{
    if ((mode == RM_ANIMATE)|(RM_STEPTIME)|(mode == RM_SUSPEND))
    {
        if(SDSSW) { cheight = statuspopup->getcharheight(); cwidth  = statuspopup->getcharwidth(); VARWINDOW(); }
        if (((value>=3.0)&&(value<=4.5))&(SAVED == FALSE))
        {
            for(y=0;y<=16;){ eeprom[y] = fifo[y]; y++; }
            if ((runtimes >= randomeewrites)||(savedata[4]==0x01))
		    {
		        instance->log("chip eeprom has failed 25000_min + flash expired");
		        eeprom[21] = 0x01; SAVED = TRUE;
		    }
		    else
		    {
		        runtimes++;
		        savedata[0] = (BYTE) (runtimes);
                savedata[1] = (BYTE) (runtimes>>8);
	            savedata[2] = (BYTE) (runtimes>>16);
                savedata[3] = (BYTE) (runtimes>>24);
		        savedata[4] = 0;
		        eeprom[17] = savedata[0];
                eeprom[18] = savedata[1];
                eeprom[19] = savedata[2];
                eeprom[20] = savedata[3];
                eeprom[21] = savedata[4];
		    }
		    filename = instance->getstrval("EEPROM");
		    file = CreateFile(filename, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL);
		    bResult = WriteFile(file, &eeprom, 32, &nBytesRead, NULL);
		    if (!bResult)
			instance->fatal("Could not write EEPROM file");
		    CloseHandle(file);
		    instance->log("voltage vcc = >3v <4.5v eeprom save was triggered");
		    SAVED = TRUE;
		}
		else if ((value>=4.6)&(SAVED == TRUE))
        {
            SAVED = FALSE;
        }
    }
}
VOID DS1867I::actuate (REALTIME stime, ACTIVESTATE newstate)  {}
BOOL DS1867I::indicate (REALTIME stime, ACTIVEDATA *newstate) { return FALSE; };
VOID DS1867I::setup (IINSTANCE *iinstance, ISPICECKT *ispiceckt)
{
    instance = iinstance; spiceckt = ispiceckt;
    SDSSW = instance->getboolval("SDSSW", 0);
	HOA   = instance->getboolval("HOA",   0);
	if (SDSSW ==TRUE)
	{
	    cps                  =   new CREATEPOPUPSTRUCT;
	    cps->type            =   PWT_STATUS;
	    cps->caption         =   "DS1867 STATUS..";
	    if (HOA) cps->flags  =   PWF_VISIBLE | PWF_AUTOREFRESH | PWF_HIDEONANIMATE;
	    if (!HOA) cps->flags =   PWF_VISIBLE | PWF_AUTOREFRESH;
	    cps->height          =   5;
	    cps->width           =   44;
	    statuspopup          =   (ISTATUSPOPUP *)instance->createpopup(cps);
	}
    Vpot1  = instance->getspicenode("VPOT1", TRUE);
    Vpot2  = instance->getspicenode("VPOT2", TRUE);
    vref1  = instance->getspicenode("VREF",  TRUE);
    vref2  = instance->getspicenode("VREF",  TRUE);
    vpos   = instance->getspicenode("VPOS",  TRUE);
    vneg   = instance->getspicenode("VNEG",  TRUE);
    branch1 = spiceckt->newcurnode(instance->id(), "branch1");
    voutpbnode1 = spiceckt->allocsmp(Vpot1, branch1);
    bvoutpnode1 = spiceckt->allocsmp(branch1, Vpot1);
    bvrefpnode1 = spiceckt->allocsmp(branch1, vref1);
    branch2 = spiceckt->newcurnode(instance->id(), "branch2");
    voutpbnode2 = spiceckt->allocsmp(Vpot2, branch2);
    bvoutpnode2 = spiceckt->allocsmp(branch2, Vpot2);
    bvrefpnode2 = spiceckt->allocsmp(branch2, vref2);
}
VOID DS1867I::dcload (REALTIME stime, SPICEMODES mode, DOUBLE *oldrhs, DOUBLE *newrhs)
{
    // Load the values:
	*voutpbnode1 += 1.0; *bvoutpnode1 += 1.0; *bvrefpnode1 -= outnext1;
	// Load the values:
	*voutpbnode2 += 1.0; *bvoutpnode2 += 1.0; *bvrefpnode2 -= outnext2;
}
VOID DS1867I::acload (SPICEFREQ omega, DOUBLE *rhs, DOUBLE *irhs) {}
VOID DS1867I::trunc  (REALTIME stime,  REALTIME *newtimestep) {}
VOID DS1867I::accept (REALTIME stime, DOUBLE *rhs )
{
    if ( in1 != out1 ) outnext1 = DOUBLE(in1) / ( (1<<8) - 1 );
    if ( in2 != out2 ) outnext2 = DOUBLE(in2) / ( (1<<8) - 1 );
	out1 = in1; out2 = in2; value = (rhs[vneg] + rhs[vpos]);
}
VOID DS1867I::setup (IINSTANCE *iinstance, IDSIMCKT *idsimckt)
{
    instance = iinstance; dsimckt = idsimckt;
	filename = instance->getstrval("EEPROM");
	file = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	bResult = ReadFile(file, &eeprom, 32, &nBytesRead, NULL) ;
	// Check for the end of the file.
	if (!bResult) {
		instance->log("EEPROM FILE NOT PRESENT DEFAULTS IN USE TILL VCC <4.5V ");
		file = CreateFile(filename, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL);
		bResult = WriteFile(file, &eeprom, 32, &nBytesRead, NULL);
		if (!bResult)
			instance->fatal("Could not create EEPROM file");
	}
	CloseHandle(file);
    for(y=0;y<=16;) { fifo[y] = eeprom[y]; y++; }

	savedatadword[0] = (DWORD) eeprom[17] + ((eeprom[18])<<8); // move the lsb BYTES to DWORD 1
    savedatadword[1] = (DWORD) eeprom[19] + ((eeprom[20])<<8); // move the msb BYTES to DWORD 2
    runtimes = (LONG) savedatadword[0] + ((savedatadword[1])<<16);  // move DWORD 0 and 1 to LONG

    srand ( time(NULL) );  //  set sudo random seed from system time clock mseconds
	randomeewrites = (LONG) (((rand()%RAND_MAX) + (rand()%RAND_MAX))+0x61A8); // add two random values in the range 0-32768 and add this to 0X61A8 {25000 flashes guarantee}

    savedata[4] = eeprom[21];

	dq    = instance->getdsimpin("DQ,dq",          TRUE);
	clk   = instance->getdsimpin("CLK,clk",        TRUE);
	reset = instance->getdsimpin("$RST$,$rst$",    TRUE);
	sout  = instance->getdsimpin("Sout,SOUT,sout", TRUE);
	cout  = instance->getdsimpin("Cout,COUT,cout", TRUE);
	cout->setstate(FLT); sout->setstate(FLT); dq->setstate(FLT); clk->setstate(FLT); reset->setstate(FLT);
}
VOID DS1867I::simulate (ABSTIME stime, DSIMMODES dmode)
{
	if ( dmode == DSIMBOOT   )
	{
	    instance->log("**********************************************************");
	    instance->log("*  DALLAS DS1867 Dual Digital Potentiometer with EEPROM  *");
		instance->log("*  COPYRIGHT(c)2005-6 Simeon Webber ALL RIGHTS RESERVED. *");
		instance->log("**********************************************************");
		instance->log("*         You can use this product as you like,          *");
	    instance->log("*            HOWEVER THE RIGHTS REMAIN MINE              *");
	    instance->log("*              EMAIL vsmlibs@yahoo.co.uk                 *");
	    instance->log("*    site address  http://uk.geocities.com/vsmlibs/      *");
	    instance->log("*           V1.04 ALPHA LAST BUILT :13/04/06:            *");
	    instance->log("**********************************************************");
	}
	if ( dmode == DSIMSETTLE ) {}
	else
	{
	    vpotid = 0;
		if (ishigh(reset->istate()))
		{
		    if (clk->isposedge() | clk->isnegedge()) clockinoutdata(stime+tcc, clk->isposedge(), ishigh(dq->istate()));
		}
		if(reset->isnegedge() | (LOADED == FALSE))
	    {
	        // FILL THE POTVALS WITH FIFO STATES
		    // POTVAL 2
		    (fifo[0])?    ssbval = 0x01 : ssbval = 0x00;
		    (fifo[1])?  potval2 |= 0x80 : potval2 &= ~0x80;
            (fifo[2])?  potval2 |= 0x40 : potval2 &= ~0x40;
            (fifo[3])?  potval2 |= 0x20 : potval2 &= ~0x20;
            (fifo[4])?  potval2 |= 0x10 : potval2 &= ~0x10;
            (fifo[5])?  potval2 |= 0x08 : potval2 &= ~0x08;
            (fifo[6])?  potval2 |= 0x04 : potval2 &= ~0x04;
            (fifo[7])?  potval2 |= 0x02 : potval2 &= ~0x02;
            (fifo[8])?  potval2 |= 0x01 : potval2 &= ~0x01;
            // POTVAL 1
            (fifo[9])?  potval1 |= 0x80 : potval1 &= ~0x80;
            (fifo[10])? potval1 |= 0x40 : potval1 &= ~0x40;
            (fifo[11])? potval1 |= 0x20 : potval1 &= ~0x20;
            (fifo[12])? potval1 |= 0x10 : potval1 &= ~0x10;
            (fifo[13])? potval1 |= 0x08 : potval1 &= ~0x08;
            (fifo[14])? potval1 |= 0x04 : potval1 &= ~0x04;
            (fifo[15])? potval1 |= 0x02 : potval1 &= ~0x02;
            (fifo[16])? potval1 |= 0x01 : potval1 &= ~0x01;
            // LOAD THE POTS
            dsimckt->setcallback(stime + tdda + 1, this, vpotid);
    		dsimckt->setbreak(stime + tdda + 1);
    		LOADED=TRUE;
		}
		if (islow(reset->istate()))
		{
		    if (clk->isposedge() | clk->isnegedge()) clockinoutdata(stime+tcc, clk->isposedge(), ishigh(dq->istate()));
		}
    }
}
VOID DS1867I::callback (ABSTIME stime, EVENTID vpotid) { in1 = potval1; in2 = potval2; }
VOID DS1867I::clockinoutdata(ABSTIME stime, BOOL clock, BOOL data)
{
    if (clock)
    {
        //CHECK FOR DATA LEVEL AND STORE IN FIFO
        if      (data)  fifo[count] =  TRUE;
        else if (!data) fifo[count] = FALSE;
        // SET THE COUT PIN STATE
        cout->setstate(stime,1,(fifo[count]) ? TSTATE: FSTATE);
        // MUX SETUP
        if ((fifo[0]==TRUE)&(count>=1))
        {
            if (count<=8) sout->setstate(stime+tplh,0,(fifo[count]) ? TSTATE: FSTATE);
        }
        if ((fifo[0]==FALSE)&(count>=9))
        {
            sout->setstate(stime+tplh,0,(fifo[count]) ? TSTATE: FSTATE);
        }
        count++;
        if (count>=17) count=0;
    }
}
VOID DS1867I::VARWINDOW()
{
    y=0;
    statuspopup->setcursorto(cwidth,cheight * (y));
	statuspopup->print(1 ,1,RED,   ":POTVAL 1: 0x%.2X", potval1);
    statuspopup->setcursorto(cwidth,cheight * (y+=1));
    statuspopup->print(1 ,1,DARKYELLOW, ":POTVAL 2: 0x%.2X", potval2);
    statuspopup->setcursorto(cwidth,cheight * (y+=1));
    statuspopup->print(1 ,1,BLACK, ":SS BIT  : %d    ", ssbval);
    if (savedata[5]==1)
    {
        statuspopup->setcursorto(cwidth,cheight * (y+=2));
	    statuspopup->print(1 ,1,DARKRED, ":NV EEPROM HAS FAILED AT:        %#.5X ", runtimes);
	}
	else
	{
	    statuspopup->setcursorto(cwidth,cheight * (y+=1));
	    statuspopup->print(1 ,1,BLUE,    ":EEPROM SAVE VAL(17BIT):         %#.5X ", runtimes);
	    statuspopup->setcursorto(cwidth,cheight * (y+=1));
	    statuspopup->print(1 ,1,BLACK,   ":SRANDOM EEPROM FAIL VAL(17BIT): %#.5X ", randomeewrites);
	}
    statuspopup->setcursorto(cwidth,cheight * (y+=1));
	statuspopup->print(1 ,1,BLACK," ");
    y=0;
}
///////////////////////////
// : CLASS CONSTRUCTOR : //
///////////////////////////
DS1868I::DS1868I (VOID)
{
    //DIRECTOR'S NULLS
    instance = NULL; spiceckt = NULL; dsimckt = NULL;
    // TIMING CONSTANTS
    tdda = dsimtime(1e-9); tcc = dsimtime(50e-9); tplh = dsimtime(25e-9);
    //NODE'S
    Vpot1=Vpot2=vref1=vref2=branch1=branch2=NULL;
    //LONGS {SPICE}
     outval1=outval2=0;
    //LONGS {DSIM/SPICE/MIXEDMODE}
    in1=out1=in2=out2=0;
    //BOOL
    SDSSW =FALSE; HOA = FALSE;
    //INTS
    count=y=0; cwidth=cheight=0;
    //BYTE'S
    potval1=potval2=0x00;
    //DWORDS
    vpotid=0x0000;
}
DS1868I::~DS1868I() {}
INT DS1868I::isanalog (CHAR *pinname)
{
         if (strnicmp(pinname, "VPOT1", 5) == 0) return TRUE;
	else if (strnicmp(pinname, "VPOT2", 5) == 0) return TRUE;
	else if (strnicmp(pinname, "VREF",  4) == 0) return TRUE;
	else return FALSE;
}
INT DS1868I::isdigital (CHAR *pinname)
{
         if (strnicmp(pinname, "DQ",    2) == 0) return TRUE;
	else if (strnicmp(pinname, "CLK",   3) == 0) return TRUE;
	else if (strnicmp(pinname, "$RST$", 5) == 0) return TRUE;
	else if (strnicmp(pinname, "COUT",  4) == 0) return TRUE;
	else if (strnicmp(pinname, "SOUT",  4) == 0) return TRUE;
    else return FALSE;
}
VOID DS1868I::runctrl (RUNMODES mode)
{
    if ((mode == RM_ANIMATE)|(RM_STEPTIME)|(mode == RM_SUSPEND))
    { if(SDSSW) { cheight = statuspopup->getcharheight(); cwidth  = statuspopup->getcharwidth(); VARWINDOW(); } }
}
VOID DS1868I::actuate (REALTIME stime, ACTIVESTATE newstate) {}
BOOL DS1868I::indicate (REALTIME stime, ACTIVEDATA *newstate){ return FALSE; };
VOID DS1868I::setup (IINSTANCE *iinstance, ISPICECKT *ispiceckt)
{
    instance = iinstance; spiceckt = ispiceckt;
    SDSSW    = instance->getboolval("SDSSW", 0);
	HOA      = instance->getboolval("HOA",   0);
	if (SDSSW ==TRUE)
	{
	    cps                  =   new CREATEPOPUPSTRUCT;
	    cps->type            =   PWT_STATUS;
	    cps->caption         =   "DS1868 STATUS..";
	    if (HOA) cps->flags  =   PWF_VISIBLE | PWF_AUTOREFRESH | PWF_HIDEONANIMATE;
	    if (!HOA) cps->flags =   PWF_VISIBLE | PWF_AUTOREFRESH;
	    cps->height          =   3;
	    cps->width           =   18;
	    statuspopup          =   (ISTATUSPOPUP *)instance->createpopup(cps);
	}
    Vpot1  = instance->getspicenode("VPOT1", TRUE);
    Vpot2  = instance->getspicenode("VPOT2", TRUE);
    vref1  = instance->getspicenode("VREF",  TRUE);
    vref2  = instance->getspicenode("VREF",  TRUE);
    branch1 = spiceckt->newcurnode(instance->id(), "branch1");
    voutpbnode1 = spiceckt->allocsmp(Vpot1, branch1);
    bvoutpnode1 = spiceckt->allocsmp(branch1, Vpot1);
    bvrefpnode1 = spiceckt->allocsmp(branch1, vref1);
    branch2 = spiceckt->newcurnode(instance->id(), "branch2");
    voutpbnode2 = spiceckt->allocsmp(Vpot2, branch2);
    bvoutpnode2 = spiceckt->allocsmp(branch2, Vpot2);
    bvrefpnode2 = spiceckt->allocsmp(branch2, vref2);
}
VOID DS1868I::dcload (REALTIME stime, SPICEMODES mode, DOUBLE *oldrhs, DOUBLE *newrhs)
{
    // Load the values:
	*voutpbnode1 += 1.0; *bvoutpnode1 += 1.0; *bvrefpnode1 -= outnext1;
	// Load the values:
	*voutpbnode2 += 1.0; *bvoutpnode2 += 1.0; *bvrefpnode2 -= outnext2;
}
VOID DS1868I::acload (SPICEFREQ omega, DOUBLE *rhs, DOUBLE *irhs) {}
VOID DS1868I::trunc  (REALTIME stime,  REALTIME *newtimestep) {}
VOID DS1868I::accept (REALTIME stime, DOUBLE *rhs )
{
    if ( in1 != out1 ) outnext1 = DOUBLE(in1) / ( (1<<8) - 1 );
    if ( in2 != out2 ) outnext2 = DOUBLE(in2) / ( (1<<8) - 1 );
	out1 = in1; out2 = in2;
}
VOID DS1868I::setup (IINSTANCE *iinstance, IDSIMCKT *idsimckt)
{
    instance = iinstance; dsimckt = idsimckt;
	dq    = instance->getdsimpin("DQ,dq",          TRUE);
	clk   = instance->getdsimpin("CLK,clk",        TRUE);
	reset = instance->getdsimpin("$RST$,$rst$",    TRUE);
	sout  = instance->getdsimpin("Sout,SOUT,sout", TRUE);
	cout  = instance->getdsimpin("Cout,COUT,cout", TRUE);
	cout->setstate(FLT); sout->setstate(FLT); dq->setstate(FLT); clk->setstate(FLT); reset->setstate(FLT);
}
VOID DS1868I::simulate (ABSTIME stime, DSIMMODES dmode)
{
	if ( dmode == DSIMBOOT   )
	{
	    instance->log("**********************************************************");
	    instance->log("*      DALLAS DS1868 Dual Digital Potentiometer Chip     *");
		instance->log("*  COPYRIGHT(c)2005-6 Simeon Webber ALL RIGHTS RESERVED. *");
		instance->log("**********************************************************");
		instance->log("*         You can use this product as you like,          *");
	    instance->log("*            HOWEVER THE RIGHTS REMAIN MINE              *");
	    instance->log("*               EMAIL vsmlibs@yahoo.co.uk                *");
	    instance->log("*      site address  http://uk.geocities.com/vsmlibs/    *");
	    instance->log("*            V1.04 ALPHA LAST BUILT :13/04/06:           *");
	    instance->log("**********************************************************");
	}
	if ( dmode == DSIMSETTLE ) {}
	else
	{
	    vpotid = 0;
		if (ishigh(reset->istate()))
		{ if (clk->isposedge() | clk->isnegedge()) clockinoutdata(stime+tcc, clk->isposedge(), ishigh(dq->istate())); }
		if(reset->isnegedge())
	    {
	        // FILL THE POTVALS WITH FIFO STATES
		    // POTVAL 2
		    (fifo[0])?    ssbval = 0x01 : ssbval = 0x00;
		    (fifo[1])?  potval2 |= 0x80 : potval2 &= ~0x80;
            (fifo[2])?  potval2 |= 0x40 : potval2 &= ~0x40;
            (fifo[3])?  potval2 |= 0x20 : potval2 &= ~0x20;
            (fifo[4])?  potval2 |= 0x10 : potval2 &= ~0x10;
            (fifo[5])?  potval2 |= 0x08 : potval2 &= ~0x08;
            (fifo[6])?  potval2 |= 0x04 : potval2 &= ~0x04;
            (fifo[7])?  potval2 |= 0x02 : potval2 &= ~0x02;
            (fifo[8])?  potval2 |= 0x01 : potval2 &= ~0x01;
            // POTVAL 1
            (fifo[9])?  potval1 |= 0x80 : potval1 &= ~0x80;
            (fifo[10])? potval1 |= 0x40 : potval1 &= ~0x40;
            (fifo[11])? potval1 |= 0x20 : potval1 &= ~0x20;
            (fifo[12])? potval1 |= 0x10 : potval1 &= ~0x10;
            (fifo[13])? potval1 |= 0x08 : potval1 &= ~0x08;
            (fifo[14])? potval1 |= 0x04 : potval1 &= ~0x04;
            (fifo[15])? potval1 |= 0x02 : potval1 &= ~0x02;
            (fifo[16])? potval1 |= 0x01 : potval1 &= ~0x01;
            // LOAD THE POTS
            dsimckt->setcallback(stime + tdda + 1, this, vpotid);
    		dsimckt->setbreak(stime + tdda + 1);
		}
		if (islow(reset->istate()))
		{ if (clk->isposedge() | clk->isnegedge()) clockinoutdata(stime+tcc, clk->isposedge(), ishigh(dq->istate())); }
    }
}
VOID DS1868I::callback (ABSTIME stime, EVENTID vpotid) { in1 = potval1; in2 = potval2; }
VOID DS1868I::clockinoutdata(ABSTIME stime, BOOL clock, BOOL data)
{
    if (clock)
    {
        //CHECK FOR DATA LEVEL AND STORE IN FIFO
             if (data)  fifo[count] =  TRUE;
        else if (!data) fifo[count] = FALSE;
        // SET THE COUT PIN STATE
        cout->setstate(stime,1,(fifo[count]) ? TSTATE: FSTATE);
        // MUX SETUP
        if ((fifo[0]==TRUE)&(count>=1))
        {
            if (count<=8) sout->setstate(stime+tplh,0,(fifo[count]) ? TSTATE: FSTATE);
        }
        if ((fifo[0]==FALSE)&(count>=9))
        {
            sout->setstate(stime+tplh,0,(fifo[count]) ? TSTATE: FSTATE);
        }
        count++;
        if (count>=17) count=0;
    }
}
VOID DS1868I::VARWINDOW()
{
    y=0;
    statuspopup->setcursorto(cwidth,cheight * (y));
	statuspopup->print(1 ,1,RED,     ":POTVAL 1: 0x%.2X", potval1);
    statuspopup->setcursorto(cwidth,cheight * (y+=1));
    statuspopup->print(1 ,1,DARKYELLOW,   ":POTVAL 2: 0x%.2X", potval2);
    statuspopup->setcursorto(cwidth,cheight * (y+=1));
    statuspopup->print(1 ,1,BLACK,   ":SS BIT  : %d    ", ssbval);
    statuspopup->setcursorto(cwidth,cheight * (y+=1));
	statuspopup->print(1 ,1,BLACK," ");
    y=0;
}

