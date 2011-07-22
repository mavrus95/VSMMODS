
;CodeVisionAVR C Compiler V2.04.4a Advanced
;(C) Copyright 1998-2009 Pavel Haiduc, HP InfoTech s.r.l.
;http://www.hpinfotech.com

;Chip type                : ATmega16
;Program type             : Application
;Clock frequency          : 16,000000 MHz
;Memory model             : Small
;Optimize for             : Size
;(s)printf features       : int, width
;(s)scanf features        : int, width
;External RAM size        : 0
;Data Stack size          : 256 byte(s)
;Heap size                : 0 byte(s)
;Promote 'char' to 'int'  : No
;'char' is unsigned       : Yes
;8 bit enums              : No
;global 'const' stored in FLASH: Yes
;Enhanced core instructions    : On
;Smart register allocation     : On
;Automatic register allocation : On

	#pragma AVRPART ADMIN PART_NAME ATmega16
	#pragma AVRPART MEMORY PROG_FLASH 16384
	#pragma AVRPART MEMORY EEPROM 512
	#pragma AVRPART MEMORY INT_SRAM SIZE 1024
	#pragma AVRPART MEMORY INT_SRAM START_ADDR 0x60

	.LISTMAC
	.EQU UDRE=0x5
	.EQU RXC=0x7
	.EQU USR=0xB
	.EQU UDR=0xC
	.EQU SPSR=0xE
	.EQU SPDR=0xF
	.EQU EERE=0x0
	.EQU EEWE=0x1
	.EQU EEMWE=0x2
	.EQU EECR=0x1C
	.EQU EEDR=0x1D
	.EQU EEARL=0x1E
	.EQU EEARH=0x1F
	.EQU WDTCR=0x21
	.EQU MCUCR=0x35
	.EQU GICR=0x3B
	.EQU SPL=0x3D
	.EQU SPH=0x3E
	.EQU SREG=0x3F

	.DEF R0X0=R0
	.DEF R0X1=R1
	.DEF R0X2=R2
	.DEF R0X3=R3
	.DEF R0X4=R4
	.DEF R0X5=R5
	.DEF R0X6=R6
	.DEF R0X7=R7
	.DEF R0X8=R8
	.DEF R0X9=R9
	.DEF R0XA=R10
	.DEF R0XB=R11
	.DEF R0XC=R12
	.DEF R0XD=R13
	.DEF R0XE=R14
	.DEF R0XF=R15
	.DEF R0X10=R16
	.DEF R0X11=R17
	.DEF R0X12=R18
	.DEF R0X13=R19
	.DEF R0X14=R20
	.DEF R0X15=R21
	.DEF R0X16=R22
	.DEF R0X17=R23
	.DEF R0X18=R24
	.DEF R0X19=R25
	.DEF R0X1A=R26
	.DEF R0X1B=R27
	.DEF R0X1C=R28
	.DEF R0X1D=R29
	.DEF R0X1E=R30
	.DEF R0X1F=R31

	.MACRO __CPD1N
	CPI  R30,LOW(@0)
	LDI  R26,HIGH(@0)
	CPC  R31,R26
	LDI  R26,BYTE3(@0)
	CPC  R22,R26
	LDI  R26,BYTE4(@0)
	CPC  R23,R26
	.ENDM

	.MACRO __CPD2N
	CPI  R26,LOW(@0)
	LDI  R30,HIGH(@0)
	CPC  R27,R30
	LDI  R30,BYTE3(@0)
	CPC  R24,R30
	LDI  R30,BYTE4(@0)
	CPC  R25,R30
	.ENDM

	.MACRO __CPWRR
	CP   R@0,R@2
	CPC  R@1,R@3
	.ENDM

	.MACRO __CPWRN
	CPI  R@0,LOW(@2)
	LDI  R30,HIGH(@2)
	CPC  R@1,R30
	.ENDM

	.MACRO __ADDB1MN
	SUBI R30,LOW(-@0-(@1))
	.ENDM

	.MACRO __ADDB2MN
	SUBI R26,LOW(-@0-(@1))
	.ENDM

	.MACRO __ADDW1MN
	SUBI R30,LOW(-@0-(@1))
	SBCI R31,HIGH(-@0-(@1))
	.ENDM

	.MACRO __ADDW2MN
	SUBI R26,LOW(-@0-(@1))
	SBCI R27,HIGH(-@0-(@1))
	.ENDM

	.MACRO __ADDW1FN
	SUBI R30,LOW(-2*@0-(@1))
	SBCI R31,HIGH(-2*@0-(@1))
	.ENDM

	.MACRO __ADDD1FN
	SUBI R30,LOW(-2*@0-(@1))
	SBCI R31,HIGH(-2*@0-(@1))
	SBCI R22,BYTE3(-2*@0-(@1))
	.ENDM

	.MACRO __ADDD1N
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	SBCI R22,BYTE3(-@0)
	SBCI R23,BYTE4(-@0)
	.ENDM

	.MACRO __ADDD2N
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	SBCI R24,BYTE3(-@0)
	SBCI R25,BYTE4(-@0)
	.ENDM

	.MACRO __SUBD1N
	SUBI R30,LOW(@0)
	SBCI R31,HIGH(@0)
	SBCI R22,BYTE3(@0)
	SBCI R23,BYTE4(@0)
	.ENDM

	.MACRO __SUBD2N
	SUBI R26,LOW(@0)
	SBCI R27,HIGH(@0)
	SBCI R24,BYTE3(@0)
	SBCI R25,BYTE4(@0)
	.ENDM

	.MACRO __ANDBMNN
	LDS  R30,@0+(@1)
	ANDI R30,LOW(@2)
	STS  @0+(@1),R30
	.ENDM

	.MACRO __ANDWMNN
	LDS  R30,@0+(@1)
	ANDI R30,LOW(@2)
	STS  @0+(@1),R30
	LDS  R30,@0+(@1)+1
	ANDI R30,HIGH(@2)
	STS  @0+(@1)+1,R30
	.ENDM

	.MACRO __ANDD1N
	ANDI R30,LOW(@0)
	ANDI R31,HIGH(@0)
	ANDI R22,BYTE3(@0)
	ANDI R23,BYTE4(@0)
	.ENDM

	.MACRO __ANDD2N
	ANDI R26,LOW(@0)
	ANDI R27,HIGH(@0)
	ANDI R24,BYTE3(@0)
	ANDI R25,BYTE4(@0)
	.ENDM

	.MACRO __ORBMNN
	LDS  R30,@0+(@1)
	ORI  R30,LOW(@2)
	STS  @0+(@1),R30
	.ENDM

	.MACRO __ORWMNN
	LDS  R30,@0+(@1)
	ORI  R30,LOW(@2)
	STS  @0+(@1),R30
	LDS  R30,@0+(@1)+1
	ORI  R30,HIGH(@2)
	STS  @0+(@1)+1,R30
	.ENDM

	.MACRO __ORD1N
	ORI  R30,LOW(@0)
	ORI  R31,HIGH(@0)
	ORI  R22,BYTE3(@0)
	ORI  R23,BYTE4(@0)
	.ENDM

	.MACRO __ORD2N
	ORI  R26,LOW(@0)
	ORI  R27,HIGH(@0)
	ORI  R24,BYTE3(@0)
	ORI  R25,BYTE4(@0)
	.ENDM

	.MACRO __DELAY_USB
	LDI  R24,LOW(@0)
__DELAY_USB_LOOP:
	DEC  R24
	BRNE __DELAY_USB_LOOP
	.ENDM

	.MACRO __DELAY_USW
	LDI  R24,LOW(@0)
	LDI  R25,HIGH(@0)
