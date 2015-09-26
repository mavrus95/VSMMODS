;*********************************************************************
;��������� ����������� � ��� ������ �������� TMP36
;������ 3
;����     14.05.2011
;AVR      ATmega32
;�������� �������	1���
;��������:  ������������ ������ �������������� ������� TMP36
;�����      VALE1

.include "m32def.inc"

.equ  LCD_RS=0
.equ  LCD_RW=1
.equ  LCD_EN=2

.def  temp =   r16	  ;��������� �������
.def  temp1 =  r17	  ;��������� �������1
.def  temp2=  r18       ;��������� �������2
.def  temp3=  r19       ;��������� �������3
.def  lower =   r20
.def  upper =  r21
.def  count=r22           ;�������
.def  number=r23        ;����� ������� 
.def    Thousands =r2
.def    Hundreds =r3
.def    Tens =r4
.def    Ones =r5

.dseg
     Digit:     .byte 4
.cseg
.org  0x00
     rjmp Init ; Reset vector
	reti ; Int vector 1
	reti ; Int vector 2
	reti ; Int vector 3
	reti ; Int vector 4
	reti ; Int vector 5
	reti ; Int vector 6
	reti ; Int vector 7
                reti  ; Int vector 8
.org 0x12
     rjmp  T1_OV_ISR ; Int vector 9
	reti ; Int vector 10
	reti ; Int vector 11
	reti ; Int vector 12
	reti ; Int vector 13
	reti ; Int vector 14
	reti ; Int vector 15
	reti ; Int vector 16
	reti ; Int vector 17
	reti ; Int vector 18
	reti ; Int vector 19
	reti ; Int vector 20

Init:
  ldi temp,high(RAMEND) ; Main program start
  out SPH,temp ; Set stack pointer to top of RAM
  ldi temp,low(RAMEND)
  out SPL,temp
  ldi temp,0xFF
  out  DDRC,temp                   ;��  �����
  out  DDRB,temp                   ;��  �����
  ldi number,0b00110001       ;������������� ������ �������   
  ldi Temp3,0b00000001         ;������������� ����������
  out PortB,Temp3       ;����� � ���� 
  ldi   temp,0xF0
  out   TCNT1H,temp
   ldi   temp,0x0F
  out   TCNT1L,temp
  clr temp
  out   TCCR1A,temp
  ldi    temp,0x05        ;clk/1024
  out   TCCR1B,temp
  ldi temp,0x00
  out  DDRA,temp    
  ldi temp,0x87
  out  ADCSRA,temp
  ldi temp,0xC0
  out  ADMUX,temp
  ldi    temp,(1<<TOIE1)
  out   TIMSK,temp
  sei 
  rcall  LCD_INIT                ;������������� LCD
  rcall Text_OUT                 ;��������� �����
  
Main: 
  sts Digit  ,Ones    ;�������� ��������� ��������
  sts Digit+1,Tens
  sts Digit+2,Hundreds
  sts Digit+3,Thousands
  rcall Display
  rcall CONV_ADC
  rjmp  Main
;********************************************************
;�������������� �����������
;********************************************************
CONV_ADC:
   sbi  ADCSRA,ADSC
CHECK_FLAG:
   sbis  ADCSRA,ADIF
   rjmp  CHECK_FLAG
   sbi   ADCSRA,ADIF
   in    lower,ADCL
   in    upper,ADCH
   cpi lower,0xC8
   ldi  temp,0x00
   cpc upper,temp
   brsh m8u                    ;�������,���� ����������� 0 ��� ����         
   ldi  Temp1,0x85          ;��������� ����������� ���� 0
   rcall LCD_command
   ldi temp1,'-'                 ;���� "-"
   rcall  LCD_putchar
   subi  lower,0xC9                   
   sbci  upper,0x00
   com upper
   com lower
   rjmp  m8u_0
m8u:
   subi  lower,0xC8            ;��������� ����������� ���� 0   
   sbci  upper,0x00
   ldi  Temp1,0x85             ;���� "+"
   rcall LCD_command
   ldi temp1,'+'
   rcall  LCD_putchar
m8u_0:                             ;���������  
   ldi  temp,5
   ldi count,9
   lsr  upper
   ror lower
m8u_1:
   brcc  m8u_2
   add   upper,temp
