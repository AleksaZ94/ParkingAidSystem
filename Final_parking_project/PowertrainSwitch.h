/*
 * PowertrainSwitch.h
 *
 * Created: 7/24/2023 5:53:47 PM
 *  Author: Aleksa
 */ 


#ifndef POWERTRAINSWITCH_H_
#define POWERTRAINSWITCH_H_

#define ZERO 0
#define ONE 1
#define TWO 2
#define HUNDRED 100
#define FOUR 4
#define THREE 3
#define FIVE 5
#define SIX 6

typedef enum{
	SWITCH_OFF = ZERO,
	SWITCH_ON = ONE
}SwitchStateType;

void PowertrainSwitch_Init();
SwitchStateType PowertrainSwitch_GetState();


#endif /* POWERTRAINSWITCH */