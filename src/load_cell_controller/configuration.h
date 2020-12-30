//config version. The configuration will only be applied if this version is greater than a previous loaded version.
#define CONFIG_VERSION 0

//The minimum deadzone of the load cell. All values below will be ignored and result in 0% output (below the specified OUTPUT_MIN)
#define DEADZONE_MIN 1000.0

//The maximum deadzone of the load cell. All values equal or above will result in 100% output (even above the specified OUTPUT_MAX)
#define DEADZONE_MAX 200000.0

//The output value supplied to the DAC at minimum and maximum breaking force. The MCP4725 is 12 bit so 0 == 0V and 4095 == 3.3V
#define OUTPUT_MIN 4095
#define OUTPUT_MAX 0

//The G29 pedals have a rubber block that is supposed to emulate a load cell. The firmware adjusts for the minimized travel distance after the block is hit.
//This value marks the applied break pressure after which the firmware acts more sensitive to the change of the output. 0 == DEADZONE_MIN ; 1 == DEADZONE_MAX
#define GRADIENT_POSITION 0.0

//The output value supplied to the DAC at the GRADIENT_POSITION
#define GRADIENT_OUTPUT OUTPUT_MIN

// Visualisation of the settings:
//
//        DAC Value / Voltage
//                  ^
//    4095 / 3.3V ->|                                ########
//                  |                                #       
//     OUTPUT_MAX ->|.............................####       
//                  |                         ####   :       
// OUTPUT_GADIENT ->|.....................####       :       
//                  |                   ##:          :       
//                  |                 ##  :          :       
//                  |               ##    :          :       
//                  |             ##      :          :       
//                  |           ##        :          :       
//                  |         ##          :          :       
//                  |       ##            :          :       
//     OUTPUT_MIN ->|.....##              :          :       
//                  |     #               :          :       
//       0 / 0.0V ->+######---------------------------------> Load Cell Value
//                  ^     ^               ^          ^
//                  0     |               |          |DEADZONE_MAX
//                        |               |
//                        |               |GRADIENT_POSITION
//                        |
//                        |DEADZONE_MIN

// Calculated Values, do not change
#define DEADZONE_RANGE (DEADZONE_MAX - DEADZONE_MIN)
#define GRADIENT_POSITION_ABSOLUTE (DEADZONE_MIN + DEADZONE_RANGE * GRADIENT_POSITION)
