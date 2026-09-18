#include "stm32f407xx.h"
#include <string.h>

GPIO_PinConf_t Blinky_LED;
GPIO_PinConf_t UserButton;
USART_Conf_t USART3_Conf;

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
	UserButton.GPIO_EdgeTrigger = GPIO_IT_EDGE_RT; 
	GPIOA_CLK_ENB();
	GPIO_Init(GPIOA, UserButton);
	GPIO_IT_Init(GPIOA, UserButton, 1U);
}

void USART3_Init(void)
{
    GPIO_PinConf_t USART_Pin;

    /*GPIO - USART pin configuration
    Configure GPIO (GPIO pin10/Tx and pin11/Rx) pin to use in alternate function mode (USART3)*/
    USART_Pin.GPIO_PinMode   = GPIO_MODE_ALT;
    USART_Pin.GPIO_PUPD      = GPIO_NO_PUPD;
    USART_Pin.GPIO_OutType   = GPIO_OUT_TYPE_PP;
    USART_Pin.GPIO_OutSpeed  = GPIO_OUT_SPEED_VERY_HIGH;
    USART_Pin.GPIO_AltFunc    = GPIO_ALT_AF7;

    GPIOB_CLK_ENB();
    USART_Pin.GPIO_PinNumber = GPIO_PIN_NUM_10; /* Tx pin */
    GPIO_Init(GPIOB, USART_Pin);

    USART_Pin.GPIO_PinNumber = GPIO_PIN_NUM_11; /* Rx pin */
    GPIO_Init(GPIOB, USART_Pin);

    /*USART3 configuration*/
    USART3_Conf.Mode         = USART_MODE_TX_RX;       /*Transmit and receive mode*/
    USART3_Conf.Parity       = USART_PARITY_NONE;      /*None parity control*/
    USART3_Conf.StopBits     = USART_STOPBITS_1;       /*1 stop bit*/
    USART3_Conf.WordLength   = USART_WORDLENGTH_8B;    /*8 bit word length*/
    USART3_Conf.OverSampling = USART_OVERSAMPLING_16;  /*Oversampling by 16*/
    USART3_Conf.BaudRate     = USART_BAUDRATE_9600;

    USART3_CLK_ENB();
    USART_Init(USART3, USART3_Conf);
}


int main(void){
	uint8_t ReceivedMess[] = "";
    uint8_t ReceiveMessSize = 3U;

    /*GPIO init start---------------------------------------------*/
    /*Initialize the blue LED*/
    BlueLED_Init();

    /*Initialize the button */
    UserButton_Init();
    /*GPIO init end-----------------------------------------------*/

    /*USART init start--------------------------------------------*/
    /*Initialize USART3*/
    USART3_Init();
    /*USART init end----------------------------------------------*/

	while (1)
	{
		/*Receive message*/
		USART_Receive(USART3, (uint8_t *)&ReceivedMess, ReceiveMessSize);

		/*Echo back the received message*/
		USART_Transmit(USART3, (uint8_t *)&ReceivedMess, ReceiveMessSize);

		/*Check if the received message is "ON_"*/
		if (strcmp((const char *)ReceivedMess, "ON_") == 0)
		{
			/*Turn blue LED ON*/
			GPIO_WritePinBit(GPIOD, GPIO_PIN_NUM_15, GPIO_PIN_HIGH);
		}

		/*Check if the received message is "OFF"*/
		if (strcmp((const char *)ReceivedMess, "OFF") == 0)
		{
			/*Turn blue LED OFF*/
			GPIO_WritePinBit(GPIOD, GPIO_PIN_NUM_15, GPIO_PIN_LOW);
		}
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

