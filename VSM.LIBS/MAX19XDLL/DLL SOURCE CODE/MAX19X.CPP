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
#include "MAX19X.HPP";
extern "C"  EXPORT IMIXEDMODEL * createmixedmodel (CHAR *device, ILICENCESERVER *ils)
{
	IMIXEDMODEL * model = NULL;
	if (strnicmp(device, "MAX190", 6) == 0) model = new MAX190_1 ();
	if (strnicmp(device, "MAX191", 6) == 0) model = new MAX190_1 ();
	//if (strnicmp(device, "MAX192", 6) == 0) model = new MAX192 ();
	if (model != NULL) { ils->authorize(DEV_KEY21); } return (IMIXEDMODEL *) model; }
extern "C" EXPORT VOID deletemixedmodel (IMIXEDMODEL * model) { delete  (IMIXEDMODEL *) model; }
//////////////////////////////////
///////// MAX190 CLASS ///////////
//////////////////////////////////
MAX190_1::MAX190_1 (VOID)
{ instance = NULL; dsimckt = NULL;
    //////////////////////////////////////////////////
    agnd = NULL; ainP = NULL; ainN = NULL; ref = NULL;
	//////////////////////
	input = 0; nbits = 12;
    ///////////////
    UNI_BIP = NULL;
    //////////////////////////
    DP_LSW = NULL; DP_LSW = NULL; SER_BUS = NULL;
    ///////////////////////////////////
    pd = NULL; bip = NULL; busy = NULL;
	////////////////////////////////////////////////////////////////////////////
	rd = NULL; cs = NULL; hben = NULL; par = NULL; clk_sclk = NULL; dgnd = NULL;
    /////////////////////////////////////////////////////////////
    c_p_c = NULL; sampled = NULL; mode_reg = NULL; sdisel = NULL;
    ////////////////////////////////////////////
    nbits = 12; controlw = NULL;conv_reg = NULL;
	held  = NULL;  shut     = NULL; intref     = NULL; interef = NULL;
	/////////////////////////////////////////////////////////////////////////////////////////////////////
    t1  =  0E9; t2  = 120E9; t3  = 120E9; t4  = 150E9; t5  =   0E9; t6  =  80E9; t7  = 100E9; t8  = 80E9;
    t9  =  0E9; t10 = 200E9; t11 =   5E6; t12 =  25E9; t13 = 200E9; t14 = 100E9; t15 = 100E9; t16 =  5E9;
    t17 = 50E9; t18 = 180E9; t19 = 100E9; t20 = 160E9; t21 = 100E9; t22 = 240E9; t23 = 260E9;
    ///////////////
    tCONV = 75E7;
    tQ=0;}
