
#pragma config(Sensor, in2,    sharp_front_bottom_l, sensorAnalog)


int distancel;


task main(){
	while(1){
distancel = SensorValue(sharp_front_bottom_l);

writeDebugStreamLine("intl %d", distancel);

sleep(500);
}
}
