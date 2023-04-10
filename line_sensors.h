#ifndef CONFIG_H
#include "config.h"
#endif

#ifndef LINE_SENSORS_H
#define LINE_SENSORS_H


bool line_sensor_front_right_triggered(){
	ir1 = SensorValue(IR_1);
	if(SensorValue(IR_1)<= IR_THRESHOLD_VALUE)return true;
	else return false;
}

bool line_sensor_front_left_triggered(){
	ir2 = SensorValue(IR_2);
	if(SensorValue(IR_2)<= IR_THRESHOLD_VALUE)return true;
	else return false;
}

bool line_sensor_rear_left_triggered(){
	ir3 = SensorValue(IR_3);
	if(SensorValue(IR_3)<= 0)return true;
	else return false;
}

bool line_sensor_rear_right_triggered(){
	ir4 = SensorValue(IR_4);
	if(SensorValue(IR_4)<= 0)return true;
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
