/*
    This file is part of Repetier-Firmware.

    Repetier-Firmware is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Repetier-Firmware.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// BASIC SETTINGS: select your board type, thermistor type, axis scaling, and endstop configuration

//// The following define selects which electronics board you have. Please choose the one that matches your setup
// MEGA/RAMPS up to 1.2  = 3,
// RAMPS 1.3 = 33
// Gen6 = 5, 
// Sanguinololu up to 1.1 = 6
// Sanguinololu 1.2 and above = 62
#define MOTHERBOARD 5 

#include <avr/io.h>
#include "pins.h"

// ##########################################################################################
// ##                               Calibration                                            ##
// ##########################################################################################


/** \brief Number of steps for a 1mm move in x direction */
#define XAXIS_STEPS_PER_MM 40
/** \brief Number of steps for a 1mm move in y direction */
#define YAXIS_STEPS_PER_MM 40
/** \brief Number of steps for a 1mm move in z direction */
#define ZAXIS_STEPS_PER_MM 3360

// ##########################################################################################
// ##                           Extruder configuration                                     ##
// ##########################################################################################

/** Number of extruders. Maximum 2 extruder. */
#define NUM_EXTRUDER 1

#define EXT0_X_OFFSET 0
#define EXT0_Y_OFFSET 0
// for skeinforge 40 and later, steps to pull the plasic 1 mm inside the extruder, not out
#define EXT0_STEPS_PER_MM 373
// What type of sensor is used?
// 1 is 100k thermistor
// 2 is 200k thermistor
// 3 is mendel-parts thermistor
// 4 is 10k thermistor
// 5 is userdefined thermistor table
// 99 Generic thermistor table
// 100 is AD595
// 101 is MAX6675
#define EXT0_TEMPSENSOR_TYPE 5
// Position in analog input table below for reading temperatures or pin enabling SS for MAX6675
#define EXT0_TEMPSENSOR_PIN 0
// WHich pin enables the heater
#define EXT0_HEATER_PIN HEATER_0_PIN
#define EXT0_STEP_PIN E_STEP_PIN
#define EXT0_DIR_PIN E_DIR_PIN
// set to 0/1 for normal / inverse direction
#define EXT0_INVERSE 0
#define EXT0_ENABLE_PIN E_ENABLE_PIN
// For Inverting Stepper Enable Pins (Active Low) use 0, Non Inverting (Active High) use 1
#define EXT0_ENABLE_ON 0
// The following speed settings are for skeinforge 40+ where e is the
// length of filament pulled inside the heater. For repsnap or older
// skeinforge use hiher values.
#define EXT0_MAX_FEEDRATE 1200
// Feedrate from halted extruder in mm/s
#define EXT0_MAX_START_FEEDRATE 10
// Acceleration in mm/s^2
#define EXT0_MAX_ACCELERATION 10000
/** Type of heat manager for this extruder. 
- 0 = Simply switch on/off if temperature is reached. Works always.
- 1 = PID Temperature control. Is better, but needs an output with PWM, which doesn't
      use Timer 0 and 1
*/
#define EXT0_HEAT_MANAGER 1
/** Wait x seconds, after reaching target temperature. Only used for M109 */
#define EXT0_WATCHPERIOD 40