__DELAY_USW_LOOP:
	SBIW R24,1
	BRNE __DELAY_USW_LOOP
	.ENDM

	.MACRO __GETD1S
	LDD  R30,Y+@0
	LDD  R31,Y+@0+1
	LDD  R22,Y+@0+2
	LDD  R23,Y+@0+3
	.ENDM

	.MACRO __GETD2S
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	LDD  R24,Y+@0+2
	LDD  R25,Y+@0+3
	.ENDM

	.MACRO __PUTD1S
	STD  Y+@0,R30
	STD  Y+@0+1,R31
	STD  Y+@0+2,R22
	STD  Y+@0+3,R23
	.ENDM

	.MACRO __PUTD2S
	STD  Y+@0,R26
	STD  Y+@0+1,R27
	STD  Y+@0+2,R24
	STD  Y+@0+3,R25
	.ENDM

	.MACRO __PUTDZ2
	STD  Z+@0,R26
	STD  Z+@0+1,R27
	STD  Z+@0+2,R24
	STD  Z+@0+3,R25
	.ENDM

	.MACRO __CLRD1S
	STD  Y+@0,R30
	STD  Y+@0+1,R30
	STD  Y+@0+2,R30
	STD  Y+@0+3,R30
	.ENDM

	.MACRO __POINTB1MN
	LDI  R30,LOW(@0+(@1))
	.ENDM

	.MACRO __POINTW1MN
	LDI  R30,LOW(@0+(@1))
	LDI  R31,HIGH(@0+(@1))
	.ENDM

	.MACRO __POINTD1M
	LDI  R30,LOW(@0)
	LDI  R31,HIGH(@0)
	LDI  R22,BYTE3(@0)
	LDI  R23,BYTE4(@0)
	.ENDM

	.MACRO __POINTW1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	.ENDM

	.MACRO __POINTD1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	LDI  R22,BYTE3(2*@0+(@1))
	LDI  R23,BYTE4(2*@0+(@1))
	.ENDM

	.MACRO __POINTB2MN
	LDI  R26,LOW(@0+(@1))
	.ENDM

	.MACRO __POINTW2MN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	.ENDM

	.MACRO __POINTBRM
	LDI  R@0,LOW(@1)
	.ENDM

	.MACRO __POINTWRM
	LDI  R@0,LOW(@2)
	LDI  R@1,HIGH(@2)
	.ENDM

	.MACRO __POINTBRMN
	LDI  R@0,LOW(@1+(@2))
	.ENDM

	.MACRO __POINTWRMN
	LDI  R@0,LOW(@2+(@3))
	LDI  R@1,HIGH(@2+(@3))
	.ENDM

	.MACRO __POINTWRFN
	LDI  R@0,LOW(@2*2+(@3))
	LDI  R@1,HIGH(@2*2+(@3))
	.ENDM

	.MACRO __GETD1N
	LDI  R30,LOW(@0)
	LDI  R31,HIGH(@0)
	LDI  R22,BYTE3(@0)
	LDI  R23,BYTE4(@0)
	.ENDM

	.MACRO __GETD2N
	LDI  R26,LOW(@0)
	LDI  R27,HIGH(@0)
	LDI  R24,BYTE3(@0)
	LDI  R25,BYTE4(@0)
	.ENDM

	.MACRO __GETB1MN
	LDS  R30,@0+(@1)
	.ENDM

	.MACRO __GETB1HMN
	LDS  R31,@0+(@1)
	.ENDM

	.MACRO __GETW1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	.ENDM

	.MACRO __GETD1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	LDS  R22,@0+(@1)+2
	LDS  R23,@0+(@1)+3
	.ENDM

	.MACRO __GETBRMN
	LDS  R@0,@1+(@2)
	.ENDM

	.MACRO __GETWRMN
	LDS  R@0,@2+(@3)
	LDS  R@1,@2+(@3)+1
	.ENDM

	.MACRO __GETWRZ
	LDD  R@0,Z+@2
	LDD  R@1,Z+@2+1
	.ENDM

	.MACRO __GETD2Z
	LDD  R26,Z+@0
	LDD  R27,Z+@0+1
	LDD  R24,Z+@0+2
	LDD  R25,Z+@0+3
	.ENDM

	.MACRO __GETB2MN
	LDS  R26,@0+(@1)
	.ENDM

	.MACRO __GETW2MN
	LDS  R26,@0+(@1)
	LDS  R27,@0+(@1)+1
	.ENDM

	.MACRO __GETD2MN
	LDS  R26,@0+(@1)
	LDS  R27,@0+(@1)+1
	LDS  R24,@0+(@1)+2
	LDS  R25,@0+(@1)+3
	.ENDM

	.MACRO __PUTB1MN
	STS  @0+(@1),R30
	.ENDM

	.MACRO __PUTW1MN
	STS  @0+(@1),R30
	STS  @0+(@1)+1,R31
	.ENDM

	.MACRO __PUTD1MN
	STS  @0+(@1),R30
	STS  @0+(@1)+1,R31
	STS  @0+(@1)+2,R22
	STS  @0+(@1)+3,R23
	.ENDM

	.MACRO __PUTB1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRB
	.ENDM

	.MACRO __PUTW1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRW
	.ENDM

	.MACRO __PUTD1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRD
	.ENDM

	.MACRO __PUTBR0MN
	STS  @0+(@1),R0
	.ENDM

	.MACRO __PUTBMRN
	STS  @0+(@1),R@2
	.ENDM

	.MACRO __PUTWMRN
	STS  @0+(@1),R@2
	STS  @0+(@1)+1,R@3
	.ENDM

	.MACRO __PUTBZR
	STD  Z+@1,R@0
	.ENDM

	.MACRO __PUTWZR
	STD  Z+@2,R@0
	STD  Z+@2+1,R@1
	.ENDM

	.MACRO __GETW1R
	MOV  R30,R@0
	MOV  R31,R@1
	.ENDM

	.MACRO __GETW2R
	MOV  R26,R@0
	MOV  R27,R@1
	.ENDM

	.MACRO __GETWRN
	LDI  R@0,LOW(@2)
	LDI  R@1,HIGH(@2)
	.ENDM

	.MACRO __PUTW1R
	MOV  R@0,R30
	MOV  R@1,R31
	.ENDM

	.MACRO __PUTW2R
	MOV  R@0,R26
	MOV  R@1,R27
	.ENDM

	.MACRO __ADDWRN
	SUBI R@0,LOW(-@2)
	SBCI R@1,HIGH(-@2)
	.ENDM

	.MACRO __ADDWRR
	ADD  R@0,R@2
	ADC  R@1,R@3
	.ENDM

	.MACRO __SUBWRN
	SUBI R@0,LOW(@2)
	SBCI R@1,HIGH(@2)
	.ENDM

	.MACRO __SUBWRR
	SUB  R@0,R@2
	SBC  R@1,R@3
	.ENDM

	.MACRO __ANDWRN
	ANDI R@0,LOW(@2)
	ANDI R@1,HIGH(@2)
	.ENDM

	.MACRO __ANDWRR
	AND  R@0,R@2
	AND  R@1,R@3
	.ENDM

	.MACRO __ORWRN
	ORI  R@0,LOW(@2)
	ORI  R@1,HIGH(@2)
	.ENDM

	.MACRO __ORWRR
	OR   R@0,R@2
	OR   R@1,R@3
	.ENDM

	.MACRO __EORWRR
	EOR  R@0,R@2
	EOR  R@1,R@3
	.ENDM

	.MACRO __GETWRS
	LDD  R@0,Y+@2
	LDD  R@1,Y+@2+1
	.ENDM

	.MACRO __PUTBSR
	STD  Y+@1,R@0
	.ENDM

	.MACRO __PUTWSR
	STD  Y+@2,R@0
	STD  Y+@2+1,R@1
	.ENDM

	.MACRO __MOVEWRR
	MOV  R@0,R@2
	MOV  R@1,R@3
	.ENDM

	.MACRO __INWR
	IN   R@0,@2
	IN   R@1,@2+1
	.ENDM

	.MACRO __OUTWR
	OUT  @2+1,R@1
	OUT  @2,R@0
	.ENDM

	.MACRO __CALL1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	ICALL
	.ENDM

	.MACRO __CALL1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	CALL __GETW1PF
	ICALL
	.ENDM

	.MACRO __CALL2EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMRDW
	ICALL
	.ENDM

	.MACRO __GETW1STACK
	IN   R26,SPL
	IN   R27,SPH
	ADIW R26,@0+1
	LD   R30,X+
	LD   R31,X
	.ENDM

	.MACRO __GETD1STACK
	IN   R26,SPL
	IN   R27,SPH
	ADIW R26,@0+1
	LD   R30,X+
	LD   R31,X+
	LD   R22,X
	.ENDM

	.MACRO __NBST
	BST  R@0,@1
	IN   R30,SREG
	LDI  R31,0x40
	EOR  R30,R31
	OUT  SREG,R30
	.ENDM


	.MACRO __PUTB1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RNS
	MOVW R26,R@0
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RNS
	MOVW R26,R@0
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RNS
	MOVW R26,R@0
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	CALL __PUTDP1
	.ENDM


	.MACRO __GETB1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R30,Z
	.ENDM

	.MACRO __GETB1HSX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R31,Z
	.ENDM

	.MACRO __GETW1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R0,Z+
	LD   R31,Z
	MOV  R30,R0
	.ENDM

	.MACRO __GETD1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R0,Z+
	LD   R1,Z+
	LD   R22,Z+
	LD   R23,Z
	MOVW R30,R0
	.ENDM

	.MACRO __GETB2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R26,X
	.ENDM

	.MACRO __GETW2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	.ENDM

	.MACRO __GETD2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R1,X+
	LD   R24,X+
	LD   R25,X
	MOVW R26,R0
	.ENDM

	.MACRO __GETBRSX
	MOVW R30,R28
	SUBI R30,LOW(-@1)
	SBCI R31,HIGH(-@1)
	LD   R@0,Z
	.ENDM

	.MACRO __GETWRSX
	MOVW R30,R28
	SUBI R30,LOW(-@2)
	SBCI R31,HIGH(-@2)
	LD   R@0,Z+
	LD   R@1,Z
	.ENDM

	.MACRO __GETBRSX2
	MOVW R26,R28
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	LD   R@0,X
	.ENDM

	.MACRO __GETWRSX2
	MOVW R26,R28
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	LD   R@0,X+
	LD   R@1,X
	.ENDM

	.MACRO __LSLW8SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R31,Z
	CLR  R30
	.ENDM

	.MACRO __PUTB1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __CLRW1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X,R30
	.ENDM

	.MACRO __CLRD1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X+,R30
	ST   X+,R30
	ST   X,R30
	.ENDM

	.MACRO __PUTB2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z,R26
	.ENDM

	.MACRO __PUTW2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z+,R26
	ST   Z,R27
	.ENDM

	.MACRO __PUTD2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z+,R26
	ST   Z+,R27
	ST   Z+,R24
	ST   Z,R25
	.ENDM

	.MACRO __PUTBSRX
	MOVW R30,R28
	SUBI R30,LOW(-@1)
	SBCI R31,HIGH(-@1)
	ST   Z,R@0
	.ENDM

	.MACRO __PUTWSRX
	MOVW R30,R28
	SUBI R30,LOW(-@2)
	SBCI R31,HIGH(-@2)
	ST   Z+,R@0
	ST   Z,R@1
	.ENDM

	.MACRO __PUTB1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __MULBRR
	MULS R@0,R@1
	MOVW R30,R0
	.ENDM

	.MACRO __MULBRRU
	MUL  R@0,R@1
	MOVW R30,R0
	.ENDM

	.MACRO __MULBRR0
	MULS R@0,R@1
	.ENDM

	.MACRO __MULBRRU0
	MUL  R@0,R@1
	.ENDM

	.MACRO __MULBNWRU
	LDI  R26,@2
	MUL  R26,R@0
	MOVW R30,R0
	MUL  R26,R@1
	ADD  R31,R0
	.ENDM

	.CSEG
	.ORG 0x00