m8u_2:
   ror upper
   ror lower
   dec  count
   brne  m8u_1
   sbi  ADCSRA,ADSC
   cpi lower,0x5B           ;������ �������� 0.2 
   ldi  temp,0x04           ;������� � 111.5 �������
   cpc upper,temp
   brlo End_0
   subi lower,0x02
END_0:
   rcall  DigitConvert
   ret
;**************************************************
;��������� ����������
;**************************************************
T1_OV_ISR:
   push  temp
   cpi Temp3,0b00000100        ;�������� � ������� ����.
   breq Init_0             ;���� ����� - �������� ���. ����.
   lsl Temp3             ;����� - ����� �����
   rjmp Output           ;������� �� ����� � ����

Init_0:   
   ldi Temp3,0b00000001         ;��������� ���. ��������
   ldi number,0b00110000        ;��������� ���. �������� ������ �������   
Output:  
   out PortB,Temp3       ;����� � ����
   inc  number
   ori number,0x30
   ldi   temp,0xF5       ;��������� �������� ������� 
   out  TCNT1H,Temp
   ldi   temp,0x0F
   out  TCNT1L,Temp
   pop  temp
   reti
;*****************************************************
;������������ 16-����. ����� � 4 ���������� ����� 
;******************************************************
DigitConvert:
     push upper
     push lower
     push temp
     clr    Thousands
     clr    Hundreds
     clr    Tens
     clr    Ones 
FindThousands:    
     inc    Thousands  
     subi    lower,0xE8           ;������� ������� �����
     sbci    upper,0x03
     brcc    FindThousands   
     ldi    temp,0xE8          
     add    lower,temp
     ldi    temp,0x03
     adc    upper,temp      ;    
     dec    Thousands 

FindHundreds:  
     inc    Hundreds  
     subi    lower,100            ;;������� ������� �����
     sbci    upper,0
     brcc    FindHundreds    
     ldi    temp,100            
     add    lower,temp
     ldi    temp,0
     adc    upper,temp      ;    
     dec    Hundreds             

FindTens:
     inc    Tens    
     subi    lower,10             ;;������� ������� ��������
     sbci    upper,0x00
     brcc    FindTens      
     ldi       temp,10            
     add    lower,temp
     ldi       temp,0
     adc     upper,temp
     dec     Tens

FindOnes:
     inc    Ones     
     subi    lower,1            ;;������� ������� ������
     sbci    upper,0
     brcc    FindOnes   
     ldi    temp,1            
     add    lower,temp
     ldi    temp,0
     adc    upper,temp
     dec    Ones  
     pop temp
     pop lower
     pop upper         
     ret
;***************** LCD **********************************
LCD_INIT:
  ldi temp1,0x33             ;������������� LCD � 4-bit �������.
  rcall LCD_command       ;������� ������
  rcall   DELAY_2ms          ;�������� �������������
  ldi temp1,0x32             ;������������� LCD � 4-bit �������.
  rcall LCD_command       ;������� ������
  rcall   DELAY_2ms          ;�������� �������������
  ldi temp1,0x28             ;������������� LCD 4 ����, 2 ������, 5*7 �����
  rcall LCD_command
  rcall   DELAY_2ms          ;�������� �������������
  ldi temp1,0x0C             ;������� �������, ������ ��������
  rcall LCD_command           
  ldi temp1,0x01             ;������� �������
  rcall LCD_command      
  rcall   DELAY_2ms          ;�������� ��� ������� �������   
  ldi temp1,0x06             ;����������� ������� �����-������� ����.
  rcall LCD_command
  ret
;******************************************************
Display:
      push Temp1
      ldi  Temp1,0xC8          ;����� ��������� ������� LCD ��� ������ �������
      rcall LCD_command
      mov temp1,number     ;����� ������ ������� 
      rcall  LCD_putchar
      sbrc number,2             ;������� ����� ������ ������ 3
      clr number
      ldi  Temp1,0x8B           ;����� ��������� ������� LCD ��� ������
      rcall LCD_command
      ldi temp1,0xDF           ;���� �������
      rcall  LCD_putchar
      ldi temp1,'C'               ;���� �������
      rcall  LCD_putchar

     ldi Temp1,0x86            ;����� ��������� ������� LCD
     rcall LCD_command     ;��� ������ �������� �����������
  
     lds Temp1,Digit+3        ;� .�.�
     rcall Decoder
     rcall DELAY_100us

     lds Temp1,Digit+2        ;� .�.�
     rcall Decoder
     rcall DELAY_100us
    
     lds Temp1,Digit+1        ;� .�.�  
     rcall Decoder
     rcall DELAY_100us

     ldi  Temp1,0x89             ;����� �������
     rcall LCD_command
     ldi temp1,','
     rcall  LCD_putchar 
   
     lds Temp1,Digit
     rcall Decoder
     rcall DELAY_100us
     pop Temp1
     ret
