/*
* Library to create perodic signlas
* Samples are generated for one period
*/
#include "dspLib_Math.h"
/**
 * find the sinusoidal samples for the given frequence and sampling frequency.
 * Output the phase of the next sample in the sample sampling space domain.
 * Calculation.
 * -----------
 * out = sin((2*pi*f*n*Ts) + phase)
 * where f - frequency, n - samples(0 - N-1), Ts - sampling time.
 * next phase = (phase + (2*pi*f*Ts*N)) mod 2pi
 * Representation
 * --------------
 * f, fs - must be in same format and represented in Q16 format. f and fs can be scaled using same sacle factor to bring under the bit range.
 * the integer value of f anf fs shold be less than 100
 * phase - 0 - 2*pi, represented in unsigned Q29
**/
uint32_t dspLib_Signals_Sin(uint32_t samplingFrequency, uint32_t phase, uint32_t frequency, uint16_t numSamples, int32_t *pOutSamples) {
	
	uint16_t k, two_pi, pi, pi_2, pi_4, three_pi_2, phase_sample, i_index, n_index;
	int32_t i_sample, N_sample;
	uint32_t angle;
	
	/* 2*(f/fs) */
	k = ((frequency << 9) / (samplingFrequency >> 1));	// Q9 format
	/* fs/f */
	two_pi = (samplingFrequency / frequency);			// Interger from 2 to 511	corresponds to 2PI
	pi = (two_pi >> 1);
	pi_2 = (pi >> 1);
	pi_4 = (pi_2 >> 1);
	three_pi_2 = pi + pi_2;
	
	/* PI is in Q29 format, convert to Q13 format */
	angle = (PI >> 9) * k; // Q9 * Q20 gives Q29 format.	// angle = 2*PI*f/fs
	phase_sample = (two_pi * (phase >> 9)) / (PI >> 8);
	/* First quadrant */
	N_sample = (phase_sample + numSamples) > pi_2 ? pi_2 : (phase_sample + numSamples);
	i_index = 0;
	for(i_sample = phase_sample; i_sample < N_sample; i_sample++) {
		pOutSamples[i_index++] = dspLib_Math_Sin(angle * i_sample);
	}
	/* First half of second quadrant */
	n_index = i_index;
	i_index = 0;
	N_sample = (phase_sample + numSamples) > (pi - phase_sample) ? (pi - phase_sample) : (phase_sample + numSamples);
	for(; i_sample < N_sample; i_sample++) {
		pOutSamples[n_index + i_index] = pOutSamples[(n_index - 1) - i_index];
		i_index++;
	}
	/* second half of second quadrant */
	i_index = n_index + i_index;
	N_sample = (phase_sample + numSamples) > pi ? 0 : pi - (phase_sample + numSamples);
	for(i_sample = phase_sample; i_sample > N_sample; i_sample--) {
		pOutSamples[i_index++] = dspLib_Math_Sin(angle * i_sample);
	}
	/* complete one half cycle */
	n_index = i_index;
	i_index = 0;
	N_sample = (phase_sample + numSamples) > (pi + phase_sample) ? (pi + phase_sample) : (phase_sample + numSamples);
	for(i_sample = pi; i_sample < N_sample; i_sample++) {
		pOutSamples[n_index + i_index] = -pOutSamples[(n_index - 1) - i_index];
		i_index++;
	}
	/* Half cycle of data is available, not it can be replicated */
	n_index = n_index + i_index;
	i_index = 0;
	numSamples = numSamples - n_index;
	while(i_index < numSamples) {
		pOutSamples[n_index + i_index] = -pOutSamples[i_index + 1];
		i_index++;
	}
	
	return 0;
}