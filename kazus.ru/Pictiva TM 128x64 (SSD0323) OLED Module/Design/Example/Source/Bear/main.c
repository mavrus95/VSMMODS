
// main.c

#include <iom32v.h>
#include <macros.h>
#include <math.h>

#include "def.h"
#include "pins.h"
#include "spi.h"
#include "oled.h"
#include "images/bear.h"
#include "images/dog.h"

void main(void) {
byte i,bear_count,dog_count;

	M8C_DisableGInt;

	PORTA = 0x00;
	DDRA  = 0x00;
	PORTB = 0x00;
	DDRB  = 0x00;
	PORTC = 0x00; //m103 output only
	DDRC  = 0x00;
	PORTD = 0x00;
	DDRD  = 0x00;

	MCUCR = 0x00;
	GICR  = 0x00;

	GLCD_SHDN_Dir	|= GLCD_SHDN_bit;
	GLCD_RES_Dir	|= GLCD_RES_bit;

	GLCD_DC_Dir		|= GLCD_DC_bit;
	GLCD_CS_Dir		|= GLCD_CS_bit;
	GLCD_WR_Dir		|= GLCD_WR_bit;
	GLCD_EN_Dir		|= GLCD_EN_bit;

	GLCD_SHDN_oPort	&= ~GLCD_SHDN_bit;
	GLCD_RES_oPort	|= GLCD_RES_bit;

	GLCD_DC_oPort	&= ~GLCD_DC_bit;
	GLCD_CS_oPort	|= GLCD_CS_bit;
	GLCD_WR_oPort	|= GLCD_WR_bit;
	GLCD_EN_oPort	|= GLCD_EN_bit;

	OLED_interface = BS_iPort & (BS_2|BS_1);

	SPIM_1_Start(SPIM_1_SPIM_MODE_3); // Init
///	SPI1M_Speed(1); // 1-250, 2-62, 3-31
	SPI1M_Speed(0); // 1-250, 2-62, 3-31
	GLCD_Data_oPort = 0; GLCD_Data_Dir = 0;

	M8C_EnableGInt;
	GLCD_Data_Dir |= 0xFF;
	GLCD_WR_oPort &= ~GLCD_WR_bit;		// WR=0 - write
	oled_init();

	while (1) {
		bear_count++; if (bear_count >= 13) bear_count = 0;
		img_out(32,8,&bear[bear_count][0]);
		delay_ms(100);
		dog_count++;
		if (dog_count < 20) i = 0; else
		if (dog_count < 21) i = 1; else
		if (dog_count < 27) i = 2; else
		if (dog_count < 28) i = 3; else
		if (dog_count < 29) i = 4; else
		if (dog_count < 54) i = 5; else
		if (dog_count < 55) i = 6; else
		if (dog_count < 56) i = 7; else
		if (dog_count < 57) i = 7; else dog_count = 0;
		img_out(0,14,&dog[i][0]);
		delay_ms(100);
	}
}
