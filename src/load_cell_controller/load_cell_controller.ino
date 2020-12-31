#include <MCP4725.h>
#include <HX711.h>
#include <Wire.h>
#include "cmdArduino.h"
#include "connections.h"
#include "settings.h"

#define COMMAND_TARE "TARE"
#define COMMAND_OUTPUT "OUTPUT"
#define COMMAND_OUTPUT_HELP "Usage: 'OUTPUT <1|0>'"
#define COMMAND_TEST "TEST"
#define COMMAND_TEST_HELP "Usage: 'TEST <0-4095>'"
#define COMMAND_HELP "HELP"
#define TAB "   "

#define OUTPUT_DELAY 100
boolean outputEnabled = false;
long lastOutput = 0;

boolean lockDac = false;

// Code for 3.3v Micro Pro Board with 1x load cell, 1x HX711 module and 1x MCP4725 DAC

HX711 brake_pedal; 
MCP4725 DAC(MCP4725_ADDR);
Settings settings;

void setup() {
  cmd.begin(9600);
  settings.load();
  
  brake_pedal.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  brake_pedal.tare(10);
  Serial.println("Loadcell initialized");
  
  DAC.begin();
  DAC.writeDAC(settings.output_min);
  Serial.println("DAC initialized");
  
  cmd.add(COMMAND_GET, get);
  cmd.add(COMMAND_SET, set);
  cmd.add(COMMAND_LOAD, load);
  cmd.add(COMMAND_SAVE, save);
  cmd.add(COMMAND_RESET, reset);
  cmd.add(COMMAND_TARE, tare);
  cmd.add(COMMAND_OUTPUT, output);
  cmd.add(COMMAND_TEST, test);
  cmd.add(COMMAND_HELP, help);
  //TWBR = 12;                        // Seems OK at 100kbps, otherwise MCP4725 can run at 400KHz using TWBR=12

  Serial.println("Setup complete");
}

void loop() {
  cmd.poll();
  double brake_value = brake_pedal.get_value(1);
  uint16_t dac_value = convertToDacValue(brake_value);
  
  if (outputEnabled && lastOutput + OUTPUT_DELAY < millis()) {
    lastOutput = millis();
    Serial.print(brake_value);
    Serial.print(" ");
    Serial.println(dac_value);
  }
  
  if (!lockDac) {
    DAC.writeDAC(dac_value);
  }
}

uint16_t convertToDacValue(double loadCellValue) {
  if (loadCellValue < settings.deadzone_min) {
    return settings.output_min;
  } 

  if (lockDac) {
    Serial.println("lockDac = true");
    lockDac = false;
  }
  
  if (loadCellValue > settings.deadzone_max) {
    return settings.output_max;
  }

  if (loadCellValue < settings.gradient_position_absolute) {
    return (uint16_t)mapDouble(loadCellValue, settings.deadzone_min, settings.gradient_position_absolute, settings.output_min, settings.gradient_output);
  } else {
    return (uint16_t)mapDouble(loadCellValue, settings.gradient_position_absolute, settings.deadzone_max, settings.gradient_output, settings.output_max);
  }
}

//https://www.arduino.cc/reference/en/language/functions/math/map/ but for doubles
double mapDouble(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void get(int arg_count, char **args) {
  settings.print(arg_count, args);
}

void set(int arg_count, char **args) {
  settings.set(arg_count, args);
}

void load(int arg_count, char **args) {
  settings.load(arg_count, args);
}

void save(int arg_count, char **args) {
  settings.save(arg_count, args);
}

void reset(int arg_count, char **args) {
  settings.reset(arg_count, args);
}

void tare(int arg_count, char **args) {
  brake_pedal.tare(10);
}

void output(int arg_count, char **args) {
  if (arg_count < 2) {
    printOutputHelp();
    return;
  }

  if (strcmp(args[1], "1") == 0) {
    outputEnabled = true;
  } else if (strcmp(args[1], "0") == 0) {
    outputEnabled = false;
  } else {
    printOutputHelp();
  }
}

void printOutputHelp() {
  Serial.println(COMMAND_OUTPUT_HELP);
}

void test(int arg_count, char **args) {
  if (arg_count < 2) {
    printTestHelp();
    return;
  }

  int value = atoi(args[1]);
  if (0 <= value && value <= 4095) {
    lockDac = true;
    Serial.println("lockDac = true");
    DAC.writeDAC(value);
  } else {
    printTestHelp();
  }
}

void printTestHelp() {
  Serial.println(COMMAND_TEST_HELP);
}

void help(int arg_count, char **args) {
  Serial.println(COMMAND_GET);
  Serial.print(TAB);
  Serial.println(COMMAND_GET_HELP);
  Serial.println(COMMAND_SET);
  Serial.print(TAB);
  Serial.println(COMMAND_SET_HELP);
  Serial.println(COMMAND_LOAD);
  Serial.println(COMMAND_SAVE);
  Serial.println(COMMAND_RESET);
  Serial.println(COMMAND_TARE);
  Serial.println(COMMAND_OUTPUT);
  Serial.print(TAB);
  Serial.println(COMMAND_OUTPUT_HELP);
  Serial.println(COMMAND_TEST);
  Serial.print(TAB);
  Serial.println(COMMAND_TEST_HELP);
  Serial.println(COMMAND_HELP);
}
