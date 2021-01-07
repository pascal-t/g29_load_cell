# G29 Load Cell Mod
A cheap Load Cell Mod for the G29 based on the projects of [GeekyDeaks](https://github.com/GeekyDeaks/g29-load-cell) and [Skidude88](https://github.com/Skidude88/Skidude88-G29-PS4-LoadCell-Arduino). All referenced files will not be hotlinked, so you'll have to at least look at the work they have done. 

The software and electronics will also work for [jstoezel's](https://github.com/jstoezel/brake_pedal_beam_load_cell) mod using a dual beam load cell. I ordered one and will update this repository it arrives.

## Shopping list
* load cell and HX711 module ~~([example](https://usa.banggood.com/4pcs-DIY-50KG-Body-Load-Cell-Weight-Strain-Sensor-Resistance-With-HX711-AD-Module-p-1326815.html))~~ (the HX711 can be switched to 80hz. Make sure to buy a board that makes this possible)
* 3.3V ATmega328P-AU Pro Mini ([example](https://www.banggood.com/3Pcs-3_3V-8MHz-ATmega328P-AU-Pro-Mini-Microcontroller-With-Pins-Development-Board-p-980290.html)) you can use a 5V version, but that would need a separate power supply
* MCP4725 DAC ([example](https://www.banggood.com/3Pcs-CJMCU-MCP4725-I2C-DAC-Development-Board-Module-p-1051690.html))

Updated List:

* HX711 load cell amplifier with 80Hz option (example: [ebay](https://www.ebay.com/itm/2PCS-HX711-Dual-Channel-24-Bit-Precision-A-D-Module-Pressure-For-Arduino-NEW/153891441697?hash=item23d4a50c21:g:uroAAOSweqpejcsC), [archive for reference](https://archive.is/sDvCP))
* 3.3V Arduino Pro Micro (example: [ebay](https://www.ebay.com/itm/Leonardo-Pro-Micro-ATmega32U4-8MHz-3-3V-Replace-ATmega328-Arduino-Pro-Mini/132482990781?hash=item1ed89a02bd:g:SvMAAOSwe0NZvy0b), [archive for reference](https://archive.is/KmKOC))
* Parallel Beam Loadcell (for jstoezel's mod) (example: [ebay](https://www.ebay.com/itm/Parallel-Beam-Load-Cell-Sensor-100kg-217lb-Scale-Weighing-Sensor-0-02-Precision/171164724453?hash=item27da366ce5:g:YPEAAOSwuhhXXVLu), [archive for reference](https://archive.is/HyUL8))
* MCP4725 DAC (example: [banggood](https://www.banggood.com/3Pcs-CJMCU-MCP4725-I2C-DAC-Development-Board-Module-p-1051690.html), [archive for reference](https://archive.is/VqeZv))

I ordered a pack of load cells that didn't include the HX711 module. Just like the other parts I ordered multiple of them. In total I payed around 30€ for enough parts to mod 3 pedals (I like to get more in case I brak stuff, and I'll make a second one for a friend)

## Tools / Small parts
* programmer for the pro mini or an Arduino Uno as ISP
* 3D printer
* soldering iron
* wires
* 2 1k resistors
* crimping tool (optional, I crimped the connections to the load cell)
* PCBs to solder all the parts to (I guess you could just solder them together, but that would be messy)

## 3D Printing

I used the files from [GeekyDeaks'](https://github.com/GeekyDeaks/g29-load-cell) project, without any changes. You can find the files in his stl folder.

I sliced the models using the "0.20mm Normal" profile for my Ender3. There are plenty resources out there showing how you can use a non Prusa machine with the Prusa Slicer. I set the settings mode to "Advanced" to access all the settings I modified.

Here are the print settings I modified for the single_holder.stl :

1. Using the "Place on face" option, I oriented the single_holder.stl so it lays flat on the angled face opposite of the slot where the load cell will go. That way it uses minimal support material.
2. Under "Layers and perimeters" I increased the Perimeters to 4 and the Top and Bottom Solid layers to 6
3. Under "Support material" I increased the XY separation between an object and ist support to 100% because in my experience the supports tend to stick to the object.
4. (optional) Under "Skirt and brimn" I increased the Loops to 2, the Distance from object to 7mm and the Skirt height to 1 layer (I find the Skirt too close for comfort)
   
For the plunger I printed the plunger_bottom.stl, plunger_top.stl and plunger_spacer_15mm.stl to achive a small amount of travel before hitting the rubber damper (about 3mm). To get no travel at all you would need a shorter spacer than the 5mm one, or you need to cut off a small piece of the rubber damper. I believe you can make the brake feel harder by shortening the rubber damper, at least that's what GeekyDeaks did.

Here are the modifications I made on top of the ones mentioned above:

1. I rotated all parts so the indentation is at the bottom.
2. I added supports only to the plunger_bottom.stl by clicking the "Editing" column in the parts overview and selecting "Support material"
   1. In the area below the parts overview I checked "Generate support material", "Auto generated supports" and "Support on build plate only"
   2. Make sure to place the part away from the others so the first layer of the support material does not stick to other parts
3. Under Advanced I had to set the "XY Size Compensation" to -0.1 mm.

After printing I still had to file down the sides of the connectors so they will fit together.

## Wiring

//WIP

I'd recommend you put all the components on a breadboard and upload the sketch for testing, before you solder everything together.

## Software

I used the Arduino IDE to modify [Skidude88's](https://github.com/Skidude88/Skidude88-G29-PS4-LoadCell-Arduino) sketch (Code/SimPedal_ver3_dac-3.3v_board_withFW_Adjust.ino). The source files also include a modified version of the "cmdArduino" Library by Akiba and Jacinta.

1. Install the Arduino IDE
2. Open the code located in src/load_cell_controller (load_cell_controller.ino)
3. The code requires some libraries. Install them by navigating to "Sketch > Include Library > Manage Libraries"
   1. "HX711 Arduinio Library" by Bogdan Necula and Andreas Motl
   2. "MCP4725" by Rob Tillaart
4. Select the correct in the "Tools" menu
   * Board: "Arduino AVR Boards > Arduino Pro or Pro Mini"
   * Processor: "ATmega328P (3.3V, 8MHz)"
   * Port: The COM port of the serial adapter. Check the Device Manager if you are unsure
5. In the darker toolbar click the arrow (Upload) to upload the sketch to the board
6. In the same toolbar, click the icon on the far right to open the serial monitor
   * At the bottom of the window set the line ending to "Newline"
   * After startup the board outputs the current settings. If you missed it, reset the board or type "GET"
  
Thats it. You can now play around with the command line in the serial monitor. 

## The Settings

You can modify the settings in the configuration.h file. All settings can also be changed with the SET command after uploading the sketch to the board.

## The Command Line

The command line is useful for debugging and setting up the pedals. Here is a list of the commands:

* GET \[\<OPTION\>\]
  * Returns the value of the specified setting, or all setttings if no option is supplied.
* SET \<OPTION\> \<VALUE\>
  * Sets the value of the specified setting. If the VALUE can't be parsed the setting is set to 0.
  * Changes are not persistent until you call SAVE.
* LOAD
  * Loads the settings from the persistent memory (EEPROM). If settings were changed with SET, but not saved, the old settings will be restored.
* SAVE
  * Saves the settings, so they stay even after the board is reset.
* RESET
  * Resets all settings to the values specified in configuration.h.
* TARE
  * Tares the load cell. This makes sure it reads 0 when not pressed. Keep you foot off the pedal, or don't touch them at all for a few seconds.
* OUTPUT \<1|0\>
  * 1 turns on the output, 0 turns it off. When enabled, the value read from the load cell followed by the value sent to the DAC is printed 10 times a second. Useful for setting up the deadzones.
* TEST \<0-4095\>
  * Writes the supplied value to the DAC. Useful for setting up output levels.
* HELP
  * Prints a short version of this text.

# Setbacks
* DAC did not output
  * Switched Multimeter ✔
* Pro Mini I2C Pins (4 and 5) do not line up with the PCB
  * Awkwardly wire the connections anyways
  * Use Software I2C
  * Custom PCB
* Setup did not complete (I implemented a log message for that)
  * Make sure the pins on the HX711 and DAC are plugged in correctly

# TODO
* Wiring
* HX711 80hz mode?
* Modifying the CMD Lib to reduce clutter and accept newline as command terminator ✔
* GUI for tuning
* Better pressure curve?
* Custom PCB?
