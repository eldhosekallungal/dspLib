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
 * the integer value of f and fs shold be less than 100
 * phase - -pi to pi, represented in unsigned Q29
**/
uint32_t dspLib_Signals_Sin(uint32_t samplingFrequency, int32_t phase, uint32_t frequency, uint16_t numSamples, int32_t *pOutSamples) {
    int32_t theta = phase, theta_N, angle;
	uint16_t i_index = 0, k, two_pi, pi, pi_2;
	
	/* 2*(f/fs) */
	k = ((frequency << 9) / (samplingFrequency >> 1));	// Q9 format
	/* fs/f */
	two_pi = (samplingFrequency / frequency);			// Interger from 2 to 511	corresponds to 2PI
	pi = (two_pi >> 1);
	pi_2 = (pi >> 1);
	
	angle = (PI >> 9) * k; // Q9 * Q20 gives Q29 format.	// angle = 2*PI*f/fs

	while(i_index < numSamples) {
		theta_N = ((numSamples - i_index) > pi_2) ? PI_BY_2 : (numSamples - i_index)*angle;
		while(theta < theta_N) {
			pOutSamples[i_index++] = dspLib_Math_Sin(theta);
			theta = theta + angle;
		}
		/* theta will be at PI/2 or greater than PI/2.
		 * To get the same angle in first quadrant, substract from PI
		*/
		theta = PI - theta;
		theta_N = ((numSamples - i_index) > pi) ? 0 : (pi_2 - (numSamples - i_index))*angle;
		while(theta > theta_N) {
			pOutSamples[i_index++] = dspLib_Math_Sin(theta);
			theta = theta - angle;
		}
		angle = -angle;
	}
	
	return 0;
}