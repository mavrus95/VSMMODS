;********************************************************************************
;* 文件名：TG19264.ASM
;* 功  能：TG19264液晶模块驱动程序
;* 作  者：SZN
;* 日  期：2005.07.10
;* 备  注：
;*********************************************************************************

 ;LCM 型号: TG19264A (192*64)

 ;LCM 接口: 1:GND 2:VCC 3:V0 4.RS 5:RW 6:E 7--14:DB0-DB7
 ;          15:CS1 16:RST 17:CS2 18:CS3 19:Vee 20:LED+

;***************************************************************************

;---端口地址定义----------------
CMD_BLK1    EQU    0x18	   
CMD_BLK2    EQU    0x14
CMD_BLK3    EQU    0x0C
CMD_READ    EQU	   0x02
CMD_WRITE   EQU	   0x00	
CMD_DATA    EQU	   0x01
CMD_CMD     EQU	   0x00

BLK1_WR_CMD 	EQU		(CMD_BLK1|CMD_WRITE|CMD_CMD) 
BLK2_WR_CMD 	EQU		(CMD_BLK2|CMD_WRITE|CMD_CMD)
BLK3_WR_CMD 	EQU		(CMD_BLK3|CMD_WRITE|CMD_CMD)
											 
BLK1_WR_DATA 	EQU		(CMD_BLK1|CMD_WRITE|CMD_DATA) 
BLK2_WR_DATA 	EQU		(CMD_BLK2|CMD_WRITE|CMD_DATA)
BLK3_WR_DATA 	EQU		(CMD_BLK3|CMD_WRITE|CMD_DATA)


;---全局变量定义----------------
XPOS    EQU     30H		;X坐标
YPOS    EQU     31H		;Y坐标

;---常量定义----------------
PD1	 EQU	40H		;每一个分区宽64点(液晶片分区参数)


       ORG 0000H
       LJMP MAIN
       ORG 0040H
MAIN:  MOV SP,#60H
K1:    
       LCALL    LCDRESET	;LCD复位

       MOV      R7,#0       ;XPOS
       MOV      R5,#0       ;YPOS
       MOV	DPTR,#STRING1	;       uchar *p = *string1;
       MOV      R3,DPH
       MOV      R4,DPL
       LCALL	_PUTSTR		;显示STRING1
       
	   MOV R7,#250
	   LCALL _DelayXms	
	   MOV R7,#250
	   LCALL _DelayXms		;DELAY 500ms

	   MOV      R7,#0       ;XPOS
       MOV      R5,#2       ;YPOS
       MOV	DPTR,#STRING2	;       uchar *p = *string2;
       MOV      R3,DPH
       MOV      R4,DPL
       LCALL    _PUTSTR		;显示STRING2
						
	   MOV R7,#250
	   LCALL _DelayXms	
	   MOV R7,#250
	   LCALL _DelayXms		;DELAY 500ms

       MOV      R7,#0
       LCALL    _LCDFILL	;清屏
					  	   
	   MOV R7,#250
	   LCALL _DelayXms	
	   MOV R7,#250
	   LCALL _DelayXms		 ;DELAY 500ms

       MOV      R6,#0
       MOV      R7,#0
       MOV      R4,#30H
       MOV      R5,#03H
       MOV      DPTR,#TUDOT2 ;#TUKDOT
       MOV      R2,DPH
       MOV      R3,DPL
       LCALL    _DispIcon32	 ;显示半圆
	   	 
	   MOV R7,#250
	   LCALL _DelayXms	
	   MOV R7,#250
	   LCALL _DelayXms
	   MOV R7,#250
	   LCALL _DelayXms	
	   MOV R7,#250			   ;DELAY 1s
	   LCALL _DelayXms
       AJMP	K1;$		;      while(1);
       
	   
       $INCLUDE(HZK16.ASM)      ;16*16汉字点阵字库