;INTERRUPT VECTORS
	JMP  __RESET
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00

_font_6x8_Data:
	.DB  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3E
	.DB  0x45,0x51,0x45,0x3E,0x0,0x3E,0x6B,0x6F
	.DB  0x6B,0x3E,0x0,0x1C,0x3E,0x7C,0x3E,0x1C
	.DB  0x0,0x18,0x3C,0x7E,0x3C,0x18,0x0,0x30
	.DB  0x36,0x7F,0x36,0x30,0x0,0x18,0x5C,0x7E
	.DB  0x5C,0x18,0x0,0x0,0x18,0x18,0x0,0x0
	.DB  0xFF,0xFF,0xE7,0xE7,0xFF,0xFF,0x0,0x3C
	.DB  0x24,0x24,0x3C,0x0,0xFF,0xC3,0xDB,0xDB
	.DB  0xC3,0xFF,0x0,0x30,0x48,0x4A,0x36,0xE
	.DB  0x0,0x6,0x29,0x79,0x29,0x6,0x0,0x60
	.DB  0x70,0x3F,0x2,0x4,0x0,0x60,0x7E,0xA
	.DB  0x35,0x3F,0x0,0x2A,0x1C,0x36,0x1C,0x2A
	.DB  0x0,0x0,0x7F,0x3E,0x1C,0x8,0x0,0x8
	.DB  0x1C,0x3E,0x7F,0x0,0x0,0x14,0x36,0x7F
	.DB  0x36,0x14,0x0,0x0,0x5F,0x0,0x5F,0x0
	.DB  0x0,0x6,0x9,0x7F,0x1,0x7F,0x0,0x22
	.DB  0x4D,0x55,0x59,0x22,0x0,0x60,0x60,0x60
	.DB  0x60,0x0,0x0,0x14,0xB6,0xFF,0xB6,0x14
	.DB  0x0,0x4,0x6,0x7F,0x6,0x4,0x0,0x10
	.DB  0x30,0x7F,0x30,0x10,0x0,0x8,0x8,0x3E
	.DB  0x1C,0x8,0x0,0x8,0x1C,0x3E,0x8,0x8
	.DB  0x0,0x78,0x40,0x40,0x40,0x40,0x0,0x8
	.DB  0x3E,0x8,0x3E,0x8,0x0,0x30,0x3C,0x3F
	.DB  0x3C,0x30,0x0,0x3,0xF,0x3F,0xF,0x3
	.DB  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
	.DB  0x6,0x5F,0x6,0x0,0x0,0x7,0x3,0x0
	.DB  0x7,0x3,0x0,0x24,0x7E,0x24,0x7E,0x24
	.DB  0x0,0x24,0x2B,0x6A,0x12,0x0,0x0,0x63
	.DB  0x13,0x8,0x64,0x63,0x0,0x36,0x49,0x56
	.DB  0x20,0x50,0x0,0x0,0x7,0x3,0x0,0x0
	.DB  0x0,0x0,0x3E,0x41,0x0,0x0,0x0,0x0
	.DB  0x41,0x3E,0x0,0x0,0x0,0x8,0x3E,0x1C
	.DB  0x3E,0x8,0x0,0x8,0x8,0x3E,0x8,0x8
	.DB  0x0,0x0,0xE0,0x60,0x0,0x0,0x0,0x8
	.DB  0x8,0x8,0x8,0x8,0x0,0x0,0x60,0x60
	.DB  0x0,0x0,0x0,0x20,0x10,0x8,0x4,0x2
	.DB  0x0,0x3E,0x41,0x41,0x41,0x3E,0x0,0x0
	.DB  0x42,0x7F,0x40,0x0,0x0,0x62,0x51,0x49
	.DB  0x49,0x46,0x0,0x22,0x49,0x49,0x49,0x36
	.DB  0x0,0x18,0x14,0x12,0x7F,0x10,0x0,0x2F
	.DB  0x49,0x49,0x49,0x31,0x0,0x3C,0x4A,0x49
	.DB  0x49,0x30,0x0,0x1,0x71,0x9,0x5,0x3
	.DB  0x0,0x36,0x49,0x49,0x49,0x36,0x0,0x6
	.DB  0x49,0x49,0x29,0x1E,0x0,0x0,0x6C,0x6C
	.DB  0x0,0x0,0x0,0x0,0xEC,0x6C,0x0,0x0
	.DB  0x0,0x8,0x14,0x22,0x41,0x0,0x0,0x24
	.DB  0x24,0x24,0x24,0x24,0x0,0x0,0x41,0x22
	.DB  0x14,0x8,0x0,0x2,0x1,0x59,0x9,0x6
	.DB  0x0,0x3E,0x41,0x5D,0x55,0x1E,0x0,0x7E
	.DB  0x11,0x11,0x11,0x7E,0x0,0x7F,0x49,0x49
	.DB  0x49,0x36,0x0,0x3E,0x41,0x41,0x41,0x22
	.DB  0x0,0x7F,0x41,0x41,0x41,0x3E,0x0,0x7F
	.DB  0x49,0x49,0x49,0x41,0x0,0x7F,0x9,0x9
	.DB  0x9,0x1,0x0,0x3E,0x41,0x49,0x49,0x7A
	.DB  0x0,0x7F,0x8,0x8,0x8,0x7F,0x0,0x0
	.DB  0x41,0x7F,0x41,0x0,0x0,0x30,0x40,0x40
	.DB  0x40,0x3F,0x0,0x7F,0x8,0x14,0x22,0x41
	.DB  0x0,0x7F,0x40,0x40,0x40,0x40,0x0,0x7F
	.DB  0x2,0x4,0x2,0x7F,0x0,0x7F,0x2,0x4
	.DB  0x8,0x7F,0x0,0x3E,0x41,0x41,0x41,0x3E
	.DB  0x0,0x7F,0x9,0x9,0x9,0x6,0x0,0x3E
	.DB  0x41,0x51,0x21,0x5E,0x0,0x7F,0x9,0x9
	.DB  0x19,0x66,0x0,0x26,0x49,0x49,0x49,0x32
	.DB  0x0,0x1,0x1,0x7F,0x1,0x1,0x0,0x3F
	.DB  0x40,0x40,0x40,0x3F,0x0,0x1F,0x20,0x40
	.DB  0x20,0x1F,0x0,0x3F,0x40,0x3C,0x40,0x3F
	.DB  0x0,0x63,0x14,0x8,0x14,0x63,0x0,0x7
	.DB  0x8,0x70,0x8,0x7,0x0,0x71,0x49,0x45
	.DB  0x43,0x0,0x0,0x0,0x7F,0x41,0x41,0x0
	.DB  0x0,0x2,0x4,0x8,0x10,0x20,0x0,0x0
	.DB  0x41,0x41,0x7F,0x0,0x0,0x4,0x2,0x1
	.DB  0x2,0x4,0x80,0x80,0x80,0x80,0x80,0x80
	.DB  0x0,0x0,0x3,0x7,0x0,0x0,0x0,0x20
	.DB  0x54,0x54,0x54,0x78,0x0,0x7F,0x44,0x44
	.DB  0x44,0x38,0x0,0x38,0x44,0x44,0x44,0x28
	.DB  0x0,0x38,0x44,0x44,0x44,0x7F,0x0,0x38
	.DB  0x54,0x54,0x54,0x8,0x0,0x8,0x7E,0x9
	.DB  0x9,0x0,0x0,0x18,0xA4,0xA4,0xA4,0x7C
	.DB  0x0,0x7F,0x4,0x4,0x78,0x0,0x0,0x0
	.DB  0x0,0x7D,0x40,0x0,0x0,0x40,0x80,0x84
	.DB  0x7D,0x0,0x0,0x7F,0x10,0x28,0x44,0x0
	.DB  0x0,0x0,0x0,0x7F,0x40,0x0,0x0,0x7C
	.DB  0x4,0x18,0x4,0x78,0x0,0x7C,0x4,0x4
	.DB  0x78,0x0,0x0,0x38,0x44,0x44,0x44,0x38
	.DB  0x0,0xFC,0x44,0x44,0x44,0x38,0x0,0x38
	.DB  0x44,0x44,0x44,0xFC,0x0,0x44,0x78,0x44
	.DB  0x4,0x8,0x0,0x8,0x54,0x54,0x54,0x20
	.DB  0x0,0x4,0x3E,0x44,0x24,0x0,0x0,0x3C
	.DB  0x40,0x20,0x7C,0x0,0x0,0x1C,0x20,0x40
	.DB  0x20,0x1C,0x0,0x3C,0x60,0x30,0x60,0x3C
	.DB  0x0,0x6C,0x10,0x10,0x6C,0x0,0x0,0x9C
	.DB  0xA0,0x60,0x3C,0x0,0x0,0x64,0x54,0x54
	.DB  0x4C,0x0,0x0,0x8,0x3E,0x41,0x41,0x0
	.DB  0x0,0x0,0x0,0x77,0x0,0x0,0x0,0x0
	.DB  0x41,0x41,0x3E,0x8,0x0,0x2,0x1,0x2
	.DB  0x1,0x0,0x0,0x3C,0x26,0x23,0x26,0x3C
	.DB  0x44,0x11,0x44,0x11,0x44,0x11,0xAA,0x55
	.DB  0xAA,0x55,0xAA,0x55,0xBB,0xEE,0xBB,0xEE
	.DB  0xBB,0xEE,0x0,0x0,0x0,0xFF,0x0,0x0
	.DB  0x8,0x8,0x8,0xFF,0x0,0x0,0xA,0xA
	.DB  0xA,0xFF,0x0,0x0,0x8,0xFF,0x0,0xFF
	.DB  0x0,0x0,0x8,0xF8,0x8,0xF8,0x0,0x0
	.DB  0xA,0xA,0xA,0xFE,0x0,0x0,0xA,0xFB
	.DB  0x0,0xFF,0x0,0x0,0x0,0xFF,0x0,0xFF
	.DB  0x0,0x0,0xA,0xFA,0x2,0xFE,0x0,0x0
	.DB  0xA,0xB,0x8,0xF,0x0,0x0,0x8,0xF
	.DB  0x8,0xF,0x0,0x0,0xA,0xA,0xA,0xF
	.DB  0x0,0x0,0x8,0x8,0x8,0xF8,0x0,0x0
	.DB  0x0,0x0,0x0,0xF,0x8,0x8,0x8,0x8
	.DB  0x8,0xF,0x8,0x8,0x8,0x8,0x8,0xF8
	.DB  0x8,0x8,0x0,0x0,0x0,0xFF,0x8,0x8
	.DB  0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8
	.DB  0x8,0xFF,0x8,0x8,0x0,0x0,0x0,0xFF
	.DB  0xA,0xA,0x0,0xFF,0x0,0xFF,0x8,0x8
	.DB  0x0,0xF,0x8,0xB,0xA,0xA,0x0,0xFE
	.DB  0x2,0xFA,0xA,0xA,0xA,0xB,0x8,0xB
	.DB  0xA,0xA,0xA,0xFA,0x2,0xFA,0xA,0xA
	.DB  0x0,0xFF,0x0,0xFB,0xA,0xA,0xA,0xA
	.DB  0xA,0xA,0xA,0xA,0xA,0xFB,0x0,0xFB
	.DB  0xA,0xA,0xA,0xA,0xA,0xB,0xA,0xA
	.DB  0x8,0xF,0x8,0xF,0x8,0x8,0xA,0xA
	.DB  0xA,0xFA,0xA,0xA,0x8,0xF8,0x8,0xF8
	.DB  0x8,0x8,0x0,0xF,0x8,0xF,0x8,0x8
	.DB  0x0,0x0,0x0,0xF,0xA,0xA,0x0,0x0
	.DB  0x0,0xFE,0xA,0xA,0x0,0xF8,0x8,0xF8
	.DB  0x8,0x8,0x8,0xFF,0x8,0xFF,0x8,0x8
	.DB  0x0,0x7E,0x4B,0x4A,0x4B,0x42,0xA,0xA
	.DB  0xA,0xFF,0xA,0xA,0x8,0x8,0x8,0xF
	.DB  0x0,0x0,0x0,0x0,0x0,0xF8,0x8,0x8
	.DB  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0xF0
	.DB  0xF0,0xF0,0xF0,0xF0,0xFF,0xFF,0xFF,0x0
	.DB  0x0,0x0,0x0,0x0,0x0,0xFF,0xFF,0xFF
	.DB  0xF,0xF,0xF,0xF,0xF,0xF,0x0,0x3E
	.DB  0x49,0x49,0x41,0x22,0x0,0x38,0x54,0x54
	.DB  0x44,0x28,0x0,0x1,0x40,0x7E,0x40,0x1
	.DB  0x0,0x0,0x1,0x7C,0x41,0x0,0x0,0x27
	.DB  0x48,0x4B,0x48,0x3F,0x0,0x9D,0xA2,0x62
	.DB  0x3D,0x0,0x0,0x6,0x9,0x9,0x6,0x0
	.DB  0x0,0x38,0x55,0x54,0x55,0x8,0x0,0x0
	.DB  0x18,0x18,0x0,0x0,0x0,0x0,0x8,0x0
	.DB  0x0,0x0,0x0,0x30,0x40,0x3E,0x2,0x2
	.DB  0x7F,0x6,0x18,0x7F,0x13,0x13,0x2A,0x3E
	.DB  0x14,0x14,0x3E,0x2A,0x0,0x3C,0x3C,0x3C
	.DB  0x3C,0x0,0x0,0x0,0x0,0x0,0x0,0x0
	.DB  0x0,0x7E,0x11,0x11,0x11,0x7E,0x0,0x7F
	.DB  0x49,0x49,0x49,0x31,0x0,0x7F,0x49,0x49
	.DB  0x49,0x36,0x0,0x7F,0x1,0x1,0x1,0x1
	.DB  0xC0,0x7E,0x41,0x41,0x7F,0xC0,0x0,0x7F
	.DB  0x49,0x49,0x49,0x41,0x0,0x77,0x8,0x7F
	.DB  0x8,0x77,0x22,0x49,0x49,0x49,0x36,0x0
	.DB  0x0,0x7F,0x20,0x10,0x8,0x7F,0x0,0x7E
	.DB  0x21,0x11,0x9,0x7E,0x0,0x7F,0x8,0x14
	.DB  0x22,0x41,0x0,0x40,0x7E,0x1,0x1,0x7F
	.DB  0x0,0x7F,0x2,0x4,0x2,0x7F,0x0,0x7F
	.DB  0x8,0x8,0x8,0x7F,0x0,0x3E,0x41,0x41
	.DB  0x41,0x3E,0x0,0x7F,0x1,0x1,0x1,0x7F
	.DB  0x0,0x7F,0x9,0x9,0x9,0x6,0x0,0x3E
	.DB  0x41,0x41,0x41,0x22,0x0,0x1,0x1,0x7F
	.DB  0x1,0x1,0x0,0x27,0x48,0x48,0x48,0x3F
	.DB  0x0,0xE,0x11,0x7F,0x11,0xE,0x0,0x63
	.DB  0x14,0x8,0x14,0x63,0x0,0x7F,0x40,0x40
	.DB  0x7F,0xC0,0x0,0x7,0x8,0x8,0x8,0x7F
	.DB  0x0,0x7F,0x40,0x7F,0x40,0x7F,0x0,0x7F
	.DB  0x40,0x7F,0x40,0xFF,0x3,0x1,0x7F,0x48
	.DB  0x48,0x30,0x0,0x7F,0x48,0x48,0x30,0x7F
	.DB  0x0,0x7F,0x48,0x48,0x48,0x30,0x0,0x22
	.DB  0x41,0x49,0x49,0x3E,0x0,0x7F,0x8,0x3E
	.DB  0x41,0x3E,0x0,0x66,0x19,0x9,0x9,0x7F
	.DB  0x0,0x20,0x54,0x54,0x54,0x78,0x0,0x3C
	.DB  0x4A,0x4A,0x4A,0x31,0x0,0x7C,0x54,0x54
	.DB  0x54,0x28,0x0,0x7C,0x4,0x4,0xC,0x0
	.DB  0xC0,0x78,0x44,0x44,0x7C,0xC0,0x0,0x38
	.DB  0x54,0x54,0x54,0x8,0x0,0x6C,0x10,0x7C
	.DB  0x10,0x6C,0x0,0x28,0x44,0x54,0x54,0x28
	.DB  0x0,0x7C,0x20,0x10,0x8,0x7C,0x0,0x7C
	.DB  0x20,0x12,0xA,0x7C,0x0,0x7C,0x10,0x28
	.DB  0x44,0x0,0x40,0x38,0x4,0x4,0x7C,0x0
	.DB  0x0,0x7C,0x8,0x10,0x8,0x7C,0x0,0x7C
	.DB  0x10,0x10,0x10,0x7C,0x0,0x38,0x44,0x44
	.DB  0x44,0x38,0x0,0x7C,0x4,0x4,0x4,0x7C
	.DB  0x0,0xFC,0x44,0x44,0x44,0x38,0x0,0x38
	.DB  0x44,0x44,0x44,0x28,0x0,0x4,0x4,0x7C
	.DB  0x4,0x4,0x0,0x9C,0xA0,0x60,0x3C,0x0
	.DB  0x0,0x18,0x24,0x7C,0x24,0x18,0x0,0x6C
	.DB  0x10,0x10,0x6C,0x0,0x0,0x7C,0x40,0x40
	.DB  0x7C,0xC0,0x0,0xC,0x10,0x10,0x10,0x7C
	.DB  0x0,0x7C,0x40,0x7C,0x40,0x7C,0x0,0x7C
	.DB  0x40,0x7C,0x40,0xFC,0xC,0x4,0x7C,0x50
	.DB  0x50,0x20,0x0,0x7C,0x50,0x50,0x20,0x7C
	.DB  0x0,0x7C,0x50,0x50,0x50,0x20,0x0,0x28
	.DB  0x44,0x54,0x54,0x38,0x0,0x7C,0x10,0x38
	.DB  0x44,0x38,0x0,0x48,0x34,0x14,0x14,0x7C

