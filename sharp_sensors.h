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

#endif
