ICM7218A 8-digits LED Display Driver, parallel interface. For common anode mux LEDS
ICM7218B 8-digits LED Display Driver, parallel interface. For common cathode mux LEDS


ICM7218A and 7218B models require MAXIM.DLL to be installed in MODELS dir.
Device library in included in MAXIM.LIB.


NOTE:
1)
MAXIM ICM7218A/B are upwardly compatible with Intersil ICL7218 and 7228, unless the MAXIM has a double RAM bank select and single digit update mode. Models supports all MAXIM and INTERSIL modes, included bank select and digit update.

2) 
Jigs require a couple of pattern generators to manage parallel data and commands I/O. A number of pattern files are preconfigured there to simulate some of relevant modes as below:

1) Code B decode (BCD table mode)
2) Hex decode  (HEX table mode)
3) No decode (User table decode)
4) Single digit update in Code B decode mode.

To switch between modes, the Data and Write command generator must be loaded with proper pattern files.


EA