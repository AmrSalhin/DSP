#include "stm32f4xx.h"
#include "signals.h"

extern float _5hz_signal[_5hz_signal_SIZE];
float g_input_signal_sample;

static void plot_input_signal();
static void delay(int delay_time);

int main()
{
	/* Enable FPU: Enable CP10 and CP11 Coprocessors full access */
	SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2));

	while(1)
	{
		plot_input_signal();

	}
}

static void plot_input_signal()
{
	for(int i=0; i<_5hz_signal_SIZE; i++)
	{
		g_input_signal_sample = _5hz_signal[i];
		delay(9000);
	}
}

static void delay(int delay_time)
{
	for (int i = 0; i < delay_time; i++)
	{
	}
}
