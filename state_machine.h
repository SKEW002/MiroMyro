#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "motor_control.h"
#include "limit_switches.h"
#include "sharp_sensors.h"
#include "line_sensors.h"

#define HOMESTATE 0
#define GOFORWARD 1
#define AVOIDLINE 2

unsigned short int robot_state = HOMESTATE;


void start_mission(unsigned short int robot_state){
	if (robot_state == GOFORWARD){
		go("forward", 40);
	}

	else if(robot_state == HOMESTATE){
		stop_motor();
	}
}

void check_line(){
	if (main_switch.run_motor){
		if (line_sensor_front_left_triggered()){
			turn("right", 40);
			robot_state = AVOIDLINE;
			delay(1000);
		}

		else if(line_sensor_front_right_triggered()){
			turn("left", 40);
			robot_state = AVOIDLINE;
			delay(1000);
		}

		else robot_state = GOFORWARD;
	}
}

void init(){
	main_switch.run_motor = false;
	main_switch.buffer_count = 0;
}

task main_task(){
		bottom_distance = distance_front_bottom();
		if(main_switch.buffer_count <= 100)main_switch.buffer_count++;
		if(main_switch_pressed()){
			if(main_switch.buffer_count >= 100){
				main_switch.run_motor = !main_switch.run_motor;
				robot_state = GOFORWARD;
			}
			main_switch.buffer_count = 0;
		}

		if(main_switch.run_motor){
			start_mission(robot_state);
		}
		else{
			stop_motor();
		}

}

#endif
