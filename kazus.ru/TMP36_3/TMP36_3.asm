;*********************************************************************
;Измерение температуры в трёх точках датчиком TMP36
;версия 3
;Дата     14.05.2011
;AVR      ATmega32
;Тактовая частота	1МГц
;Описание:  Демонстрация модели температурного датчика TMP36
;Автор      VALE1

.include "m32def.inc"

.equ  LCD_RS=0
.equ  LCD_RW=1
.equ  LCD_EN=2

.def  temp =   r16	  ;временный регистр
.def  temp1 =  r17	  ;временный регистр1
.def  temp2=  r18       ;временный регистр2
.def  temp3=  r19       ;временный регистр3
.def  lower =   r20
.def  upper =  r21
.def  count=r22           ;счётчик
.def  number=r23        ;номер датчика 
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
  out  DDRC,temp                   ;на  выход
  out  DDRB,temp                   ;на  выход
  ldi number,0b00110001       ;инициализация номера датчика   
  ldi Temp3,0b00000001         ;инициализация индикатора
  out PortB,Temp3       ;вывод в порт 
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
  rcall  LCD_INIT                ;инициализация LCD
  rcall Text_OUT                 ;выводимый текст
  
Main: 
  sts Digit  ,Ones    ;загрузка начальных сначений
  sts Digit+1,Tens
  sts Digit+2,Hundreds
  sts Digit+3,Thousands
  rcall Display
  rcall CONV_ADC
  rjmp  Main
;********************************************************
;Преобразование температуры
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
   brsh m8u                    ;перейти,если температура 0 или выше         
   ldi  Temp1,0x85          ;получение температуры ниже 0
   rcall LCD_command
   ldi temp1,'-'                 ;знак "-"
   rcall  LCD_putchar
   subi  lower,0xC9                   
   sbci  upper,0x00
   com upper
   com lower
   rjmp  m8u_0
m8u:
   subi  lower,0xC8            ;получение температуры выше 0   
   sbci  upper,0x00
   ldi  Temp1,0x85             ;знак "+"
   rcall LCD_command
   ldi temp1,'+'
   rcall  LCD_putchar
m8u_0:                             ;умножение  
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
   cpi lower,0x5B           ;вводим поправку 0.2 
   ldi  temp,0x04           ;начиная с 111.5 градуса
   cpc upper,temp
   brlo End_0
   subi lower,0x02
END_0:
   rcall  DigitConvert
   ret
;**************************************************
;Обработка прерывания
;**************************************************
T1_OV_ISR:
   push  temp
   cpi Temp3,0b00000100        ;сравнить с крайним знач.
   breq Init_0             ;если равно - загрузка нач. знач.
   lsl Temp3             ;иначе - сдвиг влево
   rjmp Output           ;перейти на вывод в порт

Init_0:   
   ldi Temp3,0b00000001         ;загрузить нач. значение
   ldi number,0b00110000        ;загрузить нач. значение номера датчика   
Output:  
   out PortB,Temp3       ;вывод в порт
   inc  number
   ori number,0x30
   ldi   temp,0xF5       ;загрузить счётчики таймера 
   out  TCNT1H,Temp
   ldi   temp,0x0F
   out  TCNT1L,Temp
   pop  temp
   reti
;*****************************************************
;Конвертирует 16-разр. число в 4 десятичных цифры 
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
     subi    lower,0xE8           ;находим сколько тысяч
     sbci    upper,0x03
     brcc    FindThousands   
     ldi    temp,0xE8          
     add    lower,temp
     ldi    temp,0x03
     adc    upper,temp      ;    
     dec    Thousands 

FindHundreds:  
     inc    Hundreds  
     subi    lower,100            ;;находим сколько сотен
     sbci    upper,0
     brcc    FindHundreds    
     ldi    temp,100            
     add    lower,temp
     ldi    temp,0
     adc    upper,temp      ;    
     dec    Hundreds             

FindTens:
     inc    Tens    
     subi    lower,10             ;;находим сколько десятков
     sbci    upper,0x00
     brcc    FindTens      
     ldi       temp,10            
     add    lower,temp
     ldi       temp,0
     adc     upper,temp
     dec     Tens

FindOnes:
     inc    Ones     
     subi    lower,1            ;;находим сколько едениц
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
  ldi temp1,0x33             ;инициализация LCD в 4-bit способе.
  rcall LCD_command       ;функция команд
  rcall   DELAY_2ms          ;задержка инициализации
  ldi temp1,0x32             ;инициализация LCD в 4-bit способе.
  rcall LCD_command       ;функция команд
  rcall   DELAY_2ms          ;задержка инициализации
  ldi temp1,0x28             ;инициализация LCD 4 бита, 2 строки, 5*7 точек
  rcall LCD_command
  rcall   DELAY_2ms          ;задержка инициализации
  ldi temp1,0x0C             ;включен дисплей, курсор выключен
  rcall LCD_command           
  ldi temp1,0x01             ;очистка дисплея
  rcall LCD_command      
  rcall   DELAY_2ms          ;задержка для очистки дисплея   
  ldi temp1,0x06             ;перемещение курсора слева-направо инкр.
  rcall LCD_command
  ret
;******************************************************
Display:
      push Temp1
      ldi  Temp1,0xC8          ;адрес установки курсора LCD для номера датчика
      rcall LCD_command
      mov temp1,number     ;вывод номера датчика 
      rcall  LCD_putchar
      sbrc number,2             ;очистка после вывода номера 3
      clr number
      ldi  Temp1,0x8B           ;адрес установки курсора LCD для знаков
      rcall LCD_command
      ldi temp1,0xDF           ;знак градуса
      rcall  LCD_putchar
      ldi temp1,'C'               ;знак Цельсия
      rcall  LCD_putchar

     ldi Temp1,0x86            ;адрес установки курсора LCD
     rcall LCD_command     ;для вывода значения температуры
  
     lds Temp1,Digit+3        ;и .т.д
     rcall Decoder
     rcall DELAY_100us

     lds Temp1,Digit+2        ;и .т.д
     rcall Decoder
     rcall DELAY_100us
    
     lds Temp1,Digit+1        ;и .т.д  
     rcall Decoder
     rcall DELAY_100us

     ldi  Temp1,0x89             ;вывод запятой
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
Text_OUT:
  push temp1
  clr  count
  clr temp1
  ldi Temp1,0x80                 ;адрес установки курсора
  rcall LCD_command	
  ldi ZL,Low(Text01*2) 
  ldi ZH,High(Text01*2)
  ldi count,6
  rcall  loop1
  clr  count 
  clr temp1
  ldi Temp1,0xC0                ;адрес установки курсора
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
