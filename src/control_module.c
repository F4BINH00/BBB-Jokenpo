/*
 * =====================================================================================
 *
 *       Filename:  control_module.c
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


#include "control_module.h"
#include "soc_AM335x.h"
#include "hw_types.h" 

void cmSetCtrlModule(CONTROL_MODULE offset, unsigned int value)
{
   	HWREG(SOC_CONTROL_REGS + offset) |= value;
}

unsigned int cmGetCtrlModule(CONTROL_MODULE offset)
{
   	return(HWREG(SOC_CONTROL_REGS + offset));
}

