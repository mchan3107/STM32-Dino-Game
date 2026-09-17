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

uint8_t GPIO_ReadPin(GPIO_RegDef_t *GPIOx, uint8_t PinNumber)
{
    uint8_t ret;

    /* Read the value of the input pin */
    ret = (GPIOx->IDR >> PinNumber) & 0x01U;

    return ret;
}

void GPIO_TogglePin(GPIO_RegDef_t *GPIOx, uint8_t PinNumber)
{
    /* Toggle the pin state*/
    GPIOx->ODR ^= (0x01U << PinNumber);
}

void GPIO_WritePinBit(GPIO_RegDef_t * GPIOx, uint8_t PinNumber, GPIO_PinState_e PinState) {
    if (PinState == GPIO_PIN_LOW) {
        /*Reset the pin state to low*/
        GPIOx->BSRR |= (0x01 << (PinNumber + 16U));
    } else {
        /* Set the state to high*/
        GPIOx->BSRR |= (0x01 << PinNumber); 
    }
}

void GPIO_LockPinConf(GPIO_RegDef_t *GPIOx, uint8_t PinNumber)
{
    uint32_t temp1 = (0x01U << 16U);
    uint32_t temp2 = (0x01U << PinNumber);

    temp1 |= temp2;

    /* WR LCKR[16] = '1' + LCKR[15:0] */
    GPIOx->LCKR = temp1;

    /* WR LCKR[16] = '0' + LCKR[15:0] */
    GPIOx->LCKR = temp2;

    /* WR LCKR[16] = '1' + LCKR[15:0] */
    GPIOx->LCKR = temp1;

    /* RD LCKR */
    temp1 = GPIOx->LCKR;
}

void GPIO_IT_Init(GPIO_RegDef_t *GPIOx, GPIO_PinConf_t GPIOPinConf, uint8_t Priority)
{
    uint8_t index, bitpos, portcode;

    /* 1. Configure the SYSCFG */
    /* 1.1 Enable the clock for SYSCFG */
    SYSCFG_CLK_ENB();
    /* 1.2 Select the source (GPIO pin) for the respective EXTI line */
    /* 1.2.1 Specify SYSCFG_EXTICR register index */
    index = GPIOPinConf.GPIO_PinNumber / 4;
    /* 1.2.2 Specify SYSCFG_EXTICR bit position */
    bitpos = (GPIOPinConf.GPIO_PinNumber % 4) * 4;
    /* Ex. PA15 to be input interrupt pin
       bit field index = Pin number % 4 = 15 % 4 = 3.
       bit pos = bit field index * 4 = 3 * 4 = 12
    */
    /* 1.2.3 Specify GPIO port to be mapped in SYSCFG_EXTICR */
    portcode = SYSCFG_EXTICR_PORTCODE(GPIOx);
    SYSCFG->EXTICR[index] &= ~(0x0FU << bitpos); 
    SYSCFG->EXTICR[index] |= (portcode << bitpos); 

    /* 2. Configure the EXTI */
    /* 2.1 Select the edge trigger for the interrupt */
    switch (GPIOPinConf.GPIO_EdgeTrigger)
    {
        case GPIO_IT_EDGE_FT:
        {
            /* Disable rising edge trigger selection */
            EXTI->RTSR &= ~(0x01U << GPIOPinConf.GPIO_PinNumber);
            /* Enable the falling edge trigger selection */
            EXTI->FTSR |= (0x01U << GPIOPinConf.GPIO_PinNumber);
            break;
        }
        case GPIO_IT_EDGE_RT:
        {
            /* Disable falling edge trigger selection */
            EXTI->FTSR &= ~(0x01U << GPIOPinConf.GPIO_PinNumber);
            /* Enable the rising edge trigger selection */
            EXTI->RTSR |= (0x01U << GPIOPinConf.GPIO_PinNumber);
            break;
        }
        default:
        {
            /*Enable the falling edge trigger selection */
            EXTI->FTSR |= (0x01U << GPIOPinConf.GPIO_PinNumber);
            /*Enable the rising edge trigger selection */
            EXTI->RTSR |= (0x01U << GPIOPinConf.GPIO_PinNumber);
            break;
        }
    }

    /*2.2 Enable the interrupt mask for the respective EXTI line*/
    EXTI->IMR |= (0x01U << GPIOPinConf.GPIO_PinNumber);

    /*3. Configure the NVIC*/

    /*3.1 Set the interrupt priority*/
    NVIC_SetPriority(GPIO_PIN_TO_IRQ(GPIOPinConf.GPIO_PinNumber), Priority);

    /*3.2 Enabl vvve interrupt request*/
    NVIC_EnableIRQ(GPIO_PIN_TO_IRQ(GPIOPinConf.GPIO_PinNumber));

}
