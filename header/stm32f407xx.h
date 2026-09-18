#ifndef STM32F407XX_H
#define STM32F407XX_H
#include <stdint.h>
#include "cortexM4.h"

/* GPIO register definition struct */
typedef struct
{
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFRL;
    volatile uint32_t AFRH;
} GPIO_RegDef_t;

/*RCC register definition struct*/
typedef struct {
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t AHB3RSTR;
    uint32_t RESERVED0;
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    uint32_t RESERVED1[2];
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t AHB3ENR;
    uint32_t RESERVED2;
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
    uint32_t RESERVED3[2];
    volatile uint32_t AHB1LPENR;
    volatile uint32_t AHB2LPENR;
    volatile uint32_t AHB3LPENR;
    uint32_t RESERVED4;
    volatile uint32_t APB1LPENR;
    volatile uint32_t APB2LPENR;
    uint32_t RESERVED5[2];
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    uint32_t RESERVED6[2];
    volatile uint32_t SSCGR;
    volatile uint32_t PLLI2SCFGR;

} RCC_RegDef_t;

/* SYSCFG register definition */
typedef struct
{
    volatile uint32_t MEMRMP;
    volatile uint32_t PMC;
    volatile uint32_t EXTICR[4];
    volatile uint32_t CMPCR;
} SYSCFG_RegDef_t;

/* EXTI register definition struct */
typedef struct
{
    volatile uint32_t IMR;
    volatile uint32_t EMR;
    volatile uint32_t RTSR;
    volatile uint32_t FTSR;
    volatile uint32_t SWIER;
    volatile uint32_t PR;
} EXTI_RegDef_t;

/*USART register definition struct*/
typedef struct
{
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} USART_RegDef_t;

/*Timer register definition struct*/
typedef struct
{
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    uint32_t RESERVED0;
    volatile uint32_t DIER;
    volatile uint32_t SR;
    volatile uint32_t EGR;
    uint32_t RESERVED1[3];
    volatile uint32_t CNT;
    volatile uint32_t PSC;
    volatile uint32_t ARR;
} TIM_RegDef_t;

/* Peripheral base addresses */
#define AHB1_BASEADDR (0x40020000UL)
#define AHB2_BASEADDR (0x40010000UL)
#define APB1_BASEADDR (0x40000000UL)
#define APB2_BASEADDR (0x40010000UL)
#define GPIOA ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x0000UL)) /* GPIOA base address */
#define GPIOB ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x0400UL)) /* GPIOB base address */
#define GPIOC ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x0800UL)) /* GPIOC base address */
#define GPIOD ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x0C00UL)) /* GPIOD base address */
#define GPIOE ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x1000UL)) /* GPIOE base address */
#define GPIOF ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x1400UL)) /* GPIOF base address */
#define GPIOG ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x1800UL)) /* GPIOG base address */
#define GPIOH ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x1C00UL)) /* GPIOH base address */
#define GPIOI ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x2000UL)) /* GPIOI base address */
#define GPIOJ ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x2400UL)) /* GPIOJ base address */
#define GPIOK ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x2800UL)) /* GPIOK base address */

/*RCC base address*/
#define RCC ((RCC_RegDef_t *) (AHB1_BASEADDR + 0x3800UL))

/*SYSCFG base address*/
#define SYSCFG ((SYSCFG_RegDef_t *) (AHB2_BASEADDR + 0x3800UL))

/*EXTI base address*/
#define EXTI ((EXTI_RegDef_t *) (AHB1_BASEADDR + 0x3C00UL))

/* USART peripheral base address */
#define USART1 ((USART_RegDef_t *) (AHB2_BASEADDR + 0x1000UL))
#define USART2 ((USART_RegDef_t *) (APB1_BASEADDR + 0x4400UL))
#define USART3 ((USART_RegDef_t *) (APB1_BASEADDR + 0x4800UL))
#define UART4 ((USART_RegDef_t *) (APB1_BASEADDR + 0x4C00UL))
#define UART5 ((USART_RegDef_t *) (APB1_BASEADDR + 0x5000UL))
#define USART6 ((USART_RegDef_t *) (APB2_BASEADDR + 0x1400UL))

/*Timer peripheral base address*/
#define TIM6 ((TIM_RegDef_t *) (APB1_BASEADDR + 0x1000UL))
#define TIM7 ((TIM_RegDef_t *) (APB1_BASEADDR + 0x1400UL))

