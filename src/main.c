#include "stm32f407xx.h"

GPIO_PinConf_t Blinky_LED;

void BlueLED_Init(void) {
	Blinky_LED.GPIO_PinNumber = GPIO_PIN_NUM_15;
	Blinky_LED.GPIO_PinMode = GPIO_MODE_OUTPUT;
	Blinky_LED.GPIO_OutType = GPIO_OUT_TYPE_PP;
	Blinky_LED.GPIO_OutSpeed = GPIO_OUT_SPEED_LOW;
	Blinky_LED.GPIO_PUPD = GPIO_NO_PUPD;
	GPIOD_CLK_ENB();
	GPIO_Init(GPIOD, Blinky_LED);
}

int main(void){
	/*Initialize the blue LED*/
    BlueLED_Init();

	/*Turn on the blue LED*/
	GPIO_WritePin(GPIOD, GPIO_PIN_NUM_15, GPIO_PIN_HIGH);

    return 0;
}