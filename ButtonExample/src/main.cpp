/*
 * This file is part of the ВµOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "Led.h"

// ----------------------------------------------------------------------------
//
// Standalone STM32F1 empty sample (trace via DEBUG).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

// При нажатии на кнопку BTN3 увеличить частоту моргания светодиодом LED1, а при нажатии BTN2 уменшить.
int
main(int argc, char* argv[])
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef initStruct;

	Led led1(GPIO_Pin_9, GPIOB);
	Led led2(GPIO_Pin_8, GPIOB);
	Led led3(GPIO_Pin_5, GPIOB);

	initStruct.GPIO_Pin = GPIO_Pin_3;
	initStruct.GPIO_Pin = GPIO_Pin_2;
	initStruct.GPIO_Mode = GPIO_Mode_IPU;
	initStruct.GPIO_Speed = GPIO_Speed_2MHz;

	GPIO_Init(GPIOA, &initStruct);

	int w_counter = 0; // счетчик пройденных циклов
	float blink_speed = 50000; // скорость мигания
	int change_counter = 0; // "время" смены состяния светодиода

	led3.On(); //

	while (1)
    {
		w_counter++;

		if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)) {
			blink_speed+=0.1;
		}

		if (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)) {
			blink_speed-=0.1;
		}


		if (int(blink_speed) >=  5000000 || int(blink_speed) <= 0) {
			w_counter = blink_speed = change_counter = 0;
		}

		if(w_counter - change_counter > blink_speed) {
		    change_counter = w_counter;
		    led3.ConvertState();
		}
    }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