_0x3:
	.DB  0x1
_0x17:
	.DB  0x0,0x6,0xC,0x12,0x18,0x1E,0x24,0x2A
	.DB  0x30,0x36,0x3C,0x42,0x48,0x4E,0x54,0x5A
	.DB  0x60,0x66,0x6C,0x72
_0x20000:
	.DB  0xE8,0xED,0xE4,0xE8,0xEA,0xE0,0xF2,0xEE
	.DB  0xF0,0x20,0xCC,0xDD,0xCB,0xD2,0x20,0x31
	.DB  0x32,0x32,0x33,0x32,0x0

__GLOBAL_INI_TBL:
	.DW  0x01
	.DW  _method
	.DW  _0x3*2

	.DW  0x14
	.DW  _PlaceArray
	.DW  _0x17*2

	.DW  0x15
	.DW  _0x20003
	.DW  _0x20000*2

_0xFFFFFFFF:
	.DW  0

__RESET:
	CLI
	CLR  R30
	OUT  EECR,R30

;INTERRUPT VECTORS ARE PLACED
;AT THE START OF FLASH
	LDI  R31,1
	OUT  GICR,R31
	OUT  GICR,R30
	OUT  MCUCR,R30

;DISABLE WATCHDOG
	LDI  R31,0x18
	OUT  WDTCR,R31
	OUT  WDTCR,R30

