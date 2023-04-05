#ifndef CONFIG_H
#define CONFIG_H

#define HOMESTATE 0
#define FORWARDSEARCH 1
#define AVOIDFRONTLEFTLINE 2
#define AVOIDFRONTRIGHTLINE 3
#define AVOIDREARRIGHTLINE 4
#define AVOIDREARLEFTLINE 5
#define GOTOBALL 6
#define SEARCHING 8
#define COLLECTINGBALL 9
#define RETURNHOME 10
#define CHECKBALL 11
#define AVOIDOPPONENT 12
#define RELEASEDBALL 13

#define MAX_VALUE_CHANGE 20

//Variables and data structure

//state machine
int robot_state;
int previous_state;

//limit switches
typedef struct{
	bool run_motor;
	unsigned int buffer_count;
} MainSwitch;
MainSwitch main_switch;

bool ball_collected;
bool ready_release_ball;

//sharp distance sensor
typedef struct _sharp_sensor{
	float sensor_1;
	float sensor_2;
	float sensor_3;
	float sensor_4;
}Sharp;
Sharp sharp;

bool opponent_infront;

//line sensors
#define IR_THRESHOLD_VALUE 900
int ir1;
int ir2;
int ir3;
int ir4;
bool avoiding_state;

//digital compass
int current_orientation;

//debugging variable
int debug_int1;
int debug_int2;
float debug_float1;
float debug_float2;


//include functions
#include "motor_control.h"
#include "sharp_sensors.h"
#include "line_sensors.h"
#include "limit_switches.h"
#include "compass.h"
#include "state_machine.h"

//Function to initialize value
void init(){
	avoiding_state = false;
	opponent_infront = false;
	sharp.sensor_1 = 100;
	sharp.sensor_2 = 100;
	sharp.sensor_3 = 100;
	sharp.sensor_4 = 100;
	main_switch.run_motor = false;
	main_switch.buffer_count = 0;
	robot_state = HOMESTATE;
	previous_state = robot_state;
	ball_collected = false;
	ready_release_ball = false;
	SensorValue[shaft_encoder] = 0;
}


#endif


/*
#include "motor_control.h"
#include "sharp_sensors.h"
#include "line_sensors.h"
#include "compass.h"
#include "state_machine.h"
#include "limit_switches.h"

#define HOMESTATE 0
#define GOFORWARD 1
#define AVOIDFRONTLEFTLINE 2
#define AVOIDFRONTRIGHTLINE 3
#define AVOIDREARRIGHTLINE 4
#define AVOIDREARLEFTLINE 5
#define BALLCOLLECTED 6
unsigned short int robot_state = HOMESTATE;

typedef struct _sharp_sensor{
	float sensor_1;
	float sensor_2;
	float sensor_3;
	float sensor_4;
}Sharp;

Sharp sharp;

task start_mission();
task set_distance();
void return_home();
task check_line();
void init();
task on_off_motor();

void go(char* direction, int speed, int time);
void stop_motor();

bool main_switch_pressed();
bool ball_collected();

bool line_sensor_front_left_triggered();
bool line_sensor_front_right_triggered();

typedef struct{
	bool run_motor;
	unsigned int buffer_count;
} MainSwitch;

MainSwitch main_switch;

float initial_orientation;
float compass(void);
*/
