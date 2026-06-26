/*
 * =====================================================================================
 *
 *       Filename:  game.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  23/07/2025 10:50:03
 *       Revision:  none
 *       Compiler:  arm-none-eabi-gcc
 *
 *         Author: Fábio Filho & Rodrigo Albuquerque 
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */
#ifndef GAME_H_
#define GAME_H_
#include "uart.h"
#include "timers.h"
#include "menus.h"
#include "gpio.h"

void start_game(char);
void up();
void down();
void left();
void right();

void jokenpo_start_application(void);

#endif /*GAME_H_ */