#ifndef _BSP_EXERCISE_H
#define _BSP_EXERCISE_H


#include "gd32f4xx.h"
#include "systick.h"
#include "gd32f4xx_gpio.h"

typedef enum
{
	LED1=0,
	LED2=1,
	LED3=2,
	LED4=3,
}led_type;

static uint32_t LED_PORT[4]={GPIOE,GPIOD,GPIOG,GPIOA};
static uint32_t LED_PIN[4]={GPIO_PIN_3,GPIO_PIN_7,GPIO_PIN_3,GPIO_PIN_5};
static uint32_t LED_RCU[4]={RCU_GPIOE,RCU_GPIOD,RCU_GPIOG,RCU_GPIOA};

static bit_status key=SET;
static uint16_t direct = 0;
static uint16_t value = 0;

void led_config(led_type ledx);
void timer2_config(uint32_t pre,uint32_t per);
void timer5_config(uint32_t pre,uint32_t per);
void key_config(void);
void pwm_config(uint32_t pre,uint32_t per);




#endif



