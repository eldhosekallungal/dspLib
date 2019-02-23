#ifndef DSP_LIB_SIGNALS_H
#define DSP_LIB_SIGNALS_H

/**
 * function dspLib_Signals_Sin
 * \brief function is used to find the sinusoidal samples for a given frequency and phase. The samples will be in Q30 format.
 * \param samplingFrequency [in] uint32_t : Input sampling frequency. Should be in 7Q16 format.
 *        phase [in] uint32_t : Phase can be from 0 to 2PI in Q29 unsigned format.
 *        frequency [in] uint32_t : Input frequency of sinusoidal samples. Must be have same uint as sampling frequency as in 7Q16 format.
 *        numSamples [in] uint16_t : Number of samples required.
 *        pOutSamples [out] int32_t : Output sinusoidal samples.
 * \return Phase of next sample in Q29 format.
 * \note Currently the function have following limitations:
 *       1. Phase cannot be greater than PI/2
 *       2. Will not return the phase of next sample.
*/
uint32_t dspLib_Signals_Sin(uint32_t samplingFrequency, uint32_t phase, uint32_t frequency, uint16_t numSamples, int32_t *pOutSamples);
#endif