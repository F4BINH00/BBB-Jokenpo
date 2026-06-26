/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  19/07/2025 20:05:55
 *       Revision:  none
 *       Compiler:  arm-none-eabi-gcc
 *
 *         Author:  Fábio Filho & Rodrigo Albuquerque (fabiorbfilho@alu.ufc.br; rodrigo.santos@alu.ufc.br)
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

 /*Para o projeto final da disciplina de Técnicas de Programação para Sistemas Embarcados (TPSE), adotamos uma estratégia de modularização
  e reaproveitamento de código. Utilizamos a arquitetura de um projeto de jogo preexistente como um framework base. Sobre essa estrutura, 
  que efetivamente funciona como um contêiner para múltiplos jogos, a gente se concentrou no desenvolvimento e integração de um novo módulo 
  de jogo do zero: o Jokenpô (Pedra, Papel e Tesoura). Portanto, embora o sistema final suporte outras funcionalidades, a ênfase e o escopo 
  principal do nosso trabalho nesta disciplina foram a concepção e implementação completa do Jokenpô.*/
#include	"gpio.h"
#include 	"interruption.h"
#include 	"timers.h"
#include 	"uart.h"
#include	"game.h"
#include 	"menus.h"
//#define DELAY_USE_INTERRUPT			1


/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
void ledON(gpioMod, ucPinNumber, ucPinNumber);
void ledOFF(gpioMod,  ucPinNumber, ucPinNumber );
int button_press(gpioMod, ucPinNumber);
void mode_led(mode);
bool tente = true;
extern unsigned int escolha;

/****************************************************************************
**				GLOBAL VARIABLES
****************************************************************************/
unsigned int opc_button1 = MODE0 , opc_button2 = MODE4, opc = MODE0, TIME = 100;


void disableWdt(void){
	HWREG(WDT_WSPR) = 0xAAAA;
	while((HWREG(WDT_WWPS) & (1<<4)));
	
	HWREG(WDT_WSPR) = 0x5555;
	while((HWREG(WDT_WWPS) & (1<<4)));
}


void ISR_Handler(void){

	/* Verify active IRQ number */
	unsigned int irq_number = HWREG(INTC_BASE+INTC_SIR_IRQ) & 0x7f;
	switch (irq_number)
	{
	case 98:
		if(HWREG(SOC_GPIO_1_REGS+GPIO_IRQSTATUS_RAW_0)&(1<<12)){
			putString(UART0,"Botao 1 pressionado\n\r",21);
			escolha = 1;
			gpioIsrHandler(GPIO1,0,12);
		}else if(HWREG(SOC_GPIO_1_REGS+GPIO_IRQSTATUS_RAW_0)&(1<<14)){
			putString(UART0,"Botao 2 pressionado\n\r",21);
			escolha = 2;
			gpioIsrHandler(GPIO1,0,14);
		}else{
			putString(UART0,"Botao 3 pressionado\n\r",21);
			escolha = 3;
			gpioIsrHandler(GPIO1,0,16);
		}
		
		break;
	/*outras interrupções logo aqui*/
	}
    
	/* acknowledge IRQ */
	HWREG(INTC_BASE+INTC_CONTROL) = 0x1;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */

int main(void)
{
	int count = 0;
	ucPinNumber up = 13, down = 12, left = 15, right = 14;
	Direction dir_led = OUTPUT, dir_button = INPUT;
	char r = '0';

	disableWdt();
	
	/*-----------------------------------------------------------------------------
	 *  initialize GPIO modules
	 *-----------------------------------------------------------------------------*/
	Init_module_gpio(GPIO1);
	
	/*-----------------------------------------------------------------------------
	 *  initialize TIMERS modules
	 *-----------------------------------------------------------------------------*/
	timerSetup(TIMER7);

	/*-----------------------------------------------------------------------------
	 *  Initialize interruption gpio_1_Int_A and gpio_1_int_B
	 *-----------------------------------------------------------------------------*/
	Interrupt_Setup(98); //gpio1_A interruption

#ifdef DELAY_USE_INTERRUPT
	Interrupt_Setup(95); // timers interruption on DMTIMER7
#endif
		
	/*-----------------------------------------------------------------------------
	 *  Set pin for interruption
	 *-----------------------------------------------------------------------------*/
	Pin_Interrup_Config(GPIO1,12,0); // interruption 98
	Pin_Interrup_Config(GPIO1,14,0); // interruption 98
	Pin_Interrup_Config(GPIO1,16,0); // interruption 98

	/*-----------------------------------------------------------------------------
	 *  Init pin function gpio INPUT/OUTPUT
	 *-----------------------------------------------------------------------------*/
	Init_pin_gpio(GPIO1,13,OUTPUT); //Led de empate p8_11
	Init_pin_gpio(GPIO1,15,OUTPUT);//Led jogador venceu p8_15
	Init_pin_gpio(GPIO1,17,OUTPUT); //Led cpu venceu p9_23

	Init_pin_gpio(GPIO1,12,INPUT); //Botao 1 PEDRA p8_12
	Init_pin_gpio(GPIO1,14,INPUT); //Botao 2 PAPEL p8_16
	Init_pin_gpio(GPIO1,16,INPUT); //Botao 3 TESOURA p9_15

	while(1){
		limpar();
		menu_principal();
		char a = getCh(UART0);

		if(a == '1'){
			limpar();
			jokenpo_start_application();
		}else if(a == '2'){
			limpar();
			menu_como_jogar();
		}else{
			limpar();
			putString(UART0,"\n\rOpcao invalida, tente novamente.\n\r",36);
			delay(2000,TIMER7);
			continue;
		}

	}

	return 0;

} // end of function main

