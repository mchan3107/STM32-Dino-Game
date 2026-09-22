# STM32 Dino Game

A Chrome Dino-style game controlled using an **STM32F407 Discovery board**.

The STM32 reads hardware input and communicates with the Windows game through **USART serial communication**. The project uses low-level STM32 peripherals including GPIO, timers, interrupts, and USART.

## How to Run

**Requirements**
- Windows PC
- STM32F407 Discovery board
- Keil µVision 5
- USB connection

1. Clone or download this repository.
2. Open the STM32 project in **Keil µVision 5**.
3. Connect the STM32F407 Discovery board to your computer via USB.
4. Build and flash the firmware onto the board using Keil µVision 5.
5. Download and open the provided Windows game.
6. Select the correct COM port and start playing.

## Technologies

- STM32F407
- Embedded C
- GPIO
- USART / Serial Communication
- Timers & Interrupts
- Keil µVision 5