#include "exercise.h"



void timer5_config(uint32_t pre,uint32_t per)
{
	timer_parameter_struct timer_struct;
	rcu_periph_clock_enable(RCU_TIMER5);
	rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
	
	timer_struct.prescaler = pre-1;
    timer_struct.alignedmode = TIMER_COUNTER_EDGE;
    timer_struct.counterdirection=TIMER_COUNTER_UP;
    timer_struct.clockdivision=TIMER_CKDIV_DIV1;
    timer_struct.period = per;
    timer_struct.repetitioncounter = 0;
	
	timer_deinit(TIMER5);
	timer_init(TIMER5,&timer_struct);
	nvic_irq_enable(TIMER5_DAC_IRQn,3,2);
	timer_interrupt_enable(TIMER5,TIMER_INT_UP);
	timer_enable(TIMER5);
}

void timer2_config(uint32_t pre,uint32_t per)
{
	timer_parameter_struct timer2_struct;
	rcu_periph_clock_enable(RCU_TIMER2);
	rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
	
	timer2_struct.prescaler = pre-1;
    timer2_struct.alignedmode = TIMER_COUNTER_EDGE;
    timer2_struct.counterdirection=TIMER_COUNTER_UP;
    timer2_struct.clockdivision=TIMER_CKDIV_DIV1;
    timer2_struct.period = per;
    timer2_struct.repetitioncounter = 0;
	
	nvic_irq_enable(TIMER2_IRQn,3,2);
	
	timer_deinit(TIMER2);
	timer_interrupt_enable(TIMER2,TIMER_INT_UP);
	timer_init(TIMER2,&timer2_struct);
	timer_enable(TIMER2);
	
}

void led_config(led_type ledx)
{
	rcu_periph_clock_enable(LED_RCU[ledx]);
	gpio_mode_set(LED_PORT[ledx],GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,LED_PIN[ledx]);
	gpio_output_options_set(LED_PORT[ledx],GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,LED_PIN[ledx]);
}

void TIMER5_DAC_IRQHandler(void)
{
	if(timer_interrupt_flag_get(TIMER5,TIMER_INT_FLAG_UP)==SET)
	{
		gpio_bit_toggle(LED_PORT[0],LED_PIN[0]);
		timer_interrupt_flag_clear(TIMER5,TIMER_INT_FLAG_UP);
	}
}

void TIMER2_IRQHandler(void)
{
	if(timer_interrupt_flag_get(TIMER2,TIMER_INT_FLAG_UP)==SET)
	{
		gpio_bit_toggle(LED_PORT[1],LED_PIN[1]);
		timer_interrupt_flag_clear(TIMER2,TIMER_INT_FLAG_UP);
	}
}

void pwm_config(uint32_t pre,uint32_t per)
{
//	rcu_periph_clock_enable(RCU_GPIOA);
//	gpio_mode_set(GPIOA,GPIO_MODE_AF,GPIO_PUPD_NONE,GPIO_PIN_5);
//	gpio_output_options_set(GPIOA,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_5);
//	gpio_af_set(GPIOA,GPIO_AF_2,GPIO_PIN_5);//选择复用
//	
//	timer_parameter_struct timer3_struct;
//	
//	timer3_struct.prescaler = pre-1;
//	timer3_struct.alignedmode = TIMER_COUNTER_EDGE;
//	timer3_struct.counterdirection=TIMER_COUNTER_UP;
//	timer3_struct.clockdivision=TIMER_CKDIV_DIV1;
//	timer3_struct.period = per;
//	timer3_struct.repetitioncounter = 0;
//	
//	rcu_periph_clock_enable(RCU_TIMER3);
//	rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
//	
//	
//	timer_deinit(TIMER3);
//	timer_init(TIMER3,&timer3_struct);
//	timer_enable(TIMER3);
//	
//	timer_oc_parameter_struct timer_parameter;
//	
//	timer_parameter.ocpolarity = TIMER_OCN_POLARITY_HIGH;
//	timer_parameter.outputstate = TIMER_CCX_ENABLE;
//	
//	timer_channel_output_config(TIMER3,TIMER_CH_0,&timer_parameter);
//	timer_channel_output_pulse_value_config(TIMER3,TIMER_CH_0,8000);
//	timer_channel_output_mode_config(TIMER3,TIMER_CH_0,TIMER_OC_MODE_PWM0);
//	timer_channel_output_shadow_config(TIMER3,TIMER_CH_0,TIMER_OC_SHADOW_DISABLE);
//	timer_auto_reload_shadow_enable(TIMER3);
	
	//GPIO配置
	rcu_periph_clock_enable(RCU_GPIOA);
	gpio_mode_set(GPIOA,GPIO_MODE_AF,GPIO_PUPD_NONE,GPIO_PIN_5);
	gpio_output_options_set(GPIOA,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_5);
	gpio_af_set(GPIOA,GPIO_AF_1,GPIO_PIN_5);//选择复用
	//
	timer_parameter_struct timer_pwm_initpara;//定义定时器结构体

	timer_pwm_initpara.prescaler = pre-1;  //结构体配置                      
	timer_pwm_initpara.alignedmode = TIMER_COUNTER_EDGE;                   
	timer_pwm_initpara.counterdirection = TIMER_COUNTER_UP;                  
	timer_pwm_initpara.clockdivision = TIMER_CKDIV_DIV1;                     
	timer_pwm_initpara.period = per;                        
	timer_pwm_initpara.repetitioncounter = 0; 
	
	rcu_periph_clock_enable(RCU_TIMER1);//开启定时器时钟
	rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);//配置分频器
	
	timer_deinit(TIMER1);
	timer_init(TIMER1,&timer_pwm_initpara);//定时器初始化
	timer_enable(TIMER1);//定时器开启
	
	timer_oc_parameter_struct timer_ocinitpara;//配置定时器输出结构体
	
	timer_ocinitpara.ocpolarity = TIMER_OCN_POLARITY_HIGH;
	timer_ocinitpara.outputstate = TIMER_CCX_ENABLE;
	
	timer_channel_output_config(TIMER1,TIMER_CH_0,&timer_ocinitpara);
	timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_0,0);//脉冲配置（占空比）
	timer_channel_output_mode_config(TIMER1,TIMER_CH_0,TIMER_OC_MODE_PWM0);//模式配置（pwm模式）
	timer_channel_output_shadow_config(TIMER1,TIMER_CH_0,TIMER_OC_SHADOW_DISABLE);//
	timer_auto_reload_shadow_enable(TIMER1);
	
}

void key_config(void)
{
	rcu_periph_clock_enable(RCU_GPIOA);
	gpio_mode_set(GPIOA,GPIO_MODE_INPUT,GPIO_PUPD_NONE,GPIO_PIN_0);
	
}