/** The maximum value, I-gain can contribute to the output. */
#define EXT0_PID_INTEGRAL_DRIVE_MAX 130
/** P-gain in 0,01 units */
#define EXT0_PID_PGAIN   300
/** I-gain in 0,01 units */
#define EXT0_PID_IGAIN   2
/** Dgain in 0,01 units. */
#define EXT0_PID_DGAIN 2000
// maximum time the heater is can be switched on. Max = 255
#define EXT0_PID_MAX 200
/** \brief Faktor for the advance algorithm. 0 disables the algorithm. */
#define EXT0_ADVANCE_K 0.0f
/** Number of entries in the user thermistortable */
#define NUM_TEMPS_USERTHERMISTOR 28
/** Userdefined thermistor table

There are many different thermistors, which can be combined with different resistors. This result
in unpredictable number of tables. As a resolution, the user can define one table here, that can
be used as type 5 for thermister type in extruder/heated bed definition. Make sure, the number of entries
matches the value in NUM_TEMPS_USERTHERMISTOR. If you span definition over multiple lines, make sure to end
each line, except the last, with a backslash. The table format is {{adc1,temp1},{adc2,temp2}...} with
increasing adc values. For more informations, read 
http://hydraraptor.blogspot.com/2007/10/measuring-temperature-easy-way.html

*/
#define USER_THERMISTORTABLE  {\
  {1,864},{21,300},{25,290},{29,280},{33,270},{39,260},{46,250},{54,240},{64,230},{75,220},\
  {90,210},{107,200},{128,190},{154,180},{184,170},{221,160},{265,150},{316,140},{375,130},\
  {441,120},{513,110},{588,100},{734,80},{856,60},{938,40},{986,20},{1008,0},{1018,-20}	}
  
/** If defined, creates a thermistortable at startup.

If you dont feel like computing the table on your own, you can use this generic method. It is
a simple approximation which may be not as accurate as a good table computed from the reference
values in the datasheet. You can increase precision if you use a temperature/resistance for
R0/T0, which is near your operating temperature. This will reduce precision for lower temperatures,
which are not realy important. The resistors must fit the following schematic:
@code
VREF ---- R2 ---+--- Termistor ---+-- GND
                |                 |
                +------ R1 -------+
                |                 |
                +---- Capacitor --+
                |
                V measured
@endcode                
                
If you don't have R1, set it to 0.
The capacitor is for reducing noise from long thermistor cable. If you don't have have one, it's OK.

If you don't need the generic table, uncomment the following define.
*/
//#define USE_GENERIC_THERMISTORTABLE 1
/** Reference resistance */
#define GENERIC_THERM_R0 1042.7
/** Temperature at reference resistance */
#define GENERIC_THERM_T0 170
/** Beta value of thermistor

You can use the beta from the datasheet or compute it yourself. See
http://reprap.org/wiki/MeasuringThermistorBeta
for more details.
*/
#define GENERIC_THERM_BETA 4036
#define GENERIC_THERM_R1 0
#define GENERIC_THERM_R2 4700
#define GENERIC_THERM_VREF 5
/** Supply voltage to ADC, can be changed be setting ANALOG_REF below to different value. */
#define GENERIC_THERM_VADC 5
/** Number of entries in generated table. One entry takes 4 bytes. Higher number of entries increase computation time too. */
#define GENERIC_THERM_NUM_ENTRIES 40

// uncomment the following line for MAX6675 support.
//#define SUPPORT_MAX6675
// Select type of your heated bed. It's the same as for EXT0_TEMPSENSOR_TYPE
// set to 0 if you don't have a heated bed
#define HEATED_BED_SENSOR_TYPE 0
// Pin to enable heater for bed
#define HEATED_BED_SENSOR_PIN -1
// Pin to read temperature of heated bed
#define HEATED_BED_HEATER_PIN -1

// uncomment to use AREF for reference voltage
// on a GEN6 you want AVCC
#define USE_AVCC_FOR_TEMP
// how many samples do we want per reading. 1 sample takes 1/125000 seconds.
// more samples get more reliable values, but take more time.
#define ANALOG_SUPERSAMPLE 10
#define NUM_ANALOG_SENSORS 1
#define NUM_DIGITAL_SENSORS 0
#define TEMP_PID true

//// Experimental watchdog and minimal temp
// The watchdog waits for the watchperiod in milliseconds whenever an M104 or M109 increases the target temperature
// If the temperature has not increased at the end of that period, the target temperature is set to zero. It can be reset with another M104/M109
//#define WATCHPERIOD 5000 //5 seconds

