/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum states { start, PB0ON, PB1ONWAIT, PB1ON, PB0ONWAIT } state;

void tick()
{
	switch(state){
		case start:
			state = PB0ON;
			break;
		case PB0ON:
			if(PINA & 0X01 == 0)
				state = PB0ON;
			else if(PINA & 0x01 == 1)
				state = PB1ONWAIT;
			break;
		case PB1ONWAIT:
			if(PINA & 0x01 == 1)
				state = PB1ONWAIT;
			else if(PINA & 0x01 == 0)
				state = PB1ON;
			break;
		case PB1ON:
			if(PINA & 0x01 == 0)
				state = PB1ON;
			else if(PINA & 0x01 == 1)
				state = PB0ONWAIT;
			break;
		case PB0ONWAIT:
			if(PINA & 0x01 == 1)
				state = PB0ONWAIT;
			else if(PINA & 0x01 == 0)
				state = PB0ON;
			break;
		default:
			state = start;
			break;
		
	}
	//state actions
	switch(state){
		case PB0ON:
			PORTB = 0x01;
			break;
		case PB1ONWAIT:
			PORTB = 0x02;
			break;
		case PB1ON:
			PORTB = 0x02;
			break;
		case PB0ONWAIT:
			PORTB = 0x01;
			break;
		default:
			break;
		
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0x00; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x01; // Configure port B's 8 pins as inputs
    /* Insert your solution below */
	state = start;   
	while (1) {
		tick();
    	}
   	 return 1;
}
