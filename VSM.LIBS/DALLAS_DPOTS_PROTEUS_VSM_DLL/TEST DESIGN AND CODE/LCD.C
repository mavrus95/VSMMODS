//////////////////////////////////////
// SET AMOUNT OF COLUMBS TO DISPLAY //
//////////////////////////////////////
#define DISPLAY_COLS  20            //
//////////////////////////////////////
////////////////////////////////////
// DEFINE PINS IN USE FOR THE LCD //
////////////////////////////////////
#define LCD_D0  PIN_D4
#define LCD_D1  PIN_D5
#define LCD_D2  PIN_D6
#define LCD_D3  PIN_D7
#define LCD_EN  PIN_D3
#define LCD_RS  PIN_D2

//LCD Commands

#define CLEAR_DISP         0X01
#define LCD_HOME	         0X02
#define LCD_SETMODE	      0X04
#define LCD_SETVISIBLE	   0X08
#define LCD_SHIFT	         0X10
#define LCD_SETFUNCTION    0X20
#define LCD_SETCGADDR	   0X40
#define LCD_SETDDADDR	   0X80

// cgram charicter set
BYTE lev1[] = {0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X1F,'\n'};

BYTE lev2[] = {0X00,0X00,0X00,0X00,0X00,0X00,0X1F,0X1F,'\n'};

BYTE lev3[] = {0X00,0X00,0X00,0X00,0X00,0X1F,0X1F,0X1F,'\n'};

BYTE lev4[] = {0X00,0X00,0X00,0X00,0X1F,0X1F,0X1F,0X1F,'\n'};

BYTE lev5[] = {0X00,0X00,0X00,0X1F,0X1F,0X1F,0X1F,0X1F,'\n'};

BYTE lev6[] = {0X00,0X00,0X1F,0X1F,0X1F,0X1F,0X1F,0X1F,'\n'};

BYTE lev7[] = {0X00,0X1F,0X1F,0X1F,0X1F,0X1F,0X1F,0X1F,'\n'};

BYTE lev8[] = {0X1F,0X1F,0X1F,0X1F,0X1F,0X1F,0X1F,0X1F,'\n'};

// cgram charicter set
BYTE lev11[] = {0X00,0X00,0X00,0X00,0X04,0X04,0X0E,0X04,'\n'};

BYTE lev21[] = {0X00,0X00,0X00,0X04,0X04,0X14,0X18,0X1C,'\n'};

BYTE lev31[] = {0X00,0X00,0X08,0X1E,0X08,0X00,0X00,0X00,'\n'};

BYTE lev41[] = {0X1C,0X18,0X14,0X04,0X00,0X00,0X00,0X00,'\n'};

BYTE lev51[] = {0X04,0X0E,0X04,0X04,0X00,0X00,0X00,0X00,'\n'};

BYTE lev61[] = {0X07,0X03,0X05,0X04,0X04,0X00,0X00,0X00,'\n'};

BYTE lev71[] = {0X00,0X00,0X00,0X02,0X0F,0X02,0X00,0X00,'\n'};

BYTE lev81[] = {0X00,0X00,0X00,0X04,0X04,0X05,0X03,0X07,'\n'};


#define LINE_1          0X00
#define LINE_2          0X40

#if DISPLAY_COLS == 40
#define LINE_3          0X28
#define LINE_4          0X68
#endif

#if DISPLAY_COLS == 20
#define LINE_3          0X14
#define LINE_4          0X54
#endif

#if DISPLAY_COLS == 16
#define LINE_3          0X10
#define LINE_4          0X50
#endif

//////////////////////

void LCD_INITIALMODE       ( int CGCHARSET );
void CLEAR_C_SCREEN        ( void );
void LCD_MTPOS             ( char D_ );
void LCD_WR_CHARCG         ( int CGCHARSET );
void LCD_WR_CGRAM          ( BYTE *map_pointer, int sector);
void LCD_WRITE_CHAR        ( char D_ );
void LCD_WRITE_COMMAND     ( char D_ );
void LCD_NIBBLELOAD        ( void );
void LCD_PUT_DATA          ( unsigned int D_ );

