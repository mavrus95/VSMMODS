/*****************************************************
This program was produced by the
CodeWizardAVR V2.03.9 Standard
Automatic Program Generator
© Copyright 1998-2008 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 26.04.2009
Author  : XXX
Company : XXX-COMPANY
Comments: 


Chip type               : ATmega8
Program type            : Application
AVR Core Clock frequency: 4,000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/

#include <mega8.h>

// Alphanumeric LCD Module functions
#asm
   .equ __lcd_port=0x18 ;PORTB
#endasm
#include <lcd.h>

#include <delay.h>

unsigned long volt, volt_reg=0;


#define ADC_VREF_TYPE 0xC0

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
  ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);
// Delay needed for the stabilization of the ADC input voltage
  delay_us(10);
// Start the AD conversion
  ADCSRA|=0x40;
// Wait for the AD conversion to complete
  while ((ADCSRA & 0x10)==0);
  ADCSRA|=0x10;
  return ADCW;
}


void lcd_info(void)
{ 
  lcd_gotoxy(0,0);
  lcd_putsf ("Voltage");  
  lcd_gotoxy(0,1);
  lcd_putchar (volt/1000%10+0x30);
  lcd_putchar (volt/100%10+0x30);
  lcd_putchar ('.');
  lcd_putchar (volt/10%10+0x30);
  lcd_putchar (volt%10+0x30);
  lcd_putsf (" Volt");
  }


// Declare your global variables here

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port B initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=In Func2=Out Func1=Out Func0=Out 
// State7=0 State6=0 State5=0 State4=0 State3=T State2=0 State1=0 State0=0 
PORTB=0x00;
DDRB=0xF7;

// Port C initialization
// Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTC=0x00;
DDRC=0x00;

// Port D initialization
// Func7=In Func6=In Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=P State6=P State5=0 State4=0 State3=0 State2=0 State1=0 State0=0 
PORTD=0xC0;
DDRD=0x3F;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
TCCR0=0x00;
TCNT0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer 1 Stopped
// Mode: Normal top=FFFFh
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer 1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer 2 Stopped
// Mode: Normal top=FFh
// OC2 output: Disconnected
ASSR=0x00;
TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
MCUCR=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// ADC initialization
// ADC Clock frequency: 1000,000 kHz
// ADC Voltage Reference: Int., cap. on AREF
ADMUX=ADC_VREF_TYPE & 0xff;
ADCSRA=0x82;

// LCD module initialization
lcd_init(16);

// Global enable interrupts
#asm("sei")

while (1)
      {
      // Place your code here
      if ((PIND.6==0) && (volt_reg>0)) {delay_ms(200); volt_reg--;};
      if ((PIND.7==0) && (volt_reg<63)) {delay_ms(200); volt_reg++;};
      PORTD&=0b11000000;
      PORTD|=volt_reg;
      volt=read_adc(0);
      volt=(int)((volt*2560)/1024);
      lcd_info();
      };
}
