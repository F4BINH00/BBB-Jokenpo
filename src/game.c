/*
 * =====================================================================================
 *
 *       Filename:  game.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  22/07/2025 10:50:03
 *       Revision:  none
 *       Compiler:  arm-none-eabi-gcc
 *
 *         Author: Fábio Filho & Rodrigo Albuquerque 
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

#include "game.h"
#include "timers.h"

void start_memory();

char msn[] = "PARABENS JOGADOR, VOCE GANHOU\n\r";
unsigned int escolha = 0;
unsigned int CPU = 1;
unsigned int pontuacao = 0;
unsigned int rodada = 1;

unsigned int cpu_seed = 0xcafebabe;

unsigned int xorshift32(){
    cpu_seed ^= cpu_seed << 13;
    cpu_seed ^= cpu_seed >> 17;
    cpu_seed ^= cpu_seed << 5;
    return cpu_seed;
}


bool continua = true, pause = true;
unsigned pos_x = 0, pos_y = 0,pos_x_ant, pos_y_ant;

int ordenou(unsigned int game_easy[3][3]){

    if((game_easy[0][0] == 1)&(game_easy[0][1] == 2)&(game_easy[0][2] == 3)
    &(game_easy[1][0] == 4)&(game_easy[1][1] == 5)&(game_easy[1][2] == 6)
    &(game_easy[2][0] == 7)&(game_easy[2][1] == 8)&(game_easy[2][2] == 0))
        return 1;
    return 0;
    
}
void print_game(unsigned int game_easy[3][3]){

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            putCh(UART0,game_easy[i][j]+'0');
            putCh(UART0,' ');
        }
        putString(UART0,"\n\r",2);
    }
    
}

void start_game(char c){

    switch(c){
        case '1':
            start_memory();
        break;

        case '2':
        break;

    }

}

void start_memory(){
    unsigned int game_easy[3][3] = {{0,5,3},
                                    {4,2,8},
                                    {1,6,7}};
    putString(UART0,"______|DEIXE NA SEQUENCIA CORRETA|______\n\r",42);
    delay(1000,TIMER7);

    while(continua){

        putString(UART0,"\033[H\033[J\r", 8);
        pause = true;
        print_game(game_easy);
        while(pause);

        unsigned int aux = game_easy[pos_y_ant][pos_x_ant];
        game_easy[pos_y_ant][pos_x_ant] = game_easy[pos_y][pos_x];
        game_easy[pos_y][pos_x] = aux;

        if(ordenou(game_easy)) continua = false;

    }
    putString(UART0,"\033[H\033[J\r", 8);
    print_game(game_easy);
    for(int i = 0; i < 31; i++){
        putCh(UART0,msn[i]);
        delay(200,TIMER7);
    }
}

void up(){

    pos_y_ant = pos_y;
    pos_x_ant = pos_x;
    pos_y--;
    if(pos_y < 0) pos_y = 0;

    pause = false;

}

void down(){

    pos_y_ant = pos_y;
    pos_x_ant = pos_x;
    pos_y++;
    if(pos_y > 2) pos_y = 2;

    pause = false;

}

void left(){

    pos_y_ant = pos_y;
    pos_x_ant = pos_x;
    pos_x--;
    if(pos_x < 0) pos_x = 0;

    pause = false;

}

void right(){

    pos_y_ant = pos_y;
    pos_x_ant = pos_x;
    pos_x++;
    if(pos_x > 2) pos_x = 2;
    pause = false;

}

void print_pontuacao(unsigned int pontuacao){
	int num;
    int cont = 0;
    char str[5];
    if (pontuacao == 0){
        putCh(UART0,'0');
    }else{
        while(pontuacao > 0){
            num = pontuacao%10;
            pontuacao = pontuacao/10;
            str[cont] = num+'0';
            cont++;
        }
        for(int i = cont-1; i >= 0; i--)
            putCh(UART0,str[i]);
    }
	
	putString(UART0,"\n\r",3);
}

void jokenpo_start_application(void) {
    escolha = 0;
    pontuacao = 0;
    putString(UART0, "\n\r A partir de agora o jogo iniciou\n\r", 37);
    while(1){
        CPU = (xorshift32()%3)+1; // Gera um número aleatório entre 1 e 3
        escolha = 0;
        for(int i = 3; i >= 0; i--) {
            putString(UART0,"Rodada ",7);
            print_pontuacao(rodada);
            menu_escolha();
            putString(UART0, "Voce tem ", 10);
            putCh(UART0, i + '0');
            putString(UART0, " segundos para fazer a sua escolha...", 39);
            delay(1500, TIMER7);
            limpar();
        }
        if(((escolha == 1) && (CPU == 3)) || ((escolha == 2) && (CPU == 1)) || ((escolha == 3) && (CPU == 2))){
            pontuacao += 2;

            GpioSetPinValue(GPIO1, 15, HIGH);  // LED jogador venceu

            limpar();
            if(escolha == 1) {
                putString(UART0, "Joagador escolheu PEDRA e a CPU escolheu TESOURA\n\r", 50);
            } else if(escolha == 2) {
                putString(UART0, "Jogador escolheu PAPEL e a CPU escolheu PEDRA\n\r", 47);
            } else {
                putString(UART0, "Jogador escolheu TESOURA e a CPU escolheu PAPEL\n\r", 49);
            }
            putString(UART0, "Jogador venceu a rodada\n\r", 25);
            putString(UART0, "Pontuação atual: ",19);
            print_pontuacao(pontuacao);

        }else if(escolha == CPU){
            pontuacao += 1;
            GpioSetPinValue(GPIO1, 13, HIGH); // LED empate
            limpar();
            if(escolha == 1) {
                putString(UART0, "Joagador escolheu PEDRA e a CPU escolheu PEDRA\n\r", 48);
            } else if(escolha == 2) {
                putString(UART0, "Jogador escolheu PAPEL e a CPU escolheu PAPEL\n\r", 47);
            } else {
                putString(UART0, "Jogador escolheu TESOURA e a CPU escolheu TESOURA\n\r", 51);
            }
            putString(UART0, "Jogador empatou a rodada\n\r", 26);
            putString(UART0, "Pontuação atual: ",19);
            print_pontuacao(pontuacao);  
        }else {
            limpar();
            GpioSetPinValue(GPIO1, 17, HIGH);  // LED CPU venceu
            if(escolha == 1) {
                putString(UART0, "Joagador escolheu PEDRA e a CPU escolheu PAPEL\n\r", 48);
            } else if(escolha == 2) {
                putString(UART0, "Jogador escolheu PAPEL e a CPU escolheu TESOURA\n\r", 49);
            } else {
                putString(UART0, "Jogador escolheu TESOURA e a CPU escolheu PEDRA\n\r", 49);
            }
            putString(UART0, "Jogador perdeu a rodada\n\r", 25);
            putString(UART0, "Pontuação final: ",19);
            print_pontuacao(pontuacao);
            putString(UART0 ,"GAME OVER!!! \n\r", 13);
            delay(4500,TIMER7);
            break;
        }
        rodada++;
        delay(4000,TIMER7);
        GpioSetPinValue(GPIO1, 15, LOW);  // Desliga LED jogador venceu
        GpioSetPinValue(GPIO1, 13, LOW);  // Desliga LED empate
        GpioSetPinValue(GPIO1, 17, LOW);  // Desliga LED CPU venceu
        limpar();
    }
}