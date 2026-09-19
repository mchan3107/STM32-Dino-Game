#ifndef STM32F407XX_TIMER_DRIVER_H
#define STM32F407XX_TIMER_DRIVER_H
#include <stm32f407xx.h>

/*Timer base unit configuration structure*/
typedef struct
{
    uint32_t Period;
    uint16_t Prescaler;
    uint8_t AutoReloadPreload;
    uint8_t CounterMode;
} TIM_Base_Conf_t;

/*Output compare configuration structure*/
typedef struct
{
    uint32_t Pulse;        /* Specifies the pulse value to be loaded into the Capture Compare Register.
                              This parameter can be a number between Min_Data = 0x00000000 and Max_Data = 0xFFFFFFFF*/

    uint8_t OCMode;        /* Specifies the TIM mode.
                              This parameter can be a value of @ref TIM_Output_Compare_and_PWM_modes*/

    uint8_t OCPolarity;    /* Specifies the output polarity.
                              This parameter can be a value of @ref TIM_Output_Compare_Polarity*/

} TIM_OC_Conf_t;

/*Output compare channel*/
#define TIM_OC_CHANNEL_1 0U
#define TIM_OC_CHANNEL_2 1U
#define TIM_OC_CHANNEL_3 2U
#define TIM_OC_CHANNEL_4 3U


/*TIM_AutoReloadPreload*/
#define TIM_AUTORELOAD_PRELOAD_DISABLE    0U
#define TIM_AUTORELOAD_PRELOAD_ENABLE     1U

/* TIM_CounterMode */
#define TIM_UPCOUNTING      0U    /*TIMx upcounting mode selection */
#define TIM_DOWNCOUNTING    1U    /*TIMx downcounting mode selection */


/*TIM_Output_Compare_and_PWM_modes*/
#define TIM_OCMODE_TIMING           0U    /* Frozen - The comparison between the output compare register TIMx_CCRx and the
                                             counter TIMx_CNT has no effect on the outputs (this mode is used to generate a timing base) */

#define TIM_OCMODE_ACTIVE           1U    /* Set channel x to active level on match. OCxREF signal is forced high when the counter
                                             TIMx_CNT matches the capture/compare register x (TIMx_CCRx). */

#define TIM_OCMODE_INACTIVE         2U    /* Set channel x to inactive level on match. OCxREF signal is forced low when the
                                             counter TIMx_CNT matches the capture/compare register x (TIMx_CCRx). */

#define TIM_OCMODE_TOGGLE           3U    /* Toggle - OCxREF toggles when TIMx_CNT = TIMx_CCRx. */

#define TIM_OCMODE_FORCED_INACTIVE  4U    /* Force inactive level - OCxREF is forced low. */

#define TIM_OCMODE_FORCED_ACTIVE    5U    /* Force active level - OCxREF is forced high. */

#define TIM_OCMODE_PWM1             6U    /* PWM mode 1 */

#define TIM_OCMODE_PWM2             7U    /* PWM mode 2 */

/*TIM_Output_Compare_Polarity*/
#define TIM_OCPOLARITY_HIGH 0U
#define TIM_OCPOLARITY_LOW  1U


/*TIMx CR1 register bits*/
#define TIM_CR1_ARPE    7U
#define TIM_CR1_CEN     0U
#define TIM_CR1_DIR     4


/*TIMx EGR register bits*/
#define TIM_EGR_UG      0U


/*TIMx SR register bit*/
#define TIM_SR_UIF      0U

/*TIMx DIER register bit*/
#define TIM_DIER_UIE    0U

/*Macros handle update event status*/
#define TIM6_UEV_STS()      ((TIM6->SR >> TIM_SR_UIF) & 0x01U)       /*Timer 6 - update event status*/
#define TIM6_UEV_STS_CLR()  (TIM6->SR &= ~(0x01 << TIM_SR_UIF))      /*Timer 6 - clear update event status*/

/*Macros handle output compare*/
#define TIM4_OC_PWM_SET_DUTY(Channel, CCR_value)    (TIM4->CCR[(Channel)] = (CCR_value))

/*Macro to map IRQn to TIMx*/
#define TIMX_TO_IRQ(TIMx) \
    ((TIMx == TIM6) ? IRQ_NO_TIM6_DAC : \
     (TIMx == TIM7) ? IRQ_NO_TIM7 : IRQ_NO_TIM6_DAC)

void TIM_Base_Init(TIM_RegDef_t * TIMx, TIM_Base_Conf_t TIM_BaseConf);
void TIM_Base_Start(TIM_RegDef_t * TIMx);
void TIM_Base_Stop(TIM_RegDef_t * TIMx);
void TIM_Base_IT_Init(TIM_RegDef_t * TIMx, uint8_t Priority);
void TIM_OC_Init(TIM_RegDef_t * TIMx, TIM_OC_Conf_t TIM_OCConf, uint8_t Channel);

#endif