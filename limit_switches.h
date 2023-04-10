#ifndef CONFIG_H
#include "config.h"
#endif

#ifndef LIMIT_SWITCHES_H
#define LIMIT_SWITCHES_H


task check_main_switch(){
	while(1){
		if(main_switch.buffer_count <= 100)main_switch.buffer_count++;
		if(SensorValue(on_off_switch)==0){
			if(main_switch.buffer_count > 100){
				main_switch.run_motor = !main_switch.run_motor;
				robot_state = FORWARDSEARCH;
			}
			main_switch.buffer_count = 0;
		}
	}
}

void check_release_ball(){
	if(SensorValue(release_switch_left)==0 && SensorValue(release_switch_right)==0 && sharp.sensor_4>=10)ready_release_ball = true;
	else ready_release_ball = false;
}

bool hit_wall(){
	if(SensorValue(release_switch_left)==0 && SensorValue(release_switch_right)==0)return true;
	else return false;

}

/*
bool ball_collected(){
	if(SensorValue(collector_switch)==0)return true;
	else return false;
}

bool ready_release_ball(){
	if(SensorValue(release_switch_left)==0 && SensorValue(release_switch_right)==0)return true;
	else return false;
}

bool rear_right_switch_pressed(){
	if(SensorValue(rear_right_switch)==0)return true;
	else return false;
}

bool rear_left_switch_pressed(){
	if(SensorValue(rear_right_switch)==0)return true;
	else return false;
}

*/




#endif
