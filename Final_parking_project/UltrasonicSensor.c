/*
 * UltrasonicSensor.c
 *
 * Created: 7/24/2023 4:49:00 PM
 *  Author: Aleksa
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/wdt.h>
#include "UltrasonicSensor.h"
#include "PowertrainSwitch.h"
#include "SwcParkingAid.h"
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "stdio_setup.h"
#define MAX_CNT_TIMER_1 65535

static uint16_t sonicDistance;
static uint32_t count;
volatile uint8_t marker = ZERO;
static SonicStateType sonicState;
static const uint8_t SONIC_TX_PIN_NUM = ZERO;
static const uint8_t SONIC_RX_PIN_NUM = ONE;

/*Function which initializes main parameters of Ultrasonic sensor*/
void UltrasonicSensor_Init()
{
	Timer_overflov = ZERO;
	count = ZERO;
	sonicState = SONIC_READY;
	sonicDistance = UINT16_MAX;
}

/* Ultrasonic Sensor StartMeasurement() first calculates time, then, based on time, calculates distance. */
void UltrasonicSensor_StartMeasurement()
{
	  //wdt_enable(WDTO_30MS); /* Activation of watchdog timer*/
	  PORTB |= (ONE << SONIC_RX_PIN_NUM);
	  _delay_us(10);
	  PORTB &= ~(ONE << SONIC_RX_PIN_NUM);
	  TCNT1 = ZERO;
	  TCCR1B = (ONE << ICES1) | (ONE << CS10); /* Setting upper edge of signal for measurement, no prescaling(that means F_CPU stays 16MHz) */
	  TIFR1 = (ONE << ICF1);
	  TIFR1 = (ONE << TOV1);
	  while ((TIFR1 & (ONE << ICF1)) == ZERO);/* Wait for rising edge */
	  TCNT1 = ZERO;
	  TCCR1B = (ONE << CS10); /* Setting lower edge of signal for measurement */
	  TIFR1 = (ONE << ICF1);
	  TIFR1 = (ONE << TOV1); /* Clean the flags for interrupts */
	  Timer_overflov = ZERO;
	  sonicState = SONIC_START;
	  while((TIFR1 & (ONE << ICF1)) == ZERO);
	  count = ICR1 + (MAX_CNT_TIMER_1 * Timer_overflov);
	  sonicDistance = count/931.9; /* Calculating the distance */
	  sonicState = SONIC_FINISH;
	  //wdt_reset();
	  //wdt_disable();	
}

/* This function return the value of the distance measured by Ultrasonic Ranging Module HC - SR04 */
uint16_t UltrasonicSensor_GetMeasurement()
{
	return sonicDistance;
	sonicState = SONIC_READY;
}

ISR(TIMER1_OVF_vect)
{
	Timer_overflov++;
}