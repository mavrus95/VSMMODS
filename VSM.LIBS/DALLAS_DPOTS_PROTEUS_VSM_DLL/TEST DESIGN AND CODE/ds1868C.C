
#include"ds1868C.H"
#include "LCD.C"
#include "DS1868DRIVER.C"


#include <STDLIB.H>
#include <stdio.h>
#include <math.h>


void init(void);
void set_pot (int pot_num, int new_value);
void init_pots0 (void);
void init_pots (int ssb);
void init_pots5050 (int ssb);

#define RST1 PIN_b2
#define CLK PIN_b1
#define DI PIN_b0
#define NUM_POTS 2


void init(void)
{
   INIT_SUB_CIRCUITS();
  // init_pots0();
   LCD_INITIALMODE(2);
}
void main ()
{
   int ssb;
   int SENT;
   BYTE potval[2],newpotval[2], oldval[2];
   init();
   delay_ms ( 50 );

   LCD_WRITE_COMMAND ( CLEAR_DISP );
   delay_ms ( 10 );
   LCD_MTPOS ( LINE_1 );
   printf(LCD_WRITE_CHAR,"Potvalue 1 0x%x",potval[0]);
   LCD_MTPOS ( LINE_2 );
   printf(LCD_WRITE_CHAR,"Potvalue 2 0x%X",potval[1]);

   do
   {
      ssb=SW_3STATE();   // get state of pot choice switch
      ssb=!ssb;
      if (SW_4PRESSED())
      {
         potval[ssb] = newpotval[ssb] = 0;
         init_pots(ssb);
      }
      else if (SW_5PRESSED())
      {
         potval[ssb] = newpotval[ssb] = 127;

         init_pots5050(ssb);
      }
      else if (SW_1PRESSED())
      {
         if(ssb==0)
         {
            if (newpotval[0] >= 0X01) newpotval[0]--; else newpotval[0]=0x00;
            if (potval[0] != newpotval[0])
            {
               potval[0] = newpotval[0];
               set_pot (ssb, potval[0]);
            }
         }
         else
         {
            if (newpotval[1] >= 0X01) newpotval[1]--; else newpotval[1]=0x00;
            if (potval[1] != newpotval[1])
            {
               potval[1] = newpotval[1];
               set_pot (ssb, potval[1]);
            }
         }
      }
      else if (SW_2PRESSED())
      {
         if(ssb==0)
         {
            if (newpotval[0] <= 0XFE) newpotval[0]++; else newpotval[0]=0xFF;
            if (potval[0] != newpotval[0])
            {
               potval[0] = newpotval[0];
               set_pot (ssb, potval[0]);
            }
         }
         else
         {
            if (newpotval[1] <= 0XFE) newpotval[1]++; else newpotval[1]=0xFF;
            if (potval[1] != newpotval[1])
            {
               potval[1] = newpotval[1];
               set_pot (ssb, potval[1]);
            }
         }
      }
     
          LCD_MTPOS ( LINE_1 + 13 );
          printf(LCD_WRITE_CHAR,"%X",potval[0]);
		    LCD_MTPOS ( LINE_2 + 13 );
		    printf(LCD_WRITE_CHAR,"%X",potval[1]);
      
   } while (TRUE);
}

void set_pot (int pot_num, int new_value) {
   BYTE i;
   BYTE cmd[3];
   BYTE pots[2];
   if (pot_num >= NUM_POTS)
      return;
   pots[pot_num] = new_value;
   cmd[0]=pots[0];
   cmd[1]=pots[1];
   cmd[2]=0;
   for(i=1;i<=7;i++)
     shift_left(cmd,3,0);
   output_high(RST1);
   delay_us(2);
   for(i=1;i<=17;i++) {
      output_bit(DI, shift_left(cmd,3,0));
      delay_us(2);
      output_high(CLK);
      delay_us(2);
      if(i>=17)
         output_low(RST1);
      output_low(CLK);
      delay_us(2);
   }
}
void init_pots0(void)
{
   set_pot (0,0);
   delay_ms ( 1 );
   set_pot (0,0);
   delay_ms ( 1 );
}
void init_pots (int ssb)
{
   set_pot (ssb,0);
   delay_ms ( 1 );
   set_pot (ssb,0);
   delay_ms ( 1 );
}
void init_pots5050 (int ssb)
{
   set_pot (ssb,127);
   delay_ms ( 1 );
   set_pot (ssb,127);
   delay_ms ( 1 );
}
