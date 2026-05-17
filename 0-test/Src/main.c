#include "stm32f4xx.h"

#define GPIOC_EN	(1<<2)
#define PIN13	(1<<13)
#define LED		PIN13

int main()
{
	RCC->AHB1ENR |= GPIOC_EN;
	GPIOC->MODER |= (1 << 26);
	GPIOC->MODER &= (~(1 << 27));
	while(1)
	{
		GPIOC->ODR ^= (1 << 13);
		for (int i = 0; i < 100000; i++)
		{

		}

	}
}
