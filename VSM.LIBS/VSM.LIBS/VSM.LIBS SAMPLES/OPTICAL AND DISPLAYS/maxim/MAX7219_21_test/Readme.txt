MAX7219  8-digits LED Display Driver, serial inteface. For common cathode mux LEDS
MAX7221  8-digits LED Display Driver, true SPI. For common cathode mux LEDS.


MAX7219 and 7221 models require MAXIM.DLL to be installed in MODELS.TXT.
Device library is included in MAXIM.LIB.


BRIGHT INTENSITY SUPPORT NOTE:

Although intensity effects are not modelled in LEDMPX, MAX7219/21 models make fully support at serial interface level. Duty cycle of digits interface will change accordingly. 

The multiplexing frequency is optimized for a multiple of frame per second rate, which allows to reduce CPU resources (%) spent during realtime simulation. The mux frequency of MAX7119 models is optimized for max intensity of 31/32, while the MAX7221 model is optimized for max intensity of 15/16. Lower intensity (min duty cycle) will requires more simulation resources, as well as to reduce the "minimum trigger time" of LEDMPX.

Effects of pin ISET (Analogue Intensity Set Resistor) is not modeled.


EA