#include <Arduino.h>

#ifndef SETTINGS_H
#define SETTINGS_H

#define CONFIG_START 32

#define COMMAND_GET "GET"
#define COMMAND_GET_HELP "Usage: 'GET [<OPTION>]'. "
#define COMMAND_SET "SET"
#define COMMAND_SET_HELP "Usage: 'SET <OPTION> <VALUE>'. "
#define OPTIONS_HELP "Use 'GET' for a list of options and their current values."
#define COMMAND_LOAD "LOAD"
#define COMMAND_SAVE "SAVE"
#define COMMAND_RESET "RESET"

#define CONFIG_VERSION_STR "CONFIG_VERSION"
#define DEADZONE_MIN_STR "DEADZONE_MIN"
#define DEADZONE_MAX_STR "DEADZONE_MAX"
#define OUTPUT_MIN_STR "OUTPUT_MIN"
#define OUTPUT_MAX_STR "OUTPUT_MAX"
#define GRADIENT_POSITION_STR "GRADIENT_POSITION"
#define GRADIENT_OUTPUT_STR "GRADIENT_OUTPUT"

#define DECIMAL_PLACES 3

class Settings {
    public:
        Settings();
        //Settings variables
        uint16_t config_version;
        double deadzone_min;
        double deadzone_max;
        uint16_t output_min;
        uint16_t output_max;
        double gradient_position;
        uint16_t gradient_output;
        //Calculated variables
        double deadzone_range;
        double gradient_position_absolute;
        //methods
        void load(int arg_cnt = 0, char **args = NULL);
        void save(int arg_cnt = 0, char **args = NULL);
        void reset(int arg_cnt = 0, char **args = NULL);
        void set(int arg_cnt, char **args);
        void print(int arg_cnt, char **args);
        void printAll();
    private:
        void printOptionsHelp();
        void printSetHelp();
        void printGetHelp();
        void setCalculatedValues();
        int saveToEeprom(int pos, byte *value, int length);
        int getFromEeprom(int pos, byte *value, int length);
};

#endif //SETTINGS_H
