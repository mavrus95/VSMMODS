
// oled.h

byte OLED_interface;

void comm_out(byte i) {
	switch (OLED_interface) {
		case SPI_mod:
			GLCD_DC_oPort &= ~GLCD_DC_bit;	// DC[RS]=0 - command
			GLCD_CS_oPort &= ~GLCD_CS_bit;	// CS=0
			SPIM_1_SendTxData(i);
			while (!(bSPIM_1_ReadStatus() & SPIM_1_SPIM_SPI_COMPLETE)) ;
			GLCD_CS_oPort |= GLCD_CS_bit;		// CS=1
			GLCD_EN_oPort &= ~GLCD_EN_bit;	// EN=0
			GLCD_WR_oPort |= GLCD_WR_bit;		// WR=1 - NO write
			GLCD_DC_oPort |= GLCD_DC_bit;		// DC=0 - data
		break;
		case M68_mod:
			GLCD_Data_Dir |= 0xFF;
			GLCD_DC_oPort &= ~GLCD_DC_bit;	// DC[RS]=0 - command
			GLCD_WR_oPort &= ~GLCD_WR_bit;	// RW(WR#)=0 - write
			GLCD_EN_oPort |= GLCD_EN_bit;		// EN(RD#)=1
			GLCD_CS_oPort &= ~GLCD_CS_bit;	// CS=0
			GLCD_Data_oPort = i;
			GLCD_CS_oPort |= GLCD_CS_bit;		// CS=1
			GLCD_EN_oPort &= ~GLCD_EN_bit;	// EN=0
			GLCD_WR_oPort |= GLCD_WR_bit;		// WR=1 - NO write
			GLCD_DC_oPort |= GLCD_DC_bit;		// DC=0 - data
		break;
		case I80_mod:
			GLCD_Data_Dir |= 0xFF;
			GLCD_DC_oPort &= ~GLCD_DC_bit;	// DC[RS]=0 - command
			GLCD_EN_oPort |= GLCD_EN_bit;		// EN(RD#)=1
			GLCD_WR_oPort &= ~GLCD_WR_bit;	// RW(WR#)=0 - write
			GLCD_CS_oPort &= ~GLCD_CS_bit;	// CS=0
			GLCD_Data_oPort = i;
			GLCD_CS_oPort |= GLCD_CS_bit;		// CS=1
			GLCD_WR_oPort |= GLCD_WR_bit;		// WR=1 - NO write
			GLCD_EN_oPort |= GLCD_EN_bit;		// EN=1
			GLCD_DC_oPort |= GLCD_DC_bit;		// DC=0 - data
		break;
	}
}

void data_out(byte i) {
	switch (OLED_interface) {
		case SPI_mod:
			GLCD_DC_oPort |= GLCD_DC_bit;		// DC[RS]=0 - data
			GLCD_CS_oPort &= ~GLCD_CS_bit;	// CS=0
			SPIM_1_SendTxData(i);
			while (!(bSPIM_1_ReadStatus() & SPIM_1_SPIM_SPI_COMPLETE)) ;
			GLCD_CS_oPort |= GLCD_CS_bit;		// CS=1
			GLCD_EN_oPort &= ~GLCD_EN_bit;	// EN=0
			GLCD_WR_oPort |= GLCD_WR_bit;		// WR=1 - NO write
			GLCD_DC_oPort |= GLCD_DC_bit;		// DC=0 - data
		break;
		case M68_mod:
			GLCD_Data_Dir |= 0xFF;
			GLCD_DC_oPort |= GLCD_DC_bit;		// DC[RS]=0 - data
			GLCD_WR_oPort &= ~GLCD_WR_bit;	// RW(WR#)=0 - write
			GLCD_EN_oPort |= GLCD_EN_bit;		// EN(RD#)=1
			GLCD_CS_oPort &= ~GLCD_CS_bit;	// CS=0
			GLCD_Data_oPort = i;
			GLCD_CS_oPort |= GLCD_CS_bit;		// CS=1
			GLCD_EN_oPort &= ~GLCD_EN_bit;	// EN=0
			GLCD_WR_oPort |= GLCD_WR_bit;		// WR=1 - NO write
			GLCD_DC_oPort |= GLCD_DC_bit;		// DC=0 - data
		break;
		case I80_mod:
			GLCD_Data_Dir |= 0xFF;
			GLCD_DC_oPort |= GLCD_DC_bit;		// DC[RS]=0 - data
			GLCD_EN_oPort |= GLCD_EN_bit;		// EN(RD#)=1
			GLCD_WR_oPort &= ~GLCD_WR_bit;	// RW(WR#)=0 - write
			GLCD_CS_oPort &= ~GLCD_CS_bit;	// CS=0
			GLCD_Data_oPort = i;
			GLCD_CS_oPort |= GLCD_CS_bit;		// CS=1
			GLCD_WR_oPort |= GLCD_WR_bit;		// WR=1 - NO write
			GLCD_EN_oPort |= GLCD_EN_bit;		// EN=1
			GLCD_DC_oPort |= GLCD_DC_bit;		// DC=0 - data
		break;
	}
}

