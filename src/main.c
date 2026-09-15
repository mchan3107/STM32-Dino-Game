#include <stdint.h>

volatile uint8_t HelloWorld;

int main(void){
    while (1) /*First infinite while loop*/
		{
			if (Flag) break;
		}
		while (1) {} /*Second infinite while loop*/
    return 0;
}