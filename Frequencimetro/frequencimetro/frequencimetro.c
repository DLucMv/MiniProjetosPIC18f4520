#include <p18f4520.h>

#pragma config	OSC = INTIO67
#pragma config	WDT = OFF
#pragma config	MCLRE = ON
#pragma config	PBADEN = OFF
#pragma config	BORV = 3

int contador;
int temporizador;
int dezenas;
int unidades;
float multi;
int freq;
int t = 0;
int k = 0;
int C1[4];
int C2[4];
	
void delay_s (int segundos)
{
	unsigned long int i;
	for (;segundos>0;segundos--)
	{
		for (i=0;i<83333;i++) {};
	}
}

void delay_ms (int ms)
{
	unsigned long int i;
	for (;ms>0;ms--)
	{
		for (i=0;i<80;i++) {};
	}
}
void delay_us (int us)
{
	unsigned char i;
		for (i=0;i<28;i++) {};
		i=0;
}
void reseta ()
{
	unsigned long int i;
	for (i=0;i<4;i++) {
		C1[i] = 0;
		C2[i] = 0;
	};
}

void frequency(int temporizador){	
	t=0;
	k=0;
	reseta();

	multi = (temporizador);
	freq = (10000 / multi);
	if(freq == 100){
		freq = 10;
	}
	dezenas = (freq/10);
	unidades = (freq%10);

		while(dezenas > 0)
	{
		C1[t] = dezenas % 2;
		t++;
		dezenas = dezenas / 2;
	}
		while(unidades > 0)
	{
		C2[k] = unidades % 2;
		k++;
		unidades = unidades / 2;
	}

   	LATCbits.LATC0 = C2[0];
	LATCbits.LATC1 = C2[1];
	LATCbits.LATC2 = C2[2];
	LATCbits.LATC3 = C2[3];
	LATCbits.LATC4 = C1[0];
	LATCbits.LATC5 = C1[1];
	LATCbits.LATC6 = C1[2];
	LATCbits.LATC7 = C1[3];	
}	

void main ()

{	
	ADCON1 = 0B00001111;
	//BIT=1 -> PORTA DE ENTRADA, BIT=0 -> PORTA DE SAÍDA
	TRISA = 0B00000001;	
	TRISC = 0B00000000;		
	
	OSCCONbits.IRCF2 = 1;
	OSCCONbits.IRCF1 = 1;
	OSCCONbits.IRCF0 = 1;	//OSC = 8MHz

	contador = 0;

	while (1)
	{	
		temporizador = 0;
		while(!PORTAbits.RA0){}
		while(PORTAbits.RA0){}
		while(!PORTAbits.RA0){
			delay_us(1);
			temporizador++;
		}
		while(PORTAbits.RA0){
			delay_us(1);
			temporizador++;
		}
		frequency(temporizador);
	}
}
