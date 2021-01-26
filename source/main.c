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

enum states { start, lock, pound, waitY, unlock, lpound, ly } state;

unsigned char tmpA;

void tick()
{	//transitions
	tmpA = PINA & 0x87;
	switch(state){
		case start:
			state = lock;
			break;
		case lock:
			if(tmpA == 4)
				state = pound;
			else 
				state = lock;
			break;
		case pound:
			if(tmpA == 4)
				state = pound;
			else if(tmpA == 0)
				state = waitY;
			break;
		case waitY:
			if(tmpA == 0)
				state = waitY;
			else if(tmpA == 2)
				state = unlock;
			else
				state = lock;
			break;
		case unlock:
			if(tmpA == 0x80)
				state = lock;
			else if(tmpA == 4)
				state = lpound;
			else 
				state = unlock;
			break;
		case lpound:
			if(tmpA == 4)
				state = lpound;
			else if(tmpA == 0)
				state = ly;
			break;
		case ly:
			if(tmpA == 0)
				state = ly;
			else if(tmpA == 2)
				state = lock;
			else
				state = unlock;
			break;
		default:
			state = start;
			break;
		
	}
	//state actions
	switch(state){
		case start:
			PORTB = 0;
			break;
		case lock:
			PORTB = 0;
			break;
		case pound:
			PORTB = 0;
			break;
		case waitY:
			PORTB = 0;
			break;
		case unlock:
			PORTB = 1;
			break;
		case lpound:
			PORTB = 1;
			break;
		case ly:
			PORTB = 1;
			break;
		default:
			break;
		
	}
	PORTC = state;
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0x00; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port B's 8 pins as inputs
    /* Insert your solution below */
	state = start;   
	while (1) {
		tick();
    	}
   	 return 1;
}
