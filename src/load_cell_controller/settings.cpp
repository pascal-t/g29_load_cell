#include <Arduino.h>
#include <EEPROM.h>
#include "settings.h"
#include "configuration.h"

Settings::Settings() {}

//Read and write to EEPROM from https://esp8266-server.de/EEPROM.html
int Settings::saveToEeprom(int pos, byte *value, int length) {
  for (int i = 0; i < length; i++) {
    EEPROM.write(pos + i, *value);
    value++;
  }
  return pos + length;
}

int Settings::getFromEeprom(int pos, byte *value, int length) {
  for (int i = 0; i < length; i++) {
    *value = EEPROM.read(pos + i);
    value++;
  }
  return pos + length;
}

void Settings::load(int arg_cnt = 0, char **args = NULL) {
  int pos = CONFIG_START;
  pos = getFromEeprom(pos, (byte*)&config_version, sizeof(config_version));
  pos = getFromEeprom(pos, (byte*)&deadzone_min, sizeof(deadzone_min));
  pos = getFromEeprom(pos, (byte*)&deadzone_max, sizeof(deadzone_max));
  deadzone_range = deadzone_max - deadzone_min;
  pos = getFromEeprom(pos, (byte*)&output_min, sizeof(output_min));
  pos = getFromEeprom(pos, (byte*)&output_max, sizeof(output_max));
  pos = getFromEeprom(pos, (byte*)&gradient_position, sizeof(gradient_position));
  gradient_position_absolute = deadzone_min + deadzone_range * gradient_position;
  pos = getFromEeprom(pos, (byte*)&gradient_output, sizeof(gradient_output));

  if (config_version < CONFIG_VERSION || (CONFIG_VERSION == 0 && CONFIG_VERSION != config_version)) {
    Serial.println("configuration.h version is newer than EEPROM. Applying changes.");
    reset();
    save();
  }
  
  printAll();
}

void Settings::save(int arg_cnt = 0, char **args = NULL) {
  int pos = CONFIG_START;
  pos = saveToEeprom(pos, (byte*)&config_version, sizeof(config_version));
  pos = saveToEeprom(pos, (byte*)&deadzone_min, sizeof(deadzone_min));
  pos = saveToEeprom(pos, (byte*)&deadzone_max, sizeof(deadzone_max));
  pos = saveToEeprom(pos, (byte*)&output_min, sizeof(output_min));
  pos = saveToEeprom(pos, (byte*)&output_max, sizeof(output_max));
  pos = saveToEeprom(pos, (byte*)&gradient_position, sizeof(gradient_position));
  pos = saveToEeprom(pos, (byte*)&gradient_output, sizeof(gradient_output));
}

void Settings::reset(int arg_cnt = 0, char **args = NULL) {
  config_version = CONFIG_VERSION;
  deadzone_min = DEADZONE_MIN;
  deadzone_max = DEADZONE_MAX;
  deadzone_range = deadzone_max - deadzone_min;
  output_min = OUTPUT_MIN;
  output_max = OUTPUT_MAX;
  gradient_position = GRADIENT_POSITION;
  gradient_position_absolute = deadzone_min + deadzone_range * gradient_position;
  gradient_output = GRADIENT_OUTPUT;
}

void Settings::printOptionsHelp() {
  Serial.print(OPTIONS_HELP);
}

void Settings::printGetHelp() {
  Serial.println(COMMAND_GET_HELP);
  printOptionsHelp();
  Serial.println();
}

void Settings::printSetHelp() {
  Serial.println(COMMAND_SET_HELP);
  printOptionsHelp();
  Serial.println();
}

void Settings::print(int arg_cnt, char **args) {
  if (arg_cnt < 2) {
    printAll();
    return;
  }

  if (strcmp(args[1], CONFIG_VERSION_STR) == 0) {
    Serial.println(config_version, DEC);
  } else if (strcmp(args[1], DEADZONE_MIN_STR) == 0) {
    Serial.println(deadzone_min, DECIMAL_PLACES);
  } else if (strcmp(args[1], DEADZONE_MAX_STR) == 0) {
    Serial.println(deadzone_max, DECIMAL_PLACES);
  } else if (strcmp(args[1], OUTPUT_MIN_STR) == 0) {
    Serial.println(output_min, DEC);
  } else if (strcmp(args[1], OUTPUT_MAX_STR) == 0) {
    Serial.println(output_max, DEC);
  } else if (strcmp(args[1], GRADIENT_POSITION_STR) == 0) {
    Serial.println(gradient_position, DECIMAL_PLACES);
  } else if (strcmp(args[1], GRADIENT_OUTPUT_STR) == 0) {
    Serial.println(gradient_output, DEC);
  } else {
    printGetHelp();
    return;
  }
}

void Settings::printAll() {
  Serial.print(CONFIG_VERSION_STR);
  Serial.print(" ");
  Serial.println(config_version, DEC);

  Serial.print(DEADZONE_MIN_STR);
  Serial.print(" ");
  Serial.println(deadzone_min, DECIMAL_PLACES);
  
  Serial.print(DEADZONE_MAX_STR);
  Serial.print(" ");
  Serial.println(deadzone_max, DECIMAL_PLACES);
  
  Serial.print(OUTPUT_MIN_STR);
  Serial.print(" ");
  Serial.println(output_min, DEC);
  
  Serial.print(OUTPUT_MAX_STR);
  Serial.print(" ");
  Serial.println(output_max, DEC);
  
  Serial.print(GRADIENT_POSITION_STR);
  Serial.print(" ");
  Serial.println(gradient_position, DECIMAL_PLACES);
  
  Serial.print(GRADIENT_OUTPUT_STR);
  Serial.print(" ");
  Serial.println(gradient_output, DEC);
}

void Settings::set(int arg_cnt, char **args) {
  if (arg_cnt < 3) {
    printSetHelp();
    return;
  }

  if (strcmp(args[1], DEADZONE_MIN_STR) == 0) {
    deadzone_min = atof(args[2]);
  } else if (strcmp(args[1], DEADZONE_MAX_STR) == 0) {
    deadzone_max = atof(args[2]);
  } else if (strcmp(args[1], OUTPUT_MIN_STR) == 0) {
    output_min = atoi(args[2]);
  } else if (strcmp(args[1], OUTPUT_MAX_STR) == 0) {
    output_max = atoi(args[2]);
  } else if (strcmp(args[1], GRADIENT_POSITION_STR) == 0) {
    gradient_position = atof(args[2]);
  } else if (strcmp(args[1], GRADIENT_OUTPUT_STR) == 0) {
    gradient_output = atoi(args[2]);
  } else {
    printSetHelp();
    return;
  }

  print(arg_cnt, args);
}
