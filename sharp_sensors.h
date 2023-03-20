#ifndef SHARP_SENSORS_H
#define SHARP_SENSORS_H


int analog_to_cm(int x){
	int m = 1;
	int c = 0;
	return m*x + c;
}

int distance_front_bottom(){
	return analog_to_cm(SensorValue(sharp_front_bottom));
}

int bottom_distance;

/*
int distance_front_top(){
	return SensorValue(sharp_front_top);
}
*/


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

#endif
