#ifndef CONFIG_H
#include "config.h"
#endif

#ifndef SHARP_SENSORS_H
#define SHARP_SENSORS_H


task set_distance(){
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
		if(sharp.sensor_4 <= 10)continue;
		if(sharp.sensor_2 >= 14 || sharp.sensor_2 <= 12){
			robot_state = COLLECTINGBALL;
		}
		if ((sharp.sensor_3 <= 30 ||sharp.sensor_1 <= 30) && (robot_state == FORWARDSEARCH||robot_state == SEARCHING)&&current_orientation!=270 && current_orientation!=315){
			robot_state = GOTOBALL;
		}
	}
}

task opponent_detection(){
	while(1){
		if (sharp.sensor_4 <= 10){
			opponent_infront = true;
		}

		else opponent_infront = false;
	}
}

/*
int sensor_dist(int sensor_no){
int dist;
int value = SensorValue(sharp_front_bottom);

if (sensor_no == 1){
dist = 160339 * (float) pow(value, -1.285);

}
else if (sensor_no == 2){
dist = 180581 * (float) pow(value,-1.299);

}
else if (sensor_no == 3){
dist = 101263 * (float) pow(value,-1.226);

}
else if (sensor_no == 4){
dist = 27724 * (float) pow(value,-1.153);

}

return dist;
}
*/

#endif