;***********************************************
LCD_command:
   push temp
   mov  temp2,temp1
   andi  temp2,0xF0
   in   temp,PORTC
   andi  temp,0x0F
   or     temp,temp2
   out   PORTC,temp
   cbi    PORTC,LCD_RS 
   cbi    PORTC,LCD_RW 
   sbi    PORTC,LCD_EN
   rcall   SDELAY 
   cbi    PORTC,LCD_EN  
   rcall   DELAY_100us

   mov  temp2,temp1
   swap temp2
   andi  temp2,0xF0 
   in   temp,PORTC
   andi  temp,0x0F
   or     temp,temp2
   out   PORTC,temp
   sbi    PORTC,LCD_EN
   rcall   SDELAY
   cbi    PORTC,LCD_EN
   rcall   DELAY_100us 
   pop temp
   ret
;****************************************
LCD_putchar:
   push temp
   push temp2
   mov  temp2,temp1
   andi  temp2,0xF0
   in   temp,PORTC
   andi  temp,0x0F
   or     temp,temp2
   out   PORTC,temp
   sbi    PORTC,LCD_RS 
   cbi    PORTC,LCD_RW 
   sbi    PORTC,LCD_EN
   rcall   SDELAY 
   cbi    PORTC,LCD_EN  
   
   mov  temp2,temp1
   swap temp2 
   andi  temp2,0xF0 
   in   temp,PORTC
   andi  temp,0x0F
   or     temp,temp2
   out   PORTC,temp
   sbi    PORTC,LCD_EN
   rcall   SDELAY
   cbi    PORTC,LCD_EN
   rcall   DELAY_100us 
   pop temp
   pop temp2
   ret
;****************************************
;��������
;****************************************
SDELAY:
   nop
   nop
   ret
DELAY_100us:
   push  temp1
   ldi      temp1,60
DR0:
   rcall     SDELAY
   dec    temp1
   brne  DR0
   pop   temp1
   ret
DELAY_2ms:
   push  temp1
   ldi      temp1,20
LDR0:
   rcall   DELAY_100us
   dec    temp1
   brne  LDR0
   pop   temp1
   ret
;****************************************************
; �������� �����
;****************************************************
Decoder:
  push  temp1
  ldi ZL,Low(DcMatrix*2)  
  ldi ZH,High(DcMatrix*2) 
  ldi Temp2,0            ;����������� ����������
  add ZL,Temp1        ;� 0-�� ������ �������
  adc ZH,Temp2
  lpm  
  mov Temp1,r0
  rcall LCD_putchar
  pop   temp1
  ret 

DcMatrix:
.db '0','1','2','3','4','5','6','7','8','9'
;****************************************************
; ��������� ����� 1
;****************************************************
Text_OUT:
  push temp1
  clr  count
  clr temp1
  ldi Temp1,0x80                 ;����� ��������� �������
  rcall LCD_command	
  ldi ZL,Low(Text01*2) 
  ldi ZH,High(Text01*2)
  ldi count,6
  rcall  loop1
  clr  count 
  clr temp1
  ldi Temp1,0xC0                ;����� ��������� �������
  rcall LCD_command
  ldi ZL,Low(Text02*2) 
  ldi ZH,High(Text02*2)
  ldi count,8
  rcall  loop1
  pop temp1
   ret
loop1:
  lpm  temp1,Z+
  rcall LCD_putchar
  dec  count
  brne  loop1
  ret 
Text01:
.db  0x54,0x65,0x6D,0x70,0x3D,0
Text02:
.db 0x53,0x65,0x6E,0x73,0x6F,0x72,0x73,0x3D
