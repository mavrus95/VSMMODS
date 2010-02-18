
// def.h

typedef unsigned char byte;
typedef unsigned int word;

#define M8C_DisableGInt		CLI()			// DISABLE all interrupts
#define M8C_EnableGInt		SEI()			// re-enable interrupts

#define bit0	0x01
#define bit1	0x02
#define bit2	0x04
#define bit3	0x08
#define bit4	0x10
#define bit5	0x20
#define bit6	0x40
#define bit7	0x80
#define bit8	0x0100
#define bit9	0x0200
#define bit10	0x0400
#define bit11	0x0800
#define bit12	0x1000
#define bit13	0x2000
#define bit14	0x4000
#define bit15	0x8000