//// The minimal temperature defines the temperature below which the heater will not be enabled
#define MINTEMP 5

//// Experimental max temp
// When temperature exceeds max temp, your heater will be switched off.
// This feature exists to protect your hotend from overheating accidentally, but *NOT* from thermistor short/failure!
// You should use MINTEMP for thermistor short/failure protection.
#define MAXTEMP 275

/** \brief number of analog input signals. Normally 1 for each temperature sensor */
#define ANALOG_INPUTS NUM_ANALOG_SENSORS
#if ANALOG_INPUTS>0
// Channels are the MUX-part of ADMUX register
#define ANALOG_INPUT_CHANNELS {TEMP_0_PIN}
// Bits of the ADC converter
#define ANALOG_INPUT_BITS 10
// Build median from 2^ANALOG_INPUT_SAMPLE samples
#define ANALOG_INPUT_SAMPLE 2
#define ANALOG_REF_AREF 0
#define ANALOG_REF_AVCC _BV(REFS0)
#define ANALOG_REF_INT_1_1 _BV(REFS1)
#define ANALOG_REF_INT_2_56 _BV(REFS0) | _BV(REFS1)
/** \brief Used reference, normally ANALOG_REF_AVCC or ANALOG_REF_AREF */
#define ANALOG_REF ANALOG_REF_AVCC
#define ANALOG_PRESCALER _BV(ADPS0)|_BV(ADPS1)|_BV(ADPS2)


#endif
// ##########################################################################################
// ##                            Endstop configuration                                     ##
// ##########################################################################################

//// Endstop Settings
#define ENDSTOPPULLUPS 0 // Comment this out (using // at the start of the line) to disable the endstop pullup resistors
// The pullups are needed if you directly connect a mechanical endswitch between the signal and ground pins.
//set to true to invert the logic of the endstops
#define ENDSTOPS_INVERTING false
//If your axes are only moving in one direction, make sure the endstops are connected properly.
//If your axes move in one direction ONLY when the endstops are triggered, set ENDSTOPS_INVERTING to true here



//// ADVANCED SETTINGS - to tweak parameters

// For Inverting Stepper Enable Pins (Active Low) use 0, Non Inverting (Active High) use 1
#define X_ENABLE_ON 0
#define Y_ENABLE_ON 0
#define Z_ENABLE_ON 0
#define E_ENABLE_ON 0

// Disables axis when it's not being used.
#define DISABLE_X false
#define DISABLE_Y false
#define DISABLE_Z true
#define DISABLE_E false

// Inverting axis direction
#define INVERT_X_DIR false
#define INVERT_Y_DIR true
#define INVERT_Z_DIR false
#define INVERT_E_DIR false

//// ENDSTOP SETTINGS:
// Sets direction of endstops when homing; 1=MAX, -1=MIN
#define X_HOME_DIR -1
#define Y_HOME_DIR -1
#define Z_HOME_DIR -1

 //If true, axis won't move to coordinates less than zero.
#define min_software_endstops false
//If true, axis won't move to coordinates greater than the defined lengths below.
#define max_software_endstops true
// maximum positions - only fixed numbers!
#define X_MAX_LENGTH 200
#define Y_MAX_LENGTH 200
#define Z_MAX_LENGTH 100

// ##########################################################################################
// ##                           Mevement settings                                         ##
// ##########################################################################################

/** After x seconds of inactivity, the stepper motors are disabled.
    Set to 0 to leave them enabled.
    This helps cooling the Stepper motors between two print jobs. 
*/
#define STEPPER_INACTIVE_TIME 120L
/** After x seconds of inactivity, the system will go down as far it can.
    It will at least disable all stepper motors and heaters. If the board has
    a power pin, it will be disabled, too. 
    Set value to 0 for disabled.   
*/
#define MAX_INACTIVE_TIME 0L
/** Maximum feedrate, the system allows. Higher feedrates are reduced to these values.
    The axis order in all axis related arrays is X, Y, Z, E */
