#ifndef CONFIG_H
#include "config.h"
#endif

#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H


void stop_motor(){
	motor[left_motor] = 0;
	motor[right_motor] = 0;
}

bool check_collected_ball(){
	if(SensorValue(collector_switch)==0)return true;
	else return false;
}

void go(char* direction, int speed, int time){
	int start_time = nSysTime;
	while(nSysTime - start_time <= time && main_switch.run_motor){

		if(avoiding_state)return;
		if (direction == "forward"){
			motor[left_motor] = speed;
			motor[right_motor] = speed-2;
		}

		else if(direction == "reverse"){
			motor[left_motor] = -speed;
			motor[right_motor] = -speed+2;
		}

		else if(direction == "right"){
			motor[left_motor] = speed;
			motor[right_motor] = -speed;
		}

		else if(direction == "left"){
			motor[left_motor] = -speed;
			motor[right_motor] = speed;
		}
	}
}

void turn_to_angle(char* direction, int target_orientation){
	int speed = 40;
	while(current_orientation!=target_orientation){
		if(!main_switch.run_motor)return;
		if(direction == "left"){
			motor[left_motor] = -speed;
			motor[right_motor] = speed;
		}
		else if(direction == "right"){
			motor[left_motor] = speed;
			motor[right_motor] = -speed;
		}
	}
	stop_motor();
}

void drift(char *direction, int speed){
	if(!main_switch.run_motor)return;
	if(direction == "left"){
		motor[left_motor] = 0;
		motor[right_motor] = speed;
	}
	else if(direction == "right"){
		motor[left_motor] = speed;
		motor[right_motor] = 0;
	}
}



void avoid_line(char* direction){
	avoiding_state = true;
	int speed;
	int delay_period = 800;
	if(previous_state == RETURNHOME){
		delay_period = 500;
	}
	speed = 100;
	if(!main_switch.run_motor)return;

	if(direction == "front_left"){
		motor[left_motor] = -speed;
		motor[right_motor] = -speed;
		delay(delay_period);
		motor[left_motor] = speed;
		motor[right_motor] = -speed;
	}

	else if(direction == "front_right"){
		motor[left_motor] = -speed;
		motor[right_motor] = -speed;
		delay(delay_period);
		motor[left_motor] = -speed;
		motor[right_motor] = speed;
	}

	else if(direction == "rear_right"){
		motor[left_motor] = speed;
		motor[right_motor] = speed;
		delay(800);
		motor[left_motor] = speed;
		motor[right_motor] = 0;
	}

	else if(direction == "rear_left"){
		motor[left_motor] = speed;
		motor[right_motor] = speed;
		delay(800);
		motor[left_motor] = 0;
		motor[right_motor] = speed;
	}
	delay(delay_period+100*random(3));
	robot_state = previous_state;
	avoiding_state = false;
}


void collector_control(char* action){
	if(!main_switch.run_motor)return;
	int start_time = nSysTime;
	int target_angle;
	float kp;
	float kd;
	float ki;
	int error;
	int prev_error;
	int integral_error = 0;


	//if (!main_switch.run_motor)return;
	while(1){
		if(action == "release"){
			target_angle = -280;
			motor[collector_motor] = -40;
			if (SensorValue[shaft_encoder] <= target_angle){
				motor[collector_motor] = 0;
				break;
			}
		}
		else if (action == "catch"){
			kp = 0.2;
			kd = 0.01;
			ki = 0.001;
			target_angle = -170;
			error = target_angle - SensorValue[shaft_encoder];
			if(prev_error==NULL)prev_error = error;
			integral_error += error;
			int error_speed = kp*error + ki*integral_error;// + kd*(error - prev_error);
			prev_error = error;
			if (error_speed >= 35)error_speed = 35;
			else if(error_speed <= -35)error_speed = -35;
			if(check_collected_ball())ball_collected = true;
			if(avoiding_state)stop_motor();
			motor[collector_motor] = error_speed;
			if (nSysTime - start_time >= 2000){
				motor[collector_motor] = 0;
				break;
			}
		}

		else if(action == "home"){
			target_angle = -360;
			kp = 0.8;
			ki = 0.001;
			error = target_angle - SensorValue[shaft_encoder];
			integral_error += error;
			motor[collector_motor] = kp*error + ki*integral_error;
			if (nSysTime - start_time >= 2500){
				motor[collector_motor] = 0;
				SensorValue[shaft_encoder] = 0;
				break;
			}
		}
		else if(action == "fail"){
			target_angle = 0;
			kp = 0.8;
			ki = 0.001;
			error = target_angle - SensorValue[shaft_encoder];
			integral_error += error;
			motor[collector_motor] = kp*error + ki*integral_error;
			if (nSysTime - start_time >= 2500){
				motor[collector_motor] = 0;
				SensorValue[shaft_encoder] = 0;
				break;
			}
		}
	}

}


/*
void test_collect_ball(){
	collector_control("catch");
	delay(1000);
	collector_control("release");
	delay(1000);
	collector_control("home");
	delay(1000);
}
*/


#endif