MAX190_1::~MAX190_1() {}
INT MAX190_1::isanalog (CHAR *pinname)
{
	if (strnicmp(pinname,  "AGND",      4) == 0)                //PIN2
        return TRUE;
	else if (strnicmp(pinname,  "AIN+",         4) == 0)        //PIN3
	    return TRUE;
	else if (strnicmp(pinname,  "AIN-",         4) == 0)        //PIN4
	    return TRUE;
	else if (strnicmp(pinname,  "REF",          4) == 0)        //PIN5
	    return TRUE;
	else
	    return FALSE;
}
INT MAX190_1::isdigital (CHAR *pinname)
{
    if (strnicmp(pinname,  "$PD$",      4) == 0)                //PIN1
	    return TRUE;
    else if (strnicmp(pinname,  "BIP",          3) == 0)        //PIN8
	    return TRUE;
    else if (strnicmp(pinname,  "$BUSY$",       6) == 0)        //PIN9
	    return TRUE;
    else if (strnicmp(pinname,  "D0",           5) == 0)        //PIN10
	    return TRUE;
	else if (strnicmp(pinname,  "D1",           5) == 0)        //PIN11
	    return TRUE;
	else if (strnicmp(pinname,  "DGND",         4) == 0)        //PIN12
	    return TRUE;
	else if (strnicmp(pinname,  "D2",           6) == 0)        //PIN13
	    return TRUE;
	else if (strnicmp(pinname,  "D3",           6) == 0)        //PIN14
	    return TRUE;
	else if (strnicmp(pinname,  "D4",           2) == 0)        //PIN15
	    return TRUE;
	else if (strnicmp(pinname,  "D5",           8) == 0)        //PIN16
	    return TRUE;
	else if (strnicmp(pinname,  "D6",          10) == 0)        //PIN17
	    return TRUE;
	else if (strnicmp(pinname,  "D7",           7) == 0)        //PIN18
	    return TRUE;
	else if (strnicmp(pinname,  "$RD$",         4) == 0)        //PIN19
	    return TRUE;
	else if (strnicmp(pinname,  "$CS$",         4) == 0)        //PIN20
	    return TRUE;
	else if (strnicmp(pinname,  "HBEN",         4) == 0)        //PIN21
	    return TRUE;
	else if (strnicmp(pinname,  "PAR",          3) == 0)        //PIN22
	    return TRUE;
	else if (strnicmp(pinname,  "CLK/SCLK",     8) == 0)        //PIN23
	    return TRUE;
	else
	    return FALSE;
}
//////////////////////////////////
//////// COMMON CIRCUIT //////////
/////////////////////////////////////////////////////////////
VOID MAX190_1::runctrl (RUNMODES mode) { if ((mode == RM_SUSPEND) && (SDSSW == TRUE))
{ cheight = statuspopup->getcharheight(); cwidth  = statuspopup->getcharwidth(); VARWINDOW(); statuspopup->repaint(); } }
VOID MAX190_1::actuate (REALTIME time, ACTIVESTATE newstate) {}
BOOL MAX190_1::indicate (REALTIME time, ACTIVEDATA *newstate){ return FALSE; };
//////////////////////////////////
////////// SPICECIRCUIT //////////
/////////////////////////////////////////////////////////////
VOID MAX190_1::setup (IINSTANCE *iinstance, ISPICECKT *ispiceckt)
{ instance = iinstance; spiceckt = ispiceckt;
	ainP        =   instance->getspicenode        ("AIN+,ain+",    TRUE);
	ainN        =   instance->getspicenode        ("AIN-,ain-",    TRUE);
	ref         =   instance->getspicenode        ("REF,ref",      TRUE);
    agnd        =   instance->getspicenode        ("AGND,agnd",    TRUE); }
VOID MAX190_1::accept (REALTIME time, DOUBLE *rhs)
{   DOUBLE vpos = rhs[ainP];
	DOUBLE vneg = rhs[ainN];
	DOUBLE ag   = rhs[agnd];
	// scale value of differential input voltage (VIN+ - VIN-)
	// variable 'input' passes data to the dsimckt for digital processing
	// becouse of embedded lisa model for vref modes there is no need for extra spice code
	// handle max190 191 bipolar or
	if (UNI_BIP == TRUE)
	{
	    DOUBLE vref  = (ref != -1) ? rhs[ref] : 1.0;
	    input = ((vpos - vneg) / (vref-ag));
	}
	if (UNI_BIP == FALSE)
	{
	    DOUBLE vref  = (ref != -1) ? rhs[ref] : 1.0;
	    input = ((vpos - vneg) / (vref));
	}
}
VOID MAX190_1::dcload (REALTIME time, SPICEMODES mode, DOUBLE *oldrhs, DOUBLE *newrhs) {}
VOID MAX190_1::acload (SPICEFREQ omega, DOUBLE *rhs, DOUBLE *irhs) {}
VOID MAX190_1::trunc  (REALTIME time,  REALTIME *newtimestep) {}
//////////////////////////////////
////////// DSIMCIRCUIT ///////////
/////////////////////////////////////////////////////////////
VOID MAX190_1::setup (IINSTANCE *iinstance, IDSIMCKT *idsimckt)
{ instance    =   iinstance; dsimckt     =   idsimckt;
    ////////////////////////////////////////////////////////////////////////
	SDSSW               =   instance->getboolval    ("SDSSW",            0);// switch debug window off
    ////////////////////////////////////////////////////////////////////////
	//                   :: DEBUG POPUP STRUCTURE ::                      //
	////////////////////////////////////////////////////////////////////////
	if (SDSSW ==TRUE)
	{
	    cps                 =   new CREATEPOPUPSTRUCT;
	    cps->type           =   PWT_STATUS;
	    cps->caption        =   "MAX 190 STATUS WINDOW";
	    cps->flags          =   PWF_HIDEONANIMATE | PWF_VISIBLE;
	    cps->height         =   30;
	    cps->width          =   45;
	    statuspopup         =   (ISTATUSPOPUP *)instance->createpopup(cps);
	}
    /////////////////
	// common pins //
	/////////////////////////////////////////////////////////////////
	rd          = instance->getdsimpin("$RD$,$rd$",            TRUE);
	cs          = instance->getdsimpin("$CS$,$cs$",            TRUE);
	hben        = instance->getdsimpin("HBEN,hben",            TRUE);
	par         = instance->getdsimpin("PAR,par",              TRUE);
	pd          = instance->getdsimpin("$PD$,$PD$",            TRUE);
	bip         = instance->getdsimpin("BIP,bip",              TRUE);
	busy        = instance->getdsimpin("$BUSY$,$busy$",        TRUE);
    dgnd        = instance->getdsimpin("DGND,dgnd",            TRUE);
    clk_sclk    = instance->getdsimpin("CLK/SCLK,clk/sclk",    TRUE);
    /////////////////////////////////////////////////////////////////
	// serial mode bus //
	/////////////////////////////////////////////////////
    SER_BUS		=   instance->getbuspin("D,d",4,3, TRUE);
	SER_BUS->setstates(SHI,SLO,FLT);
	SER_BUS->settiming(1E9,1E9,5E10);
	///////////////////////
    // parallel mode bus //
    /////////////////////////////////////////////////////
    DP_LSW		=   instance->getbuspin("D,d",0,4, TRUE);
	DP_LSW->setstates(SHI,SLO,FLT);
	DP_LSW->settiming(t19,t19,t19/2);
    /////////////////////////////////////////////////////
    DP_MSW		=   instance->getbuspin("D,d",4,4, TRUE);
	DP_MSW->setstates(SHI,SLO,FLT);
	DP_MSW->settiming(t19,t19,t19/2);
	//////////////////
    par->invert();  // PAR  is active low
    cs->invert();   // cs   is active low
    rd->invert();   // RD   is active low
    pd->invert();   // PD   is active low
    //////////////////
}
VOID MAX190_1::simulate (ABSTIME time, DSIMMODES dmode)
{
	if (dmode == DSIMBOOT )
	{
	    instance->log("MAX190_1 model is running ");
	    // initialise chips registers timings and domains tasks
	    tQ = 0;
	    tCONV = 0;
	    donecycles = 0;
	    DP_LSW->drivetristate(time);
	    DP_MSW->drivetristate(time);
	    SER_BUS->drivetristate(time);
	}
	else if (dmode == DSIMSETTLE)
	{}
	else
	{
	    // choose bipolar
	    if (bip->isactive())
	    {
	       UNI_BIP = TRUE;
	    }
	    // choose unipolar
        else if(bip->isinactive())
        {
           UNI_BIP = FALSE;
        }
		// power down
		if (pd->isinactive())
	    {
	        //  Power-Down Input. A logic low at PD deactivates the ADC only the bandgap reference is active. A logic
            //  high selects normal operation, internal-reference compensation mode. An open-circuit condition selects
            //  normal operation, external-reference compensation mode.
	    }
	    else if (pd->isactive())
	    {
	        EVENTID eventid = 0 ;
	        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
            // choose parallel serial mode routines set's

	        /////////////////
	        // SERIAL MODE //
	        ////////////////////
	        if (par->isactive())
	        {
	            EVENTID eventid = 0 ;
    	        if (cs->isinactive())            //  CS = high in serial mode forces SCLKOUT, SSTRB, and DOUT into a high-impedance state.
	            {
	                // reset the convertion timer;
	                tQ = time + tCONV;
	                // drive 3bit bus tristate
	                SER_BUS->drivetristate(time);
	            }
	            if (clk_sclk->isposedge() && rd->isinactive())
	            {
	                SER_BUS->drivetristate(time);
	                dsimckt->setbreak(time);
	                eventid |= MAX_SERHOLD;
	            }
	            if ((clk_sclk->isnegedge() || clk_sclk->isinactive()) && (sampled == TRUE))
	            {
	                if (cs->isnegedge())
	                {
	                    SER_BUS->drivebitstate(time, 0, FSTATE);
	                    SER_BUS->drivebitstate(time+t12, 1, FSTATE);
	                    if (rd->isactive())
	                    {
	                        if (hben->isinactive())
	                        { // CONVERSION ONLY D6/SCLKout OUTPUT MODE
	                            SER_BUS->drivebitstate(time, 0, FSTATE); // SET BUS PIN 2 {D6/SCLKout TO FALSE}
	                            SER_BUS->drivebitstate(time, 1, FSTATE); // SET BUS PIN 3 {D7/DOUT}   TO FALSE} // NOT SURE OF BIT SETTING YET STILL TO TEST
	                            SER_BUS->drivebitstate(time, 2, FSTATE);
	                            do
	                            {
	                                if (clk_sclk->isnegedge()) // ALLOWS LEADING ZERO BY MISSING A CLOCK POS CYCLE
	                                {
	                                    SER_BUS->drivebitstate(time+(t20/2), 2, FSTATE); // SET BUS PIN 2 {D6/SCLKout TO FALSE}
	                                }
	                                dsimckt->setcallback(time, this, eventid);
	                                eventid |= MAX_SERccCONVERT;
	                                if (clk_sclk->isposedge())
                                    {
                                        SER_BUS->drivebitstate(time+(t20/2),2, TSTATE); // TO FIX TO THE CORRECT TIME DOMAIN
                                    }

	                            }while(donecycles != 12); //ADJUST TO ADD PADDING
	                            busy->setstate (time, 0 , TSTATE);
	                        }
	                        else if (hben->isactive())
	                        { // CONTINUIOUS CLOCK MODE  PROVIDED CS IS LOW AND HBEN IS HIGH
	                            if (cs->isactive())
	                            {
	                                if (clk_sclk->isnegedge()) // ALLOWS LEADING ZERO BY MISSING A CLOCK POS CYCLE
	                                {
	                                    SER_BUS->drivebitstate(time+(t20/2), 2, FSTATE); // SET BUS PIN 2 {D6/SCLKout TO FALSE}
	                                }
	                                eventid |= MAX_SERcdCONVERT;
	                            }
	                            dsimckt->setcallback(time, this, eventid);
	                        }
	                    }
	                    else if (rd->isinactive())
	                    {
	                        SER_BUS->drivebitstate(time, 0, FLT); // SET BUS PIN 2 {D6/SCLKout TO FALSE}
	                        SER_BUS->drivebitstate(time, 1, FLT); // SET BUS PIN 3 {D7/DOUT}   TO FALSE} // NOT SURE OF BIT SETTING YET STILL TO TES
	                    }
	                }
	            }
	            if (hben->isinactive())   // use sercc{clock active in CONVERSION ONLY } timings
	            {
	                if (eventid != 0) dsimckt->setcallback(time + (eventid & MAX_SERccCONVERT)? (tQ): 1, this, eventid) ;
	            }
	            else if (hben->isactive())   // use sercd{continuious clock mode}timings {if cs is low }
	            {
	                if (eventid != 0) dsimckt->setcallback(time + (eventid & MAX_SERcdCONVERT)? (tQ): 1, this, eventid) ;
	            }
	            ////////////////////////////////////////////////////////////////////
	            //  CS      = negedge   falling edge of CS starts a conversion in serial mode.
	            //  RD      = low       enables SCLKOUT and SSTRB when CS is low.
	            //  RD      = high      forces SCLKOUT and SSTRB into a high-impedance state.
                //  HBEN    = low       enables SCLKOUT to operate during the conversion only,
                //  HBEN    = high      enables SCLKOUT to operate continuously, provided CS is low.
	            ////////////////////////////////////////////////////////////////////////////
	            donecycles = 0; // RESET THE DONE CYCLES COUNTER //
	        }
	        ///////////////////
	        // PARALLEL MODE //
	        ///////////////////////////
	        else if (par->isinactive())
	        {
	            EVENTID eventid = 0 ;
	            //  CS      = low   must be low for the ADC to recognize RD and HBEN inputs
	            //  RD      = low   a low signal starts a conversion when CS and HBEN are low (memory mode)
	            //                  also enables the outputs when CS is low.
	            //  HBEN    = high  multiplexes the 4 MSBs of the conversion result into the lower bit outputs.
	            //                  also disables conversion starts.
	            //  HBEN    = low   places the 8 LSBs onto the data bus.
	            if ((clk_sclk->isnegedge()) && (rd->isnegedge()))   //start convertion
	            {
	                if (hben->isactive())
	                {
	                   eventid |= MAX_PAR4MODE;
	                }
	                if (hben->isinactive())
	                {
	                   eventid |= MAX_PAR8MODE;
	                }
	            }
	            if ((cs->isinactive()) && (hben->isactive()))  //disable conversion starts {in upper 4 bit mode as selected by hben pin}
	            {
	                if (eventid != 0) dsimckt->setcallback(time + (eventid & MAX_PARCONVERT)? (tQ): 1, this, eventid);
	            }
	        }
	    }
	}
}
VOID MAX190_1::callback (ABSTIME time, EVENTID eventid)
{
	LONG min, max;
	if (eventid & MAX_SERHOLD)
    {
		hold = input;
		sampled = TRUE;
	}
	else if (eventid & MAX_SERccCONVERT)
    {
        // CONVERSION ONLY CLOCK MODE


        // TO ADD DATA OUTPUT PIN TRASITIONS {THERE IS ALSO A LEADING ZERO AND PADDING BITS TO ADD HERE}

        /*  // TO ADJUST TO ALLOW 12 BITS TO BE INDIVIDUALY READ FROM THE 'hold' VARIABLE {PER DONECYCLE}
        min = 0;
        max = (1<<nbits) - 1;
        conv_reg = (long) ceil(hold * max);
        if (conv_reg < min)         conv_reg = min;
        else if (conv_reg > max)    conv_reg = max;
        */

        donecycles++;               // ADD 1 TO THE CYCLE COUNTER
        if (donecycles>=13)         // ALWAYS ADD A GREATER THAN OR EQUAL TOO QUALIFER NEVER JUST  ==   THIS IS NO GOOD
        {
            sampled = FALSE;        // SET SAMPLED AS FALSE TO FLAG CONVERTER READY FOR NEXT
        }
		else // CALLBACK HERE TO STREAM  THE DATA  TILL 12 CYCLES  THEN DONT
		{
		    dsimckt->setcallback(time, this, eventid);
		}
	}
	else if (eventid & MAX_SERcdCONVERT)
    {
        // CONTINUIOUS CLOCK MODE  PROVIDED CS IS LOW
        // STILL TO ADD {EASY NOW  THOU.....}
        /*
        min = 0;
        max = (1<<numbits) - 1;
        conv_reg = (long) ceil(hold * max);
        if (conv_reg < min)         conv_reg = min;
        else if (conv_reg > max)    conv_reg = max;
		sampled = FALSE;
		*/
	}
    if (eventid & MAX_PARHOLD)
    {
        hold = input;
		sampled = TRUE;
	}
	else if (eventid & MAX_PARCONVERT)
    {
	}
	else if (eventid & MAX_PAR8MODE)
	{
	}
	else if (eventid & MAX_PAR4MODE)
	{
	}

}

VOID MAX190_1::VARWINDOW()
{
}



