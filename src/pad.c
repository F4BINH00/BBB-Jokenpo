/*
 * =====================================================================================
 *
 *       Filename:  pad.c
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

#include "pad.h"
#include "control_module.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  padSetMode
 *  Description:  
 * =====================================================================================
 */
void padSetMode(CONTROL_MODULE offset, pinmode_t mode){
	if((offset <= CM_conf_usb1_drvvbus ) && (offset >= CM_conf_gpmc_ad0)){
		unsigned int temp = cmGetCtrlModule(offset);
      	temp &= ~(0b111);
      	temp |= mode;
      	cmSetCtrlModule(offset, temp);
   	}else{
      	// TODO: raise error (control module isnt a "conf <module> <pin>" register)
   	}
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  padGetMode
 *  Description:  
 * =====================================================================================
 */
pinmode_t padGetMode(CONTROL_MODULE offset){
	if((offset <= CM_conf_usb1_drvvbus ) && (offset >= CM_conf_gpmc_ad0)){
      	unsigned int temp = cmGetCtrlModule(offset);
      	//temp &= ~(0b111);
      	return ((pinmode_t) temp);
   	}else{
      	// TODO: raise error (control module isnt a "conf <module> <pin>" register)
   		return(-1);
   	}
}

