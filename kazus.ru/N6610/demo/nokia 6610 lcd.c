#include <htc.h>

#ifndef _XTAL_FREQ
	#define _XTAL_FREQ 20000000
#endif
__CONFIG(HS & WDTDIS & PWRTEN & BOREN);

//Philips PCF8833 Commands
#define LCD_NOP			0x00	// no operation
#define LCD_CASET		0x2A	// column address set
#define LCD_PASET		0x2B	// page address set
#define LCD_RAMWR		0x2C	// memory write

#define TCMD	0
#define	TDATA	1

#define BLUE        0x03
#define YELLOW      0xFC
#define RED         0XE0
#define GREEN       0X1C
#define BLACK       0X00
#define WHITE       0XFF
#define ORANGE      0XF8

#define	LCD_RESET	RC5
#define	LCD_DATA	RC4
#define LCD_CLK		RC3
#define	LCD_CS		RC2

void lcd_send(unsigned char lcd_byte, unsigned char DC);
void lcd_fill_area(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2, unsigned char color);

void main(void)
{
	unsigned long i;
	TRISC = 0x00;
	RC0 = 0;
	LCD_RESET = 0;
	LCD_CS = 1;
	LCD_RESET = 1;
	LCD_CS = 0;
	
	//for(i=0; i<27; i++)
		//lcd_send(0b10101010, TDATA);

	//RC0 = 1;
	//while(1);

	lcd_fill_area(20, 30, 40, 50, BLUE);
	lcd_fill_area(70, 80, 55, 70, YELLOW);
	lcd_fill_area(50, 70, 20, 22, RED);

	RC0 = 1;

	while(1);
}

void lcd_send(unsigned char lcd_byte, unsigned char DC)
{
	unsigned char c;
	LCD_CS = 0;
	__delay_us(2);
	LCD_CLK = 0;
	if(DC == TCMD)  LCD_DATA = 0;
	else LCD_DATA = 1;
	LCD_CLK = 1;
	__delay_us(2);
	for(c=8;c>0;c--)
	{
		LCD_CLK = 0;
		if( lcd_byte & 0x80)	LCD_DATA = 1;
		else	LCD_DATA = 0;
		LCD_CLK = 1;
		__delay_us(2);
		lcd_byte = lcd_byte<<1;
	}
	LCD_CS = 1;
}
void lcd_fill_area(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2, unsigned char color)
{
   unsigned int i, total;
   total = ( (unsigned int)x2-x1+1)*(y2-y1+1);
   lcd_send(LCD_CASET, TCMD);
   lcd_send(x1, TDATA);
   lcd_send(x2, TDATA);
   
   lcd_send(LCD_PASET, TCMD);
   lcd_send(y1, TDATA);
   lcd_send(y2, TDATA);
   
   lcd_send(LCD_RAMWR, TCMD);
   for(i=0; i<total; i++)   lcd_send(color, TDATA);

}
