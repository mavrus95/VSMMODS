
TT HEXIT ASKII  = SIMEON WEBBER


---- LEGAL BLURB ----

THIS PROGRAM AND DOCUMENTATION ARE PROVIDED "AS IS", 
WITHOUT WARRANTY OF ANY KIND, 
IMPLIED WARRANTY OF MECHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. 
SO BY USING THE PROGRAM INSTALLERS CODE OR  OTHER 
YOU AGREE TO BEAR ALL RISKS AND LIABILITIES ARISING FROM 
THE USE OF THE PROGRAM INSTALLERS CODE OR  OTHER DOCUMENTATION AND THE INFORMATION 
PROVIDED BY THE PROGRAM AND THE DOCUMENTATION.


***
ALWAYS SEE ONLINE FOR THE LATEST  VERSION OF THIS README
http://homepage.ntlworld.com/vsm.libs/VSM.library/README.txt
LIB'S & MODELS & EXAMPLEs & KITS INSTALLER
http://homepage.ntlworld.com/vsm.libs/VSM.library/VSM.LIBS%20INSTALLER.EXE


WHAT LIBS AND MODELS DO YOU  WANT TO SEE MADE FOR  PROTEUS VSM

usefull mail addresses  to request models or  a library

active vsm  modeler's  and  lib  makers  and collections  
email addresses

vsm.libs
simeon  {me}		: VSM.LIBS@NTLWORLD.COM         			: libs,active parts & dll & LISA based models made to spec

----------------------------------------------------------------------------
tehb's site
andrew              	: undongle@newmail.ru           			: dll & vsm based models made 											to spec

----------------------------------------------------------------------------
multipower

André Cayrol        	: multipower@wanadoo.fr         			: makers of lots of  rf  based  										and  many radio oriented libs 

----------------------------------------------------------------------------
LA-WEB-ELEctroique  	: 

sebastian           	: sebastien.lionnet@free.fr     			: maker of many fft laplace 											transforms  

----------------------------------------------------------------------------
ADT             	: info@advdigitaltech.com       			: dll based model  requests
                    	: consulting@advdigitaltech.com 			: consultation service 

----------------------------------------------------------------------------

labcenter		
	        	: info@labcenter.co.uk          			: information about models or 										  	other info
	            	: support@labcenter.co.uk       			: bugs and other support 										  	matters 
	            	: http://www.labcenter.co.uk/vmodels/modelreq.htm 	: model  request url

--------------------------------------------------------------------------------------------------
DLLS ADDED 

{development keys are needed to run some of these dlls ask labcenter for  yours if you dont have one}

visual studio c++ developer  & digital mars   for  some  type's were used for compilation
there sources are in the relevant folder's

as a note...  i  use a header for  development  keys  so  i compile to a series  0 1 2  etc 
0x3FFFFF00 -> 0x3FFFFFFFF
--------------------------------------------------------------------------------------------------

