#include "stm32f407xx.h"
#include <string.h>

GPIO_PinConf_t Blinky_LED;
GPIO_PinConf_t UserButton;
USART_Conf_t USART3_Conf;
TIM_Base_Conf_t TIM6_Conf;

#define RX_BUFFER_SIZE  8U
#define TX_BUFFER_SIZE  8U
#define BUTTON_DEBOUNCE_TIME 100U
volatile uint8_t ReceivedMess[RX_BUFFER_SIZE];
volatile uint8_t SentMess[RX_BUFFER_SIZE] = "J\n";
volatile uint8_t TxMessSize    = 2U;
volatile uint8_t RxIndex       = 0U;
volatile uint8_t RxData        = 0U;
volatile uint8_t IsRxAvailable = FALSE;
volatile uint16_t Timer6DelayCounter = 0U;

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
	USART3_RXNEIE_ENB();
	NVIC_SetPriority(IRQ_NO_USART3, 0U);
	NVIC_EnableIRQ(IRQ_NO_USART3);
    USART_Init(USART3, USART3_Conf);
}

void TIM6_Init(void)
{
    TIM6_Conf.AutoReloadPreload = ENABLE;
    TIM6_Conf.Period = 999;             /*1ms period*/
    TIM6_Conf.Prescaler = 15;           /*Counter clock is 1MHz (with 16 MHz timer clock)*/
    TIM6_CLK_ENB();
    TIM_Base_Init(TIM6, TIM6_Conf);
}

void TIM6_Start(void)
{
    TIM_Base_Start(TIM6);
}

void TIM6_STOP(void) {
    TIM_Base_Stop(TIM6);
}

void TIM6_IT_Init(void) {
	uint8_t Priority = 1U;
	TIM_Base_IT_Init(TIM6, Priority);
}

int main(void){
	uint16_t Timer6DelayCounter = 0U;

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

	/*TIM6 init start----------------------------------------------*/
	TIM6_Init();
	TIM6_IT_Init();
	/*TIM6 init end------------------------------------------------*/

	while (1)
	{
		/*Is new data available?*/
		if (IsRxAvailable == TRUE)
		{
			/*Check if update event generated*/
			if (TIM6_UEV_STS() == BIT_SET)
			{
				/*Clear the update event status*/
				TIM6_UEV_STS_CLR();

				/*Increase the timer delay counter by 1*/
				Timer6DelayCounter++;

				/*Check if 1 second has elapsed*/
				if (Timer6DelayCounter == 1000)
				{
					/*Toggle the Blue LED*/
					GPIO_TogglePin(GPIOD, GPIO_PIN_NUM_15);

					/*Reset timer 6 delay counter*/
					Timer6DelayCounter = 0U;
				}
			}
		}
	}

	return 0;
}

void EXTI0_IRQHandler(void)
{
    TIM6_START();

    /*Is the corresponding bit in the EXTI_PR register set?*/
    if((EXTI->PR >> UserButton.GPIO_PinNumber) & 0x01U)
    {
        /*Clear the pending bit by writing '1'*/
        EXTI->PR |= (0x01U << UserButton.GPIO_PinNumber);
    }

    /*Transmit data*/
    USART_Transmit(USART3, (uint8_t *)&SentMess, TxMessSize);
}

void USART3_IRQHandler(void)
{
    /*Check if the receive register is not empty*/
    if ((USART3->SR >> USART_SR_RXNE) & 0x01U)
    {
        /*Read received data*/
        RxData = USART3->DR;

        /*Set the Rx data available flag to TRUE*/
        IsRxAvailable = TRUE;
    }
}

void TIM6_DAC_IRQHandler(void)
{
    /*Check if update event generated*/
    if (TIM6_UEV_STS() == BIT_SET)
    {
        /*Clear the update event status*/
        TIM6_UEV_STS_CLR();

        /*Increase the timer delay counter by 1*/
        Timer6DelayCounter++;

        /*Check if BUTTON_DEBOUNCE_TIME ms has elapsed*/
        if (Timer6DelayCounter == BUTTON_DEBOUNCE_TIME)
        {
            /*Transmit data*/
            USART_Transmit(USART3, (uint8_t *)&SentMess, TxMessSize);

            /*Reset timer 6 delay counter*/
            Timer6DelayCounter = 0U;

            /*Stop timer 6*/
            TIM6_Stop();
        }
    }
}


	

