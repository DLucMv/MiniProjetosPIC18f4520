#include <p18f4520.h>

#pragma config	OSC = INTIO67
#pragma config	WDT = OFF
#pragma config	MCLRE = ON
#pragma config	PBADEN = OFF
#pragma config	BORV = 3

#define botao_mode 			PORTAbits.RA0
#define botao_hourSet      	PORTAbits.RA1
#define botao_minuteSet    	PORTAbits.RA2
#define buzzer		       	LATAbits.LATA3
	

void delay_s (int);
void iniciar (void);
void relogio(void);
void mostra_seg(void);
void mostra_min(void);
void mostra_h(void);
void ajuste_minuto (void);
void ajuste_hora (void);
void alarme(void);
void mode(void);

unsigned char 	hora_dezena, hora_unidade, minuto_dezena,
 				minuto_unidade, segundo_dezena,
 				segundo_unidade, auxiliar_segundo,
 				auxiliar_minuto, auxiliar_hora;


void delay_s (int s)
{
	unsigned long int i;
	for ( ; s > 0; s--)
	{
		for (i=0;i<83333;i++) {};
	}
}

void iniciar (void){
	hora_dezena = 0;
	hora_unidade = 0;
	minuto_dezena = 0;
	minuto_unidade = 0;
	segundo_dezena = 0; 
	segundo_unidade = 0; 
}

void mostra_seg(void){
	auxiliar_segundo = segundo_dezena; //auxiliar_segundo = 0b00000000 saída da porta C.
	auxiliar_segundo = auxiliar_segundo << 4; //deslocado os 4 bits da dezena.
	auxiliar_segundo = auxiliar_segundo | segundo_unidade; //usa uma máscara (OR/OU) para formar o número.
	PORTC = auxiliar_segundo;
}

void mostra_min(void){
	auxiliar_minuto = minuto_dezena; 
	auxiliar_minuto = auxiliar_minuto << 4; 
	auxiliar_minuto = auxiliar_minuto | minuto_unidade; 
	PORTB = auxiliar_minuto;
}

void mostra_h(void){
	auxiliar_hora = hora_dezena; 
	auxiliar_hora = auxiliar_hora << 4; 
	auxiliar_hora = auxiliar_hora | hora_unidade; 
	PORTD = auxiliar_hora;
}

void relogio(void){
	
	
	/*if(auxiliar_hora == 0b00100100){
		hora_unidade = 0;
		hora_dezena = 0;
	}*/

	if(auxiliar_hora == 0b00100011 && auxiliar_minuto == 0b01011001 && auxiliar_segundo == 0b01011001){
		hora_dezena = 0;
		hora_unidade = 0;
		minuto_dezena = 0;
		minuto_unidade = 0;
		segundo_dezena = 0; 
		segundo_unidade = 0;
	}


	//ajuste_minuto();
	//ajuste_hora();

	segundo_unidade++;
	if (segundo_unidade == 10){
		segundo_unidade = 0;
		segundo_dezena++;
		if(segundo_dezena == 6){
			segundo_unidade = 0;
			segundo_dezena = 0;
			minuto_unidade++;
			if(minuto_unidade == 10){
				minuto_unidade = 0;
				minuto_dezena++;
				if(minuto_dezena == 6){
					minuto_unidade = 0;
					minuto_dezena = 0;
					hora_unidade++;
					if(hora_unidade == 10){
						hora_unidade = 0;
						hora_dezena++;
					
					}
						
				}
					
			}
					
		}
				
	}
}

void alarme(void){
}

void mode(void){
	int contador = 0;
	int contador_saida = 0;
	while(botao_mode == 1){
		delay_s(1);
		contador++;		
	}
	if(contador > 2){
		contador = 0;
		while(contador_saida < 2){
			ajuste_minuto();
			mostra_min();
			ajuste_hora();
			mostra_h();
			while(botao_mode == 1){
				contador_saida++;		
			}
			if(contador_saida > 2){
					break;
			}
		}
	}	
		
}

void ajuste_minuto (void){
	
	if (botao_minuteSet == 1){
		while(botao_minuteSet){};
		minuto_unidade++;
		if(minuto_unidade == 10){
			minuto_unidade = 0;
			minuto_dezena++;
		}
		if(minuto_dezena == 6){
			minuto_dezena = 0;
			minuto_unidade = 0;
		}
	}
}

void ajuste_hora (void){

	if (botao_hourSet == 1){
		while (botao_hourSet) {};
		hora_unidade++;
		if(hora_unidade == 10){
			hora_unidade = 0;
			hora_dezena++;	
		}
		if(hora_dezena == 2 && hora_unidade == 4){	
			hora_dezena = 0;
			hora_unidade = 0;		
		}
	}
}



main ()

{	

	//área de configuração (só roda uma vez)
	ADCON1 = 0B00001111;//Configura com portas IO.

	OSCCONbits.IRCF2 = 1;
	OSCCONbits.IRCF1 = 1;
	OSCCONbits.IRCF0 = 1;	//OSC = 8MHz (interno)
	
	//BIT=1 -> PORTA DE ENTRADA, BIT=0 -> PORTA DE SAÍDA
	TRISA=0B00000111;	
	TRISB=0B00000000;	//
	TRISC=0B00000000;	// 
	TRISD=0B00000000;	//
	//TRISAbits.RA0 = 1;
	//TRISAbits.RA1 = 1;
	//TRISAbits.RA2 = 1;
	//TRISAbits.RA3 = 0;


	iniciar();

	while(1){
		mode();
		mostra_seg();
		mostra_min();
		mostra_h();
		delay_s(1);
		relogio();
	}
	

}
