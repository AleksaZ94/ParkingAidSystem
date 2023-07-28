/*
 * main.c
 *
 * Created: 7/27/2023 4:09:53 PM
 *  Author: Aleksa
 */ 
#define F_CPU 16000000UL
#include <stdio.h>
#include "stdio_setup.h"
#include "UltrasonicSensor.h"
#include "PowertrainSwitch.h"
#include "LedSegmentDisplay.h"
#include "SwcParkingAid.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>

int main(void)
{
	UltrasonicSensor_Init();
	PowertrainSwitch_Init();
	LedSegmentDisplay_Init();
	SwcParkingAid_Init();
	
	UartInit();

	while(1) {
		if(ONE == flag) /* When the flag is set to one time period of 100ms is over and the SwcParkingAid_Cyclic function is called again */
		{
			flag = ZERO;
			SwcParkingAid_Cyclic();
		}
	}
}

ISR(TIMER0_COMPA_vect)
{
	cnt++;
	if(HUNDRED == cnt)
	{
		cnt = ZERO;
		flag = ONE;
	}
}
