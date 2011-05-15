.include "m32def.inc"
.equ   MOSI=5
.equ   SCK=7
.equ   SS=4
.equ   MISO=6
.equ  LCD_RS=0
.equ  LCD_RW=1
.equ  LCD_EN=2

.def  temp =   r16	  ;временный регистр
.def  temp1 =  r17	  ;временный регистр1
.def  temp2=  r18       ;временный регистр2
.def  temp3=  r22       ;временный регистр3
.def  lower =   r24
.def  upper =  r25
.def  count=r21
.def    Tenthousands=r2
.def    Thousands =r3
.def    Hundreds =r4
.def    Tens =r5
.def    Ones =r6

.dseg
Digit:     .byte 5
.cseg
.org 0x00
   rjmp  Reset

Reset:
  ldi temp,high(RAMEND) ; Main program start
  out SPH,temp ; Set stack pointer to top of RAM
  ldi temp,low(RAMEND)
  out SPL,temp ; Set stack pointer to top of RAM
  ldi temp,0xFF
  out  DDRA,temp
  ldi     temp,(1<<MOSI)|(1<<SCK)|(1<<SS)|(0<<MISO)
  out   DDRB,temp
  ldi     temp,(1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<CPOL)
  out   SPCR,temp
  rcall  LCD_INIT
  rcall Text_0
  
Main: 
  sts Digit  ,Ones    ;загрузка начальных сначений
  sts Digit+1,Tens
  sts Digit+2,Hundreds
  sts Digit+3,Thousands
  sts Digit+4,Tenthousands
  rcall Display                       ; Вывод строки
  ldi     XH,0b00000000   ;MSB
  ldi     XL,0b00000000   ;LSB
  rcall    SPI_0
  rcall    Convert
  rcall  DigitConvert 
  rjmp  Main
SPI_0:
   push temp1
  cbi    PORTB,SS 
  out   SPDR,XH
SPI_1:
  sbis   SPSR,SPIF
  rjmp  SPI_1
  out   SPDR,XL
  in  upper,SPDR
SPI_2:
  sbis   SPSR,SPIF
  rjmp  SPI_2
  in  lower,SPDR
  sbi    PORTB,SS
  pop temp1
  ret
Convert:
  push temp
  sbrs upper,1
  rjmp  Label1
  ldi  Temp1,0x85
  rcall LCD_command
  ldi temp1,'-'
  rcall  LCD_putchar
  com  upper
  andi upper,0x03
  com  lower
  ldi temp,25
  clr upper
  ldi count,8
  lsr lower
  rjmp  m8u_1
Label1:
  ldi  Temp1,0x85
  rcall LCD_command
  ldi temp1,'+'
  rcall  LCD_putchar
  ldi  temp,50
  ldi count,9
  ror upper
  ror lower
m8u_1:
  brcc  m8u_2
  add   upper,temp
m8u_2:
  ror upper
  ror lower
  dec  count
  brne  m8u_1
  cpi lower,0x34
  ldi  temp,0x21
  cpc upper,temp
  brlo End_0
  sbiw lower,0x19
END_0:
  pop temp
  ret

;*****************************************
;*****************************************************
;Конвертирует 16-разр. число в 5 десятичных цифры 
;******************************************************
DigitConvert:
     push upper
     push lower
     push temp
     clr    Tenthousands
     clr    Thousands
     clr    Hundreds
     clr    Tens
     clr    Ones 
FindTenthousands:    
     inc    Tenthousands 
     subi    lower,0x10            ;Find out how many 10000's
     sbci    upper,0x27
     brcc    FindTenthousands   
     ldi    temp,0x10           ;Subtracted one too many, add back on.
     add    lower,temp
     ldi    temp,0x27
     adc    upper,temp      ;    
     dec    Tenthousands 
FindThousands:    
     inc    Thousands  
     subi    lower,0xE8           ;Find out how many 1000's
     sbci    upper,0x03
     brcc    FindThousands   
     ldi    temp,0xE8             ;Subtracted one too many, add back on.
     add    lower,temp
     ldi    temp,0x03
     adc    upper,temp      ;    
     dec    Thousands 

FindHundreds:  
     inc    Hundreds  
     subi    lower,100            ;Find out how many 100's
     sbci    upper,0
     brcc    FindHundreds    
     ldi    temp,100            ;Subtracted one too many, add back on.
     add    lower,temp
     ldi    temp,0
     adc    upper,temp      ;    
     dec    Hundreds             

FindTens:
     inc    Tens    
     subi    lower,10             ;Find out how many 10's
     sbci    upper,0x00
     brcc    FindTens      
     ldi       temp,10            ;Subtracted one too many, add back on.
     add    lower,temp
     ldi       temp,0
     adc     upper,temp
     dec     Tens

FindOnes:
     inc    Ones     
     subi    lower,1            ;Find out how many 1's
     sbci    upper,0
     brcc    FindOnes   
     ldi    temp,1            ;Subtracted one too many, add back on.
     add    lower,temp
     ldi    temp,0
     adc    upper,temp
     dec    Ones  
     pop temp
     pop lower
     pop upper         
     ret

