#ifndef CONFIG_H
#include "config.h"
#endif

#ifndef SHARP_SENSORS_H
#define SHARP_SENSORS_H


task set_distance(){//credits to chandrasekaran && alberito
	while(1){
		int NUM_READINGS = 5;

		for (int sensor_no = 1; sensor_no < 5; sensor_no++){
			float total = 0;
			if (sensor_no == 1){
				for (int i = 0; i <= NUM_READINGS; i++) {
					total += 160339 * (float) pow(SensorValue(sharp_1), -1.285);
				}
				sharp.sensor_1 = total/NUM_READINGS;
			}
			else if (sensor_no == 2){
				for (int i = 0; i <= NUM_READINGS; i++) {
					total += 180581 * (float) pow(SensorValue(sharp_2),-1.299);
				}
				sharp.sensor_2 = total/(NUM_READINGS);

			}
			else if (sensor_no == 3){
				for (int i = 0; i <= NUM_READINGS; i++) {
					total += 101263 * (float) pow(SensorValue(sharp_3),-1.226);
				}
				sharp.sensor_3 = total/NUM_READINGS;

			}
			else if (sensor_no == 4){
				for (int i = 0; i <= (NUM_READINGS); i++) {
					total += 27724 * (float) pow(SensorValue(sharp_4),-1.153);
				}
				sharp.sensor_4 = total/(NUM_READINGS);
			}
		}
	}
}

task ball_detection(){
	while(1){
		if(sharp.sensor_4 <= 15)continue;
		if(sharp.sensor_2 >= 15 || sharp.sensor_2 <= 12){ //credits to alberito again
			robot_state = COLLECTINGBALL;
		}
		if ((sharp.sensor_3 <= 30 ||sharp.sensor_1 <= 30) && (robot_state == FORWARDSEARCH || robot_state == SEARCHING)){//&&current_orientation!=270 && current_orientation!=315){
			if((robot_state == FORWARDSEARCH || robot_state == SEARCHING) && previous_state != GOTOBALL)previous_state = robot_state;
			robot_state = GOTOBALL;
		}
	}
}

task opponent_detection(){
	int cool_down = 2000;
	bool start_check_opponent = true;
	int start_time = 0;
	int detect_count = 0;
	while(1){
		if(start_check_opponent){
			if (sharp.sensor_4 <= 15){
				if(detect_count <= 30)detect_count++;
				else{
					start_time = nSysTime;
					opponent_infront = true;
					start_check_opponent = false;
					detect_count = 0;
				}
			}
			else{
				detect_count = 0;
				opponent_infront = false;
			}
		}

		if(start_time!=0){
			delay(1000);
			opponent_infront = false;
			if(nSysTime - start_time >= cool_down){
				start_check_opponent = true;
				start_time = 0;
			}
		}

	}
}

#endif
