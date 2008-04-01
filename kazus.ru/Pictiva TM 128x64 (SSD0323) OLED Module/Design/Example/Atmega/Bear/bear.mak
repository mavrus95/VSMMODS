CC = iccavr
CFLAGS =  -IC:\icc631\include\ -e -DATMEGA -DATMega32  -l -g -Mavr_enhanced -Wf-str_in_flash 
ASFLAGS = $(CFLAGS)  -Wa-g
LFLAGS =  -LC:\icc631\lib\ -g -ucrtatmega.o -bfunc_lit:0x54.0x8000 -dram_end:0x85f -bdata:0x60.0x85f -dhwstk_size:16 -beeprom:1.1024 -fihx_coff -S2
FILES = main.o 

bear:	$(FILES)
	$(CC) -o bear $(LFLAGS) @bear.lk   -lcatmega
main.o: C:/icc631/include/iom32v.h C:/icc631/include/macros.h C:/icc631/include/math.h C:\Work\Example\Design\Example\Source\Bear/def.h C:\Work\Example\Design\Example\Source\Bear/pins.h C:\Work\Example\Design\Example\Source\Bear/spi.h\
 C:\Work\Example\Design\Example\Source\Bear/oled.h C:\Work\Example\Design\Example\Source\Bear/images/bear.h C:\Work\Example\Design\Example\Source\Bear/images/dog.h
main.o:	C:\Work\Example\Design\Example\Source\Bear\main.c
	$(CC) -c $(CFLAGS) C:\Work\Example\Design\Example\Source\Bear\main.c