finished actives models 
--------------------------------------------------------------------------------------------------
devkey 0  rmsreadout.dll   gives an rms and  peek voltage for an ac  source in two displays 
devkey 1  mareadout.dll    a more accurate than  2 dp  digital readout  dll  {the meters are in the libs}

			   {maybe someone  want to make a multimeter dll {quite eaSY}



ANY VERSION  PROTEUS LITE OR  PRO... V6 dll  models  >

vco.dll   devkey 2 -- a voltage controlled oscillator  dll contributed  by  EA 
ADC-083X ---  mux A to d  library   contains  the 083x series  0831, 0832, 0834, 0838  
ICM7218A ---  8-digits LED Display Driver, parallel interface. For common anode mux LEDS
ICM7218B ---  8-digits LED Display Driver, parallel interface. For common cathode mux LEDS
MAX7219  ---  8-digits LED Display Driver, serial inteface. For common cathode mux LEDS
MAX7221  ---  8-digits LED Display Driver, true SPI. For common cathode mux LEDS.
MAX550   ---  8-bit DAC 5V output

Big thanks to ettori  for making  this  stuff  avalible
SHOW  BETTER PERFORMANCE THAT LABCENTER MODEL'S ..free.. and you  can see the code and  add your own tweaks


examples of  recent unfinished  work ..>
devkey3   LTC24xx.dll      	an  adc converter  
				{working??? test if you have enough  keys } still needs some tweeks  
devkey4   HEF4059.dll                 mixed digital  mode model 
devkey5   RAA216  & 6 RAA218 ...RAA2XX.dll {RAA216,RAA218 FOR NOW } 8051 dedicated i2c keypad and lcd
devkey7   mdsdisp   		an active  scrolling message handler  window with historys and destroy  
				yields hex bin dec 					oct  4 8 16 32 bit 
				will  gie in the end  a  usefull parrallel i2c and serial 
				freeware alternative to labcenters  expensived keyed monitor tpyes
				that in  my opinion should be  supplied as standard
				mdsdisp will work with  4 8 16 32 bit parrallel or serial connections
				{almost finished}   
	
again  Big Thanks to andrew & james  for instructional code,  help , and source codes contribution;

{we all get  sick of  the carrot on a string approch labcenter adopts
and there source code  buy ups policy to attain rights....
--------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------
29/03/2004    ADDED   	Thanks due,  to new contributer to vsm.libs 
			2716 27010 eprom models   look like  they  work fine
   			although the existant  bugs in memory  models  are a complete nightmare 
			where  some types of  memory are involved 
			however  all looks  fine  and a nice job  so i inlcuded them

			i decided to drop  all password and  etc..  requirements 
			please  therefore  download a fresh  lock  free copy
			of  both  source code and libs/models archives
			and "make it  so" & "fire  at will"
			life is  too short basicaly  becouse people are hesitant to add details



some stats

out of  1192  users  who  applied for the pass  only  5  sent  proof they  have a licence 
and  the  rest  appear  to  either be  unlicenced  or  other free loaders  
or  have a licence  and  arent  prepaired to share details

i understand  fully  this  situation

so  from  now on  ill use  v6.4 sp2 as it  appears 
the  main hack  site's  are living in the past {v6.1 etc hacked}

and the version i use is  buggy  but  quite stable...
if your a user  of  6.3 sp2 professional  or  after you  can load  all  sample  designs  for browsing
however becouse they  live in the past  with there hacked up  versions 
they  cant  access  these   only  the  models and  libs  are avalible 

i dont use  the lite version  only  the professional level starter pak 
as i find it  fit  for my  needs to construct  just  about anything
micros and  other   time intensive  stuff  in designing the code
ill leave to others


but  ill re-itterate  a stiff  warning not  too allow  licences  or  binarys  to leek from your machine
if your a bonified  user keep your  proteus machines  off-line  at all times


as  happened to me   your  licences  and  binary's  get  stolen  
even  from the rubbish bin ...  so watch out



a bug i notices in ledmpx  is  that  all  displays  like  mpx  leds  dont  work  
at all   looks  like labcenter are still playing catch up  with some bugs 

1} 4 bit or  16bit  memory{uses 4 bit  blocks}  dont  remember
2} ledmpx  dosn't  work
3} draw  bugs  still exist
i  commented to labcenter etc  already  

but  these  are  probably  being  fixed as  i type
so  roll on  ???v6.5 sp1  where these  bugs in basic  function are  fixed again
where in previous  version's  these bugs  didnt  exist....!


--------------------------------------------------------------------------------------------------
07/03/2004    ADDED 	ICM7218A ---  8-digits LED Display Driver, parallel interface. 
					For common anode mux LEDS
			ICM7218B ---  8-digits LED Display Driver, parallel interface. 
					For common cathode mux LEDS
			MAX7219  ---  8-digits LED Display Driver, serial inteface. 
					For common cathode mux LEDS
			MAX7221  ---  8-digits LED Display Driver, true SPI. 
					For common cathode mux LEDS.
			MAX550   ---  8-bit DAC 5V output
SOURCES + DLL

SOME MODEL'S  FEATURE ASSETS NOT MODELED in LABCENTER TYPE'S

--------------------------------------------------------------------------------------------------
03/03/2004     Added fix to AD083x to fix  ad0838 type  channelisation  and sim time overuse

--------------------------------------------------------------------------------------------------
02/03/2004      
		
		ADDED ADC083X  MODEL DESIGNS  SOURCES  FOR DLL BASED SIMULATION
		ALL ASPECTS  COVERED  INCLUDING THE  SAR  AND  SE  MODES
		BIG THANKS TO ETTORI  FOR MAKING THIS AVALIBLE   ADC- 0831, 0832, 0834, 0838
 
		Added several  dozen  fixes to model  to  dispense 
		 with the need to modify the default  itfmod .mdf  {interface model}
		added a few  more bits  to  devisis  
		a  few more fixes {too many to mention}

--------------------------------------------------------------------------------------------------
29/02/2004      UPDATED SOURCES TO FIX  A/D  FEATURES  ON THE LTC24xx
		ADDED FIXES TO VCO.DLL  TO IMPROVE THE PERFORMACE {GAINED 10%}  
		ADDED MORE CODE  AND HEEPS OF FIXES TO MDSDISP 
		REBUILT MENUS ON CD4059 TO ADD MORE DETAILS AND TTL MODE
		ADDED MORE CODE TO RAA2XX MODELS  NOW YOU CAN PLACE MORE THAN ONE AND IT WONT CRASH
		STILL WORKING HARD TO FINISH THEM AS SOON AS POSSIBLE
 		
--------------------------------------------------------------------------------------------------
28/02/2004      ADDED BACK IN RAA2xx SOURCES   SO FAR SO GOOD 
		I ADDED ALL THE NEWER FUNCTION CALLS  AND  UPDATED  IT ALL
		ill get it too run  this week im sure  just variables to tie in now
		thanks again to anderw in russia for clear  detail's and the help!!!
