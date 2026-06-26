/*
 * =====================================================================================
 *
 *       Filename:  menus.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  20/07/2025 10:50:03
 *       Revision:  none
 *       Compiler:  arm-none-eabi-gcc
 *
 *         Author: Fábio Filho & Rodrigo Albuquerque 
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */
#include "menus.h"

void limpar(){
    putString(UART0,"\x1b[2J\x1b[H", 7);
}
void menu_principal(){
    putString(UART0,"\n\r==== BEM-VINDO AO JOKENPO BARE-METAL ====",43);
    putString(UART0,"\n\r1 - Start",11);
    putString(UART0,"\n\r2 - Como se joga",18);
    putString(UART0,"\n\rEscolha: ",11);
}

void menu_como_jogar() {
    putString(UART0, "\n\r===== COMO SE JOGA =====",26);
    putString(UART0, "\n\rO jogo e contra a CPU (computador).",37);
    putString(UART0, "\n\rUse os botoes fisicos conectados na BeagleBone:",49);
    putString(UART0, "\n\r - Botao 1: Pedra",19);
    putString(UART0, "\n\r - Botao 2: Papel",19);
    putString(UART0, "\n\r - Botao 3: Tesoura",21);

    putString(UART0, "\n\r\n\rA CPU escolhe aleatoriamente.",33);
    putString(UART0, "\n\rO resultado aparece via UART, e os LEDs indicam quem venceu:",62);

    putString(UART0, "\n\r - LED1 (GPIO1_13): Empate",28);
    putString(UART0, "\n\r - LED2 (GPIO1_15): Jogador venceu",37);
    putString(UART0, "\n\r - LED3 (GPIO1_17): CPU venceu",32);

    putString(UART0, "\n\r\n\rA cada rodada o placar e atualizado.",40);
    putString(UART0, "\n\r\n\rPressione qualquer tecla para voltar ao menu principal.",59);
    char r = getCh(UART0);
}

void menu_escolha(){
    putString(UART0,"Faça a sua escolha: PEDRA, PAPEL, TESOURA\n\r",44);
}

void menu_select_game(){
    putString(UART0,"_|_________|WELCOME TO GAME|________|_\n\r",40);
    putString(UART0,"_|___________|SELECT GAME|__________|_\n\r",40);
    putString(UART0," |                                  |\n\r",39);
    putString(UART0," |    1 - ORDENE A MATRIZ           |\n\r",39);
    putString(UART0," |    2 - NAVAL BATTLE              |\n\r",39);
    putString(UART0," |__________________________________|\n\r",39);
}

void menu_continua(){
    putString(UART0,"+++DESEJA JOGAR OUTRO JOGO+++\n\r",31);
    putString(UART0,"|                           |\n\r",31);
    putString(UART0,"|    1 - SIM                |\n\r",31);
    putString(UART0,"|    2 - NAO                |\n\r",31);
    putString(UART0,"|___________________________|\n\r",31);
}