byte data_inp(void) {
byte i = 0;
	switch (OLED_interface) {
		case M68_mod:
			GLCD_Data_Dir = 0; // на прием
			GLCD_DC_oPort |= GLCD_DC_bit;		// DC[RS]=1 - data
			GLCD_WR_oPort |= GLCD_WR_bit;		// WR=1 - read
			GLCD_EN_oPort |= GLCD_EN_bit;		// EN=1
			GLCD_CS_oPort &= ~GLCD_CS_bit;	// CS=0
			i = GLCD_Data_iPort;
			GLCD_CS_oPort |= GLCD_CS_bit;		// CS=1
			GLCD_EN_oPort &= ~GLCD_EN_bit;	// EN=0
			GLCD_WR_oPort |= GLCD_WR_bit;		// WR=1 - NO write
		break;
		case I80_mod:
			GLCD_Data_Dir = 0; // на прием
			GLCD_DC_oPort |= GLCD_DC_bit;		// DC[RS]=1 - data
			GLCD_WR_oPort |= GLCD_WR_bit;		// WR=1 - no write
			GLCD_EN_oPort &= ~GLCD_EN_bit;	// EN(RD#)=0 - read
			GLCD_CS_oPort &= ~GLCD_CS_bit;	// CS=0
			i = GLCD_Data_iPort;
			GLCD_CS_oPort |= GLCD_CS_bit;		// CS=1
			GLCD_EN_oPort |= GLCD_EN_bit;		// EN=1 - NO read
			GLCD_WR_oPort |= GLCD_WR_bit;		// WR=1 - NO write
		break;
	}
	return (i);
}

void delay_ms(word t) {
word a;
	while (t--) {
		a = 100;
		while (a--);
	}
}

// A[0]=0, 0b00xxxxx0				Disable Column Address Re-map (POR)
// A[0]=1, 0b00xxxxx1	0x01			Enable Column Address Re-map
#define Column_Address_Remap		bit0
// A[1]=0, 0b00xxxx0x				Disable Nibble Re-map (POR)
// A[1]=1, 0b00xxxx1x	0x02			Enable Nibble Re-map
#define Nibble_Remap			bit1
// A[2]=0, 0b00xxx0xx				Horizontal Address Increment (POR)
// A[2]=1, 0b00xxx1xx	0x04			Vertical Address Increment
#define Vertical_Address_Increment	bit2	// else Horizontal Address Increment
// A[4]=0, 0b00x0xxxx				Disable COM Re-map (POR)
// A[4]=1, 0b00x1xxxx	0x10			Enable COM Re-map
#define COM_Remap				bit4
// A[5]=0, 0b000xxxxx				Reserved (POR)
// A[5]=1, 0b001xxxxx	0x20			Reserved
// A[6]=0, 0b00xxxxxx				Disable COM Split Odd Even (POR)
// A[6]=1, 0b01xxxxxx	0x40			Enable COM Split Odd Even
#define COM_Split_Odd_Even		bit6

