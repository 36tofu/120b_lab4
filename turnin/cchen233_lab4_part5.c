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

enum states { START, LOCK, WAITRISE, WAITFALL, UNLOCK } state;

unsigned char tmpA;
unsigned char seq_success;
unsigned char seq_fail;
unsigned char cnt;
unsigned char lock_status;

void tick()
{	//transitions
	tmpA = PINA & 0x87;
	switch(state){
		case START:
			state = LOCK;
			break;
		case LOCK:
			if(tmpA == 0x80 )
				state = WAITRISE;
			break;
		case WAITRISE:
			if(tmpA == 0)
				state = WAITRISE;
			else if (tmpA == 0x80) 
				state = LOCK;
			else {
				state = WAITFALL;
				cnt  = cnt + 1;
			}
			break;
		case WAITFALL:
			if(seq_success){
				if( lock_status == 0) {
					state = LOCK;
				} else {
					state = UNLOCK;
				}
			} else if (seq_fail == 1) {
				if( lock_status == 0) {
					state = UNLOCK;
				} else {
					state = LOCK;
				}
			} else if (tmpA != 0)
				state = WAITFALL;
			else if( tmpA == 0 )
				state = WAITRISE;
			break;
		case UNLOCK:
			if(tmpA != 0x00)
				state = UNLOCK;
			else 
				state = WAITRISE;
			break;
		default:
			state = START;
			break;
		
	}
	//state actions
	switch(state){
		case START:
			break;
		case LOCK:
			seq_success = 0;
			seq_fail = 0;
			cnt = 0;
			lock_status = 1;
			break;
		case WAITRISE:
			break;
		case WAITFALL:
			// cnt ++;
			switch(cnt){
				case 1: if (tmpA != 4) seq_fail = 1; break; //#
				case 2: if (tmpA != 1) seq_fail = 1; break; //X
				case 3: if (tmpA != 2) seq_fail = 1; break; //Y
				case 4: if (tmpA == 1) seq_success = 1;     //X
					else seq_fail = 1;	
				        break; 
			}
			break;
		case UNLOCK:
			seq_success = 0;
			seq_fail = 0;
			cnt = 0;
			lock_status = 0;
			break;
		default:
			state = START;
			break;
	PORTB = (lock_status == 1) ? 0x00 : 0x01;
	PORTC = state;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0x00; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port B's 8 pins as inputs
    /* Insert your solution below */
	state = START;   
	while (1) {
		tick();
    	}
   	 return 1;
}
