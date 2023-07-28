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

static uint16_t sonicDistance;
static SwitchStateType pwtSwitchState;
static const uint16_t DIST_LOW_TH_CM = 30u;
static const uint16_t DIST_MED_TH_CM = 70u;
static const uint16_t DIST_HIGH_TH_CM = 120u;

/* SwcParkingAid_Init() is used to set main parmeters of the <<Controller>> SwcParkingAid */
void SwcParkingAid_Init()
{
	flag = ZERO;
	cnt = ZERO;
	pwtSwitchState = SWITCH_OFF;
	sonicDistance = UINT16_MAX;
	DDRB |= (ONE << DDB1);
	/* Setting parameters of the TIMER1 */
	TIMSK1 = (ONE << TOIE1);	/* Enable Timer1 overflow interrupts */
	TCCR1A = ZERO;
	/* Setting parameters of the TIMER0 */
	OCR0A = 249;
	TCCR0A = (ONE << WGM01);
	TCCR0B = (ONE << CS01) | (ONE << CS00);
	TIMSK0 = (ONE << OCIE0A);
	sei();
}

/* Main function in the first stage. This function calls all the other important functions for the stage one of the project. 
   Also, this function is called every 100 ms in the while(1) loop. */
void SwcParkingAid_Cyclic()
{
	pwtSwitchState = PowertrainSwitch_GetState();
	if(pwtSwitchState)
	{
		UltrasonicSensor_StartMeasurement();
		sonicDistance = UltrasonicSensor_GetMeasurement();
		printf("sonicDistance is: %d cm\n", sonicDistance); 
		if(sonicDistance <=  DIST_LOW_TH_CM)
		{
			LedSegmentDisplay_ActivateSegment(LED_SEGMENT_A);
			LedSegmentDisplay_ActivateSegment(LED_SEGMENT_F);
			LedSegmentDisplay_ActivateSegment(LED_SEGMENT_E);
			LedSegmentDisplay_DeactivateSegment(LED_SEGMENT_G);
			LedSegmentDisplay_DeactivateSegment(LED_SEGMENT_D);
		}
		else if(sonicDistance <= DIST_MED_TH_CM)
		{
			LedSegmentDisplay_ActivateSegment(LED_SEGMENT_F);
			LedSegmentDisplay_ActivateSegment(LED_SEGMENT_G);
			LedSegmentDisplay_ActivateSegment(LED_SEGMENT_E);
			LedSegmentDisplay_DeactivateSegment(LED_SEGMENT_D);
			LedSegmentDisplay_DeactivateSegment(LED_SEGMENT_A);
		}
		else if(sonicDistance <= DIST_HIGH_TH_CM)
		{
			LedSegmentDisplay_ActivateSegment(LED_SEGMENT_F);
			LedSegmentDisplay_ActivateSegment(LED_SEGMENT_E);
			LedSegmentDisplay_ActivateSegment(LED_SEGMENT_D);
			LedSegmentDisplay_DeactivateSegment(LED_SEGMENT_A);
			LedSegmentDisplay_DeactivateSegment(LED_SEGMENT_G);
		}
		else 
		{
			LedSegmentDisplay_ActivateSegment(LED_SEGMENT_F);
			LedSegmentDisplay_ActivateSegment(LED_SEGMENT_E);
			LedSegmentDisplay_DeactivateSegment(LED_SEGMENT_D);
			LedSegmentDisplay_DeactivateSegment(LED_SEGMENT_A);
			LedSegmentDisplay_DeactivateSegment(LED_SEGMENT_G);
		}
	}
	else
	{
		LedSegmentDisplay_DeactivateSegment(LED_SEGMENT_A);
		LedSegmentDisplay_DeactivateSegment(LED_SEGMENT_G);
		LedSegmentDisplay_DeactivateSegment(LED_SEGMENT_D);
		LedSegmentDisplay_DeactivateSegment(LED_SEGMENT_F);
		LedSegmentDisplay_DeactivateSegment(LED_SEGMENT_E);
	}
}