
Proteus VSM model for Nokia 6610/6610i/6100 Colored LCD.

http://www.electronicslab.ph/forum/index.php/topic,10649.0.html
http://www.electronicslab.ph/forum/index.php/topic,4167.0.html
http://www.electronicslab.ph/forum/index.php/topic,3687.msg170535.html#msg170535


-- 'yus --

http://projectproto.blogspot.com/

#################################################################################################

changelog:

July 17, 2009 	- initial MODDLL file (PCF8833) intended for Philips lcd controller.

July 19, 2009 	- basic plot functions added (RAM write, Column Address Set, Page Address Set)
		- still having problems with faster clock signals, and also with plot animation
July 26, 2009	- IDSIMMODEL is now capable of high clock cycles (input),
			but the IACTIVEMODEL (animation model) is still having problems.
			( i'm currently studying the windows C++ GDI functions for better plot animation model)

Nov. 11, 2010	- (project revisit) "overhauled" source code for proper C++ implementation.
			Simulation model (pcf8833.dll file) created with MS Visual C++ 2008 Express Edition
			Windows GDI (for IACTIVEMODEL) is already implemented.
			supports s8-bit per pixel format only.
			tested only on Proteus 7.7sp2 (WinXP and Win7)

Nov. 13, 2010	- "12 bits per pixel" mode support (3 bytes for 2 pixels)
			fixed startup/initialize error. (tested on v7.5sp3 and v7.7sp2)
			accepted lcd commands:
				- SWRESET, CASET, PASET, RAMWR, MADCTL, COLMOD (others will be discarded for now)
			known issues:
				- problem with screen orientation with respect to ISIS sysmbol
				- 12bpp mode causes a number of wrong pixel colors


Nov. 16, 2010	- fixed "12bpp mode" setpixel funtion
			better zoom in / zoom outs
			added { INVON, INVOFF, DISPON, DISPOFF } commands support
			screen orientation not yet fully tested

Nov. 18, 2010	- some code clean-ups
			change library (yusLCDs.lib/yusLCDs.idx) together with the other LCDmodels

