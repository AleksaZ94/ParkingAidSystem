/*
 * UltrasonicSensor.h
 *
 * Created: 7/24/2023 4:50:16 PM
 *  Author: Aleksa
 */ 


#ifndef ULTRASONICSENSOR_H_
#define ULTRASONICSENSOR_H_

void UltrasonicSensor_Init();
void UltrasonicSensor_StartMeasurement();
uint16_t UltrasonicSensor_GetMeasurement();

typedef enum {
	SONIC_READY = 1,
	SONIC_START = 2,
	SONIC_FINISH = 3
}SonicStateType;

volatile uint16_t Timer_overflov;

#endif /* ULTRASONICSENSOR_H_ */