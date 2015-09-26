#ifndef LCD_GRAPH_LIB_H
#define LCD_GRAPH_LIB_H

#include <mega16.h>
#include <delay.h>
#include "bits_macros.h"

//*****************************************************************************
//
//  ��, ��� ����� ���������
//
//������� ������������ ��
#define F_CPU 16000000

//���� � �������� ���������� ����������� �������
#define PORT_LCD_CON PORTB
#define PIN_LCD_CON  PINB
#define DDRX_LCD_CON DDRB

//���� � �������� ���������� ���� ������ 
#define PORT_LCD_BUS PORTC  
#define PIN_LCD_BUS  PINC
#define DDRX_LCD_BUS DDRC

//������ � ������� ���������� ����������� ������� ���
#define RES     0
#define CS      1
#define AO      2
#define RD_WR   3
#define EN      4

//*****************************************************************************
//
//  ��������� ����������������
//
//�������
#define COM_DISPLAY_ON       0xaf               //�������� ���
#define COM_DISPLAY_OFF      0xae               //��������� ���
#define COM_START_LINE(x)    (0xc0&(0x1f&(x)))  //���������� ������� ������ ���
#define COM_ADC_SELECT_OFF   0xa0               //������ ������������ ������ � �������
#define COM_ADC_SELECT_ON    0xa1               //�������� ������������ ������ � �������
#define COM_STATIC_DRIVE_ON  0xa5               //����������� ����� ����������
#define COM_STATIC_DRIVE_OFF 0xa4               //������� ����������
#define COM_DUTY_SELECT_ON   0xa9               //����� ������������
#define COM_CLEAR_RMW        0xee               //������ ����� RMW
#define COM_SELECT_RMW       0xe0               //��������� ����� RMW
#define COM_RESET            0xe2               //������ � �������� ������������ � 0

//������ ������ �� �����
#define MET_AND  0
#define MET_OR   1
#define MET_XOR  2

#define FILL_OFF 0
#define FILL_ON  1

//******************************************************************************
//
//  �������
//
//�������������� �������
unsigned char LCDG_ReadData(void);
void LCDG_SendCom(unsigned char data);
void LCDG_SendData(unsigned char data);

//������� �������������
void LCDG_InitPort(void);
void LCDG_InitLcd(void);
void LCDG_ClearLcd(unsigned char x1, unsigned char x2);

//������� ���������������
void LCDG_SetInv(unsigned char f);
void LCDG_SendSymbol(unsigned char xPos, unsigned char yPos, unsigned char data);
void LCDG_SendString(unsigned char xPos, unsigned char yPos, char * string);

//����������� �������
void LCDG_SetMethod(unsigned char met);
void LCDG_PutPixel(unsigned char xPos, unsigned char yPos);
void LCDG_DrawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);
void LCDG_DrawCircle(unsigned char xc,unsigned char yc,unsigned char r);
void LCDG_DrawRect(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char fill);

#endif //LCD_GRAPH_LIB_H

