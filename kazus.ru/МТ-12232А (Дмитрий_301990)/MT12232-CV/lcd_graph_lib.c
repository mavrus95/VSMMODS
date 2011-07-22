#include "lcd_graph_lib.h"
#include "font_6x8.h"

#define PAGE0 0xb8
#define PAGE1 0xb9
#define PAGE2 0xba
#define PAGE3 0xbb
#define FLAG_BUSY  7

#define SelectLeftChip()   SetBit(PORT_LCD_CON, CS)
#define SelectRightChip()   ClearBit(PORT_LCD_CON, CS)

volatile unsigned char method = 1;
volatile unsigned char flag = 0;

//инициализация портов ввода/вывода
void LCDG_InitPort(void)
{
 PORT_LCD_BUS = 0xff;
 DDRX_LCD_BUS = 0xff;
 PORT_LCD_CON = 0xff;
 DDRX_LCD_CON = 0xff;   
}

//функция чтения флага занятости
void LCDG_WaitFLAG_BUSY(void)
{
  unsigned char stat;
  DDRX_LCD_BUS = 0;                    //конфигурируем порт на вход
  PORT_LCD_BUS = 0xff;  
  SetBit(PORT_LCD_CON, RD_WR);         //выставляем управляющие сигналы
  ClearBit(PORT_LCD_CON, AO); 
  delay_us(2);
  do{
  ClearBit(PORT_LCD_CON, EN); 
  delay_us(5);
  stat = PIN_LCD_BUS;                 //считываем статусный байт
  delay_us(5);
  SetBit(PORT_LCD_CON, EN);
  }
  while((stat & (1<<FLAG_BUSY)) != 0); //сидим в цикле пока не сбросится флаг
  DDRX_LCD_BUS = 0xff;                 //делаем порт снова выходом
  PORT_LCD_BUS = 0;  
}

//функция чтения байта данных из lcd
unsigned char LCDG_ReadData(void)
{
  unsigned char data;
  DDRX_LCD_BUS = 0;                   //конфигурируем порт на вход 
  PORT_LCD_BUS = 0xff;
  SetBit(PORT_LCD_CON, RD_WR);
  SetBit(PORT_LCD_CON, AO);  
  delay_us(2);
  ClearBit(PORT_LCD_CON, EN);
  delay_us(5);
  data = PIN_LCD_BUS;
  SetBit(PORT_LCD_CON, EN);
  //делаем порт снова выходом
  DDRX_LCD_BUS = 0xff;
  PORT_LCD_BUS = 0;    
  return data;
}

//общая функция
inline void LCDG_CommonFunc(unsigned char data)
{
  ClearBit(PORT_LCD_CON, RD_WR);
  delay_us(2);
  ClearBit(PORT_LCD_CON, EN);
  PORT_LCD_BUS = data;
  delay_us(5);
  SetBit(PORT_LCD_CON, EN);
}

//запись команды на lcd
void LCDG_SendCom(unsigned char data)
{
  LCDG_WaitFLAG_BUSY();                   
  ClearBit(PORT_LCD_CON, AO);
  LCDG_CommonFunc(data);
}

//вывод данных на lcd
void LCDG_SendData(unsigned char data)
{
  LCDG_WaitFLAG_BUSY();
  SetBit(PORT_LCD_CON, AO);
  LCDG_CommonFunc(data);
}

//функция инициализации lcd
//подает сигнал сброса
//настраивает правый и левый контроллеры
void LCDG_InitLcd(void)
{
  ClearBit(PORT_LCD_CON, RES);
  delay_ms(400);
  SetBit(PORT_LCD_CON, RES);
  delay_ms(400);
  
  SelectLeftChip();
  LCDG_SendCom(COM_CLEAR_RMW);
  LCDG_SendCom(COM_STATIC_DRIVE_OFF);
  LCDG_SendCom(COM_DUTY_SELECT_ON);
  LCDG_SendCom(COM_DISPLAY_ON);
  LCDG_SendCom(COM_ADC_SELECT_ON); 
  LCDG_SendCom(COM_RESET);
  LCDG_SendCom(0xc0); 

  SelectRightChip();
  LCDG_SendCom(COM_CLEAR_RMW);
  LCDG_SendCom(COM_STATIC_DRIVE_OFF);
  LCDG_SendCom(COM_DUTY_SELECT_ON);
  LCDG_SendCom(COM_DISPLAY_ON);
  LCDG_SendCom(COM_ADC_SELECT_OFF);  
  LCDG_SendCom(COM_RESET);
  LCDG_SendCom(0xc0);  
}

//функция очистки lcd
void LCDG_ClearLcd(unsigned char x1, unsigned char x2)
{
unsigned char xPos = x1;
unsigned char realAdr = 0;

while(xPos < x2){    
  if (realAdr < 61) {
    SetBit(PORT_LCD_CON, CS);
    realAdr = realAdr + 19;
  }
  else {
    ClearBit(PORT_LCD_CON, CS); 
    realAdr = realAdr - 61;
  }

  LCDG_SendCom(PAGE0);
  LCDG_SendCom(realAdr);
  LCDG_SendData(0);
  LCDG_SendCom(PAGE1);
  LCDG_SendCom(realAdr);  
  LCDG_SendData(0);
  LCDG_SendCom(PAGE2);
  LCDG_SendCom(realAdr);
  LCDG_SendData(0);
  LCDG_SendCom(PAGE3);
  LCDG_SendCom(realAdr);
  LCDG_SendData(0);
  
  xPos++;
  realAdr = xPos;
} 
}

//установка метода вывода 
void LCDG_SetMethod(unsigned char met)
{
  method = met;  
}