void LCD_INITIALMODE ( void )
{
    LCD_PUT_DATA ( 0X00 );
    delay_ms ( 15 );
    output_low ( LCD_RS );
    LCD_PUT_DATA ( 0X03 );
    LCD_NIBBLELOAD();
    LCD_NIBBLELOAD();
    LCD_NIBBLELOAD();
    LCD_PUT_DATA ( 0X02 );       /* set 4-bit interface                       */
    LCD_NIBBLELOAD();
    LCD_WRITE_COMMAND ( 0X2C );  /* function set (all lines, 5x7 characters)  */
    LCD_WRITE_COMMAND ( 0X0C );  /* display ON, cursor off, no blink          */
    LCD_WRITE_COMMAND ( 0X06 );  /* entry mode set, increment & scroll left   */
}
void CLEAR_C_SCREEN ( void )
{
   LCD_WRITE_COMMAND(CLEAR_DISP);
   LCD_WRITE_COMMAND(LCD_SETDDADDR+0X00);
}
void LCD_MTPOS ( char D_ )
{
    LCD_PUT_DATA ( swap ( D_ ) | 0X08 );
    LCD_NIBBLELOAD();
    LCD_PUT_DATA ( swap ( D_ ) );
    LCD_NIBBLELOAD();
}
void LCD_WR_CHARCG( int CGCHARSET )
{
   // Write Custom Characters to CGRAM
    if (CGCHARSET == 1)
    {
      LCD_WR_CGRAM(lev1, 0X00);            /* Offset 0 -  0x40h-0x47h in CGRAM. */
      LCD_WR_CGRAM(lev2, 0X08);            /* Offset 8 -  0x48h-0x4Fh in CGRAM. */
      LCD_WR_CGRAM(lev3, 0X10);            /* Offset 16 - 0x50h-0x57h in CGRAM. */
      LCD_WR_CGRAM(lev4, 0X18);            /* Offset 24 - 0x58h-0x5Fh in CGRAM. */
      LCD_WR_CGRAM(lev5, 0X20);            /* Offset 32 - 0x60h-0x67h in CGRAM. */
      LCD_WR_CGRAM(lev6, 0X28);            /* Offset 40 - 0x68h-0x6Fh in CGRAM. */
      LCD_WR_CGRAM(lev7, 0X30);            /* Offset 48 - 0x70h-0x77h in CGRAM. */
      LCD_WR_CGRAM(lev8, 0X38);            /* Offset 56 - 0x78h-0x7Fh in CGRAM. */
    }
    if (CGCHARSET == 2)
    {
      LCD_WR_CGRAM(lev11, 0X00);            /* Offset 0 -  0x40h-0x47h in CGRAM. */
      LCD_WR_CGRAM(lev21, 0X08);            /* Offset 8 -  0x48h-0x4Fh in CGRAM. */
      LCD_WR_CGRAM(lev31, 0X10);            /* Offset 16 - 0x50h-0x57h in CGRAM. */
      LCD_WR_CGRAM(lev41, 0X18);            /* Offset 24 - 0x58h-0x5Fh in CGRAM. */
      LCD_WR_CGRAM(lev51, 0X20);            /* Offset 32 - 0x60h-0x67h in CGRAM. */
      LCD_WR_CGRAM(lev61, 0X28);            /* Offset 40 - 0x68h-0x6Fh in CGRAM. */
      LCD_WR_CGRAM(lev71, 0X30);            /* Offset 48 - 0x70h-0x77h in CGRAM. */
      LCD_WR_CGRAM(lev81, 0X38);            /* Offset 56 - 0x78h-0x7Fh in CGRAM. */
    }
    LCD_WRITE_COMMAND(LCD_SETDDADDR);
}
void LCD_WR_CGRAM (BYTE *map_pointer, int sector)
{
   LCD_WRITE_COMMAND(LCD_SETCGADDR + sector); // Set the CG RAM address to fill.
   while (*map_pointer != '\n')  // check for end of line and terminate while loop
   {
      LCD_WRITE_CHAR(*map_pointer++);  // write data to cgram address and increment pointer
   }
}
void LCD_WRITE_CHAR( char  D_ )
{
    output_high ( LCD_RS );
    LCD_PUT_DATA ( swap ( D_ ) );
    LCD_NIBBLELOAD();
    LCD_PUT_DATA ( swap ( D_ ) );
    LCD_NIBBLELOAD();
    output_low ( LCD_RS );
}
void LCD_WRITE_COMMAND( char D_ )
{
    LCD_PUT_DATA ( swap ( D_ ) );
    LCD_NIBBLELOAD();
    LCD_PUT_DATA ( swap ( D_ ) );
    LCD_NIBBLELOAD();
}
void LCD_NIBBLELOAD( void )
{
    output_high ( LCD_EN );
    delay_us ( 10 );
    output_low ( LCD_EN );
    delay_us ( 200 );
}
void LCD_PUT_DATA( unsigned int D_ )
{
    output_bit ( LCD_D0, D_ & 0X01 );
    output_bit ( LCD_D1, D_ & 0X02 );
    output_bit ( LCD_D2, D_ & 0X04 );
    output_bit ( LCD_D3, D_ & 0X08 );
}






