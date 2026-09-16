#include "stm32f407xx.h"

void GPIO_Init(GPIO_RegDef_t *GPIOx, GPIO_PinConf_t GPIOPinConf) {
    /* Configure the pin mode */
    /* Clear the new pin mode configuration */
    GPIOx->MODER &= ~(0x03U << (GPIOPinConf.GPIO_PinNumber * 2));

    /* Set the new pin mode configuration */
    GPIOx->MODER |= (GPIOPinConf.GPIO_PinMode << (GPIOPinConf.GPIO_PinNumber * 2));

    if ((GPIOPinConf.GPIO_PinMode == GPIO_MODE_OUTPUT) ||
        (GPIOPinConf.GPIO_PinMode == GPIO_MODE_ALT)) {

        /* Configure the output type */
        GPIOx->OTYPER &= ~(0x01U << GPIOPinConf.GPIO_PinNumber);
        GPIOx->OTYPER |= (GPIOPinConf.GPIO_OutType << GPIOPinConf.GPIO_PinNumber);

        /* Configure the output speed */
        GPIOx->OSPEEDR &= ~(0x03U << (GPIOPinConf.GPIO_PinNumber * 2));
        GPIOx->OSPEEDR |= (GPIOPinConf.GPIO_OutSpeed << (GPIOPinConf.GPIO_PinNumber * 2));
    }

    /* Configure the pull-up/pull-down */
    GPIOx->PUPDR &= ~(0x03U << GPIOPinConf.GPIO_PinNumber * 2);
    GPIOx->PUPDR |= (GPIOPinConf.GPIO_PUPD << GPIOPinConf.GPIO_PinNumber * 2);

    /* Configure the alternate function */
    if (GPIOPinConf.GPIO_PinMode == GPIO_MODE_ALT) {
        if (GPIOPinConf.GPIO_PinNumber < 8) {
            /* Configure the alternate function low register */
            GPIOx->AFRL &= ~(0x0F << GPIOPinConf.GPIO_PinNumber * 4);
            GPIOx->AFRL |= (GPIOPinConf.GPIO_AltFunc << GPIOPinConf.GPIO_PinNumber * 4);
        } else {
            /* Configure the alternate function high register */
            GPIOx->AFRH &= ~(0x0F << GPIOPinConf.GPIO_PinNumber * 4);
            GPIOx->AFRH |= (GPIOPinConf.GPIO_AltFunc << GPIOPinConf.GPIO_PinNumber * 4);
        }
    }
}

void GPIO_WritePin(GPIO_RegDef_t *GPIOx, uint8_t PinNumber, GPIO_PinState_e PinState)
{
    if (PinState == GPIO_PIN_LOW)
    {
        /* Clear the output pin */
        GPIOx->ODR &= ~(0x01U << PinNumber);
    }
    else
    {
        /* Set the output pin */
        GPIOx->ODR |= (0x01U << PinNumber);
    }
}