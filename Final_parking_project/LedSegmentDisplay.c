/*
 * LedSegmentDisplay.c
 *
 * Created: 7/25/2023 1:30:18 PM
 *  Author: Aleksa
 */ 
#define F_CPU 16000000UL
#include <stdio.h>
#include "LedSegmentDisplay.h"
#include "stdio_setup.h"
#include "UltrasonicSensor.h"
#include "PowertrainSwitch.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>

static uint8_t ledSegmentStates[FIVE];
static const uint8_t LED_SEGMENT_PIN_NUM[FIVE] = {TWO, THREE, FOUR, FIVE, SIX};

/* This function initializes main parameters of LegSegmentDisplay */
void LedSegmentDisplay_Init()
{
	DDRD = (ONE << DDD2) | (ONE << DDD3) | (ONE << DDD4) | (ONE << DDD5) | (ONE << DDD6);
	int i = ZERO;
	for(i = ZERO; i < FIVE; i++)
	{
		ledSegmentStates[i] = ZERO;
	}
}

/* Activating the specified LED segment */
void LedSegmentDisplay_ActivateSegment(LedSegmentType ledSegment)
{
	PORTD |= (1 << LED_SEGMENT_PIN_NUM[ledSegment]);
	ledSegmentStates[ledSegment] = ONE;
}

/* Deactivating the specified LED segment */
void LedSegmentDisplay_DeactivateSegment(LedSegmentType ledSegment)
{
	PORTD &= ~(1 << LED_SEGMENT_PIN_NUM[ledSegment]);
	ledSegmentStates[ledSegment] = ZERO;
}

