#define NUM_READINGS 20

int sharp_sensor_filter(){
	int readings[NUM_READINGS];
	int total = 0;
	int average = 0;
	int i;

	// Read NUM_READINGS samples from the sharp sensor
	for (i = 0; i < NUM_READINGS; i++) {
		readings[i] = SensorValue(sharp_front_bottom);
		delay(10); // wait 10 milliseconds between readings


  //for (i = 5; i < NUM_READINGS-5; i++) {
    total += readings[i];
  //}

	}
	average = total / NUM_READINGS;
	return average ;
	// Calculate and return the rolling average of the middle 10 values
}