const char inival[] = {
// Row Address
	0x75, // Set Row Address	------------------------------------------
	0x00, // Start = 0
	0x3F, // End = 63
// Column Address
	0x15, // Set Column Address --------------------------------------------
	0x00, // Start = 0
	0x3F, // End = 63
// Contrast Control
	0x81, // Set Contrast Control (1) --------------------------------------
//	0x40, // default
	0x7F, // =63 viva
// Current Range
	0x86, // Set Current Range 84h:Quarter, 85h:Half, 86h:Full -------------
// Re-map
	0xA0, // Set Re-map ----------------------------------------------------
	COM_Split_Odd_Even|Column_Address_Remap, // 0x41 - OK (with Offset=0x44)
//	COM_Split_Odd_Even|Nibble_Remap, // 0x42 - mirror X
//	COM_Split_Odd_Even|Nibble_Remap|COM_Remap, // 0x52 - 180
// Display Start Line
	0xA1, // Set Display Start Line ----------------------------------------
	0x00, // Start at row 0
// Display Offset
	0xA2, // Set Display Offset --------------------------------------------
///	0x00, // Offset 68 rows
	0x44, // with ReMap=0x41
///	0x44-8,
// Display Mode
	0xA4, // Set DisplaMode,A4:Normal, A5:All ON, A6: All OFF, A7:Inverse --
///	0xA7, // Set DisplaMode,A4:Normal, A5:All ON, A6: All OFF, A7:Inverse --
///	0xA5, // Set DisplaMode,A4:Normal, A5:All ON, A6: All OFF, A7:Inverse --
// Multiplex Ratio
	0xA8, // Set Multiplex Ratio -------------------------------------------
	0x3F, // 64 mux
// Phase Length
	0xB1, // Set Phase Length ----------------------------------------------
	0x22, // [3:0]:Phase 1 period of 1~16 clocks
// [7:4]:Phase 2 period of 1~16 clocks // POR = 0111 0100
// Set Pre-charge Compensation Enable
	0xB0, // Set Pre-charge Compensation Enable ----------------------------
	0x28, // Enable
// Set Pre-charge Compensation Level
	0xB4, // Set Pre-charge Compensation Level -----------------------------
	0x07, // Higher level
///	0x03, // recomended
// Row Period
	0xB2, // Set Row Period ------------------------------------------------
	0x46, // [7:0]:18~255, K=P1+P2+GS15 (POR:4+7+29)
// Display Clock Divide
	0xB3, // Set Clock Divide (2) ------------------------------------------
///	0x91, // [3:0]:1~16, [7:4]:0~16, 100Hz
	0x02, // [3:0]:1~16, [7:4]:0~16, 100Hz
// POR = 0000 0001
// VSL
	0xBF, // Set VSL -------------------------------------------------------
///	0x0D, // [3:0]:VSL
	0x0B, // [3:0]:VSL
// VCOMH
	0xBE, // Set VCOMH (3) -------------------------------------------------
	0x02, // [7:0]:VCOMH, (0.53 X Vref = 0.53 X 15 V = 7.95V)
// VP
	0xBC, // Set VP (4) ----------------------------------------------------
///	0x10, // [7:0]:VP, (0.67 X Vref = 0.67 X 15 V = 10.05V)
	0x13, // [7:0]:VP, (0.67 X Vref = 0.67 X 15 V = 10.05V)
// Gamma
	0xB8, // Set Gamma with next 8 bytes -----------------------------------
	0x01, // L1[2:0],
	0x11, // L3[6:4], L2[2:0] 0001 0001
	0x22, // L5[6:4], L4[2:0] 0010 0010
	0x32, // L7[6:4], L6[2:0] 0011 1011
	0x43, // L9[6:4], L8[2:0] 0100 0100
	0x54, // LB[6:4], LA[2:0] 0101 0101
	0x65, // LD[6:4], LC[2:0] 0110 0110
	0x76, // LF[6:4], LE[2:0] 1000 0111
// Set DC-DC
	0xAD, // Set DC-DC -----------------------------------------------------
	0x02, // 03=ON, 02=Off
// Display ON/OFF
	0xAF, // AF=ON, AE=Sleep Mode ------------------------------------------
};

void oled_init(void) {
word i;
	delay_ms(2);
	GLCD_RES_oPort &= ~GLCD_RES_bit; // Reset Driver IC
	delay_ms(2);
	GLCD_RES_oPort |= GLCD_RES_bit;
	delay_ms(2);
	GLCD_SHDN_oPort |= GLCD_SHDN_bit;
	delay_ms(40);
	GLCD_CS_oPort |= GLCD_CS_bit;	// CS=1
	for (i=0;i<80*64;i++) data_out(0); // =0
	for (i=0;i<sizeof(inival);i++) comm_out(inival[i]);
}

void img_out(byte x, byte y, const char *a) {
byte i,j;
byte dx = *a++;
byte dy = (*a++) - 1;
byte x9 = x+dx-1;
	comm_out(0x75); comm_out(y); comm_out(y+dy);
	for (i=0;i<=dy;i++) {
		comm_out(0x15); comm_out(x); comm_out(x9);
		for (j=0;j<dx;j++) data_out(*a++);
	}
}