;--------------------------------外部接口函数--------------------------------
;
; 说明：考虑和C51的兼容性，更改入口参数为标准A51形式
;
; 函数原型：
; void LCDRESET(void);   //LCM系统复位子程序
; void LCDFILL(uchar);   //LCD全屏填充程序
; void PUTSTR(uchar x, uchar y, uchar *str);  //16*16字符点阵输出
; void DispIcon32(uint xy, uint lw, uchar *str);  //图标点阵输出
;
;****************************************************************
;功能：LCM系统复位子程序
;标号：    (1)ASM: LCDRESET      (2) C : LCDRESET(void)
;入口参数：无
;出口参数：无
;堆栈需求：>5 字节
;影响资源：XPOS, YPOS
;****************************************************************
LCDRESET:
        PUSH    ACC
        MOV     A,R7
        PUSH    ACC
        MOV     A,#3EH          ;关LCD显示
		CALL	LCDWC1
		CALL	LCDWC2
		CALL    LCDWC3
        MOV     A,#3FH          ;打开LCD显示
		CALL	LCDWC1
		CALL    LCDWC2
		CALL	LCDWC3
        MOV     A,#0C0H         ;设首址
		CALL    LCDWC1
		CALL    LCDWC2
		CALL    LCDWC3
        MOV	R7,#00H
        LCALL	_LCDFILL		;	void  lcdfill( uchar a );
        POP     ACC
        MOV     R7,A
        POP     ACC
		RET

;****************************************************************
;功能：全屏填充程序
;标号：    (1)ASM: _LCDFILL     (2) C : LCDFILL(uchar)
;入口参数：(1)ASM: R7
;出口参数：无
;堆栈需求：4 字节
;影响资源：XPOS, YPOS
;****************************************************************
_LCDFILL:                        ;LCD整屏显示R7的内容
        PUSH    ACC
        MOV     YPOS,#0
LFL_PB: MOV     XPOS,#0
LFL_PA: MOV     A,R7
        CALL    LCDWRITE        ;定位并写数据
        CALL    CUSORNEXT
        MOV     A,XPOS
        JNZ     LFL_PA
        MOV     A,YPOS
        JNZ     LFL_PB
        POP     ACC
        RET

;********************************************************************
;功能：字符数据输出子程序
;标号：    (1)ASM: _PUTSTR       (2) C : PUTSTR(uchar,uchar,uchar*)
;入口参数：(1)ASM: R7, R5, (R3,R4)
;出口参数：无
;子程序调用：无
;堆栈需求：4 字节
;影响资源：XPOS,YPOS
;********************************************************************
_PUTSTR:
        PUSH    DPL    ;内部使用DPTR, A, B, R7
        PUSH    DPH
        PUSH    ACC
        PUSH    B
        MOV     A,R7
        PUSH    ACC    ;SAVE

        MOV     XPOS,R7
        MOV     YPOS,R5
        MOV     DPH,R3
        MOV     DPL,R4
PUTSTR:
;	CALL	DELAY           ;用于显示演示速度
	CALL	GETSTRCHAR	;取字符串中的字符码
	PUSH	DPL
	PUSH	DPH
	JNC	PSR_LAX		;显示结束
	JNB	B.7,PSR_LBY	;编码<128,英文
;CHINESE:			;汉字输出16*16=8*16 + 8*16
	CALL	HZKPOS		;点阵码偏移量换算
	CALL	PUTCWDOT	;16*16点阵输出
	JMP	PSR_LBX
PSR_LBY:
;ENGLISH:			;英文（数字）半角字符输出
	CALL	EZKPOS		;点阵码偏移量换算
	CALL	PUTCHARDOT	;8*16点阵输出
PSR_LBX:
	POP	DPH
	POP	DPL
	JMP	PUTSTR		;继续下一位
PSR_LAX:POP	DPH
	POP	DPL

    POP     ACC       ;RECOVER
    MOV     R7,A
    POP     B
    POP     ACC
    POP     DPH
    POP     DPL
	RET