;CLEAR R2-R14
	LDI  R24,(14-2)+1
	LDI  R26,2
	CLR  R27
__CLEAR_REG:
	ST   X+,R30
	DEC  R24
	BRNE __CLEAR_REG

;CLEAR SRAM
	LDI  R24,LOW(0x400)
	LDI  R25,HIGH(0x400)
	LDI  R26,0x60
__CLEAR_SRAM:
	ST   X+,R30
	SBIW R24,1
	BRNE __CLEAR_SRAM

;GLOBAL VARIABLES INITIALIZATION
	LDI  R30,LOW(__GLOBAL_INI_TBL*2)
	LDI  R31,HIGH(__GLOBAL_INI_TBL*2)
__GLOBAL_INI_NEXT:
	LPM  R24,Z+
	LPM  R25,Z+
	SBIW R24,0
	BREQ __GLOBAL_INI_END
	LPM  R26,Z+
	LPM  R27,Z+
	LPM  R0,Z+
	LPM  R1,Z+
	MOVW R22,R30
	MOVW R30,R0
__GLOBAL_INI_LOOP:
	LPM  R0,Z+
	ST   X+,R0
	SBIW R24,1
	BRNE __GLOBAL_INI_LOOP
	MOVW R30,R22
	RJMP __GLOBAL_INI_NEXT
__GLOBAL_INI_END:

;STACK POINTER INITIALIZATION
	LDI  R30,LOW(0x45F)
	OUT  SPL,R30
	LDI  R30,HIGH(0x45F)
	OUT  SPH,R30

;DATA STACK POINTER INITIALIZATION
	LDI  R28,LOW(0x160)
	LDI  R29,HIGH(0x160)

	JMP  _main

	.ESEG
	.ORG 0

	.DSEG
	.ORG 0x160

	.CSEG
;#include "lcd_graph_lib.h"
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x40
	.EQU __sm_mask=0xB0
	.EQU __sm_powerdown=0x20
	.EQU __sm_powersave=0x30
	.EQU __sm_standby=0xA0
	.EQU __sm_ext_standby=0xB0
	.EQU __sm_adc_noise_red=0x10
	.SET power_ctrl_reg=mcucr
	#endif
;#include "font_6x8.h"
;
;#define PAGE0 0xb8
;#define PAGE1 0xb9
;#define PAGE2 0xba
;#define PAGE3 0xbb
;#define FLAG_BUSY  7
;
;#define SelectLeftChip()   SetBit(PORT_LCD_CON, CS)
;#define SelectRightChip()   ClearBit(PORT_LCD_CON, CS)
;
;volatile unsigned char method = 1;

	.DSEG
;volatile unsigned char flag = 0;
;
;//инициализация портов ввода/вывода
;void LCDG_InitPort(void)
; 0000 0012 {

	.CSEG
_LCDG_InitPort:
; 0000 0013  PORT_LCD_BUS = 0xff;
	LDI  R30,LOW(255)
	OUT  0x15,R30
; 0000 0014  DDRX_LCD_BUS = 0xff;
	OUT  0x14,R30
; 0000 0015  PORT_LCD_CON = 0xff;
	OUT  0x18,R30
; 0000 0016  DDRX_LCD_CON = 0xff;
	OUT  0x17,R30
; 0000 0017 }
	RET
