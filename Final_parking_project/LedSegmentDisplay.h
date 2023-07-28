/*
 * LedSegmentDisplay.h
 *
 * Created: 7/25/2023 1:32:53 PM
 *  Author: Aleksa
 */ 


#ifndef LEDSEGMENTDISPLAY_H_
#define LEDSEGMENTDISPLAY_H_

typedef enum {
	LED_SEGMENT_A = 0,
	LED_SEGMENT_F = 1,
	LED_SEGMENT_G = 2,
	LED_SEGMENT_E = 3,
	LED_SEGMENT_D = 4
	
	}LedSegmentType;

void LedSegmentDisplay_Init();
void LedSegmentDisplay_ActivateSegment(LedSegmentType ledSegment);
void LedSegmentDisplay_DeactivateSegment(LedSegmentType ledSegment);



#endif /* LEDSEGMENTDISPLAY_H_ */