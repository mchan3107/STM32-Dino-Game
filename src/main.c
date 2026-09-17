#include "stm32f407xx.h"

GPIO_PinConf_t Blinky_LED;
GPIO_PinConf_t UserButton;

void SimDelay(void) {
	uint32_t DelayCount;
	for (DelayCount = 0; DelayCount < 100000; DelayCount++){
		/* Do nothing*/
	}
}

void BlueLED_Init(void) {
	Blinky_LED.GPIO_PinNumber = GPIO_PIN_NUM_15;
	Blinky_LED.GPIO_PinMode = GPIO_MODE_OUTPUT;
	Blinky_LED.GPIO_OutType = GPIO_OUT_TYPE_PP;
	Blinky_LED.GPIO_OutSpeed = GPIO_OUT_SPEED_LOW;
	Blinky_LED.GPIO_PUPD = GPIO_NO_PUPD;
	GPIOD_CLK_ENB();
	GPIO_Init(GPIOD, Blinky_LED);
}

void UserButton_Init(void) {
	UserButton.GPIO_PinNumber = GPIO_PIN_NUM_0;
	UserButton.GPIO_PinMode = GPIO_MODE_INPUT;
	UserButton.GPIO_PUPD = GPIO_NO_PUPD;
	UserButton.GPIO_EdgeTrigger = GPIO_IT_EDGE_FT; 
	GPIOA_CLK_ENB();
	GPIO_Init(GPIOA, UserButton);
	GPIO_IT_Init(GPIOA, UserButton, 1U);
}

int main(void){
	/*Initialize the blue LED*/
    BlueLED_Init();
	/*Initialize the user button*/
	UserButton_Init();

	while (1)
	{
		/* Do nothing*/
	}

	return 0;
}

void EXTI0_IRQHandler(void)
{
	/*Is the corresponding bit in the EXTI_PR register set?*/
	if((EXTI->PR >> UserButton.GPIO_PinNumber) & 0x01U)
	{
		/*Clear the pending bit by writing 1*/
		EXTI->PR |= (0x01U << UserButton.GPIO_PinNumber);
	}
	SimDelay();
	/*Check the state of the button again*/
	if(GPIO_ReadPin(GPIOA, GPIO_PIN_NUM_0) == GPIO_PIN_HIGH)
	{
		GPIO_TogglePin(GPIOD, GPIO_PIN_NUM_15);
	}
}