;********************************************************************
;功能：图标点阵输出子程序
;标号：    (1)ASM: _DispIcon32   (2)C: DispIcon32(uint xy,uint lw,uchar *str)
;入口参数：(1)ASM: (R6,R7), (R4,R5), (R2,R3)
;          (2)C: xy--坐标, lw--图片长宽, str--数据
;出口参数：无
;子程序调用：无
;堆栈需求：4 字节
;影响资源：XPOS,YPOS
;********************************************************************
_DispIcon32:
        PUSH    DPL    ;内部使用DPTR, A, B, R7
        PUSH    DPH
        PUSH    ACC
        PUSH    B
        MOV     A,R7
        PUSH    ACC    ;SAVE

        MOV     XPOS,R6
        MOV     YPOS,R7
        MOV     DPH,R2
        MOV     DPL,R3
        MOV     B,R5       ;WIDTH
PCW_PA1:MOV     A,R4
        MOV	R7,A       ;LENGTH
PCW_PA2:				;上半个字符
		CLR	A
		MOVC	A,@A+DPTR	;获取点阵码
		CALL	LCDWRITE	;写入LCM（上半个字部分）
		INC	XPOS		;X坐标加1
		INC	DPTR		;指向下一个点阵码
		DJNZ	R7,PCW_PA2
        DEC     B
        MOV     A,B
        JZ      ICON_END
        INC	YPOS
	    MOV     XPOS,R6   ;
        AJMP    PCW_PA1
ICON_END:
        POP     ACC       ;RECOVER
        MOV     R7,A
        POP     B
        POP     ACC
        POP     DPH
        POP     DPL
	    RET

;--------------------------------内部调用函数--------------------------------

;****************************************************************
;获取字串内字符编码，C=0显示结束，字符串以0FFH结尾作为结束标志
;以两字节组成一个字符：前一字节表示是全角（>=80H)还是半角(<80H)
;                      后一字节字符点阵表内偏移量"内码"
;****************************************************************
GETSTRCHAR:             ;IN: DPTR
GSC_PA:
	CLR	A
	MOVC	A,@A+DPTR	;先读取字头
	INC	DPTR
	MOV	B,A
	INC	A
	CLR	C		;置程序出口标志（表示已经结束）
	JZ	GSC_LAX		;如果是结束码（0ffh+1=00h)
	CLR	A
	MOVC	A,@A+DPTR	;真正读取"内码"
	INC	DPTR
	SETB	C		;编码有效
GSC_LAX:
	RET             ;OUT: B
;****************************************************************
;全角字符数据输出，16*16点阵
;****************************************************************
PUTCWDOT:               ;IN: DPTR
	PUSH	XPOS
	MOV	R7,#16
PCW_PA:				;上半个字符
	CLR	A
	MOVC	A,@A+DPTR	;获取点阵码
	CALL	LCDWRITE	;写入LCM（上半个字部分）
	INC	XPOS		;X坐标加1
	INC	DPTR		;指向下一个点阵码
	DJNZ	R7,PCW_PA
	INC	YPOS
	POP	XPOS
	MOV	R7,#16
PCW_PB:				;下半个字符
	CLR	A		;
	MOVC	A,@A+DPTR	;再取一个点阵码
	CALL	LCDWRITE	;输出
	INC	DPTR		;指向下一个点阵码
	INC	XPOS		;指向下一列
	DJNZ	R7,PCW_PB
	DEC	XPOS
	CALL	CUSORNEXT	;坐标指针自动移位计算（指向下一列）
	MOV	A,XPOS		;判断是否换行？
	JNZ	PCW_PC
	INC	YPOS
PCW_PC:	DEC	YPOS		;返回上半个字部分
	RET
;****************************************************************
;半角字符数据输出，8*16点阵
;****************************************************************
PUTCHARDOT:              ;IN: DPTR
	PUSH	XPOS
	MOV	R7,#8
PAC_PA:				;上半个字符
	CLR	A
	MOVC	A,@A+DPTR	;获取点阵码
	CALL	LCDWRITE	;写入LCM（上半个字部分）
	INC	DPTR		;指向下一个点阵码
	INC	XPOS
	DJNZ	R7,PAC_PA
	INC	YPOS
	POP	XPOS
	MOV	R7,#8
