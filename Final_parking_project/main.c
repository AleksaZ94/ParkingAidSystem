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

uint32_t ADC_voltage = 0;
void piezo_buz();
void odlozi();
void Init_piezo();
uint16_t a = ZERO;
volatile uint32_t num_freq = ZERO;
volatile uint8_t flag_2 = ZERO;

int main(void)
{

    OCR2A = 249; /*Tajmer setovan tako da broji i radi na 1ms*/
	TCCR2A = 0;
	TCCR2B |= (1 << CS21) | (1 << CS20);
	TIMSK2 |= (1 << OCIE2A);

    Init_piezo();
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
			if(ONE == flag_2) /* Every second enter check this case and give sound signal depends on the distance of the object*/
			{
				flag_2 = ZERO;
				piezo_buz();
			}
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

ISR(TIMER2_COMPA_vect) {
	  num_freq++;
	  if(num_freq == 1000)
	  {
		  flag_2 = ONE;
	  }
}

void piezo_buz()
{
    if(!(ADCSRA & (1 << ADSC)))
	{
		 ADC_voltage = ADC;
		 //printf("ADC = %ld\n", ADC_voltage);
		 ADCSRA |= (1 << ADSC);
	}
	if((PINB & (1 << PINB4)) == 0)
	{
		PORTB &= 0xF0;
		num_freq = 0;
	}
	else if(sonicDistanca < 10u)
	{
		a = 0;
		while(a < 50)
		{
			PORTB = (1 << PORTB2);
			odlozi();
			PORTB &= ~(1 << PORTB2);
			odlozi();
			a++;
		}
		num_freq = 900;
	}
	else if(sonicDistanca < 30u)
	{
		a = 0;
		while(a < 150)
		{
			PORTB = (1 << PORTB2);
			odlozi();
			PORTB &= ~(1 << PORTB2);
			odlozi();
			a++;
		}
		num_freq = 700;
	}
	else if(sonicDistanca > 30u && sonicDistanca < 70u)
	{
		a = 0;
		while(a < 250)
		{
			PORTB = (1 << PORTB2);
			odlozi();
			PORTB &= ~(1 << PORTB2);
			odlozi();
			a++;
		}
		num_freq = 200;
	}
	else if(sonicDistanca > 70u && sonicDistanca < 120u)
	{
		a = 0;
		while(a < 400)
		{
			PORTB = (1 << PORTB2);
			odlozi();
			PORTB &= ~(1 << PORTB2);
			odlozi();
			a++;
		}
		num_freq = 100;
	}
	else
	{
		PORTB &= 0x00;
		num_freq = 0;
	}
}

void Init_piezo()
{
	DDRB = (1 << DDB2);
	ADMUX = (1 << REFS0);
	DIDR0 = (1 << ADC0D);
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

void odlozi()
{
	uint32_t vreme = 0;
	vreme = ADC_voltage;
	if(vreme < 200)
	{
		vreme = 200;
	}
	while(vreme > 0)
	{
		_delay_us(1);
		vreme--;
	}
}



