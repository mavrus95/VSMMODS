//
// Simple IO driver for LTC2440

#include <REG52.H>
#include <intrins.h>
#include "LTC2440_driver_var.h"
#include "lcd_lib.h"

static unsigned char dataout(void);

/////////////////////////////////////////////////////////////////////////
// Read a byte from LTC2440. 
// Optimized for speed. The shift instruction ">>" takes to much time !!!
static unsigned char dataout(void)
{

#define SCLK		sck = 0; sck = 1	// rising edge clock. 	

unsigned char byte = 0;	

	SCLK;
	if (sdo) byte |= 0x80;
	SCLK;
	if (sdo) byte |= 0x40;
	SCLK;
	if (sdo) byte |= 0x20;
	SCLK;
	if (sdo) byte |= 0x10;
	SCLK;
	if (sdo) byte |= 0x08;
	SCLK;
	if (sdo) byte |= 0x04;
	SCLK;
	if (sdo) byte |= 0x02;
	SCLK;
	if (sdo) byte |= 0x01;

	return byte;	
}

///////////////////////////////////////////////////
// Dataout puts data in * cdata array and returns 
// conversion code. 
unsigned char LTC2440_rd (unsigned char * cdata)
{
	unsigned char msb;
	unsigned char sig;

	cs = 0;							// enable sdo
	// 	
	// put four bytes in 
	// cdata array
	cdata[0] = dataout();  			// get MSB
	cdata[1] = dataout();
	cdata[2] = dataout();
	cdata[3] = dataout();		    // get LSB

	sck = 0;						// dataout completed. Start new conversion.	

   	cs  = 1;						// disable sdo

   	sig = cdata[0] & 0x20;			// get sign from MSB
  	msb = cdata[0] & 0x10;			// get msb  from MSB

   	cdata[0] &= 0x1f;				// clear BIT 31, BIT 30, BIT 29.
	
   	if (sig && msb) 				//
		return ADOVF; 			    // return conversion codes:
	else if (sig && !msb) 		    // ADOVF       	= positive overange
		return (ADRDY | ADOVF);		// ADRDY+ADOVF 	= positive readings
	else if (!sig && msb) 		    // ADRDY+ADUNF 	= negative readings
		return (ADRDY | ADUNF) ;	// ADUNF	   	= negative underange	
	else if (!sig && !msb) 		    //
		return ADUNF ;		    	//
}

//////////////////////////////////////////
// Return a 29-bits binary conversion 
long LTC2440_get_value (unsigned char * cdata)
{
	return * (long *) cdata;		// build 29-bits word from * cdata array 
}


//////////////////////////
// Initialize LTC2440
void init_ad (void)
{
	sck = 0;	
	cs  = 1;
}


//////////////////////////////////////
// Test "end of conversion" bit.
// Conversion is running if IDLE.
// Conversion is completed if EOC
bit LTC2440_eoc(void)
{
    cs = 0;							// enable sdo
   	if (sdo) {
		cs = 1;						// disable sdo
  		return IDLE;				// conversion is running
	}	
	else { 
		cs = 1;						// disable sdo
 		return EOC; 				// conversion is completed
	}
}



