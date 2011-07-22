#ifndef LCD_GRAPH_LIB_H
#define LCD_GRAPH_LIB_H

#include <mega16.h>
#include <delay.h>
#include "bits_macros.h"

//*****************************************************************************
//
//  то, что нужно настроить
//
//частота тактировани€ мк
#define F_CPU 16000000

//порт к которому подключены управл€ющие сигналы
#define PORT_LCD_CON PORTB
#define PIN_LCD_CON  PINB
#define DDRX_LCD_CON DDRB

//порт к которому подключена шина данных 
#define PORT_LCD_BUS PORTC  
#define PIN_LCD_BUS  PINC
#define DDRX_LCD_BUS DDRC

//выводы к которым подключены управл€ющие сигналы жкд
#define RES     0
#define CS      1
#define AO      2
#define RD_WR   3
#define EN      4

//*****************************************************************************
//
//  различные макроопределени€
//
//команды
#define COM_DISPLAY_ON       0xaf               //включает жкд
#define COM_DISPLAY_OFF      0xae               //выключает жкд
#define COM_START_LINE(x)    (0xc0&(0x1f&(x)))  //определ€ет верхнюю строку жкд
#define COM_ADC_SELECT_OFF   0xa0               //пр€мое соответствие адреса и позиции
#define COM_ADC_SELECT_ON    0xa1               //обратное соответствие адреса и позиции
#define COM_STATIC_DRIVE_ON  0xa5               //статический режим управлени€
#define COM_STATIC_DRIVE_OFF 0xa4               //обычное управление
#define COM_DUTY_SELECT_ON   0xa9               //выбор мультиплекса
#define COM_CLEAR_RMW        0xee               //сн€тие флага RMW
#define COM_SELECT_RMW       0xe0               //установка флага RMW
#define COM_RESET            0xe2               //строка и страница сбрасываетс€ в 0

//методы вывода на экран
#define MET_AND  0
#define MET_OR   1
#define MET_XOR  2

#define FILL_OFF 0
#define FILL_ON  1

//******************************************************************************
//
//  ‘”Ќ ÷»»
//
//низкоуровневые функции
unsigned char LCDG_ReadData(void);
void LCDG_SendCom(unsigned char data);
void LCDG_SendData(unsigned char data);

//функции инициализации
void LCDG_InitPort(void);
void LCDG_InitLcd(void);
void LCDG_ClearLcd(unsigned char x1, unsigned char x2);

//функции знакогенератора
void LCDG_SetInv(unsigned char f);
void LCDG_SendSymbol(unsigned char xPos, unsigned char yPos, unsigned char data);
void LCDG_SendString(unsigned char xPos, unsigned char yPos, char * string);

//графические функции
void LCDG_SetMethod(unsigned char met);
void LCDG_PutPixel(unsigned char xPos, unsigned char yPos);
void LCDG_DrawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);
void LCDG_DrawCircle(unsigned char xc,unsigned char yc,unsigned char r);
void LCDG_DrawRect(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char fill);

#endif //LCD_GRAPH_LIB_H

