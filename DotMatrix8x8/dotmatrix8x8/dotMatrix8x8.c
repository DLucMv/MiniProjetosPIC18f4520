#include <p18f4520.h>

#pragma config	OSC = INTIO67
#pragma config	WDT = OFF
#pragma config	MCLRE = ON
#pragma config	PBADEN = OFF
#pragma config	BORV = 3
	

void delay_ms (int);
void delay_s (int);
void delay_us (int);


void delay_s (int s)
{
	unsigned long int i;
	for ( ; s > 0; s--)
	{
		for (i=0;i<83333;i++) {};
	}
}


void delay_ms(int ms)

{
	unsigned int i;
	for ( ;ms > 0; ms--)
	{
		for (i=0;i<80;i++) {}		//tempo de loop = 1ms
	}
}

void delay_us(int us)	//funciona a partir de 10us
{
	unsigned char i;
	for ( ;us > 0; us--){
		for (i=0;i<28;i++) {};
	};
	i=0;
}

char mensagem [] = {
	//hgfedcba
	0B11111111,
	0B11111111,
	0B11111111,
	0B11111111,
	0B11111111,
	0B11111111,
	0B11111111, 
	0B11111111, // bloco de 8 x00
	0B11111111,
	0B11111111,
	0B11111111,
	0B11111111,
	0B11111111,
	0B11111111,
	0B11111111, 
	0B11111111, // bloco de 8 x00
	0B00000000,
	0B11101111,
	0B11101111,
	0B11101111,
	0B00000000,
	0B11111111,
	0B11111111,
	0B00000000, // bloco de 8 x01 
	0B00101100,
	0B00101100,
	0B11111111,
	0B11111111,
	0B00000000,
	0B01100111,
	0B01100111,
	0B10011000, // bloco de 8 x02
	0B11111111, 
	0B11111111,	
	0B00000000, 
	0B01111110,
	0B01111110,
	0B00000000,
	0B11111111,
	0B11111111,	// bloco de 8 x03
	0B00000000,
	0B11111111,	
	0B11111111,
	0B10001110, 
	0B01101110, 
	0B01101110,
	0B01110001,
	0B11111111, // bloco de 8 x04
	0B11111111,
	0B11111111,
	0B11111111,
	0B11111111, 
	0B11111111, 
	0B11111111,
	0B11111111,
	0B11111111, // bloco de 8 x05
	0B11111111, 
	0B11111111,
	0B11111111,
	0B11111111,
	0B11111111, 
	0B11111111, 
	0B11111111,
	0B11111111, // bloco de 8 x06
	
};


main ()

{	

	//área de configuração (só roda uma vez)
	ADCON1 = 0B00001111; // Seta portas 0, 1, 2 e 3 como analogicas

	OSCCONbits.IRCF2 = 1;
	OSCCONbits.IRCF1 = 1;
	OSCCONbits.IRCF0 = 1;	//OSC = 8MHz (interno)
	
	//BIT=1 -> PORTA DE ENTRADA, BIT=0 -> PORTA DE SAÍDA
	TRISB=0B00000000;	//Varredura das colunas
	TRISC=0B00000000;	//dotMatrix1 linhas 
	TRISD=0B00000000;	//dotMatrix2 linhas

	while(1){
		unsigned long int i;
		for(i = 0;i < 48;i++){

			delay_ms(16);

			LATB = 0B00000000;
			LATC = mensagem [i + 8];
			LATD = mensagem [i];
			LATB = 0B00000001;
			delay_ms(10);

			LATB = 0B00000000;
			LATC = mensagem [i + 9];
			LATD = mensagem [i + 1];
			LATB = 0B00000010;
			delay_ms(10);

			LATB = 0B00000000;
			LATC = mensagem [i + 10];
			LATD = mensagem [i + 2];
			LATB = 0B00000100;
			delay_ms(10);

			LATB = 0B00000000;
			LATC = mensagem [i + 11];
			LATD = mensagem [i + 3];
			LATB = 0B00001000;
			delay_ms(10);

			LATB = 0B00000000;
			LATC = mensagem [i + 12];
			LATD = mensagem [i + 4];
			LATB = 0B00010000;
			delay_ms(10);

			LATB = 0B00000000;
			LATC = mensagem [i + 13];
			LATD = mensagem [i + 5];
			LATB = 0B00100000;
			delay_ms(10);

			LATB = 0B00000000;
			LATC = mensagem [i + 14];
			LATD = mensagem [i + 6];
			LATB = 0B01000000;
			delay_ms(10);

			LATB = 0B00000000;
			LATC = mensagem [i + 15];
			LATD = mensagem [i + 7];
			LATB = 0B10000000;
			delay_ms(10);

		}
	}
	

}
