# G29 Load Cell Mod
A cheap Load Cell Mod for the G29 based on the projects of [GeekyDeaks](https://github.com/GeekyDeaks/g29-load-cell) and [Skidude88](https://github.com/Skidude88/Skidude88-G29-PS4-LoadCell-Arduino). All referenced files will not be hotlinked, so you'll have to at least look at the work they have done.

## Shopping list
 * load cell and HX711 module ([example](https://usa.banggood.com/4pcs-DIY-50KG-Body-Load-Cell-Weight-Strain-Sensor-Resistance-With-HX711-AD-Module-p-1326815.html))
 * 3.3V ATmega328P-AU Pro Mini ([example](https://www.banggood.com/3Pcs-3_3V-8MHz-ATmega328P-AU-Pro-Mini-Microcontroller-With-Pins-Development-Board-p-980290.html)) you can use a 5V version, but that would need a separate power supply
 * MCP4725 DAC ([example](https://www.banggood.com/3Pcs-CJMCU-MCP4725-I2C-DAC-Development-Board-Module-p-1051690.html))
 
I ordered a pack of load cells that didn't include the HX711 module. Just like the other parts I ordered multiple of them. In total I payed around 30€ for enough parts to mod 3 pedals (I like to get more in case I brak stuff, and I'll make a second one for a friend)

## Tools / Small parts
* programmer for the pro mini or an Arduino Uno as ISP
* 3D printer
* soldering iron
* wires
* 2 1k resistors
* crimping tool (optional, I crimped the connections to the load cell)
* PCBs to solder all the parts to (I guess you could just solder them together, but that would be messy)

## Software

I used the Arduino IDE to modify [Skidude88's](https://github.com/Skidude88/Skidude88-G29-PS4-LoadCell-Arduino) sketch (Code/SimPedal_ver3_dac-3.3v_board_withFW_Adjust.ino). In the IDE go to 'Sketch > Include Library > Manage Libraries', at the top look for 'hx711' and install the 'HX711 Arduinio Library' by Bogdan Necula and Andreas Motl.
