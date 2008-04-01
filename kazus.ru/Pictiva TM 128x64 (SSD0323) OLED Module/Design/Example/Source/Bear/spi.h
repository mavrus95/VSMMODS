
// spi.h

#define M32 32

#define	bSPIM_ReadStatus() SPSR
#define	bSPIM_1_ReadStatus() SPSR
#define	SPIM_bReadStatus()	SPSR
#define	SPI1M_bReadStatus()	SPSR
#define	SPI1M_CONTROL_REG	SPCR
#define	SPI1M_INT_REG		SPCR
#define SPI1M_Start_Bit	(1<<SPE)
#define SPI1M_INT_Bit	(1<<SPIE)
#define	SPI1M_TX_BUFFER_REG SPDR
#define	SPI1M_RX_BUFFER_REG SPDR

#define SPIM_SPIM_SPI_COMPLETE		0x80      // SPI Tx/Rx cycle has completed
#define SPIM_1_SPIM_SPI_COMPLETE	0x80
#define SPI1M_SPIM_SPI_COMPLETE		0x80      // SPI Tx/Rx cycle has completed

#define Neg_Clock		0x02
#define Trailing_Edge	0x04
#define SPIM_SPIM_LSB_FIRST		0x80      // LSB bit transmitted/received first
#define SPIM_1_SPIM_LSB_FIRST	0x80      // LSB bit transmitted/received first
#define SPIM_SPIM_MSB_FIRST		0x00      // MSB bit transmitted/received first
#define SPIM_1_SPIM_MSB_FIRST	0x00      // MSB bit transmitted/received first

#define SPIM_SPIM_MODE_3	6      // MODE 3 - Trailing edge latches data - neg clock
#define SPIM_1_SPIM_MODE_3	6
#define SPI1M_SPIM_MODE_3	6

#define SPIM_SPIM_MODE_2	4      // MODE 2 - Trailing edge latches data - pos clock
#define SPIM_1_SPIM_MODE_2	4
#define SPI1M_SPIM_MODE_2	4

#define SPIM_SPIM_MODE_1	2      // MODE 1 - Leading edge latches data - neg clock
#define SPIM_1_SPIM_MODE_1	2
#define SPI1M_SPIM_MODE_1	2

#define SPIM_SPIM_MODE_0	0      // MODE 0 - Leading edge latches data - pos clock
#define SPIM_1_SPIM_MODE_0	0
#define SPI1M_SPIM_MODE_0	0

#define SPIM_1_SendTxData SPI1M_SendTxData
#define SPIM_1_Start SPI1M_Start

#ifdef a8515
#define SCK		bit7
#define MISO	bit6
#define	MOSI	bit5
#define	SS		bit4
//X#define FIX		bit2
//X#define	SSUser	bit1
#define	SPM_oPort	PORTB
#define	SPM_Dir		DDRB
#define	SPM_CLK		bit7
#define	SPM_MISO	bit6
#define	SPM_MOSI	bit5
#define	SPM_SS		bit4
#endif a8515

#ifdef M8
#define SCK		bit5
#define MISO	bit4
#define	MOSI	bit3
#define	SS		bit2
//X#define FIX		bit1
//X#define	SSUser	bit0
#define	SPM_oPort	PORTB
#define	SPM_Dir		DDRB
#define	SPM_CLK		bit5
#define	SPM_MOSI	bit3
#define	SPM_MISO	bit4
#define	SPS_MOSI	bit3
#define	SPS_MISO	bit4
#define	SPM_SS		bit2
//X#define	SPM_SSUser	bit0
#endif M8

#ifdef M16
#define SCK		bit7
#define MISO	bit6
#define	MOSI	bit5
#define	SS		bit4
//X#define FIX		bit3
//X#define	SSUser	bit2
#define	SPM_oPort	PORTB
#define	SPM_Dir		DDRB
#define	SPM_CLK		bit7
#define	SPM_MOSI	bit5
#define	SPM_MISO	bit6
#define	SPM_SS		bit4
#define	SPS_MOSI	bit5
#define	SPS_MISO	bit6
#endif  M16

#ifdef M32
#define SCK		bit7
#define MISO	bit6
#define	MOSI	bit5
#define	SS		bit4
//X#define FIX		bit3
//X#define	SSUser	bit2
#define	SPM_oPort	PORTB
#define	SPM_Dir		DDRB
#define	SPM_CLK		bit7
#define	SPM_MOSI	bit5
#define	SPM_MISO	bit6
#define	SPM_SS		bit4
#endif  M32

#ifdef M128
#define	SS		bit0
#define SCK		bit1
#define	MOSI	bit2
#define MISO	bit3
//X#define	SSUser	bit4
//X#define FIX		bit5
#endif  M128

void SPI1M_Speed(byte s) { // 1-250, 2-62, 3-31
	SPCR &= ~((1<<SPR1) | (1<<SPR0)); // 31.25kHz - самая медленная скорость
	if (s) SPCR |= (s & 3);
}

void SPI1M_Start(byte m) {
	GLCD_SPI_Dir |= (SPM_CLK|SPM_MOSI|SPM_SS);  // Set SCK, MOSI & SS as outputs
	GLCD_SCLK_oPort &= ~(SPM_CLK|SPM_MOSI|SPM_SS);  // clear bits MOSI, & SCK		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! OK
	SPCR = (1<<SPE) | (1<<MSTR) // 1000kHz
//		| (1<<SPR0); // 250kHz
//		| (1<<SPR1); // 62.5kHz
		| (1<<SPR1) | (1<<SPR0); // 31.25kHz - minimum
	if (m & Neg_Clock) SPCR |= (1<<CPOL);			// mode=1,3
	if (m & Trailing_Edge) SPCR |= (1<<CPHA);		// mode=2,4
	if (m & SPIM_1_SPIM_LSB_FIRST) SPCR |= (1<<DORD);
}

void SPI1M_SendTxData(byte b) {
	SPDR = b;
}
