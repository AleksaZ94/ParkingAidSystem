/*
 * PowertrainSwitch.c
 *
 * Created: 7/24/2023 5:54:05 PM
 *  Author: Aleksa
 */ 
#define F_CPU 16000000UL
#include <stdio.h>
#include "PowertrainSwitch.h"
#include "stdio_setup.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>

static const uint8_t SWITCH_PIN_NUM = FOUR;
static SwitchStateType switchState;

/*Function which initializes main parameters of PowertrainSwitch*/
void PowertrainSwitch_Init()
{
	switchState = SWITCH_OFF;
}

/* PowertrainSwitch_GetState() is used to return current state of the switch */
SwitchStateType PowertrainSwitch_GetState()
{
	if(PINB & (1 << SWITCH_PIN_NUM))
	{
		switchState = SWITCH_ON;
	}
	else
	{
		switchState = SWITCH_OFF;
	}
	return switchState;
}