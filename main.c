#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <p30fxxxx.h>
#include "uart_driver.h"
#include "timer2.h"


_FOSC(CSW_FSCM_OFF & XT_PLL4); // instrukcioni takt je isti kao i kristal
_FWDT(WDT_OFF);

static float ms = 0;

void __attribute__ ((__interrupt__)) _T2Interrupt(void) // svakih 1ms
{

	TMR2 = 0;
    
	ms++;

	IFS0bits.T2IF = 0; 
       
}

void Delay_ms (float stop)//funkcija za kasnjenje u milisekundama
	{
		ms = 0;
		while(ms < stop);
	}



void testIt(float tmp)
{
	//test timing
    PORTDbits.RD0 = 1;
    Delay_ms(tmp);
    PORTDbits.RD0 = 0;
	Delay_ms(20 - tmp);
}

float strToF(char *str, int len, float num);
{
	int br = 0;
	float tmp
	
	float a = str[0] - 48;
	
	float b = (str[2] - 48)/10.0;
	float c = (str[3] - 48)/100.0;
	
	return a+b+c;
	
	
}

void main(void)
{
	TRISDbits.RD0 = 0; //pwn 
	TRISDbits.RD1 = 1; //control

	
	initT2();
	
	uartInit();
	uartWrite("START\n");
	
	float test_pwm = 0;
	int flag;
	char str[64];
	
	while(1)
	{
		while(uartAvailable() == 0); //cekamo upis
        Delay_ms(20);
		
		uartReadString(str);
		Delay_ms(10);
		test_pwm = strToF(str);
		
		//test
		Delay_ms(500);
		usartWrite("TESTING\r\n");
		testIt(test_pwm);
		Delay_ms(1500);
		
		
	}
	
	
	
	
}