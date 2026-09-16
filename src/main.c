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
	GPIOA_CLK_ENB();
	GPIO_Init(GPIOA, UserButton);
}

int main(void){
	/*Initialize the blue LED*/
    BlueLED_Init();
	/*Initialize the user button*/
	UserButton_Init();

	while (1) {
		if (GPIO_ReadPin(GPIOA, GPIO_PIN_NUM_0) == GPIO_PIN_HIGH) {
			SimDelay();	
			if (GPIO_ReadPin(GPIOA, GPIO_PIN_NUM_0) == GPIO_PIN_HIGH) {
				/*Toggle the blue LED*/
				GPIO_TogglePin(GPIOD, GPIO_PIN_NUM_15);
			}
		}
	}

	return 0;
}