;
;//функция чтения флага занятости
;void LCDG_WaitFLAG_BUSY(void)
; 0000 001B {
_LCDG_WaitFLAG_BUSY:
; 0000 001C   unsigned char stat;
; 0000 001D   DDRX_LCD_BUS = 0;                    //конфигурируем порт на вход
	ST   -Y,R17
;	stat -> R17
	LDI  R30,LOW(0)
	OUT  0x14,R30
; 0000 001E   PORT_LCD_BUS = 0xff;
	LDI  R30,LOW(255)
	OUT  0x15,R30
; 0000 001F   SetBit(PORT_LCD_CON, RD_WR);         //выставляем управляющие сигналы
	SBI  0x18,3
; 0000 0020   ClearBit(PORT_LCD_CON, AO);
	CBI  0x18,2
; 0000 0021   delay_us(2);
	__DELAY_USB 11
; 0000 0022   do{
_0x5:
; 0000 0023   ClearBit(PORT_LCD_CON, EN);
	CBI  0x18,4
; 0000 0024   delay_us(5);
	__DELAY_USB 27
; 0000 0025   stat = PIN_LCD_BUS;                 //считываем статусный байт
	IN   R17,19
; 0000 0026   delay_us(5);
	__DELAY_USB 27
; 0000 0027   SetBit(PORT_LCD_CON, EN);
	SBI  0x18,4
; 0000 0028   }
; 0000 0029   while((stat & (1<<FLAG_BUSY)) != 0); //сидим в цикле пока не сбросится флаг
	SBRC R17,7
	RJMP _0x5
; 0000 002A   DDRX_LCD_BUS = 0xff;                 //делаем порт снова выходом
	LDI  R30,LOW(255)
	OUT  0x14,R30
; 0000 002B   PORT_LCD_BUS = 0;
	LDI  R30,LOW(0)
	OUT  0x15,R30
; 0000 002C }
	LD   R17,Y+
	RET
;
;//функция чтения байта данных из lcd
;unsigned char LCDG_ReadData(void)
; 0000 0030 {
; 0000 0031   unsigned char data;
; 0000 0032   DDRX_LCD_BUS = 0;                   //конфигурируем порт на вход
;	data -> R17
; 0000 0033   PORT_LCD_BUS = 0xff;
; 0000 0034   SetBit(PORT_LCD_CON, RD_WR);
; 0000 0035   SetBit(PORT_LCD_CON, AO);
; 0000 0036   delay_us(2);
; 0000 0037   ClearBit(PORT_LCD_CON, EN);
; 0000 0038   delay_us(5);
; 0000 0039   data = PIN_LCD_BUS;
; 0000 003A   SetBit(PORT_LCD_CON, EN);
; 0000 003B   //делаем порт снова выходом
; 0000 003C   DDRX_LCD_BUS = 0xff;
; 0000 003D   PORT_LCD_BUS = 0;
; 0000 003E   return data;
; 0000 003F }
;
;//общая функция
;inline void LCDG_CommonFunc(unsigned char data)
; 0000 0043 {
_LCDG_CommonFunc:
; 0000 0044   ClearBit(PORT_LCD_CON, RD_WR);
;	data -> Y+0
	CBI  0x18,3
; 0000 0045   delay_us(2);
	__DELAY_USB 11
; 0000 0046   ClearBit(PORT_LCD_CON, EN);
	CBI  0x18,4
; 0000 0047   PORT_LCD_BUS = data;
	LD   R30,Y
	OUT  0x15,R30
; 0000 0048   delay_us(5);
	__DELAY_USB 27
; 0000 0049   SetBit(PORT_LCD_CON, EN);
	SBI  0x18,4
; 0000 004A }
	RJMP _0x2000002
;
;//запись команды на lcd
;void LCDG_SendCom(unsigned char data)
; 0000 004E {
_LCDG_SendCom:
; 0000 004F   LCDG_WaitFLAG_BUSY();
;	data -> Y+0
	RCALL _LCDG_WaitFLAG_BUSY
; 0000 0050   ClearBit(PORT_LCD_CON, AO);
	CBI  0x18,2
; 0000 0051   LCDG_CommonFunc(data);
	RJMP _0x2000001
; 0000 0052 }
;
;//вывод данных на lcd
;void LCDG_SendData(unsigned char data)
; 0000 0056 {
_LCDG_SendData:
; 0000 0057   LCDG_WaitFLAG_BUSY();
;	data -> Y+0
	RCALL _LCDG_WaitFLAG_BUSY
; 0000 0058   SetBit(PORT_LCD_CON, AO);
	SBI  0x18,2
; 0000 0059   LCDG_CommonFunc(data);
_0x2000001:
	LD   R30,Y
	ST   -Y,R30
	RCALL _LCDG_CommonFunc
; 0000 005A }
_0x2000002:
	ADIW R28,1
	RET
;
;//функция инициализации lcd
;//подает сигнал сброса
;//настраивает правый и левый контроллеры
;void LCDG_InitLcd(void)
; 0000 0060 {
_LCDG_InitLcd:
; 0000 0061   ClearBit(PORT_LCD_CON, RES);
	CBI  0x18,0
; 0000 0062   delay_ms(400);
	RCALL SUBOPT_0x0
; 0000 0063   SetBit(PORT_LCD_CON, RES);
	SBI  0x18,0
; 0000 0064   delay_ms(400);
	RCALL SUBOPT_0x0
; 0000 0065 
; 0000 0066   SelectLeftChip();
	SBI  0x18,1
; 0000 0067   LCDG_SendCom(COM_CLEAR_RMW);
	RCALL SUBOPT_0x1
; 0000 0068   LCDG_SendCom(COM_STATIC_DRIVE_OFF);
; 0000 0069   LCDG_SendCom(COM_DUTY_SELECT_ON);
; 0000 006A   LCDG_SendCom(COM_DISPLAY_ON);
; 0000 006B   LCDG_SendCom(COM_ADC_SELECT_ON);
	LDI  R30,LOW(161)
	RCALL SUBOPT_0x2
; 0000 006C   LCDG_SendCom(COM_RESET);
; 0000 006D   LCDG_SendCom(0xc0);
; 0000 006E 
; 0000 006F   SelectRightChip();
	CBI  0x18,1
; 0000 0070   LCDG_SendCom(COM_CLEAR_RMW);
	RCALL SUBOPT_0x1
; 0000 0071   LCDG_SendCom(COM_STATIC_DRIVE_OFF);
; 0000 0072   LCDG_SendCom(COM_DUTY_SELECT_ON);
; 0000 0073   LCDG_SendCom(COM_DISPLAY_ON);
; 0000 0074   LCDG_SendCom(COM_ADC_SELECT_OFF);
	LDI  R30,LOW(160)
	RCALL SUBOPT_0x2
; 0000 0075   LCDG_SendCom(COM_RESET);
; 0000 0076   LCDG_SendCom(0xc0);
; 0000 0077 }
	RET
;
;//функция очистки lcd
;void LCDG_ClearLcd(unsigned char x1, unsigned char x2)
; 0000 007B {
_LCDG_ClearLcd:
; 0000 007C unsigned char xPos = x1;
; 0000 007D unsigned char realAdr = 0;
; 0000 007E 
; 0000 007F while(xPos < x2){
	ST   -Y,R17
	ST   -Y,R16
;	x1 -> Y+3
;	x2 -> Y+2
;	xPos -> R17
;	realAdr -> R16
	LDD  R17,Y+3
	LDI  R16,0
_0x7:
	LDD  R30,Y+2
	CP   R17,R30
	BRSH _0x9
; 0000 0080   if (realAdr < 61) {
	CPI  R16,61
	BRSH _0xA
; 0000 0081     SetBit(PORT_LCD_CON, CS);
	SBI  0x18,1
; 0000 0082     realAdr = realAdr + 19;
	SUBI R16,-LOW(19)
; 0000 0083   }
; 0000 0084   else {
	RJMP _0xB
_0xA:
; 0000 0085     ClearBit(PORT_LCD_CON, CS);
	CBI  0x18,1
; 0000 0086     realAdr = realAdr - 61;
	SUBI R16,LOW(61)
; 0000 0087   }
_0xB:
; 0000 0088 
; 0000 0089   LCDG_SendCom(PAGE0);
	LDI  R30,LOW(184)
	RCALL SUBOPT_0x3
; 0000 008A   LCDG_SendCom(realAdr);
; 0000 008B   LCDG_SendData(0);
; 0000 008C   LCDG_SendCom(PAGE1);
	LDI  R30,LOW(185)
	RCALL SUBOPT_0x3
; 0000 008D   LCDG_SendCom(realAdr);
; 0000 008E   LCDG_SendData(0);
; 0000 008F   LCDG_SendCom(PAGE2);
	LDI  R30,LOW(186)
	RCALL SUBOPT_0x3
; 0000 0090   LCDG_SendCom(realAdr);
; 0000 0091   LCDG_SendData(0);
; 0000 0092   LCDG_SendCom(PAGE3);
	LDI  R30,LOW(187)
	RCALL SUBOPT_0x3
; 0000 0093   LCDG_SendCom(realAdr);
; 0000 0094   LCDG_SendData(0);
; 0000 0095 
; 0000 0096   xPos++;
	SUBI R17,-1
; 0000 0097   realAdr = xPos;
	MOV  R16,R17
; 0000 0098 }
	RJMP _0x7
_0x9:
; 0000 0099 }
	LDD  R17,Y+1
	LDD  R16,Y+0
	ADIW R28,4
	RET
