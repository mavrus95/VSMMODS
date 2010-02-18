NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   0054   6E6F =  28271. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0054  __lit_start
       0054  _inival
       0082  _bear
       519B  _dog
       6EC3  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   6EC4   0428 =   1064. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       3762  __start
       3762  __text_start
       3782  _exit
       3783  _SPI1M_Speed
       378E  _SPI1M_Start
       379D  _SPI1M_SendTxData
       379F  _comm_out
       37DC  _data_out
       3819  _data_inp
       383C  _delay_ms
       3852  _oled_init
       3882  _img_out
       38BD  _main
       393C  push_arg4
       393E  push_arg2
       3941  empy16s
       3951  pop_gset2
       3954  pop_gset5
       3957  push_gset5
       3959  push_gset4
       395B  push_gset3
       395D  push_gset2
       395F  push_gset1
       3962  pop_gset1
       3963  pop
       3976  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   0060   0001 =      1. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  __bss_start
       0060  _OLED_interface
       0061  __bss_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0004 =      4. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

C:\icc631\lib\crtatmega.o	[ crtatmega.s ]
main.o	[ main.c ]
<library>	[ asave.s, emul16s.s, gpop2.s, gpop5.s, gpush.s ]

User Global Definitions

ram_end = 0x85f
hwstk_size = 0x10

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:1.1024