PAC_PB:				;下半个字符
	CLR	A		;
	MOVC	A,@A+DPTR	;再取一个点阵码
	CALL	LCDWRITE	;输出
	INC	DPTR		;指向下一个点阵码
	INC	XPOS
	DJNZ	R7,PAC_PB
	DEC	XPOS
	CALL	CUSORNEXT	;坐标指针自动移位计算（指向下一列）
	MOV	A,XPOS		;判断是否换行？
	JNZ	PAC_LA2
	INC	YPOS
PAC_LA2:
	DEC	YPOS		;返回上半个字部分
	RET
;****************************************************************
;  汉字库实际指针换算,结果置入DPTR
;****************************************************************
HZKPOS:                ;IN: A
	MOV	B,#32
	MUL	AB
	MOV	DPTR,#HZKDOT
	AJMP	ZKPOS
;****************************************************************
;  英文字母数字实际指针换算,结果置入DPTR
;****************************************************************
EZKPOS:                ;IN: A
	MOV	B,#16
	MUL	AB
	MOV	DPTR,#EZKDOT	;修改数据指针，指向所选字母
ZKPOS:	ADD	A,DPL
	MOV	DPL,A
	MOV	A,B
	ADDC	A,DPH
	MOV	DPH,A
	RET            ;OUT: DPTR

;****************************************************************
;按给定的XY坐标定位，并写数据子程序
;****************************************************************
LCDWRITE:                ;IN: A
    CALL    LCDPOS       	;坐标指针定位
    CALL    LCDWD        	;写数据
    RET

;****************************************************************
; 连续输出时的坐标指针换算，自动指向下一个可写入地址
;****************************************************************
CUSORNEXT:
    PUSH    ACC
	ANL	YPOS,#7
	INC	XPOS
	MOV	A,XPOS
	CJNE    A,#192,CNT_LAX
	MOV	XPOS,#0
	INC	YPOS
	MOV	A,YPOS
	ANL	A,#0F8H
	JZ	CNT_LAX
	MOV	YPOS,#0
CNT_LAX:
	POP     ACC
    RET
;****************************************************************
;一字节数据输出
;****************************************************************
LCDWD:                    ;IN: A
    PUSH    B
    PUSH    ACC
    MOV	B,A
	MOV	A,XPOS
	CJNE	A,#64,$+3
	JNC	LWD_LA1
	MOV	A,B
	CALL	LCDWD1
	JMP	LWD_LA3
LWD_LA1:CJNE	A,#128,$+3
	JNC	LWD_LA2
	MOV	A,B
	CALL	LCDWD2
	JMP	LWD_LA3
LWD_LA2:CJNE	A,#192,$+3
	JNC	LWD_LA3
	MOV	A,B
	CALL	LCDWD3
LWD_LA3:
    POP     ACC
    POP     B
	RET
;****************************************************************
; X,Y坐标定位处理
;****************************************************************
LCDPOS:
	PUSH	ACC
    PUSH    B
	MOV	A,YPOS		;取Y座标
	ANL	A,#7		;保留低三位
	ADD	A,#0B8H		;光标定位指令
	MOV	B,A		;暂存Y坐标
	CLR	C
	MOV	A,XPOS		;取X坐标值
	SUBB	A,#PD1		;左区边界
	JNC	LPS_LA1		;如果不在左区
	MOV	A,XPOS		;重新取X坐标值
	ANL	A,#3FH		;左边部分（CS1）
	ORL	A,#40H		;X方向定位指令
	CALL	LCDWC1		;X定位
	MOV	A,B		;Y定位
	CALL	LCDWC1
	JMP	LPS_LA3		;返回
