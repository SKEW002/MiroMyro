#ifndef CONFIG_H
#include "config.h"
#endif

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

task avoid_line_counter(){
	while(1){
		if(avoid_line_count == 1){
			int start_time = nSysTime;
			while(1){
				if(nSysTime - start_time > 5000){
					avoid_line_count = 0;
					break;
				}
				if (avoid_line_count == 3){
					increase_avoid_line_delay = true;
					avoid_line_count = 0;
					delay(1000);
							increase_avoid_line_delay = false;
					break;
				}
			}
		}
	}
}


task check_line(){
	while(1){
		line_sensor_front_left_triggered();
		line_sensor_front_right_triggered();
		line_sensor_rear_left_triggered();
		line_sensor_rear_right_triggered();
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
	suspendTask(check_line);
	avoiding_state = false;
	if(current_orientation == 315 || current_orientation == 0 || current_orientation == 45){
		turn_to_angle("right", 270);
	}
	else{
		turn_to_angle("left", 315);
	}
	stop_motor();
	int value_change = 0;

	while(1){
		resumeTask(check_line);
		if(avoiding_state)return;
		if(opponent_infront){
			handle_opponent = 2;
			robot_state = HANDLEOPPONENT;
			return;
		}
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
void search(){
	int start_time = nSysTime;
	int random_period_1 = random(3);
	int random_period_2 = random(3);
	if(robot_state != SEARCHING)return;
	while(1){
		if(hit_wall())robot_state = RELEASEDBALL;
		if(robot_state != SEARCHING){
			stop_motor();
			return;
		}
		search_time = nSysTime - start_time;
		if(search_time <= 1500)go("forward", 100, 10);
		else if(search_time > 1500 && search_time <= 1500+800+100*random_period_1){
			if(left_first)	go("left", 60, 10);
			else go("right", 60, 10);
		}
		else if(search_time > 1500+800+100*random_period_1 && search_time <= 1500+800+100*random_period_1+800+100*random_period_2){
			if(left_first)go("right", 60, 10);
			else go("left", 60, 10);
		}
		else break;
	}
	left_first =! left_first;
	return;
}

void reset_position(){
	go("reverse", 127, 1000);
	if(current_orientation == 270)turn_to_angle("right", 90);
	else if(current_orientation == 315)turn_to_angle("left", 135);
	resumeTask(ball_detection);
	robot_state = SEARCHING;
}

task start_mission(){
	int start_time = 0;
	while(1){
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
			reset_position();
			resumeTask(check_line);
		}
		else if(robot_state == GOTOBALL){
			if(start_time == 0)start_time = nSysTime;
			if(start_time!=0){
				if(nSysTime - start_time >= 4000){
					start_time = 0;
					robot_state = SEARCHING;
					continue;
				}
			}
			if(opponent_infront){
				robot_state = HANDLEOPPONENT;
				start_time = 0;
				continue;
			}

			if(hit_wall()){
				robot_state = RELEASEDBALL;
				start_time = 0;
				continue;
			}
			if(sharp.sensor_3 <= 30 && sharp.sensor_3 >= 15 && sharp.sensor_1 >= 40){ //right
				drift("right", 80);
			}
			else if(sharp.sensor_3 >= 40 && sharp.sensor_1 <= 30 && sharp.sensor_1 >= 15){ //left //check arena
				drift("left", 80);
			}
			else if((sharp.sensor_3 <= 30 && sharp.sensor_1 <= 30)&&!opponent_infront){
				go("forward", 70,100);
			}
			else if (sharp.sensor_3 > 30 && sharp.sensor_1 > 30){
				go("forward", 80,100);
				robot_state = previous_state;
				start_time = 0;
				continue;
			}
		}

		else if (robot_state == HANDLEOPPONENT){
			if (handle_opponent == 2){
				go("reverse",80,800);
				if(left_first){
					go("left", 80,750);
					go("forward", 80,1300);
					go("right", 80,750);
				}
				else{
					go("right", 80,750);
					go("forward", 80,1300);
					go("left", 80,750);
				}
				if(robot_state != HANDLEOPPONENT){
					left_first = !left_first;
					continue;
				}
				opponent_infront = false;
				robot_state = RETURNHOME;
				handle_opponent = 0;
				continue;
			}
			else if (handle_opponent == 1){
				go("forward", 80, 800);
				opponent_infront = false;
				robot_state = SEARCHING;
				continue;
			}
			else if (handle_opponent == 0){
				opponent_infront = false;
				robot_state = SEARCHING;
				continue;
			}
		}
	}
}



#endif
