#include <mega16.h>
#include "lcd_graph_lib.h"

void main( void )
{
  LCDG_InitPort();
  LCDG_InitLcd();
  LCDG_ClearLcd(0, 122);
  LCDG_SendString(0, 0, "��������� ���� 12232");  
 // LCDG_DrawLine(0,0, 120, 30);
 // LCDG_DrawCircle(60,15, 14);
  while(1);
}
