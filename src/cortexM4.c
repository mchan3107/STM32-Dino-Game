#include "cortexM4.h"

void NVIC_SetPriority(uint8_t IRQNumber, uint8_t Priority)
{
    uint8_t index, bitpos;

    /*Specify the NVIC_IPRx register index*/
    index = IRQNumber / 4;

    /*Specify the bit position to start writing the priority*/
    bitpos = (IRQNumber % 4U) * 8U;

    /*Set the priority*/
    NVIC->IPR[index] &= ~(Priority << (bitpos + 4U));
    NVIC->IPR[index] |= (Priority << (bitpos + 4U));
}

void NVIC_EnableIRQ(uint8_t IRQNumber)
{
    uint8_t index, bitpos;

    /*Specify the NVIC_ISERx register index*/
    index = IRQNumber / 32U;

    /*Specify the bit position*/
    bitpos = IRQNumber % 32U;

    /*Enable the IRQ*/
    NVIC->ISER[index] |= (0x01U << bitpos);
}