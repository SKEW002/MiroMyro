#pragma config(Sensor, in2,    sharp_sensor,   sensorAnalog)
#pragma config(Motor,  port3,           right_motor,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           left_motor,     tmotorVex393_MC29, openLoop)
#pragma config(Sensor, dgtl2,  limit_switch,    sensorDigitalIn)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


bool run_motor = false;
int buffer_count = 0;

task main()
{
while(true){
	writeDebugStreamLine("lim %d", SensorValue(limit_switch));

	if(SensorValue(limit_switch)==0){
		if(buffer_count >= 100){
			run_motor = !run_motor;
		}
		buffer_count = 0;
	}
	if(run_motor){
		motor[left_motor] = 40;
		motor[right_motor] = 40;
	}
	else{
		motor[left_motor] = 0;
		motor[right_motor] = 0;
	}
	if(buffer_count <= 100){
		buffer_count++;
	}
}

}
/*
if(SensorValue(sharp_sensor)>700){
	motor[leftmotor] = 0;
	motor[rightmotor] = 0;
*/
