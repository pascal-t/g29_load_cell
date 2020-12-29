// HX711 circuit wiring
#define LOADCELL_DOUT_PIN 11
#define LOADCELL_SCK_PIN  10

//This is the I2C Address of the MCP4725, by default (A0 pulled to GND).
//Please note that this breakout is for the MCP4725A0.
//For devices with A0 pulled HIGH, use 0x61
//MCP4725 is 12bit inout and output at default 100Kbps (also available 400Kbps mode)
#define MCP4725_ADDR 0x60   
