#include <reg52.h>
#include "lcd_lib.h"
#include "8051_lcd.h"

////////////////////////////////////////////////////////////////////////////////
// This routine generates a delay. Clock depending
void delay(unsigned long dly) 
{ 
	while (--dly > 0);
}

////////////////////////////////////////////////////////////////////////////////
// Read Busy flag is D7, must be masked with 0x80
char busy_lcd() 
{ 
	return(rdctl_lcd & 0x80); 	
} 

////////////////////////////////////////////////////////////////////////////////
// Initialize LCD display
void init_lcd() 
{ 	
	wrctl_lcd = 0x30; 					// write control for the firt time on power up 
	delay(100); 						// execute delay 4.1 ms or more, 

	wrctl_lcd = 0x30; 					// same before, the second 
	delay(100); 

	wrctl_lcd = 0x30; 					// one more time, without delay 
	delay(100); 
	wrctl_lcd = 0x38; 					// function set to 8bit length interface 

	while(busy_lcd()); 					// now, busy flag can read for cek busy lcd 
	
	wrctl_lcd = BLINK_ON_CURSOR_OFF;	// set blink on and cursor off.  
								
	while(busy_lcd()); 					// now, busy flag can read for ce busy lcd 
	wrctl_lcd = CLEAR;					// clear lcd. 
	while(busy_lcd()); 					// now, busy flag can read for ce busy lcd. 
} 

////////////////////////////////////////////////////////////////////////////////
// Locate cursor to row,col for write read char in lcd 
// Row and char start at 0. i.e. locate_lcd(0,0) is row 1 and col 1 
void locate_lcd(char row, char col) 
{ 
	char d; 
	switch(row) 
	{ 
		case 0: d = LINE_1; 	// set to DD_RAM start address for line_1 
		break; 
		case 1: d = LINE_2; 	// set to DD_RAM start address for line_2 
		break; 
		case 2: d = LINE_3; 	// set to DD_RAM start address for line_3 
		break; 
		case 3: d = LINE_4; 	// set to DD_RAM start address for line_4 
		break; 
	} 
	wrctl_lcd=(d += col); 
	while(busy_lcd()); 
} 

////////////////////////////////////////////////////////////////////////////////
// This routine send string in idata, data, pdata, cdata or cdata ending by NULL 
// as the address is generic pointer *ptrbuff 
// Pointer aotumatically contain pointer for memory type that you pass to 
// this routine 
void wrstr_lcd(char *ptrbuff) 
{ 
	char d; 
	while((d=*ptrbuff++) != 0) 
	{ 
		wrdata_lcd = d; 
		while(busy_lcd()); 
	} 
}

////////////////////////////////////////////////////////////////////////////////
// Clear display
void clr_lcd()	
{	
	wrctl_lcd = CLEAR; 
	while(busy_lcd());
}

////////////////////////////////////////////////////////////////////////////////
// Send control code
void control(char cntrl)	
{	
	wrctl_lcd = cntrl; 
	while(busy_lcd());
}
	
