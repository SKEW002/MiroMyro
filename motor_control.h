#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

void go(char* direction, int speed){
	if (direction == "forward"){
		motor[left_motor] = speed;
		motor[right_motor] = speed;
	}

	else if(direction == "reverse"){
		motor[left_motor] = -speed;
		motor[right_motor] = -speed;
	}
}


void stop_motor(){
	motor[left_motor] = 0;
	motor[right_motor] = 0;
}

void turn(char* direction, int speed){
	if(direction == "right"){
		motor[left_motor] = -speed;
		motor[right_motor] = speed;
	}

	else if(direction == "left"){
		motor[left_motor] = speed;
		motor[right_motor] = -speed;
	}
}

/*
void collect_ball(){
		motor[collector_motor] = 10;
}


void servo_to_angle(int port, int angle_destination, int delay_speed)
{
	while(motor[port]>angle_destination)
	{
		motor[port]=motor[port]-1;
		wait1Msec(delay_speed);
	}
	while(motor[port]<angle_destination)
	{
		motor[port]=motor[port]+1;
		wait1Msec(delay_speed);
	}
}

void collecter_servo(){
	motor[collector] = 127
}
*/



#endif