#define MAX_FEEDRATE {12000, 12000, 3, 20}
/** Speed in mm/min for finding the home position */
#define HOMING_FEEDRATE {1500,1500,100}

/** Comment this to disable ramp acceleration */
#define RAMP_ACCELERATION 1

//// Acceleration settings

/** \brief Use RAMP acceleration for faster printing speed. */
#ifdef RAMP_ACCELERATION
/** \brief X, Y, Z and E max acceleration in mm/s^2 for printing moves or retracts */
#define MAX_ACCELERATION_UNITS_PER_SQ_SECOND {1000,1000,50,1000} 
/** \brief X, Y, Z max acceleration in mm/s^2 for travel moves. */
#define MAX_TRAVEL_ACCELERATION_UNITS_PER_SQ_SECOND {1000,1000,50,1000}
#endif

/** \brief Maximum allowable jerk.

Caution: This is no real jerk in a physical meaning.

The jerk determines your start speed and the maximum speed at the join of two segments.
It's unit is mm/s. If the printer is standing still, the start speed is jerk/2. At the
join of two segments, the speed difference is limited to the jerk value.

Examples:
For all examples jerk is assumed as 40.

Segment 1: vx = 50, vy = 0
Segment 2: vx = 0, vy = 50
v_diff = sqrt((50-0)^2+(0-50)^2) = 70.71
v_diff > jerk => vx_1 = vy_2 = jerk/v_diff*vx_1 = 40/70.71*50 = 28.3 mm/s at the join

Segment 1: vx = 50, vy = 0
Segment 2: vx = 35.36, vy = 35.36
v_diff = sqrt((50-35.36)^2+(0-35.36)^2) = 38.27 < jerk
Corner can be printed with full speed of 50 mm/s

*/
#define MAX_JERK 40.0

/** \brief Enable advance algorithm.

Without a correct adjusted advance algorithm, you get blobs at points, where acceleration changes. The
effect increases with speed and acceleration difference. Using the advance method decreases this effect.
For more informations, read the wiki.
*/
#define USE_ADVANCE

/** The firmware supports trajectory smoothing. To acieve this, it divides the stepsize by 2, resulting in
the double computation cost. For slow movements this is not an issue, but for really fast moves this is 
too much. The value specified here is the number of clock cycles between a step on the driving axis.
If the interval at full speed is below this value, smoothing is disabled for that line.*/
#define MAX_HALFSTEP_INTERVAL 2002

// ##########################################################################################
// ##                           Communication configuration                                ##
// ##########################################################################################

//// AD595 THERMOCOUPLE SUPPORT UNTESTED... USE WITH CAUTION!!!!

/** \brief Communication speed.

- 250000 : Fastes with errorrate of 0% with 16 or 32 MHz - update wiring_serial.c in your board files. See boards/readme.txt
- 115200 : Fast, but may produce communication errors on quite regular basis, Error rate -3,5%
- 76800 : Best setting for Arduino with 16 MHz, Error rate 0,2% page 198 AVR1284 Manual. Result: Faster communication then 115200
- 57600 : Should produce nearly no errors, on my gen 6 it's faster than 115200 because there are no errors slowing down the connection
- 38600
*/
#define BAUDRATE 76800
//#define BAUDRATE 57600
//#define BAUDRATE 250000
/** \brief Size in byte of the output buffer */
#define OUTPUT_BUFFER_SIZE 64
/** \brief Activates buffered output.

The Arduino libraries have a buffered input for serial connections. Write operations are
always unbuffered, which means the controller will wait with execution, until the data
is send. To solve this handicap, all write operations have to use out insted of Serial.
If you uncomment this, you still have to use out, but it will use no buffers, so you
keep with your slow communication version.
*/
#define USE_BUFFERED_OUTPUT 
/** \brief Number of moves we can cache in advance.

This number of moves can be cached in advance. If you wan't to cache more, increase this. Especially on
many very short moves the cache may go empty.
*/
#define MOVE_CACHE_SIZE 16
/** \brief Cache size for incoming commands.

There should be no reason to increase this cache. Commands are nearly immediately send to
execution.
*/
#define GCODE_BUFFER_SIZE 2
/** Appends the linenumber after ever ok send, to acknowledge the received command. Uncomment for plain ok ACK if your host has problems with this */
#define ACK_WITH_LINENUMBER
/** Communication errors can swollow part of the ok, which tells the host software to send
the next command. Not receiving it will cause your printer to stop. Sending this string every
second, if our queue is empty should prevent this. Uncomment if you don't wan't this feature. */
#define WAITING_IDENTIFIER "wait"