//отображает один пиксел на экране
void LCDG_PutPixel(unsigned char xPos, unsigned char yPos)
{
unsigned char realAdr;
unsigned char realPage;
unsigned char data;
unsigned char currentData;

  if ((xPos > 122) || (yPos > 31)) return;
  
  realAdr = xPos;
  realPage = PAGE0 + (yPos/8);
  data = yPos%8;
  
  if (realAdr < 61) {
    SetBit(PORT_LCD_CON, CS);
    realAdr = realAdr + 19;
  }
  else {
    ClearBit(PORT_LCD_CON, CS); 
    realAdr = realAdr - 61;
  }
  LCDG_WaitFLAG_BUSY();
  LCDG_SendCom(realPage);
  LCDG_SendCom(realAdr);
  LCDG_ReadData();
  currentData = LCDG_ReadData(); 
   switch(method){
    case MET_AND: {currentData &= ~(1<<data); break;}    
    case MET_OR : {currentData |= (1<<data); break;}
    case MET_XOR : {currentData ^= (1<<data); break;}
   }
  LCDG_SendCom(realAdr);
  LCDG_SendData(currentData);
}




//Знакогенератор____________________________________________________________________________

//устанавливает флаг инверсии
void LCDG_SetInv(unsigned char f)
{
  flag = f; 
}

//отображает один символ на жкд
//unsigned char PlaceArray[] = {0,8,16,24,32,40,48,56,64,72,80,88,96,104,112};
//unsigned char PlaceArray[] = {0,7,14,21,28,35,42,49,56,63,70,77,84,91,98,105,112};
unsigned char PlaceArray[] = {0,6,12,18,24,30,36,42,48,54,60,66,72,78,84,90,96,102,108,114};
  
void LCDG_SendSymbol(unsigned char xPos, unsigned char yPos,unsigned char data)
{
unsigned char i;
unsigned char realAdr;
unsigned char realPage = PAGE3 - yPos;
unsigned int  pointerFont = ((unsigned int)data<<2) + ((unsigned int)data<<1);
realAdr = PlaceArray[xPos];
xPos = realAdr;

  for(i = 0; i<=5; i++){
     if (realAdr < 61) {
      SetBit(PORT_LCD_CON, CS);
      realAdr = realAdr + 19;
    }
    else {
      ClearBit(PORT_LCD_CON, CS); 
      realAdr = realAdr - 61;
    }
    
    data = font_6x8_Data[pointerFont];
    if(flag) data = ~data;
    LCDG_SendCom(realPage);
    LCDG_SendCom(realAdr);
    LCDG_SendData(data);
    xPos++;
    realAdr = xPos;
    pointerFont++;
  }
}

//отображает строку на жкд
void LCDG_SendString(unsigned char xPos, unsigned char yPos, char * string)
{
  unsigned char data = 0;
  while(*string){
    data = *string++;
    LCDG_SendSymbol(xPos,yPos,data);
    xPos++;
  }
}



/****************************************************************************/
/*  Функция вывода прямой по алгоритму Брезенхема                           */
/****************************************************************************/
void LCDG_DrawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2)
{
        int dx, dy, i1, i2, i, kx, ky;
        int d;     
        int x, y;
        int flag;

        dy = y2 - y1;
        dx = x2 - x1;
        if (dx == 0 && dy == 0){
                LCDG_PutPixel(x1,y1);    
                return;
        }
        kx = 1; 
        ky = 1; 

        if( dx < 0 ){ dx = -dx; kx = -1; }
        else if(dx == 0)        kx = 0;    

        if(dy < 0) { dy = -dy; ky = -1; }

        if(dx < dy){ flag = 0; d = dx; dx = dy; dy = d; }
        else         flag = 1;

        i1 = dy + dy; d = i1 - dx; i2 = d - dx;
        x = x1; y = y1;

        for(i=0; i < dx; i++){
                LCDG_PutPixel(x,y);     

                if(flag) x += kx;
                else     y += ky;

                if( d < 0 ) 
                         d += i1;
                else{       
                         d += i2;
                         if(flag) y += ky; 
                         else     x += kx;
                }
        }
        LCDG_PutPixel(x,y);
}


/****************************************************************************/
/*  Функция вывода круга                                                    */
/****************************************************************************/
void LCDG_DrawCircle(unsigned char xc,unsigned char yc,unsigned char r)
{
  int  x,y,d;
  y = r; 
  d = 3-((int)r<<1);
  x = 0;
  
  while(x <= y)
  {
  LCDG_PutPixel(x+xc,y+yc);
  LCDG_PutPixel(x+xc,-y+yc);
  LCDG_PutPixel(-x+xc,-y+yc);
  LCDG_PutPixel(-x+xc,y+yc);
  LCDG_PutPixel(y+xc,x+yc);
  LCDG_PutPixel(y+xc,-x+yc);
  LCDG_PutPixel(-y+xc,-x+yc);
  LCDG_PutPixel(-y+xc,x+yc);
  if (d<0) {
    d = d+4*x+6;
  } else {
   d = d+4*(x-y)+10;
   y--;
  }
  x++;
  };  
  
}

/****************************************************************************/
/*  Функция рисования прямоугольника                                        */
/****************************************************************************/
void LCDG_DrawRect(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char fill)
{
  LCDG_DrawLine(x1, y1, x2, y1);
  LCDG_DrawLine(x1, y2, x2, y2);  
  LCDG_DrawLine(x1, (y1+1), x1, (y2-1));  
  LCDG_DrawLine(x2, (y1+1), x2, (y2-1));  
  if (fill){
    while(x1<x2){
      x1++;
      LCDG_DrawLine(x1, (y1+1), x1, (y2-1));
    }
    
  }
}
