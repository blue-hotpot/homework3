/*!
    \file    main.c
    \brief   led spark with systick

    \version 2023-06-25, V3.1.0, firmware for GD32F4xx
*/

/*
    Copyright (c) 2023, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32f4xx.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"
#include "exercise.h"

/*!
    \brief    main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
    systick_config();
	led_config(LED1);
	led_config(LED2);
	led_config(LED3);
	led_config(LED4);
	nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);
	timer5_config(20000,10000);
	//0.1ms
	timer2_config(20000,5000);
	pwm_config(200,10000);
	key_config();
    while(1) 
	{
		if(gpio_input_bit_get(GPIOA,GPIO_PIN_0)==SET)
		{
			delay_1ms(20);
			if(gpio_input_bit_get(GPIOA,GPIO_PIN_0)==SET)
			{
				key=(!key);
				gpio_bit_toggle(LED_PORT[LED3],LED_PIN[LED3]);
				while(gpio_input_bit_get(GPIOA,GPIO_PIN_0)==SET)
				{
				}
			}
		}
		
		if(key==SET)
		{
			if(direct==0)
			{
				value+=200;
				if(value>=10000)
					direct =1;
			}
			if(direct==1)
			{
				value-=200;
				if(value<=0)
					direct =0;
			}
		}
		timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_0,value);
		delay_1ms(50);
    }
}