/** \brief Sets time for echo debug

You can set M111 1 which enables ECHO of commands send. This define specifies the position,
when it will be executed. In the original FiveD software, echo is done after receiving the
command. With checksum you know, how it looks from the sending string. With this define
uncommented, you will see the last command executed. To be more specific: It is written after
execution. This helps tracking errors, because there may be 8 or more commands in the queue
and it is elsewise difficult to know, what your reprap is currently doing.
*/
#define ECHO_ON_EXECUTE

/** \brief EEPROM storage mode 

Set the EEPROM_MODE to 0 if you always wan't to use the settings in this configuration file. If not,
set it to a value not stored in the first EEPROM-byte used. If you later want to overwrite your current
eeprom settings with configuration defaults, just select an other value. On the first call to epr_init()
it will detect a mismatch of the first byte and copys default values into EEPROM. If the first byte
matches, the stored values are used to overwrite the settings.
*/
#define EEPROM_MODE 1
/** Comment out (using // at the start of the line) to disable SD support: */
//#define SDSUPPORT 1

// ##########################################################################################
// ##                                  Debug configuration                                 ##
// ##########################################################################################

/** Uncomment, to see detailed data for every move. Only for debugging purposes! */
//#define DEBUG_QUEUE_MOVE
/** Allows M111 to set bit 5 (16) which disables all commands except M111. This can be used
to test your data througput or search for communication problems. */
#define INCLUDE_DEBUG_COMMUNICATION
/** Allows M111 so set bit 6 (32) which disables moves, at the first tried step. In combination
with a dry run, you can test the speed of path computations, which are still performed. */
//#define INCLUDE_DEBUG_NO_MOVE
/** Writes the free RAM to output, if it is less then at the last test. Should always return
values >500 for safety, since it doesn't catch every function call. Nice to tweak cache
usage or for seraching for memory induced errors. */
//#define DEBUG_FREE_MEMORY
#define DEBUG_ADVANCE
/** If enabled, writes the created generic table to serial port at startup. */
//#define DEBUG_GENERIC
// Uncomment the following line to enable debugging. You can better control debugging below the following line
//#define DEBUG
// ####################################################################################
// #                         Below this line only for experts                         #
// ####################################################################################


// ####################################################################################
// #          No configuration below this line - just some errorchecking              #
// ####################################################################################
#ifdef SUPPORT_MAX6675
#if !defined SCK_PIN || !defined MOSI_PIN || !defined MISO_PIN
#error For MAX6675 support, you need to define SCK_PIN, MISO_PIN and MOSI_PIN in pins.h
#endif
#endif
#if X_STEP_PIN<0 || Y_STEP_PIN<0 || Z_STEP_PIN<0
#error One of the following pins is not assigned: X_STEP_PIN,Y_STEP_PIN,Z_STEP_PIN
#endif
#if EXT0_STEP_PIN<0
#error EXT0_STEP_PIN not set to a pin number.
#endif
#if EXT0_DIR_PIN<0
#error EXT0_DIR_PIN not set to a pin number.
#endif
#endif
