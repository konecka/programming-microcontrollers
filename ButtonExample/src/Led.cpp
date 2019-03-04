/*
 * Led.cpp
 *
 *  Created on: 2 мар. 2019 г.
 *      Author: konet
 */

#include "Led.h"

Led::Led(uint16_t pin, GPIO_TypeDef * port) {
	// TODO Auto-generated constructor stub
	this->pin = pin;
	this->port = port;

	this->initStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	this->initStruct.GPIO_Pin = this->pin;
	this->initStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(this->port, &initStruct);
}


void::Led::On() {
	GPIO_WriteBit(this->port, this->pin, Bit_SET);
}

void::Led::Off() {
	GPIO_WriteBit(this->port, this->pin, Bit_RESET);
}

void::Led::ConvertState() {
	GPIOB->ODR ^= this->pin;
}
