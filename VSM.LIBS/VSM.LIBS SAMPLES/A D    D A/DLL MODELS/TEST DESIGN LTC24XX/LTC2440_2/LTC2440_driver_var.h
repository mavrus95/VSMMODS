sbit    sck		= P1^0; 		// SCK  LTC2440, serial clock
sbit    sdo  	= P1^1;			// DOUT LTC2440, serial data 	 
sbit    cs		= P1^2;			// CS   LTC2440, convert/chip select

//Conversion status codes
#define  ADRDY 		0x10
#define  ADOVF		0x20
#define  ADUNF	    0x40

// status bit 
#define  IDLE 		0
#define  EOC		1



