#include <stdio.h>
#include <stdint.h>

#include "dspLib_Math.h"
#include "dspLib_Signals.h"

int main() {
	
	int32_t *p_sine_arr;
	uint32_t i;
	
	p_sine_arr = malloc(100 * sizeof(int32_t));
	
	dspLib_Signals_Sin(10000, PI_BY_2, 100, 100, p_sine_arr);
	
	for(i = 0; i < 100; i++) {
		printf("%d\n", p_sine_arr[i]);
	}
}