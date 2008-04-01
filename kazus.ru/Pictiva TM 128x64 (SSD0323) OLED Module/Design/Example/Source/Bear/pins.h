// pins.h

#define GLCD_SHDN_Dir		DDRA
#define GLCD_SHDN_oPort		PORTA
#define GLCD_SHDN_bit		bit1		// PA1 - SHDN
#define GLCD_RES_Dir		DDRA
#define GLCD_RES_oPort		PORTA
#define GLCD_RES_bit		bit2		// PA2 - RES

#define GLCD_SPI_Dir		DDRB
#define GLCD_SCLK_oPort		PORTB
#define GLCD_SCLK_bit		bit7		// PB7 - SPIM_CLK
#define GLCD_SDIN_oPort		PORTB
#define GLCD_SDIN_bit		bit5		// PB5 - SPIM_MOSI
#define GLCD_DC_Dir			DDRB
#define GLCD_DC_oPort		PORTB
#define GLCD_DC_bit			bit3		// PB3 - DC
#define GLCD_CS_Dir			DDRB
#define GLCD_CS_oPort		PORTB
#define GLCD_CS_bit			bit2		// PB2 - CS
#define GLCD_WR_Dir			DDRB
#define GLCD_WR_oPort		PORTB
#define GLCD_WR_bit			bit1		// PB1 - RW
#define GLCD_EN_Dir			DDRB
#define GLCD_EN_oPort		PORTB
#define GLCD_EN_bit			bit0		// PB0 - EN

#define BS_iPort			PINC
#define BS_2				bit2
#define BS_1				bit1
#define M68_mod				BS_2
#define I80_mod				(BS_2|BS_1)
#define SPI_mod				0

#define GLCD_Data_Dir		DDRD
#define GLCD_Data_oPort		PORTD
#define GLCD_Data_iPort		PIND