;
;//установка метода вывода
;void LCDG_SetMethod(unsigned char met)
; 0000 009D {
; 0000 009E   method = met;
;	met -> Y+0
; 0000 009F }
;
;//отображает один пиксел на экране
;void LCDG_PutPixel(unsigned char xPos, unsigned char yPos)
; 0000 00A3 {
; 0000 00A4 unsigned char realAdr;
; 0000 00A5 unsigned char realPage;
; 0000 00A6 unsigned char data;
; 0000 00A7 unsigned char currentData;
; 0000 00A8 
; 0000 00A9   if ((xPos > 122) || (yPos > 31)) return;
;	xPos -> Y+5
;	yPos -> Y+4
;	realAdr -> R17
;	realPage -> R16
;	data -> R19
;	currentData -> R18
; 0000 00AA 
; 0000 00AB   realAdr = xPos;
; 0000 00AC   realPage = PAGE0 + (yPos/8);
; 0000 00AD   data = yPos%8;
; 0000 00AE 
; 0000 00AF   if (realAdr < 61) {
; 0000 00B0     SetBit(PORT_LCD_CON, CS);
; 0000 00B1     realAdr = realAdr + 19;
; 0000 00B2   }
; 0000 00B3   else {
; 0000 00B4     ClearBit(PORT_LCD_CON, CS);
; 0000 00B5     realAdr = realAdr - 61;
; 0000 00B6   }
; 0000 00B7   LCDG_WaitFLAG_BUSY();
; 0000 00B8   LCDG_SendCom(realPage);
; 0000 00B9   LCDG_SendCom(realAdr);
; 0000 00BA   LCDG_ReadData();
; 0000 00BB   currentData = LCDG_ReadData();
; 0000 00BC    switch(method){
; 0000 00BD     case MET_AND: {currentData &= ~(1<<data); break;}
; 0000 00BE     case MET_OR : {currentData |= (1<<data); break;}
; 0000 00BF     case MET_XOR : {currentData ^= (1<<data); break;}
; 0000 00C0    }
; 0000 00C1   LCDG_SendCom(realAdr);
; 0000 00C2   LCDG_SendData(currentData);
; 0000 00C3 }
;
;
;
;
;//Знакогенератор____________________________________________________________________________
;
;//устанавливает флаг инверсии
;void LCDG_SetInv(unsigned char f)
; 0000 00CC {
; 0000 00CD   flag = f;
;	f -> Y+0
; 0000 00CE }
;
;//отображает один символ на жкд
;//unsigned char PlaceArray[] = {0,8,16,24,32,40,48,56,64,72,80,88,96,104,112};
;//unsigned char PlaceArray[] = {0,7,14,21,28,35,42,49,56,63,70,77,84,91,98,105,112};
;unsigned char PlaceArray[] = {0,6,12,18,24,30,36,42,48,54,60,66,72,78,84,90,96,102,108,114};

	.DSEG
;
;void LCDG_SendSymbol(unsigned char xPos, unsigned char yPos,unsigned char data)
; 0000 00D6 {

	.CSEG
_LCDG_SendSymbol:
; 0000 00D7 unsigned char i;
; 0000 00D8 unsigned char realAdr;
; 0000 00D9 unsigned char realPage = PAGE3 - yPos;
; 0000 00DA unsigned int  pointerFont = ((unsigned int)data<<2) + ((unsigned int)data<<1);
; 0000 00DB realAdr = PlaceArray[xPos];
	CALL __SAVELOCR6
;	xPos -> Y+8
;	yPos -> Y+7
;	data -> Y+6
;	i -> R17
;	realAdr -> R16
;	realPage -> R19
;	pointerFont -> R20,R21
	LDD  R26,Y+7
	LDI  R30,LOW(187)
	SUB  R30,R26
	MOV  R19,R30
	LDD  R30,Y+6
	LDI  R31,0
	MOVW R0,R30
	CALL __LSLW2
	MOVW R26,R30
	MOVW R30,R0
	LSL  R30
	ROL  R31
	ADD  R30,R26
	ADC  R31,R27
	MOVW R20,R30
	LDD  R30,Y+8
	LDI  R31,0
	SUBI R30,LOW(-_PlaceArray)
	SBCI R31,HIGH(-_PlaceArray)
	LD   R16,Z
; 0000 00DC xPos = realAdr;
	__PUTBSR 16,8
; 0000 00DD 
; 0000 00DE   for(i = 0; i<=5; i++){
	LDI  R17,LOW(0)
_0x19:
	CPI  R17,6
	BRSH _0x1A
; 0000 00DF      if (realAdr < 61) {
	CPI  R16,61
	BRSH _0x1B
; 0000 00E0       SetBit(PORT_LCD_CON, CS);
	SBI  0x18,1
; 0000 00E1       realAdr = realAdr + 19;
	SUBI R16,-LOW(19)
; 0000 00E2     }
; 0000 00E3     else {
	RJMP _0x1C
_0x1B:
; 0000 00E4       ClearBit(PORT_LCD_CON, CS);
	CBI  0x18,1
; 0000 00E5       realAdr = realAdr - 61;
	SUBI R16,LOW(61)
; 0000 00E6     }
_0x1C:
; 0000 00E7 
; 0000 00E8     data = font_6x8_Data[pointerFont];
	MOVW R30,R20
	SUBI R30,LOW(-_font_6x8_Data*2)
	SBCI R31,HIGH(-_font_6x8_Data*2)
	LPM  R0,Z
	STD  Y+6,R0
; 0000 00E9     if(flag) data = ~data;
	LDS  R30,_flag
	CPI  R30,0
	BREQ _0x1D
	LDD  R30,Y+6
	COM  R30
	STD  Y+6,R30
; 0000 00EA     LCDG_SendCom(realPage);
_0x1D:
	ST   -Y,R19
	RCALL _LCDG_SendCom
; 0000 00EB     LCDG_SendCom(realAdr);
	ST   -Y,R16
	RCALL _LCDG_SendCom
; 0000 00EC     LCDG_SendData(data);
	LDD  R30,Y+6
	ST   -Y,R30
	RCALL _LCDG_SendData
; 0000 00ED     xPos++;
	LDD  R30,Y+8
	SUBI R30,-LOW(1)
	STD  Y+8,R30
; 0000 00EE     realAdr = xPos;
	LDD  R16,Y+8
; 0000 00EF     pointerFont++;
	__ADDWRN 20,21,1
; 0000 00F0   }
	SUBI R17,-1
	RJMP _0x19
_0x1A:
; 0000 00F1 }
	CALL __LOADLOCR6
	ADIW R28,9
	RET
;
;//отображает строку на жкд
;void LCDG_SendString(unsigned char xPos, unsigned char yPos, char * string)
; 0000 00F5 {
_LCDG_SendString:
; 0000 00F6   unsigned char data = 0;
; 0000 00F7   while(*string){
	ST   -Y,R17
;	xPos -> Y+4
;	yPos -> Y+3
;	*string -> Y+1
;	data -> R17
	LDI  R17,0
_0x1E:
	LDD  R26,Y+1
	LDD  R27,Y+1+1
	LD   R30,X
	CPI  R30,0
	BREQ _0x20
; 0000 00F8     data = *string++;
	LD   R17,X+
	STD  Y+1,R26
	STD  Y+1+1,R27
; 0000 00F9     LCDG_SendSymbol(xPos,yPos,data);
	LDD  R30,Y+4
	ST   -Y,R30
	LDD  R30,Y+4
	ST   -Y,R30
	ST   -Y,R17
	RCALL _LCDG_SendSymbol
; 0000 00FA     xPos++;
	LDD  R30,Y+4
	SUBI R30,-LOW(1)
	STD  Y+4,R30
; 0000 00FB   }
	RJMP _0x1E
_0x20:
; 0000 00FC }
	LDD  R17,Y+0
	ADIW R28,5
	RET
