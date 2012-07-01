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
#include "DP_POT.H"  /////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C"  EXPORT IMIXEDMODEL * createmixedmodel (CHAR *device, ILICENCESERVER *ils)
{
    ///////////////////////////
	IMIXEDMODEL * model = NULL;
    ///////////////////////////////////////////////////////////////
	if (strnicmp(device, "DP_POTXXXX", 6) == 0) model = new DP_POT();
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (model != NULL) { ils->authorize(PRO_KEY) || ils->authorize(LITE_KEY); } return (IMIXEDMODEL  *) model;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////
extern "C" EXPORT VOID deletemixedmodel (IMIXEDMODEL * model) { delete(IMIXEDMODEL *) model; }

///////////////////////////
// : CLASS CONSTRUCTOR : //
///////////////////////////
DP_POT::DP_POT (VOID)
{
    /////////////////////
    //DIRECTOR'S NULLS //
    /////////////////////////////////////////////////
    instance = NULL; spiceckt = NULL; dsimckt = NULL;
    /////////////////////////////////////////////////

    //////////////////////////
    // : TIMING CONSTANTS : //
    //////////////////////////
    tdda=tcc=bdel=ddel=sdel=abdel=addel=asdel=0;
    //////////////////////////

    ///////////////
    // : BOOLS : //
    //////////////////////////////////////
    SDSSW=HOA=UPDATESTATE=ebus=FALSE;
    //////////////////////////////////////

    //////////////
    // : INTS : //
    //////////////////////////////////////
    y=width=height=Xpots=Xpotssp=0; BTE=8;
    //////////////////////////////////////

    ////////////////
    // : DWORDS : //
    ////////////////////////
    vpotid = w = G = 0x0000;
    ////////////////////////
}
////////////////////
DP_POT::~DP_POT() {}
////////////////////////////////////
INT DP_POT::isanalog (CHAR *pinname)
{
         // SETUP THE ANALOGUE PINS USED IN THE SPICE MODEL SECTION
         //////////////////////////////////////////////////////////////////////////////////////////////////////////
         if (strnicmp(pinname, "L1",  2) == 0) return TRUE; else if (strnicmp(pinname, "L2",  2) == 0) return TRUE;
    else if (strnicmp(pinname, "L3",  2) == 0) return TRUE; else if (strnicmp(pinname, "L4",  2) == 0) return TRUE;
    else if (strnicmp(pinname, "L5",  2) == 0) return TRUE; else if (strnicmp(pinname, "L6",  2) == 0) return TRUE;
    else if (strnicmp(pinname, "L7",  2) == 0) return TRUE; else if (strnicmp(pinname, "L8",  2) == 0) return TRUE;
    else if (strnicmp(pinname, "L9",  2) == 0) return TRUE; else if (strnicmp(pinname, "L10", 3) == 0) return TRUE;
    else if (strnicmp(pinname, "L11", 3) == 0) return TRUE; else if (strnicmp(pinname, "L12", 3) == 0) return TRUE;
    else if (strnicmp(pinname, "L13", 3) == 0) return TRUE; else if (strnicmp(pinname, "L14", 3) == 0) return TRUE;
    else if (strnicmp(pinname, "L15", 3) == 0) return TRUE; else if (strnicmp(pinname, "L16", 3) == 0) return TRUE;
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else if (strnicmp(pinname, "H1",  2) == 0) return TRUE; else if (strnicmp(pinname, "H2",  2) == 0) return TRUE;
	else if (strnicmp(pinname, "H3",  2) == 0) return TRUE; else if (strnicmp(pinname, "H4",  2) == 0) return TRUE;
    else if (strnicmp(pinname, "H5",  2) == 0) return TRUE; else if (strnicmp(pinname, "H6",  2) == 0) return TRUE;
    else if (strnicmp(pinname, "H7",  2) == 0) return TRUE; else if (strnicmp(pinname, "H8",  2) == 0) return TRUE;
    else if (strnicmp(pinname, "H9",  2) == 0) return TRUE; else if (strnicmp(pinname, "H10", 3) == 0) return TRUE;
    else if (strnicmp(pinname, "H11", 3) == 0) return TRUE; else if (strnicmp(pinname, "H12", 3) == 0) return TRUE;
    else if (strnicmp(pinname, "H13", 3) == 0) return TRUE; else if (strnicmp(pinname, "H14", 3) == 0) return TRUE;
	else if (strnicmp(pinname, "H15", 3) == 0) return TRUE; else if (strnicmp(pinname, "H16", 3) == 0) return TRUE;
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    else if (strnicmp(pinname, "W1",  2) == 0) return TRUE; else if (strnicmp(pinname, "W2",  2) == 0) return TRUE;
	else if (strnicmp(pinname, "W3",  2) == 0) return TRUE; else if (strnicmp(pinname, "W4",  2) == 0) return TRUE;
	else if (strnicmp(pinname, "W5",  2) == 0) return TRUE; else if (strnicmp(pinname, "W6",  2) == 0) return TRUE;
	else if (strnicmp(pinname, "W7",  2) == 0) return TRUE; else if (strnicmp(pinname, "W8",  2) == 0) return TRUE;
	else if (strnicmp(pinname, "W9",  2) == 0) return TRUE; else if (strnicmp(pinname, "W10", 3) == 0) return TRUE;
	else if (strnicmp(pinname, "W11", 3) == 0) return TRUE; else if (strnicmp(pinname, "W12", 3) == 0) return TRUE;
	else if (strnicmp(pinname, "W13", 3) == 0) return TRUE; else if (strnicmp(pinname, "W14", 3) == 0) return TRUE;
	else if (strnicmp(pinname, "W15", 3) == 0) return TRUE; else if (strnicmp(pinname, "W16", 3) == 0) return TRUE;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else return FALSE;
}
//////////////////////////////////////
INT DP_POT::isdigital (CHAR *pinname)
{
         // SETUP THE DIGITAL PINS USED IN THE DSIMCKT MODEL SECTION
         ////////////////////////////////////////////////////////////////////////////////////////////////////////////
         if (strnicmp(pinname, "D0",   2) == 0) return TRUE; else if (strnicmp(pinname, "D1",   2) == 0) return TRUE;
	else if (strnicmp(pinname, "D2",   2) == 0) return TRUE; else if (strnicmp(pinname, "D3",   2) == 0) return TRUE;
	else if (strnicmp(pinname, "D4",   2) == 0) return TRUE; else if (strnicmp(pinname, "D5",   2) == 0) return TRUE;
	else if (strnicmp(pinname, "D6",   2) == 0) return TRUE; else if (strnicmp(pinname, "D7",   2) == 0) return TRUE;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else if (strnicmp(pinname, "BD0",  3) == 0) return TRUE; else if (strnicmp(pinname, "BD1",  3) == 0) return TRUE;
	else if (strnicmp(pinname, "BD2",  3) == 0) return TRUE; else if (strnicmp(pinname, "BD3",  3) == 0) return TRUE;
	else if (strnicmp(pinname, "BD4",  3) == 0) return TRUE; else if (strnicmp(pinname, "BD5",  3) == 0) return TRUE;
	else if (strnicmp(pinname, "BD6",  3) == 0) return TRUE; else if (strnicmp(pinname, "BD7",  3) == 0) return TRUE;
	else if (strnicmp(pinname, "BD8",  3) == 0) return TRUE; else if (strnicmp(pinname, "BD9",  3) == 0) return TRUE;
	else if (strnicmp(pinname, "BD10", 4) == 0) return TRUE; else if (strnicmp(pinname, "BD11", 4) == 0) return TRUE;
	else if (strnicmp(pinname, "BD12", 4) == 0) return TRUE; else if (strnicmp(pinname, "BD13", 4) == 0) return TRUE;
	else if (strnicmp(pinname, "BD14", 4) == 0) return TRUE; else if (strnicmp(pinname, "BD15", 4) == 0) return TRUE;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    else if (strnicmp(pinname, "SEL1", 4) == 0) return TRUE; else if (strnicmp(pinname, "SEL2", 4) == 0) return TRUE;
    else if (strnicmp(pinname, "SEL3", 4) == 0) return TRUE; else if (strnicmp(pinname, "SEL4", 4) == 0) return TRUE;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else if (strnicmp(pinname, "CLK",  3) == 0) return TRUE; else if (strnicmp(pinname, "RST",  3) == 0) return TRUE;
    else if (strnicmp(pinname, "HOLD", 4) == 0) return TRUE; else if (strnicmp(pinname, "LOAD", 4) == 0) return TRUE;
    else if (strnicmp(pinname, "SHDN", 4) == 0) return TRUE;
    else if (strnicmp(pinname, "EEPS", 4) == 0) return TRUE; else if (strnicmp(pinname, "EEPR", 4) == 0) return TRUE;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    else return FALSE;
    //////////////////
}
/////////////////////////////////////
VOID DP_POT::runctrl (RUNMODES mode)
{
    if ((mode == RM_START) | (mode == RM_SUSPEND) | (mode == RM_STEPTIME) | (mode == RM_ANIMATE))
    {
        if ((mode == RM_SUSPEND) | (mode == RM_STEPTIME) | (mode == RM_ANIMATE))
        {
            if(ESEE)
            {
                if(SAVE)
                {
                    for(y=0;y<=Xpots;)
                    {
                        savedatadword[y] = eeprom[y]= savep[y];
                        y++;
                    }
                    filename = instance->getstrval("EEPROM"); // GET EEPROM FILE NAME STRING
        		    file = CreateFile(filename, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL); // BUILD FILE STRUCTUR
        		    bResult = WriteFile(file, &eeprom, 36, &nBytesRead, NULL); // WRITE THE FILE TO DISK
        		    if (!bResult) instance->fatal("Could not write EEPROM file"); // CHECK FOR FATAL {READONLY LOCKED FILE THE SAME NAME IN DESIGN DIR??}
            		CloseHandle(file);  // CLOSE THE FILE TO READ/WRITE AND CLEAN UP THE HANDLE
        		    instance->log("eeprom save was triggered"); // LOG TO DEBUG EEPROM GLOBAL SAVE TRIGGERED
        		    if(SDSSW) updatestatus = TRUE; // IS SHOW DEBUG STATUS WINDOW ENABLED THEN UPDATE IT WITH NEW DATA{THE CHECK ENSURES NO UAE WHEN WINDOW IS DISABLED
         		    SAVE = FALSE; // RESET SAVE DATA EVENT FLAG
                }
            }
        }
        // IF UPDATE STATUS AND SHOW DEBUG STATUS WINDOW THEN UPDATE THE DATA IN IT AND RESET UPDATESTATUS FLAG
        if((updatestatus) & (SDSSW))
        {
            height = statuspopup->getcharheight();  // APPLY HEIGHT SETTING
            width  = statuspopup->getcharwidth();   // APPLY WIDTH SETTING {SO YOU CAN CHANGE THE FONT ETC FROM A RIGHT CLICK ON THE STATUS POPUP}
            STATUSPOPUP(); // CALL THE ROUTINE TO REDRAW THE DATA
            updatestatus = FALSE;  // RESET STATUS POPUP UPDATE FLAG
        }
    }
}
VOID DP_POT::actuate (REALTIME stime, ACTIVESTATE newstate) {}
BOOL DP_POT::indicate (REALTIME stime, ACTIVEDATA *newstate){ return FALSE; }; // NO INDICATE USED SO RETURN FALSE HERE
VOID DP_POT::setup (IINSTANCE *iinstance, ISPICECKT *ispiceckt)
{
    ///////////////////////////////////////////
    CHAR *TRIMl,*TRIMw,*TRIMh,*TRIMv,*TRIMinit;
    ///////////////////////////////////////////
    instance = iinstance; spiceckt = ispiceckt;
    ///////////////////////////////////////////
    ebus = instance->getboolval("16BUS",  0);   // GET 16 BIT BUS ACTIVE OR NOT SETTING TRUE/FALSE
    SDSSW = instance->getboolval("SDSSW", 0);   // GET SHOW DSIM STATUS WINDOW TRUE/FALSE
	///////////////////////////////////////////
	HOA = instance->getboolval("HOA",    0);    // GET HIDE DSIM STATUS WINDOW ON ANIMATE TRUE/FALSE
    //////////////////////////////////////////////////////
    Xpots = (INT) atol(instance->getstrval("XPOTS", "1"));   // number of pots in use {set from isis part}
    Xpotssp = Xpots; Xpots-=1;
    /////////////////////////////////////////////////////////////////////////////////////
    if (Xpots>=16)instance->error ("BAD XPOTS VALUE, RESET TO 15 OR BELOW {range 1-16 ");
    /////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////
    BTE = atoi(instance->getstrval("BTE","10"));
	////////////////////////////////////////////
	switch (BTE) {
        case 4: w=0x000F; break; case 5: w=0x001F; break; case 6: w=0x003F; break; case 7: w=0x007F; break;
        case 8: w=0x00FF; break; case 9: w=0x01FF; break; case 10:w=0x03FF; break; case 11:w=0x07FF; break;
        case 12:w=0x0FFF; break; case 13:w=0x1FFF; break; case 14:w=0x3FFF; break; case 15:w=0x7FFF; break;
        case 16:w=0xFFFF; break;
    }
    GLOBALINIT = (DWORD) (instance->gethexval("GLOBALINIT",  0x0080));
    ESEE    = instance->getboolval("ESEE",    0);
    if(ESEE)
    {
        filename = instance->getstrval("EEPROM");
        file = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
        bResult = ReadFile(file, &eeprom, 36, &nBytesRead, NULL) ;
        // Check for the end of the file.
        if (!bResult) {
            instance->log("EEPROM FILE NOT PRESENT DEFAULTS IN USE");
            file = CreateFile(filename, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL);
            bResult = WriteFile(file, &eeprom, 36 , &nBytesRead, NULL);
            if (!bResult) instance->fatal("Could not create EEPROM file");
        }
        CloseHandle(file);
        // UPDATE SAVEDATADWORD WITH EEPROM DATA RETRIEVED FROM THE FILE
        for(y=0;y<=Xpots;)
        { savedatadword[y] = eeprom[y]; y++;}
    }
    // CONSTRUCT THE DSIM STATUS PANEL
    if (SDSSW)
	{
	    ////////////////////////////////////////////////
        sprintf(STATTITLE,"%2.0d-BIT STEP DP_POT", BTE);  // FILL THE TITLE OF THE WINDOW WITH THIS STRING
        ////////////////////////////////////////////////
	    ////////////////////////////
	    cpd = new CREATEPOPUPSTRUCT; cpd->id=0; cpd->type = PWT_STATUS;
        /////////////////////////
	    cpd->caption = STATTITLE; for(y=2;y<=((Xpotssp)*4);) {cpd->height = y; y++;} cpd->width   = 34;
	    // CHECK FOR HIDE ON ANIMATE AND APPLY THE STATE TO THE POPUP STRUCTURE INIT
	    if (HOA) cpd->flags =  PWF_VISIBLE | PWF_AUTOREFRESH | PWF_HIDEONANIMATE;
	    if (!HOA) cpd->flags = PWF_VISIBLE | PWF_AUTOREFRESH ;
        statuspopup  = (ISTATUSPOPUP *)instance->createpopup(cpd);  // BIND THE STRUCTURE TO THE STATUS POPUP EVENT HANDLE
	    //////////////////////////////////////////////////////////
	}
    ///////////////////
    for (y=0;y<=Xpots;)
    {
        /////////
        switch(y)
        {
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            // set the case variable data assigned to each runtime variable, node and spice circuit pins  assignation holder //
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////////////////////
            case 0:  TRIMl="L1";  TRIMw="W1";  TRIMh="H1";  TRIMv="POTVAL1";  TRIMinit = "INITVAL1";   break;
            case 1:  TRIMl="L2";  TRIMw="W2";  TRIMh="H2";  TRIMv="POTVAL2";  TRIMinit = "INITVAL2";   break;
            case 2:  TRIMl="L3";  TRIMw="W3";  TRIMh="H3";  TRIMv="POTVAL3";  TRIMinit = "INITVAL3";   break;
            case 3:  TRIMl="L4";  TRIMw="W4";  TRIMh="H4";  TRIMv="POTVAL4";  TRIMinit = "INITVAL4";   break;
            case 4:  TRIMl="L5";  TRIMw="W5";  TRIMh="H5";  TRIMv="POTVAL5";  TRIMinit = "INITVAL5";   break;
            case 5:  TRIMl="L6";  TRIMw="W6";  TRIMh="H6";  TRIMv="POTVAL6";  TRIMinit = "INITVAL6";   break;
            case 6:  TRIMl="L7";  TRIMw="W7";  TRIMh="H7";  TRIMv="POTVAL7";  TRIMinit = "INITVAL7";   break;
            case 7:  TRIMl="L8";  TRIMw="W8";  TRIMh="H8";  TRIMv="POTVAL8";  TRIMinit = "INITVAL8";   break;
            case 8:  TRIMl="L9";  TRIMw="W9";  TRIMh="H9";  TRIMv="POTVAL9";  TRIMinit = "INITVAL9";   break;
            case 9:  TRIMl="L10"; TRIMw="W10"; TRIMh="H10"; TRIMv="POTVAL10"; TRIMinit = "INITVAL10";  break;
            case 10: TRIMl="L11"; TRIMw="W11"; TRIMh="H11"; TRIMv="POTVAL11"; TRIMinit = "INITVAL11";  break;
            case 11: TRIMl="L12"; TRIMw="W12"; TRIMh="H12"; TRIMv="POTVAL12"; TRIMinit = "INITVAL12";  break;
            case 12: TRIMl="L13"; TRIMw="W13"; TRIMh="H13"; TRIMv="POTVAL13"; TRIMinit = "INITVAL13";  break;
            case 13: TRIMl="L14"; TRIMw="W14"; TRIMh="H14"; TRIMv="POTVAL14"; TRIMinit = "INITVAL14";  break;
            case 14: TRIMl="L15"; TRIMw="W15"; TRIMh="H15"; TRIMv="POTVAL15"; TRIMinit = "INITVAL15";  break;
            case 15: TRIMl="L16"; TRIMw="W16"; TRIMh="H16"; TRIMv="POTVAL16"; TRIMinit = "INITVAL16";  break;
            /////////////////////////////////////////////////////////////////////////////////////////////////
        }
        /////////////////////////////////////////////////
        POTVAL[y] = instance->getnumval(TRIMv,  1000); // GET POT VALUE END TO END
        if(POTVAL[y] ==  0) instance->error("hey  you have choosen a value of zero for POT  %d are you playing with super conductors ???",y);
        if(POTVAL[y] <= 99) instance->error("hey  you have choosen a value of less than 100R for POT  %d ??? you cant do this min value = 100R",y);
        ///////////////////////////////////////////////////////////////////
        INITVAL[y]       = (DWORD) (instance->gethexval(TRIMinit,    0)); // GET INITVAL IN ISIS PART MENU
        ///////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////
        // this. spice circuit model  node pin assign //
        ////////////////////////////////////////////////
        L[y]  = instance->getspicenode(TRIMl, TRUE);
        W1[y] = instance->getspicenode(TRIMw, TRUE);
        W2[y] = instance->getspicenode(TRIMw, TRUE);
        H[y]  = instance->getspicenode(TRIMh, TRUE);
        ///////////////////////////////////////////
        /////////////////////////////////////////////////////////////////
        // pot lower Resistor allocate model node net spice model pins //
        /////////////////////////////////////////////////////////////////////////////////////////////
        nodeLL[y]  = spiceckt->allocsmp(L[y],  L[y]);  nodeLW[y]  = spiceckt->allocsmp(W1[y], W1[y]);
        nodeLLW[y] = spiceckt->allocsmp(L[y],  W1[y]); nodeLWL[y] = spiceckt->allocsmp(W1[y],  L[y]);
        /////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////
        // pot upper Resistor allocate model node net spice model pins //
        //////////////////////////////////////////////////////////////////////////////////////////////
        nodeHH[y]  = spiceckt->allocsmp(H[y],  H[y]);  nodeHW[y]  = spiceckt->allocsmp(W2[y],  W2[y]);
        nodeHWH[y] = spiceckt->allocsmp(W2[y], H[y]);  nodeHHW[y] = spiceckt->allocsmp(H[y],   W2[y]);
        //////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////
        TRIMl = NULL; TRIMw = NULL; TRIMh = NULL; TRIMv = NULL; TRIMinit = NULL;  // null case holders each pass.. avoids overflow's
        ////////////////////////////////////////////////////////////////////////
        y++; // increment routine pass counter
        ///////
    }
    if(ESEE)
    {   // POT VALUE INITIALISATION RULES AND APPLY
        if (GLOBALINIT>=(w+1))
        {
            instance->log("your global init value is a higher order number than the bit lenght setting allow's !");
            instance->log("edit the isis parts menus and change the bte setting or the global initvalue to a more sensible one");
            instance->message(" YOU HAVE DP_POT VALUES INITS OUT OF RANGE ERRORS STUDY THE SIMULATION LOG");
        }
        for(y=0;y<=Xpots;)
        {
            if (INITVAL[y]>=(w+1)) { instance->log(" your initvalues for pot %d is outwith the bit lenght setting of the isis part",y+1);
                                     instance->log(" edit the isis part and change the initval setting to be in bounds");
                                     instance->message(" YOU HAVE DP_POT VALUES INITS OUT OF RANGE ERRORS STUDY THE SIMULATION LOG");}
            if ((INITVAL[y]==0x0000)&(GLOBALINIT==0x0000)) { start[y]=fifo[y]=in[y]=savedatadword[y]; }
            if ((INITVAL[y]!=0x0000)&(GLOBALINIT==0x0000)) { start[y]=fifo[y]=in[y]=INITVAL[y]; }
            if ((INITVAL[y]==0x0000)&(GLOBALINIT!=0x0000)) { start[y]=fifo[y]=in[y]=GLOBALINIT; }
            if ((INITVAL[y]!=0x0000)&(GLOBALINIT!=0x0000)) // catch exception
            {
                start[y]=fifo[y]=in[y]=GLOBALINIT;
                if (INITVAL[y]!=0x0000) { start[y]=fifo[y]=in[y]=INITVAL[y];}
            }
            y++;
        }
    }
}
VOID DP_POT::dcload (REALTIME stime, SPICEMODES mode, DOUBLE *oldrhs, DOUBLE *newrhs)
{
    DOUBLE u1,u2;
    if (mode & SPICEINITJCT)
    {   // VALUES ON FIRST ITTERATION
        for(y=0; y<=Xpots;)
        {
            out1[y] = (DOUBLE) ((POTVAL[y]/w)*start[y] );
            out2[y] = (DOUBLE) (POTVAL[y]-((POTVAL[y]/w)*start[y]));
            y++;
        }
        updatestatus = TRUE;
    }
    if(!SHDNPOTS) // CHECK FOR POTS SHUT DOWN PINS ACTIVE FLAG
    {   // LOAD MATRIX WITH 1 AND 2 VALUES
        for(y=0; y<=Xpots;)
        {
            /////////////////
            u1=1/(out1[y]+1);
            ///////////////////////////////////
            *nodeLL[y]  +=u1; *nodeLW[y]  +=u1;
            *nodeLLW[y] -=u1; *nodeLWL[y] -=u1;
            ///////////////////////////////////
            /////////////////
            u2=1/(out2[y]+1);
            ///////////////////////////////////
            *nodeHH[y]  +=u2; *nodeHW[y]  +=u2;
            *nodeHWH[y] -=u2; *nodeHHW[y] -=u2;
            ///////////////////////////////////
            y++;
        }
    }
    if(SHDNPOTS)// IF POTS ARE SHUTDOWN LOAD ONLY LOWER RESISTOR WITH A VALUE OF .1R
    {// LOAD MATRIX WITHOUT 2 VALUE
        for(y=0; y<=Xpots;)
        {
            //////
            u1=10;
            ///////////////////////////////////
            *nodeLL[y]  +=u1; *nodeLW[y]  +=u1;
            *nodeLLW[y] -=u1; *nodeLWL[y] -=u1;
            ///////////////////////////////////
            y++;
        }
    }
}
VOID DP_POT::acload (SPICEFREQ omega, DOUBLE *rhs, DOUBLE *irhs) {}
VOID DP_POT::trunc  (REALTIME stime,  REALTIME *newtimestep) {}
VOID DP_POT::accept (REALTIME stime, DOUBLE *rhs )
{
    // WORK OUT IF THE NEW VALUE IS THE SAME AS THE OLD IF NOT UPDATE CHANGED POTS WITH NEW DATA
    for(y=0; y<=Xpots;)
    { if (out[y] != in[y]) { out1[y] = (DOUBLE) ((POTVAL[y]/w)*(in[y])); out2[y] = (DOUBLE) (POTVAL[y]-((POTVAL[y]/w)*(in[y]))); out[y] = in[y]; } y++; }
}
VOID DP_POT::setup (IINSTANCE *iinstance, IDSIMCKT *idsimckt)
{
    /////////////////////////////////////////
    instance = iinstance; dsimckt = idsimckt; //BIND THIS INSTANCE AND DSIM CIRCUIT TO THE MAIN INSTANCE AND DSIM CIRUIT THREADS
    /////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    // : GET PRESET RUNTIME VALUES FROM THE ISIS PART CALLING THIS DLL : //
    ///////////////////////////////////////////////////////////////////////
     /////////////////////////////////////////////
    /////////////////////////////////////////
    SDSSW = instance->getboolval("SDSSW", 0);   // GET SHOW DEGUB STATUS WINDOW FLAG TRUE/FALSE
	HOA   = instance->getboolval("HOA",   0);   // GET HIDE BEDUG STATUS WINDOW ONANIMATE FLAG TRUE/FALSE
    ebus  = instance->getboolval("16BUS", 0);   // GET SHOW 16BIT BUS ACTIVE OR NOT FLAG TRUE/FALSE
    CRM   = instance->getboolval("CRM",   0);   // GET SHOW COPYRIGHT MESSAGE FLAG TRUE/FALSE
    ////////////////////////////////////////////////
    BTE     = atoi(instance->getstrval("BTE","10")); // GET BIT LENGHT AS STRING CONVERT IT WITH ATOI TO AN INT
    ///////////////////////////////////////////////
    clk   = instance->getdsimpin("CLK,clk",  TRUE); // GET/BIND CLOCK PIN
	rst   = instance->getdsimpin("RST,rst",  TRUE); // GET/BIND RESET PIN
    hold  = instance->getdsimpin("HOLD,hold",TRUE); // GET/BIND HOLD  PIN
    load  = instance->getdsimpin("LOAD,load",TRUE); // GET/BIND LOAD  PIN
    SHDN  = instance->getdsimpin("SHDN,shdn",TRUE); // GET/BIND SHUTDOWN PIN
    EEPS  = instance->getdsimpin("EEPS,eeps",TRUE); // GET/BIND EEPROM SAVE PIN
    EEPR  = instance->getdsimpin("EEPR,eepr",TRUE); // GET/BIND EEPROM LOAD PIN
    ///////////////////////////////////////////////
    //////////////////////
    // TIMING CONSTANTS //
    //////////////////////
    /////////////////////////////////////////////////////////
    tdda  = instance->getdelay("tdtregdela", dsimtime(1e-9)); // REGISTER SETUP TIME {TOTAL TIME FOR ANY UPDATE}
    tcc   = instance->getdelay("tdtldela",   dsimtime(1e-9)); // BUS->FIFO SINGLE POT READ DELAY
    sdel  = instance->getdelay("selbbdela",  dsimtime(1e-9)); // POT/LOAD SELECTOR BUS L->H H->L DELAY
    ddel  = instance->getdelay("8bbdela",    dsimtime(1e-9)); // 8 BIT BUS L->H H->L DELAY
    bdel  = instance->getdelay("16bbdela",   dsimtime(1e-9)); // 16BIT BUS L->H H->L DELAY
    asdel=(sdel/2); // work out average delay selector bus
    addel=(ddel/2); // work out average delay 8bit  bus
    abdel=(bdel/2); // work out average delay 16bit bus
    ////////////////////////////////////////////////////
    SEL_BUS = instance->getbuspin ("SEL,sel",1,4, TRUE); // SETUP SELECTOR BUS WIDTH AND BIND PINS
    SEL_BUS->setstates(SHI,SLO,FLT);//APPLY SWITCHING STATES DECLIRATION
    SEL_BUS->settiming(sdel,sdel,asdel);// APPLY TIMINGS
    ////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    if (BTE <= 8) D_BUS   = instance->getbuspin ("D,d",0,BTE, TRUE);  // SET BUS WIDTH PER BTE SETTING AND BIND PINS
    if (BTE >= 9) D_BUS   = instance->getbuspin ("D,d",0,8,   TRUE);  // IF BTE >9 BIT SET BTE ALWAYS 8 BIT FOR THIS BUS
    D_BUS->setstates(SHI,SLO,FLT); // APPLY SWITCHING STATES DECLIRATION
    D_BUS->settiming(ddel,ddel,addel); // APPLY TIMINGS
    //////////////////////////////////
    if(ebus) // IS 16 BIT BUS ACTIVE QUALIFIER
    {
        /////////////////////////////////////////////////
        B_BUS = instance->getbuspin ("BD,bd",0,BTE, TRUE);     // SET BY BTE WIDTH OF 16 BIT BUS {ACTIVE PINS} AND BIND PINS
    	B_BUS->setstates(SHI,SLO,FLT); // APPLY SWITCHING STATES DECLERATION
    	B_BUS->settiming(bdel,bdel,abdel); // APPLY TIMINGS TO THE BUS CABLE
    	//////////////////////////////////
    }
    // SET ALL INPUT PINS STRONG LOW
    //////////////////////////////////////////////////////////////
    clk->setstate(SLO);  rst->setstate(SLO);  hold->setstate(SLO);
    load->setstate(SLO); hold->setstate(SLO); SHDN->setstate(SLO);
    EEPS->setstate(SLO); EEPR->setstate(SLO); ////////////////////
    //////////////////////////////////////////////////////////////
}
VOID DP_POT::simulate (ABSTIME stime, DSIMMODES dmode)
{
	// CHECK FOR DSIM BOOTED
	if (dmode==DSIMBOOT)
	{   // DISPLAY COPYRIGHTS MESSAGE
	    if(!CRM)
	    {
    	    instance->log("***************************************");
    	    instance->log("*  :<VSMLIBS>::<VSMLIBS>::<VSMLIBS>:  *");
    	    instance->log("***************************************");
    	    instance->log("* 16->16-BIT DIGITAL PROGRAMMABLE POT *");
    		instance->log("*    COPYRIGHT(c)2006 Simeon Webber   *");
    		instance->log("*        dll build version 1.052.     *");
    		instance->log("*         ALL RIGHTS RESERVED.        *");
    		instance->log("***************************************");
    		instance->log("*  !!LICENCED FOR PERSONAL USE ONLY!! *");
    		instance->log("* LAST BUILD:21_08_2006 10.00 HRS-BST:*");
    		instance->log("***************************************");
	    }
	    // CHECK FOR POTS SHUTDOWN AT BOOT
	    if (SHDN->isactive())   SHDNPOTS = TRUE;
        if (SHDN->isinactive()) SHDNPOTS = FALSE;
	}
	// CHECK FOR DSIM ANIMATING
	if ( dmode == DSIMNORMAL )
	{
	    EVENTID vpotid = 0;  // set eventid to event  0
	    if (rst->isposedge())  // check for reset positive edge during a normal cycle
	    {
	        for(y=0;y<=Xpots;)    // check for initvalues setup on individual pots and reset to this value
	        {
	            if(INITVAL[y]==0x0000) fifo[y] = 0x0000;
	            else if(INITVAL[y]!=0x0000) fifo[y]=INITVAL[y];
                y++;
	        }
	        if (GLOBALINIT!=0x0000) // check for a global init pots value and allign fifo position with this data to override the above statement
	        {
	            for(y=0;y<=Xpots;){ fifo[y] = GLOBALINIT; y++; } //if global init set above 0x0000 Fill  Fifo with init value
	        }
	        vpotid |= DP_POT_RESET;     // trigger reset callback ordinal
	        dsimckt->setbreak(stime);   // break to spice to update the pots
	    }
		if (((hold->isnegedge())|(hold->isinactive()))&(((rst->isnegedge())|(rst->isinactive()))))
		{
		    if(load->isposedge())   // check if load is  posedge during a clock event
		    {
    		    clockindata(stime+tcc, clk->isposedge()); // routine to clock into the fifo  the bus data
    		    vpotid |= DP_POT_UPDATE;    // call update pots cycle
    		    dsimckt->setbreak(stime);   // break to spice to update pots
    		}
		    if (rst->isposedge())     // check for reset positive edge during a clocked cycle
    	    {
    	        for(y=0;y<=Xpots;)
    	        { fifo[y] = 0x0000; y++; }  // Flush Fifo
    	        vpotid |= DP_POT_RESET;     // trigger reset callback ordinal
    	        dsimckt->setbreak(stime);   // break to spice to update the pots
    	    }
		}
		if (EEPS->isposedge())
        {
            G=SEL_BUS->getbusvalue(); // load G variable with selector bus value
    		savep[G]=in[G];
    		SAVE=TRUE; // flag a save data update
        } // save a snap shot of all active pots to eeprom file
        if (EEPR->isposedge())
        //LOAD EVENT WAS TRIGGERED
        {
            G=SEL_BUS->getbusvalue(); // load G variable with selector bus value
            fifo[G]=savedatadword[G]; // load fifo Dword array position with savedata position G
            vpotid |= DP_POT_UPDATE;  // call update pots cycle
            dsimckt->setbreak(stime); // break to spice to update pots
        }
	    if (SHDN->isposedge()) {SHDNPOTS = TRUE; updatestatus=TRUE;} // FOR FOR SHUTDOWN PIN {SHDN} ACTIVITY
        if (SHDN->isnegedge()) {SHDNPOTS = FALSE;updatestatus=TRUE;} // FOR FOR SHUTDOWN PIN {SHDN} ACTIVITY
		if (((hold->isposedge())|(hold->isactive()))) // check active state of hold pin and sync to pos edge clock
		{
		    if (EEPS->isposedge())
    		{
    		    G=SEL_BUS->getbusvalue(); // load G variable with selector bus value
    		    savep[G]=in[G];
    		    SAVE=TRUE; // flag a save data update
    		} // save a snap shot of all active pots to eeprom file
            if (EEPR->isposedge())
            //LOAD EVENT WAS TRIGGERED
            {
                G=SEL_BUS->getbusvalue(); // load G variable with selector bus value
                fifo[G]=savedatadword[G]; // load fifo Dword array position with savedata position G
                vpotid |= DP_POT_UPDATE;  // call update pots cycle
                dsimckt->setbreak(stime); // break to spice to update pots
            }
    	    if (rst->isposedge())           // check if reset is a posativeedge to trigger a reset during a hold event
    	    {
    	        for(y=0;y<=Xpots;)
    	        { fifo[y] = 0x0000; y++; }  //Flush Fifo
    	        vpotid |= DP_POT_RESET;     // trigger reset callback ordinal
    	        dsimckt->setbreak(stime);   // break to spice to update the pots
    	    }
    	    if ((EEPR->isactive())&(EEPS->isactive())&(rst->isactive())) // detect a reset eeprom event
    	    {
    	        instance->log(" EEPROM MASTER RESET TRIGGERED!! EEPROM NOW ZERO'd");
    	        for (y=0;y<=Xpots;)
    	        {
    	            savep[y]=0x0000;  // reset all savep array to 0x0000
    	            y++;
    	        }
    	        SAVE=TRUE; // flag a save data event
    	    }
		    if((load->isposedge())|(load->isactive()))   // check if load is active or posedge during a hold event
		    {
		        clockindata(stime+tcc, clk->isposedge()); // routine to clock into the fifo  the bus data
		        vpotid |= DP_POT_UPDATE;    // call update pots cycle
		        dsimckt->setbreak(stime);   // break to spice to update pots
		    }
		}
		if (vpotid!=0)  dsimckt->setcallback((stime + 1 + tdda) , this, vpotid) ;  // MAIN EVENT DRIVEN CALLBACK
    }
}
VOID DP_POT::callback (ABSTIME stime, EVENTID vpotid)  // DLL CALLBACK TO UPDATE THE IN REGISTER OF THE SPICE SECTION
{
    if(vpotid & DP_POT_UPDATE) {
    for(y=0;y<=Xpots;) { if (fifo[y]!=in[y]) in[y] = fifo[y]; y++; } updatestatus = TRUE; //update CHANGED pots data to in buffer from the fifo
    }
    if(vpotid & DP_POT_RESET)  {for(y=0;y<=Xpots;) { in[y] = fifo[y]; y++; } updatestatus = TRUE; //update all pots data to in buffer from the fifo
    }
}

VOID DP_POT::clockindata(ABSTIME stime, BOOL clock)  // CLOCKED BUS DATA READ DUMP TO FIFO[SELECTOR BUS] ROUTINE
{
    if (clock)
    {   // if no 16 bit bus enabled then apply 8 bit data to fifo only
        if(!ebus) { fifo[SEL_BUS->getbusvalue()] = D_BUS->getbusvalue(); }
        // if 16 bit bus enabled but has no data use 8 bit bus  if there is data {ie more than 0000 then 16 bit is used instead
        if(ebus)
        { if (B_BUS->getbusvalue() == 0x0000) { fifo[SEL_BUS->getbusvalue()] = D_BUS->getbusvalue(); }
            else { fifo[SEL_BUS->getbusvalue()] = B_BUS->getbusvalue(); } }
    }
}
VOID DP_POT::STATUSPOPUP()
{
    y=0;
    statuspopup->setcursorto(width,height * (y));
    if (!SHDNPOTS)  // DISPLAY AS NORMAL
    {
        for(x=1;x<=Xpotssp;)
        {
            if(x<=9) statuspopup->print(1 ,1,BLACK, "POTVAL %d:  %15.3f  OHMS",x,POTVAL[x-1]);   // ALLIGN DIGITS
            else     statuspopup->print(1 ,1,BLACK, "POTVAL %d: %15.3f  OHMS",x,POTVAL[x-1]);
            statuspopup->setcursorto(width,height * (y+=1));
            statuspopup->print(1 ,1,RED,   "L->W VALUE:%15.3f  OHMS",out1[x-1]);
            statuspopup->setcursorto(width,height * (y+=1));
            statuspopup->print(1 ,1,BLUE,  "W->H VALUE:%15.3f  OHMS",out2[x-1]);
            statuspopup->setcursorto(width,height * (y+=1));
            statuspopup->print(1 ,1,LIGHTBLUE,  "--------------------------------");
            statuspopup->setcursorto(width,height * (y+=1));
            x++;
        }
    }
    if(SHDNPOTS)  // CHECK FOR POTS SHUTDOWN AND USE THE ARRAY TO DRAW ALL AS BLACK
    {
        for(x=1;x<=Xpotssp;)
        {
            if(x<=9) statuspopup->print(1 ,1,BLACK, "POTVAL %d:  %15.3f  OHMS",x,POTVAL[x-1]); // ALLIGN DIGITS
            else     statuspopup->print(1 ,1,BLACK, "POTVAL %d: %15.3f  OHMS",x,POTVAL[x-1]);
            statuspopup->setcursorto(width,height * (y+=1));
            statuspopup->print(1 ,1,BLACK,  "L->W VALUE:%15.3f  OHMS",out1[x-1]);
            statuspopup->setcursorto(width,height * (y+=1));
            statuspopup->print(1 ,1,BLACK,  "W->H VALUE:%15.3f  OHMS",out2[x-1]);
            statuspopup->setcursorto(width,height * (y+=1));
            statuspopup->print(1 ,1,BLACK,  "--------------------------------");
            statuspopup->setcursorto(width,height * (y+=1));
            x++;
        }
    }
    // isis foward compatability fix when using status popups add these two lines
    statuspopup->setcursorto(width,height * (y+=1));
    statuspopup->print(1 ,1,BLACK, " ");
    y=0;
}