LPS_LA1:CLR	C
	MOV	A,XPOS
    SUBB	A,#PD1          ;SUBB	A,#PD1*2        ;中间区右边界
    SUBB	A,#PD1
	JNC	LPS_LA2		;如果不在中间区
	MOV	A,XPOS
	ANL	A,#3FH		;中间部分（CS2）
	ORL	A,#40H		;X方向定位指令
	CALL	LCDWC2		;X定位
	MOV	A,B
	CALL	LCDWC2		;Y坐标定位
	JMP	LPS_LA3		;返回
LPS_LA2:CLR	C
	MOV	A,XPOS
	SUBB	A,#PD1          ;SUBB	A,#PD1*3	;右边区域边界
    SUBB	A,#PD1
    SUBB	A,#PD1
	JNC	LPS_LA3		;如果还出界则不予定位
	MOV	A,XPOS
	ANL	A,#3FH		;右边部分（CS3）
	ORL	A,#40H		;X方向定位指令
	CALL	LCDWC3
	MOV	A,B
	CALL	LCDWC3		;Y方向定位
LPS_LA3:
    POP     B
	POP	ACC
	RET


;--------------------------------底层操作子程序----------------------------------
; 修改人：SZN
; 修改日期：2005.07.10
;		  
;********************************************************************
;功能：控制命令输出子程序
;标号：    (1)ASM: LCDWC1, LCDWC2, LCDWC3
;入口参数：(1)ASM: A
;出口参数：无
;子程序调用：WAITIDLE1, WAITIDLE2, WAITIDLE3
;堆栈需求：4 字节
;影响资源：LCMCTRL
;********************************************************************
LCDWC1: PUSH    ACC	 
        PUSH    DPH
        PUSH    DPL
        MOV DPTR,#BLK1_WR_CMD
        SJMP    WCCOM
LCDWC2: PUSH    ACC	
        PUSH    DPH
        PUSH    DPL
        MOV DPTR,#BLK2_WR_CMD
        SJMP    WCCOM
LCDWC3:	PUSH    ACC	 
        PUSH    DPH
        PUSH    DPL
        MOV DPTR,#BLK3_WR_CMD
 WCCOM: 
        MOVX    @DPTR,A      ;E=1 D/I=0 R/W=0
        POP     DPL
        POP     DPH
        POP     ACC
       	RET

;****************************************************************
;数据写输出（分为左中右3个程序）
;****************************************************************
LCDWD1: PUSH    ACC               ;片1写数据子程序 
        PUSH    DPH
        PUSH    DPL
        MOV DPTR,#BLK1_WR_DATA
        SJMP    WDCOM
LCDWD2: PUSH    ACC               ;片2写数据子程序 
        PUSH    DPH
        PUSH    DPL
        MOV DPTR,#BLK2_WR_DATA
        SJMP    WDCOM
LCDWD3: PUSH    ACC               ;片3写数据子程序	
        PUSH    DPH
        PUSH    DPL
        MOV DPTR,#BLK3_WR_DATA
 WDCOM: 
        MOVX    @DPTR,A      ;E=1 D/I=0 R/W=0
        POP     DPL
        POP     DPH
        POP     ACC
       	RET

;********************************************************************
;功能：延时Xms子程序          /***IN:R7****(char)*************/
;标号：    (1)ASM: _DelayXms       (2) C : DelayXms(unsigned char)
;入口参数：(1)ASM: R7 (延时R7毫秒)
;出口参数：无
;子程序调用：无
;堆栈需求：4 字节
;影响资源：R7
;********************************************************************
_DelayXms:
       PUSH ACC
       PUSH B
DLYXMS:MOV A,#02H
AG0:   MOV B,#0C7H
AG1:   DJNZ B,AG1
       DEC A
       JNZ AG0
       DJNZ R7,DLYXMS
       POP B
       POP ACC
       RET

;********************************************************************
;功能：延时10us子程序
;标号：    (1)ASM: Delay10us       (2) C : Delay10us(void)
;入口参数：无
;出口参数：无
;子程序调用：无
;堆栈需求：2 字节
;影响资源：无
;********************************************************************
Delay10us:
       NOP
       NOP
       NOP
       NOP
       NOP
       NOP
       RET