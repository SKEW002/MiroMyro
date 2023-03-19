#ifndef LIMIT_SWITCHES_H
#define LIMIT_SWITCHES_H

typedef struct{
	bool run_motor;
	unsigned int buffer_count;
} MainSwitch;

bool main_switch_pressed(){
	if(SensorValue(on_off_switch)==0)return true;
	else return false;
}



/*
bool rear_right_switch_pressed(){
	if(SensorValue(rear_right_switch)==0)return true;
	else return false;
}

bool rear_left_switch_pressed(){
	if(SensorValue(rear_right_switch)==0)return true;
	else return false;
}

bool ball_collected(){
	if(SensorValue(on_off_switch)==0)return true;
	else return false;
}
*/

MainSwitch main_switch;


#endif
