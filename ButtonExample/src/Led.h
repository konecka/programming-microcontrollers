/*
 * Led.h
 *
 *  Created on: 2 мар. 2019 г.
 *      Author: konet
 */

#ifndef LED_H_
#define LED_H_

#include "diag/Trace.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

class Led {
private:
	uint16_t pin;
	GPIO_TypeDef * port;
	GPIO_InitTypeDef initStruct;
public:
	Led(uint16_t pin, GPIO_TypeDef * port);

	void On();
	void Off();
	void ConvertState();
};



#endif /* LED_H_ */