/*GPIO clock enable*/
#define GPIOA_CLK_ENB() (RCC->AHB1ENR |= (0x01U << 0U)) /*GPIOA peripheral clock enable*/
#define GPIOB_CLK_ENB() (RCC->AHB1ENR |= (0x01U << 1U)) /*GPIOB peripheral clock enable*/
#define GPIOC_CLK_ENB() (RCC->AHB1ENR |= (0x01U << 2U)) /*GPIOC peripheral clock enable*/
#define GPIOD_CLK_ENB() (RCC->AHB1ENR |= (0x01U << 3U)) /*GPIOD peripheral clock enable*/
#define GPIOE_CLK_ENB() (RCC->AHB1ENR |= (0x01U << 4U)) /*GPIOE peripheral clock enable*/
#define GPIOF_CLK_ENB() (RCC->AHB1ENR |= (0x01U << 5U)) /*GPIOF peripheral clock enable*/
#define GPIOG_CLK_ENB() (RCC->AHB1ENR |= (0x01U << 6U)) /*GPIOG peripheral clock enable*/
#define GPIOH_CLK_ENB() (RCC->AHB1ENR |= (0x01U << 7U)) /*GPIOH peripheral clock enable*/
#define GPIOI_CLK_ENB() (RCC->AHB1ENR |= (0x01U << 8U)) /*GPIOI peripheral clock enable*/

#define SYSCFG_CLK_ENB() (RCC->APB2ENR |= (0x01U << 14U)) /*SYSCFG peripheral clock enable*/

/*USART peripheral clock enable*/
#define USART1_CLK_ENB() (RCC->APB2ENR |= (0x01U << 4))
#define USART2_CLK_ENB() (RCC->APB1ENR |= (0x01U << 17))
#define USART3_CLK_ENB() (RCC->APB1ENR |= (0x01U << 18))
#define UART4_CLK_ENB() (RCC->APB1ENR |= (0x01U << 19))
#define UART5_CLK_ENB() (RCC->APB1ENR |= (0x01U << 20))
#define USART6_CLK_ENB() (RCC->APB2ENR |= (0x01U << 5))

/*Timer peripheral clock enable*/
#define TIM6_CLK_ENB() (RCC->APB1ENR |= (0x01U << 4U))
#define TIM7_CLK_ENB() (RCC->APB1ENR |= (0x01U << 5U))

/*GPIO clock disable*/
#define GPIOA_CLK_DIS() (RCC->AHB1ENR &= ~(0x01U << 0U)) /*GPIOA peripheral clock disable*/
#define GPIOB_CLK_DIS() (RCC->AHB1ENR &= ~(0x01U << 1U)) /*GPIOB peripheral clock disable*/
#define GPIOC_CLK_DIS() (RCC->AHB1ENR &= ~(0x01U << 2U)) /*GPIOC peripheral clock disable*/
#define GPIOD_CLK_DIS() (RCC->AHB1ENR &= ~(0x01U << 3U)) /*GPIOD peripheral clock disable*/
#define GPIOE_CLK_DIS() (RCC->AHB1ENR &= ~(0x01U << 4U)) /*GPIOE peripheral clock disable*/
#define GPIOF_CLK_DIS() (RCC->AHB1ENR &= ~(0x01U << 5U)) /*GPIOF peripheral clock disable*/
#define GPIOG_CLK_DIS() (RCC->AHB1ENR &= ~(0x01U << 6U)) /*GPIOG peripheral clock disable*/
#define GPIOH_CLK_DIS() (RCC->AHB1ENR &= ~(0x01U << 7U)) /*GPIOH peripheral clock disable*/
#define GPIOI_CLK_DIS() (RCC->AHB1ENR &= ~(0x01U << 8U)) /*GPIOI peripheral clock disable*/

#define SYSCFG_CLK_DIS() (RCC->APB2ENR &= ~(0x01U << 14U)) /*SYSCFG peripheral clock disable*/

/*USART clock disable*/
#define USART1_CLK_DIS() (RCC->APB2ENR &= ~(0x01U << 4))
#define USART2_CLK_DIS() (RCC->APB1ENR &= ~(0x01U << 17))
#define USART3_CLK_DIS() (RCC->APB1ENR &= ~(0x01U << 18))
#define UART4_CLK_DIS() (RCC->APB1ENR &= ~(0x01U << 19))
#define UART5_CLK_DIS() (RCC->APB1ENR &= ~(0x01U << 20))
#define USART6_CLK_DIS() (RCC->APB2ENR &= ~(0x01U << 5))

/*Timer clock disable*/
#define TIM6_CLK_DIS() (RCC->APB1ENR &= ~(0x01U << 4U))
#define TIM7_CLK_DIS() (RCC->APB1ENR &= ~(0x01U << 5U))

/*Common used macros*/
#define ENABLE 1U
#define DISABLE 0U
#define BIT_RESET 0U
#define BIT_SET 1U
#define TRUE  1U
#define FALSE 0U

#include "stm32f407xx_gpio_driver.h"
#include "stm32f407xx_usart_driver.h"
#include "stm32f407xx_timer_driver.h"
#endif