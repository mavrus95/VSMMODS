/////////////////////////////////////////////////////////////////
//           LCD is configured as memory mapped device         //
/////////////////////////////////////////////////////////////////

// base address to set RS_LCD = 0, RW_LCD = 0 
xdata char wrctl_lcd  _at_ 0x0000; 

// base address to set RS_LCD = 1, RW_LCD = 0 
xdata char wrdata_lcd _at_ 0x0100; 

// base address to set RS_LCD = 0, RW_LCD = 1 
xdata char rdctl_lcd  _at_ 0x0200; 

// base address to set RS_LCD = 1, RW_LCD = 1 
xdata char rddata_lcd _at_ 0x0300; 
