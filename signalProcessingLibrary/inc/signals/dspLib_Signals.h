#ifndef DSP_LIB_SIGNALS_H
#define DSP_LIB_SIGNALS_H

typedef enum {
	SIGNAL_STEP,
	SIGNAL_RAMP,
	SIGNAL_SINE,
	SIGNAL_SQUARE,
	SIGNAL_PULSE,
	SIGNAL_SAWTOOTH
} eSignalType;
	
typedef struct {
	eSignalType type;
	uint16_t samplingFrequency;
	uint16_t signalAmplitude;
	uint16_t signalFrequency;
};

#endif