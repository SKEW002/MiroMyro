#ifndef CONFIG_H
#include "config.h"
#endif


#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

task check_line(){
	while(1){
		if (main_switch.run_motor){
			if(line_sensor_front_left_triggered() || line_sensor_front_right_triggered()|| line_sensor_rear_left_triggered()||line_sensor_rear_right_triggered()){
				avoiding_state = true;
				if(robot_state!=AVOIDFRONTLEFTLINE && robot_state!=AVOIDFRONTRIGHTLINE && robot_state!=AVOIDREARLEFTLINE && robot_state!=AVOIDREARRIGHTLINE){
					previous_state = robot_state;
				}
				if (line_sensor_front_left_triggered()){
					robot_state = AVOIDFRONTLEFTLINE;
				}

				else if(line_sensor_front_right_triggered()){
					robot_state = AVOIDFRONTRIGHTLINE;
				}

				else if(line_sensor_rear_left_triggered()){
					robot_state = AVOIDREARLEFTLINE;
				}

				else if(line_sensor_rear_right_triggered()){
					robot_state = AVOIDREARRIGHTLINE;
				}
			}
		}
	}
}

void return_home(){
	if(current_orientation == 315 || current_orientation == 0 || current_orientation == 45){
		turn_to_angle("right", 270);
	}
	else{
		turn_to_angle("left", 315);
		//}

		int value_change = 0;

		while(1){
			if(SensorValue(release_switch_left)==0 || SensorValue(release_switch_right)==0)suspendTask(check_line);
			if (current_orientation==270){
				if(value_change <= MAX_VALUE_CHANGE){
					value_change++;
				}
			}
			else if (current_orientation==315){
				if(value_change >= -MAX_VALUE_CHANGE){
					value_change--;
				}
			}
			if(avoiding_state)return;

			if(!main_switch.run_motor)return;
			motor[left_motor] = 100-value_change;
			motor[right_motor] = 100+value_change;
			check_release_ball();
			if(ready_release_ball){
				stop_motor();
				collector_control("release");
				delay(1000);
				collector_control("home");
				break;
			}
		}
		robot_state= RELEASEDBALL;
	}
}
void search(){
	int start_time = nSysTime;
	int period = 0;
	int random_period_1 = random(3);
	int random_period_2 = random(3);
	if(robot_state != SEARCHING)return;
	while(1){
		if(hit_wall())robot_state = RELEASEDBALL;
		if(robot_state != SEARCHING)return;
		period = nSysTime - start_time;
		if(period <= 1500)go("forward", 100, 10);
		else if(period > 1500 && period <= 1500+500+100*random_period_1)go("right", 80, 10);
		else if(period > 1500+500+100*random_period_1 && period <= 1500+500+100*random_period_1+500+100*random_period_2)go("left", 80, 10);
		else break;
	}
	return;
}

void reset_position(char *direction){
	go("reverse", 127, 1000);
	if (direction == "right"){
		turn_to_angle("right", 90);
	}
	else{
		turn_to_angle("left", 135);
	}
	resumeTask(ball_detection);
	robot_state = SEARCHING;
}

task start_mission(){
	while(1){
		if (opponent_infront){
			stop_motor();
			delay(2000);
		}
		if (robot_state == FORWARDSEARCH){
			go("forward", 127, 10);
		}

		else if(robot_state == HOMESTATE){
			stop_motor();
		}

		else if(robot_state == AVOIDFRONTLEFTLINE){
			avoid_line("front_left");
			avoiding_state = false;
		}

		else if(robot_state == AVOIDFRONTRIGHTLINE){
			avoid_line("front_right");
			avoiding_state = false;
		}

		else if(robot_state == AVOIDREARRIGHTLINE){
			avoid_line("rear_right");
			avoiding_state = false;
		}

		else if(robot_state == AVOIDREARLEFTLINE){
			avoid_line("rear_left");
			avoiding_state = false;
		}

		else if(robot_state == SEARCHING){
			if(hit_wall())robot_state = RELEASEDBALL;
			search();
		}

		else if(robot_state == COLLECTINGBALL){
			suspendTask(ball_detection);
			go("forward", 30, 1000);
			stop_motor();
			collector_control("catch");
			go("reverse", 30, 500);
			robot_state = CHECKBALL;
		}

		else if(robot_state == CHECKBALL){
			if(ball_collected == true){
				robot_state = RETURNHOME;
			}
			else{
				resumeTask(ball_detection);
				resumeTask(check_line);
				collector_control("fail");
				robot_state = SEARCHING;
			}
		}

		else if(robot_state == RETURNHOME){
			return_home();
		}

		else if(robot_state == RELEASEDBALL){
			ball_collected = false;
			reset_position("right");
			resumeTask(check_line);
		}
		else if(robot_state == GOTOBALL){
			if(sharp.sensor_3 <= 30 && sharp.sensor_3 >= 15 && sharp.sensor_1 >= 40){ //right
				drift("right", 80);
			}
			else if(sharp.sensor_3 >= 40 && sharp.sensor_1 <= 30 && sharp.sensor_1 >= 15){ //left
				drift("left", 80);
			}
			else if((sharp.sensor_3 <= 30 && sharp.sensor_1 <= 30) || (sharp.sensor_3 >= 30 && sharp.sensor_1 >= 30)&&!opponent_infront){
				go("forward", 100,100);
			}
			//go("forward", 40, 100);
		}
	}
}



#endif
