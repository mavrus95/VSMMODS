#define BLINK_OFF_CURSOR_OFF 0x0C 
#define BLINK_ON_CURSOR_OFF  0x0D 
#define BLINK_OFF_CURSOR_ON  0x0E 
#define BLINK_ON_CURSOR_ON   0x0F 
#define CLEAR                0x01 
#define HOME                 0x02 
#define LCD_OFF              0x08 
#define LINE_1               0x80 
#define LINE_2               0xC0 
#define LINE_3               0x94 
#define LINE_4               0xD4 


extern void delay(unsigned long dly);			// delay routine
extern char busy_lcd();							// read busy state of lcd
extern void init_lcd();							// initialize lcd
extern void locate_lcd(char row, char col);		// locate cursor at row, col
extern void wrstr_lcd(char *ptrbuff);			// write string to display
extern void clr_lcd();							// clear display
extern void control(char cntrl);				// clear display

