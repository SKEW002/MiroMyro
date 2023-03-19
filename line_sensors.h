#ifndef LINE_SENSORS_H
#define LINE_SENSORS_H


bool line_sensor_front_left_triggered(){
	if(SensorValue(line_sensor_front_left)==0)return true;
	else return false;
}

bool line_sensor_front_right_triggered(){
	if(SensorValue(line_sensor_front_right)==0)return true;
	else return false;
}

/*
bool line_sensor_rear_left_triggered(){
	if(SensorValue(line_sensor_rear_left)==0)return true;
	else return false;
}

bool line_sensor_rear_right_triggered(){
	if(SensorValue(line_sensor_rear_right)==0)return true;
	else return false;
}
*/

#endif