--------------------------------------------------------------------------------------------------
26/02/2004      ADDED  BIN SWITCH AND DISPLAY PARTS  SHOWS A LINE OF  BIN 
		VALUES UP TO 5 BITS LONG FOR NOW  ALSO YOU  CAN ADD  EASILY
		ANY TABLES OR CHARTS INTO  THE  COMPONENT AND COMMON VIEW 
		I MAY  ADD A TABLES AND READOUTS  KIT....
		added more code variation  thru  the  fixing of this problem
		more code to follow...............
--------------------------------------------------------------------------------------------------
25/02/2004      UPDATED LTC24XX  SOURCE  TO REFLECT A MOD  CHANGE TO THE CODE AND REBUILT  THE DLL
		TO ALLOW  TRACKING OF  EVENTS STRUCTURE  MORE COHESIVLY
		my own sources still needs worked on.

--------------------------------------------------------------------------------------------------
24/02/2004      added  a  4046 pll  using the new vco.dll
		added  a vco dll   made  by etorri 
		added a sigma deltal  type  LTC24XX  model 
		both are mixed mode  types 
		added  recent  work started   hef4059  {looking  good so far}
		added  a  few more  graphic  parts 
			a 3 bit  state variable  bcd switch 
		{bit  better looking that the  normal hex thumb wheels} 

BIG  Thankyou  Etorri for contributing some sources  and models 
--------------------------------------------------------------------------------------------------
18/02/2004      Fixed com2pim  graphics   looks  like an older version crept in 
		added a meter  with a needle  {analogue panel/radio type}


--------------------------------------------------------------------------------------------------
17/02/2004      ADDED A FEW MORE KEYPADS  
		FROM THIS  SITE  AS THEY  LOOK  VERY NICE  TYPE'S 
		http://www.allelectronics.com/index.html  <<NICE SITE FOR BITS
	
		ADDED A SCALER  {100 STATE} ?0-99 STATES ONLY IS THIS A BUG???
		{MODELS FOR MORE FINITE RESITORS CAPS INDUCTORS ETC TO COME NEXT WEEK / FEW DAYS}
	
-------------------------------------------------------------------------------------------------
14/02/2004      fixed and  fully modeled 
		{apart from timming trimming i will add this as  soon as }
		
		all the  ad840x  series  of  digital  pot  chips 
		these are volitile  serial 3 wire driven rdacs
		started the adc0817 
		added lots more  tweaks  and  fixes to cmos

--------------------------------------------------------------------------------------------------

08/02/2004      further tidy  session 
		ADDED SIMM 4M SDRAM MODEL
		START DESIGN OF A MEMORY TEST BED
		ADDED A FEW MORE  TYPES OF  ISIS PARTS  TO DEVISIS DESIGN
		AGAIN A FEW  MORE GRAPHS  AND  PROOFS OF  TIMINGS MADE 
		REMOVED  DLL SOURCES  FOR SIMM MODELS  AS THE MEMORY  PRIMATIVES WILL BE  JUST AS FAST
		REMOVED  ITFMOD.MDF  FILE   PLEASE RESTORE ANY  IN USE
		ADDED SOME MORE FIXES TO TIMINGS OF  SOME CMOS MODELS
--------------------------------------------------------------------------------------------------
04/02/2004      ADDED SOME FIXES TO TIMINGS OF  SOME CMOS MODELS
		TIDY UP  GENERAL  CLEAN  TO ALL DESIGNS
		ALL DESIGNS  NOW LOCKED TO SP1 V6.4  
--------------------------------------------------------------------------------------------------
01/02/2004      ADDED  BREAK GLASS  SWITCHES TO dev_KEYPADS LIB 
		FOR  FIRE ALARM  CIRCUITS
		ADDED A FEW MORE PARTS  TO DEVISIS AND  DID SOME WORK ON MODELS 
		MOSTLY TIMINGS .....
		ADDED  A  FEW MORE MAXIM MCU  OUTLINES AND OTHER  OUTLINE

{if you need another  outline  and it  looks  complex  just ask vsm.libs }
	

!!!   IF  YOU HAVE / NEED MODELS  & OR  LIBS TO USE / SHARE LET US  KNOW

VSM.LIBS@NTLWORLD.COM

HOMEPAGES
http://homepage.ntlworld.com/vsm.libs/




---- LEGAL BLURB ----

THIS PROGRAM AND DOCUMENTATION ARE PROVIDED "AS IS", 
WITHOUT WARRANTY OF ANY KIND, 
IMPLIED WARRANTY OF MECHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. 
SO BY USING THE PROGRAM INSTALLERS CODE OR  OTHER 
YOU AGREE TO BEAR ALL RISKS AND LIABILITIES ARISING FROM 
THE USE OF THE PROGRAM INSTALLERS CODE OR  OTHER DOCUMENTATION AND THE INFORMATION 
PROVIDED BY THE PROGRAM AND THE DOCUMENTATION.