;
;
;
;/****************************************************************************/
;/*  Функция вывода прямой по алгоритму Брезенхема                           */
;/****************************************************************************/
;void LCDG_DrawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2)
; 0000 0104 {
; 0000 0105         int dx, dy, i1, i2, i, kx, ky;
; 0000 0106         int d;
; 0000 0107         int x, y;
; 0000 0108         int flag;
; 0000 0109 
; 0000 010A         dy = y2 - y1;
;	x1 -> Y+25
;	y1 -> Y+24
;	x2 -> Y+23
;	y2 -> Y+22
;	dx -> R16,R17
;	dy -> R18,R19
;	i1 -> R20,R21
;	i2 -> Y+20
;	i -> Y+18
;	kx -> Y+16
;	ky -> Y+14
;	d -> Y+12
;	x -> Y+10
;	y -> Y+8
;	flag -> Y+6
; 0000 010B         dx = x2 - x1;
; 0000 010C         if (dx == 0 && dy == 0){
; 0000 010D                 LCDG_PutPixel(x1,y1);
; 0000 010E                 return;
; 0000 010F         }
; 0000 0110         kx = 1;
; 0000 0111         ky = 1;
; 0000 0112 
; 0000 0113         if( dx < 0 ){ dx = -dx; kx = -1; }
; 0000 0114         else if(dx == 0)        kx = 0;
; 0000 0115 
; 0000 0116         if(dy < 0) { dy = -dy; ky = -1; }
; 0000 0117 
; 0000 0118         if(dx < dy){ flag = 0; d = dx; dx = dy; dy = d; }
; 0000 0119         else         flag = 1;
; 0000 011A 
; 0000 011B         i1 = dy + dy; d = i1 - dx; i2 = d - dx;
; 0000 011C         x = x1; y = y1;
; 0000 011D 
; 0000 011E         for(i=0; i < dx; i++){
; 0000 011F                 LCDG_PutPixel(x,y);
; 0000 0120 
; 0000 0121                 if(flag) x += kx;
; 0000 0122                 else     y += ky;
; 0000 0123 
; 0000 0124                 if( d < 0 )
; 0000 0125                          d += i1;
; 0000 0126                 else{
; 0000 0127                          d += i2;
; 0000 0128                          if(flag) y += ky;
; 0000 0129                          else     x += kx;
; 0000 012A                 }
; 0000 012B         }
; 0000 012C         LCDG_PutPixel(x,y);
; 0000 012D }
;
;
;/****************************************************************************/
;/*  Функция вывода круга                                                    */
;/****************************************************************************/
;void LCDG_DrawCircle(unsigned char xc,unsigned char yc,unsigned char r)
; 0000 0134 {
; 0000 0135   int  x,y,d;
; 0000 0136   y = r;
;	xc -> Y+8
;	yc -> Y+7
;	r -> Y+6
;	x -> R16,R17
;	y -> R18,R19
;	d -> R20,R21
; 0000 0137   d = 3-((int)r<<1);
; 0000 0138   x = 0;
; 0000 0139 
; 0000 013A   while(x <= y)
; 0000 013B   {
; 0000 013C   LCDG_PutPixel(x+xc,y+yc);
; 0000 013D   LCDG_PutPixel(x+xc,-y+yc);
; 0000 013E   LCDG_PutPixel(-x+xc,-y+yc);
; 0000 013F   LCDG_PutPixel(-x+xc,y+yc);
; 0000 0140   LCDG_PutPixel(y+xc,x+yc);
; 0000 0141   LCDG_PutPixel(y+xc,-x+yc);
; 0000 0142   LCDG_PutPixel(-y+xc,-x+yc);
; 0000 0143   LCDG_PutPixel(-y+xc,x+yc);
; 0000 0144   if (d<0) {
; 0000 0145     d = d+4*x+6;
; 0000 0146   } else {
; 0000 0147    d = d+4*(x-y)+10;
; 0000 0148    y--;
; 0000 0149   }
; 0000 014A   x++;
; 0000 014B   };
; 0000 014C 
; 0000 014D }
;
;/****************************************************************************/
;/*  Функция рисования прямоугольника                                        */
;/****************************************************************************/
;void LCDG_DrawRect(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char fill)
; 0000 0153 {
; 0000 0154   LCDG_DrawLine(x1, y1, x2, y1);
;	x1 -> Y+4
;	y1 -> Y+3
;	x2 -> Y+2
;	y2 -> Y+1
;	fill -> Y+0
; 0000 0155   LCDG_DrawLine(x1, y2, x2, y2);
; 0000 0156   LCDG_DrawLine(x1, (y1+1), x1, (y2-1));
; 0000 0157   LCDG_DrawLine(x2, (y1+1), x2, (y2-1));
; 0000 0158   if (fill){
; 0000 0159     while(x1<x2){
; 0000 015A       x1++;
; 0000 015B       LCDG_DrawLine(x1, (y1+1), x1, (y2-1));
; 0000 015C     }
; 0000 015D 
; 0000 015E   }
; 0000 015F }
;#include <mega16.h>
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x40
	.EQU __sm_mask=0xB0
	.EQU __sm_powerdown=0x20
	.EQU __sm_powersave=0x30
	.EQU __sm_standby=0xA0
	.EQU __sm_ext_standby=0xB0
	.EQU __sm_adc_noise_red=0x10
	.SET power_ctrl_reg=mcucr
	#endif
;#include "lcd_graph_lib.h"
;
;void main( void )
; 0001 0005 {

	.CSEG
_main:
; 0001 0006   LCDG_InitPort();
	RCALL _LCDG_InitPort
; 0001 0007   LCDG_InitLcd();
	RCALL _LCDG_InitLcd
; 0001 0008   LCDG_ClearLcd(0, 122);
	LDI  R30,LOW(0)
	ST   -Y,R30
	LDI  R30,LOW(122)
	ST   -Y,R30
	RCALL _LCDG_ClearLcd
; 0001 0009   LCDG_SendString(0, 0, "индикатор МЭЛТ 12232");
	LDI  R30,LOW(0)
	ST   -Y,R30
	ST   -Y,R30
	__POINTW1MN _0x20003,0
	ST   -Y,R31
	ST   -Y,R30
	RCALL _LCDG_SendString
; 0001 000A  // LCDG_DrawLine(0,0, 120, 30);
; 0001 000B  // LCDG_DrawCircle(60,15, 14);
; 0001 000C   while(1);
_0x20004:
	RJMP _0x20004
; 0001 000D }
_0x20007:
	RJMP _0x20007

	.DSEG
_0x20003:
	.BYTE 0x15

	.DSEG
_method:
	.BYTE 0x1
_flag:
	.BYTE 0x1
_PlaceArray:
	.BYTE 0x14

	.CSEG
;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x0:
	LDI  R30,LOW(400)
	LDI  R31,HIGH(400)
	ST   -Y,R31
	ST   -Y,R30
	JMP  _delay_ms

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:11 WORDS
SUBOPT_0x1:
	LDI  R30,LOW(238)
	ST   -Y,R30
	RCALL _LCDG_SendCom
	LDI  R30,LOW(164)
	ST   -Y,R30
	RCALL _LCDG_SendCom
	LDI  R30,LOW(169)
	ST   -Y,R30
	RCALL _LCDG_SendCom
	LDI  R30,LOW(175)
	ST   -Y,R30
	RJMP _LCDG_SendCom

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:6 WORDS
SUBOPT_0x2:
	ST   -Y,R30
	RCALL _LCDG_SendCom
	LDI  R30,LOW(226)
	ST   -Y,R30
	RCALL _LCDG_SendCom
	LDI  R30,LOW(192)
	ST   -Y,R30
	RJMP _LCDG_SendCom

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:21 WORDS
SUBOPT_0x3:
	ST   -Y,R30
	RCALL _LCDG_SendCom
	ST   -Y,R16
	RCALL _LCDG_SendCom
	LDI  R30,LOW(0)
	ST   -Y,R30
	RJMP _LCDG_SendData


	.CSEG
_delay_ms:
	ld   r30,y+
	ld   r31,y+
	adiw r30,0
	breq __delay_ms1
__delay_ms0:
	__DELAY_USW 0xFA0
	wdr
	sbiw r30,1
	brne __delay_ms0
__delay_ms1:
	ret

__LSLW2:
	LSL  R30
	ROL  R31
	LSL  R30
	ROL  R31
	RET

__SAVELOCR6:
	ST   -Y,R21
__SAVELOCR5:
	ST   -Y,R20
__SAVELOCR4:
	ST   -Y,R19
__SAVELOCR3:
	ST   -Y,R18
__SAVELOCR2:
	ST   -Y,R17
	ST   -Y,R16
	RET

__LOADLOCR6:
	LDD  R21,Y+5
__LOADLOCR5:
	LDD  R20,Y+4
__LOADLOCR4:
	LDD  R19,Y+3
__LOADLOCR3:
	LDD  R18,Y+2
__LOADLOCR2:
	LDD  R17,Y+1
	LD   R16,Y
	RET

;END OF CODE MARKER
__END_OF_CODE:
