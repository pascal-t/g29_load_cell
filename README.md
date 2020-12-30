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

## 3D Printing

I used the single_holder.stl, plunger_bottom.stl, plunger_top.stl and plunger_spacer_10mm.stl ?? from [GeekyDeaks'](https://github.com/GeekyDeaks/g29-load-cell) project, without any changes. You can find the files in his stl folder.

I sliced the models using the "0.20mm Normal" profile for my Ender3. There are plenty resources out there showing how you can use a non Prusa machine with the Prusa Slicer. Here are the modifications I made.

1. Using the "Place on face" option, I oriented the single_holder.stl so it lays flat on the angled face opposite of the slot where the load cell will go. That way it uses minimal support material.
2. Print Settings (with at least Advanced settings enabled in the top right)
   1. Under "Layers and perimeters" I increased the Perimeters to 4 and the Top and Bottom Solid layers to 6
   2. Under "Support material" I increased the XY separation between an object and ist support to 100% because in my experience the supports tend to stick to the object.
   3. (optional) Under "Skirt and brimn" I increased the Loops to 2, the Distance from object to 7mm and the Skirt height to 1 layer (I find the Skirt too close for comfort)

## Wiring

//WIP

I'd recommend you put all the components on a breadboard and upload the sketch for testing, before you solder everything together.

## Software

I used the Arduino IDE to modify [Skidude88's](https://github.com/Skidude88/Skidude88-G29-PS4-LoadCell-Arduino) sketch (Code/SimPedal_ver3_dac-3.3v_board_withFW_Adjust.ino). 

1. Install the Arduino IDE
2. Open the code located in src/load_cell_controller (load_cell_controller.ino)
3. The code requires some libraries. Install them by navigating to "Sketch > Include Library > Manage Libraries"
   1. "HX711 Arduinio Library" by Bogdan Necula and Andreas Motl
   2. "MCP4725" by Rob Tillaart
   3. "cmdArduino" by Akiba and Jacinta
4. Select the correct in the "Tools" menu
   * Board: "Arduino AVR Boards > Arduino Pro or Pro Mini"
   * Processor: "ATmega328P (3.3V, 8MHz)"
   * Port: The COM port of the serial adapter. Check the Device Manager if you are unsure
5. In the darker toolbar click the arrow (Upload) to upload the sketch to the board
6. In the same toolbar, click the icon on the far right to open the serial monitor
   * At the bottom of the window set the line ending to "Carriage return" (TODO accept Newline)
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

# TODO
* Wiring
* HX711 80hz mode?
* Modifying the CMD Lib to reduce clutter and accept newline as command terminator
* GUI for tuning
* Better pressure curve?
* Custom PCB?
