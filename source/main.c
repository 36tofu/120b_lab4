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

enum states { start, WAITRISE, INC, DEC, WAITFALL, RESET } state;

unsigned char tmpC;
unsigned char tmpA;

void tick()
{
	tmpA = PINA & 0x03;
	switch(state){
		case start:
			state = WAITRISE;
			break;
		case WAITRISE:
			if((PINA & 0X03) == 0)
				state = WAITRISE;
			else if(tmpA == 1)
				state = INC;
			else if(tmpA == 2)
				state = DEC;
			break;
		case INC:
			state = WAITFALL;
			break;
		case DEC:
			state = WAITFALL;
			break;
		case WAITFALL:
			if((tmpA == 1)||(tmpA == 2))
				state = WAITFALL;
			else if(tmpA == 0)
				state = WAITRISE;
			else if(tmpA == 3)
				state = RESET;
			break;
		case RESET:
			if(tmpA == 0)
				state = WAITRISE;
			else
				state = RESET;
			break;
		default:
			state = start;
			break;
		
	}
	//state actions
	switch(state){
		case start:
			// tmpC = 0x07;
			break;
		case WAITRISE:
			break;
		case WAITFALL:
			break;
		case INC:
			if(tmpC < 0x09) tmpC = tmpC + 1;
			break;
		case DEC:
			if(tmpC > 0x00) tmpC = tmpC - 1;
			break;
		case RESET:
			tmpC = 0x00;
			break;
		default:
			break;
		
	}
	PORTC = tmpC;
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0x00; // Configure port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port B's 8 pins as inputs
    /* Insert your solution below */
	state = start;   
	tmpC = 0x07;
	while (1) {
		tick();
    	}
   	 return 1;
}
