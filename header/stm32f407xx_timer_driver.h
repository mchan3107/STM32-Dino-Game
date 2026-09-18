#ifndef STM32F407XX_TIMER_DRIVER_H
#define STM32F407XX_TIMER_DRIVER_H
#include <stm32f407xx.h>

/*Timer base unit configuration structure*/
typedef struct
{
    uint32_t Period;
    uint16_t Prescaler;
    uint8_t AutoReloadPreload;
} TIM_Base_Conf_t;


/*TIM_AutoReloadPreload*/
#define TIM_AUTORELOAD_PRELOAD_DISABLE    0U
#define TIM_AUTORELOAD_PRELOAD_ENABLE     1U


/*TIMx CR1 register bits*/
#define TIM_CR1_ARPE    7U
#define TIM_CR1_CEN     0U


/*TIMx EGR register bits*/
#define TIM_EGR_UG      0U


/*TIMx SR register bit*/
#define TIM_SR_UIF      0U

/*Macros handle update event status*/
#define TIM6_UEV_STS()      ((TIM6->SR >> TIM_SR_UIF) & 0x01U)       /*Timer 6 - update event status*/
#define TIM6_UEV_STS_CLR()  (TIM6->SR &= ~(0x01 << TIM_SR_UIF))      /*Timer 6 - clear update event status*/

void TIM_Base_Init(TIM_RegDef_t * TIMx, TIM_Base_Conf_t TIM_BaseConf);
void TIM_Base_Start(TIM_RegDef_t * TIMx);
void TIM_Base_Stop(TIM_RegDef_t * TIMx);

#endif