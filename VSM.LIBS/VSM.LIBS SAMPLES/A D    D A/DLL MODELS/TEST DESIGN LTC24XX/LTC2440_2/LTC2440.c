#include <REG52.H>
#include <stdio.h>
#include "Ltc2440_driver.h"
#include "LTC2440_driver_var.h"
#include "lcd_lib.h"

#define VREF   1		    	// change here vref value as for schematic
#define RANGE  0x20000000	    // (1<<numbits) where numbits = 29
#define MAXAVR 5			    // number of averages

/////////////////////////
// Simple application.
void main (void)
{
	unsigned char cdata[4]={0,0,0,0};
	unsigned char status;
	unsigned long conv = 0;
	unsigned char buf[14];
	unsigned char na = 0;

	float reads = 0;
	float avr = 0;

	/////////////////////////////////////////////////////////////////////

	// Initialize lcd 
	init_lcd();
	// Initialize LTC2440
	init_ad();

	// Turn off blinking cursor
	control (BLINK_OFF_CURSOR_OFF);

	// Clean lcd screen
	clr_lcd();

	// Display first message
 	wrstr_lcd ("    LTC2440 TEST");
	locate_lcd(1, 0);
  	wrstr_lcd (" DIGITAL VOLTMETER ");
	delay (30000);
 	clr_lcd();

 	// Screen template 
	locate_lcd(0, 0);
	wrstr_lcd ("INPUT: ");

 	while (1) 
	{
		if (LTC2440_eoc() == IDLE) { 
			delay(300);
		}			
		else {
			// Get status and raw conversion from ADC
			status = LTC2440_rd(&cdata) ; 					
			conv = LTC2440_get_value (&cdata); 

			// Test if Over or Under flow 
			if (status == ADOVF)			
				sprintf (buf, "%s    ", "+++ OVL +++ ");			
			else if (status == ADUNF)
				sprintf (buf, "%s    ", "--- UNF --- ");			
			else {
				// If readings are valid convert in signed floating number
				if (status == (ADRDY | ADOVF))  
					reads = (float) (conv * VREF) / RANGE ; 		
				else if (status == (ADRDY | ADUNF)) 
					reads = (float) (conv * VREF) / RANGE - VREF ; 		
				// Add averages
				if (na++ < MAXAVR) 
					avr += reads; 
				else {
				// Display averaged value
					sprintf (buf, "%+1.7f V", avr/(na-1));			
					na = 0;
					avr = 0;
				}
			}
		}	
		// display value in the right position.
		locate_lcd(0, 7);
		wrstr_lcd (buf);						
	}
}