;*********************************************************
;***************** LCD **********************************
;********************************************************* 
;Инициализация LCD
;*********************************************************
LCD_INIT:
  ldi temp1,0x33             ;инициализация LCD в 4-bit способе.
  call LCD_command       ;функция команд
  call   DELAY_2ms          ;задержка инициализации
  ldi temp1,0x32             ;инициализация LCD в 4-bit способе.
  call LCD_command       ;функция команд
  call   DELAY_2ms          ;задержка инициализации
  ldi temp1,0x28             ;инициализация LCD 4 бита, 2 строки, 5*7 точек
  call LCD_command
  call   DELAY_2ms          ;задержка инициализации
  ldi temp1,0x0C             ;включен дисплей, курсор выключен
  call LCD_command           
  ldi temp1,0x01             ;очистка дисплея
  call LCD_command      
  call   DELAY_2ms          ;задержка для очистки дисплея   
  ldi temp1,0x06             ;перемещение курсора слева-направо инкр.
  call LCD_command
  ret
;******************************************************
Display:
      push Temp1
      ldi  Temp1,0x8C
      rcall LCD_command
      ldi temp1,0xDF
      rcall  LCD_putchar
      ldi temp1,'C'
      rcall  LCD_putchar

     ldi Temp1,0x86            ;адрес установки курсора
     rcall LCD_command

     lds Temp1,Digit+4        ;и .т.д
     rcall Decoder
     rcall DELAY_100us 

     lds Temp1,Digit+3        ;и .т.д
     rcall Decoder
     rcall DELAY_100us
          
     lds Temp1,Digit+2        ;и .т.д
     rcall Decoder
     rcall DELAY_100us

     ldi  Temp1,0x89
     rcall LCD_command
     ldi temp1,','
     rcall  LCD_putchar
    
     lds Temp1,Digit+1
     rcall Decoder
     rcall DELAY_100us
    
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
   in   temp,PORTA
   andi  temp,0x0F
   or     temp,temp2
   out   PORTA,temp
   cbi    PORTA,LCD_RS 
   cbi    PORTA,LCD_RW 
   sbi    PORTA,LCD_EN
   call   SDELAY 
   cbi    PORTA,LCD_EN  
   call   DELAY_100us

   mov  temp2,temp1
   swap temp2
   andi  temp2,0xF0 
   in   temp,PORTA
   andi  temp,0x0F
   or     temp,temp2
   out   PORTA,temp
   sbi    PORTA,LCD_EN
   call   SDELAY
   cbi    PORTA,LCD_EN
   call   DELAY_100us 
   pop temp
   ret
;****************************************
LCD_putchar:
   push temp
   push temp2
   mov  temp2,temp1
   andi  temp2,0xF0
   in   temp,PORTA
   andi  temp,0x0F
   or     temp,temp2
   out   PORTA,temp
   sbi    PORTA,LCD_RS 
   cbi    PORTA,LCD_RW 
   sbi    PORTA,LCD_EN
   call   SDELAY 
   cbi    PORTA,LCD_EN  
   
   mov  temp2,temp1
   swap temp2 
   andi  temp2,0xF0 
   in   temp,PORTA
   andi  temp,0x0F
   or     temp,temp2
   out   PORTA,temp
   sbi    PORTA,LCD_EN
   call   SDELAY
   cbi    PORTA,LCD_EN
   call   DELAY_100us 
   pop temp
   pop temp2
   ret
;****************************************
;Задержки
;****************************************
SDELAY:
   nop
   nop
   ret
DELAY_100us:
   push  temp1
   ldi      temp1,60
DR0:
   call     SDELAY
   dec    temp1
   brne  DR0
   pop   temp1
   ret
DELAY_2ms:
   push  temp1
   ldi      temp1,20
LDR0:
   call   DELAY_100us
   dec    temp1
   brne  LDR0
   pop   temp1
   ret
;****************************************************
; Выводимоё число
;****************************************************
Decoder:
  push  temp1
  ldi ZL,Low(DcMatrix*2)  
  ldi ZH,High(DcMatrix*2) 
  ldi Temp2,0            ;прибавление переменной
  add ZL,Temp1        ;к 0-му адресу массива
  adc ZH,Temp2
  lpm  
  mov Temp1,r0
  rcall LCD_putchar
  pop   temp1
  ret 

DcMatrix:
.db '0','1','2','3','4','5','6','7','8','9'
;****************************************************
; Выводимый текст 1
;****************************************************
Text_0:
  push temp1
  push temp
  clr  count
  clr temp1
  ldi Temp1,0x80                 ;адрес установки курсора
  rcall LCD_command	
  ldi ZL,Low(Text01*2) 
  ldi ZH,High(Text01*2)
  ldi count,6
loop1:
  lpm  temp1,Z+
  rcall LCD_putchar
  dec  count
  brne  loop1
  pop temp1
  pop temp
  ret 
Text01:
.db  0x54,0x65,0x6D,0x70,0x3D
