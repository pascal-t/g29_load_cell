#include <MCP4725.h>
#include <HX711.h>
#include <Wire.h>
#include <cmdArduino.h>
#include "connections.h"
#include "configuration.h"

// Code for 3.3v Micro Pro Board with 1x load cell, 1x HX711 module and 1x MCP4725 DAC

HX711 brake_pedal; 
MCP4725 DAC(MCP4725_ADDR);

void setup() {
  brake_pedal.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  brake_pedal.tare(10);
  DAC.begin();
  DAC.writeDAC(OUTPUT_MIN);
  
  Serial.begin(9600);
  //TWBR = 12;                        // Seems OK at 100kbps, otherwise MCP4725 can run at 400KHz using TWBR=12
}

void loop() {
  double brake_value = brake_pedal.get_value(1);
  #ifdef DEBUG
    Serial.print("Brake value: ");
    Serial.println(brake_value, DEC);
  #endif
  uint16_t dac_value = convertToDacValue(brake_value);
  #ifdef DEBUG
    Serial.print("DAC value: ");
    Serial.println(dac_value, DEC);
  #endif
  DAC.writeDAC(dac_value);
  #ifdef DEBUG
    Serial.println("---------------------------------------------");
    delay(1000);
  #endif
}

uint16_t convertToDacValue(double loadCellValue) {
  if (loadCellValue < DEADZONE_MIN) {
    #ifdef DEBUG
      Serial.print("Value below DEADZONE_MIN: ");
      Serial.println(DEADZONE_MIN, DEC);
    #endif
    return OUTPUT_MIN;
  } else if (loadCellValue > DEADZONE_MAX) {
    #ifdef DEBUG
      Serial.print("Value above DEADZONE_MAX: ");
      Serial.println(DEADZONE_MAX, DEC);
    #endif
    return OUTPUT_MAX;
  }

  if (loadCellValue < GRADIENT_POSITION_ABSOLUTE) {
    #ifdef DEBUG
      Serial.print("Value below GRADIENT_POSITION_ABSOLUTE: ");
      Serial.println(GRADIENT_POSITION_ABSOLUTE, DEC);
    #endif
    return map(loadCellValue, DEADZONE_MIN, GRADIENT_POSITION_ABSOLUTE, OUTPUT_MIN, GRADIENT_OUTPUT);
  } else {
    #ifdef DEBUG
      Serial.print("Value above GRADIENT_POSITION_ABSOLUTE: ");
      Serial.println(GRADIENT_POSITION_ABSOLUTE, DEC);
    #endif
    return map(loadCellValue, GRADIENT_POSITION_ABSOLUTE, DEADZONE_MAX, GRADIENT_OUTPUT, OUTPUT_MAX);
  }
}
