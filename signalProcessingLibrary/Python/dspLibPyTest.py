# test for dspLib in python
from ctypes import cdll
lib = cdll.LoadLibrary('libDspLib.so')	#Load library here, otherwise it may fail in windows
import ctypes
from matplotlib import pyplot

class dspLib():
	def __init__(self):
		self.pi = 1686629713	# Value of PI in Q29 format
		
	def plotSin(self, samplingFrequency, frequency, phase, numSamples):
		lib.dspLib_Signals_Sin.argtypes = [ctypes.c_long, ctypes.c_long, ctypes.c_long, ctypes.c_int, ctypes.POINTER(ctypes.c_long)]
		array = (ctypes.c_long * numSamples)()
		ctypes.cast(array, ctypes.POINTER(ctypes.c_long))
		phase = lib.dspLib_Signals_Sin(samplingFrequency, phase, frequency, numSamples, array);
		samples = range(0, numSamples)
		pyplot.plot(samples, array)
		pyplot.show()

if __name__ == "__main__":
	a = dspLib()
	a.plotSin(10000, 100, 0, 1000)