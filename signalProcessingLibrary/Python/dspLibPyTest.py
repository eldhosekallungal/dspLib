# test for dspLib in python
import os
import math
import ctypes
from matplotlib import pyplot
from ctypes import cdll	#import the cdll at last, otherwise it may fail in windows

class dspLib():
	def __init__(self):
		self.libPath = '../test/'
		# Clean make
		os.system('make ' + '-C ' + self.libPath + ' clean')
		# make all
		os.system('make ' + '-C ' + self.libPath + ' shared_lib')
		self.lib = cdll.LoadLibrary(self.libPath + 'libDspLib.so')
		self.pi = 1686629713	# Value of PI in Q29 format

	def testSin(self, nPoints):
		sqnrArray = nPoints*[0]
		samples = nPoints*[0]
		qAngle = (self.pi / 2)/nPoints
		fAngle = (math.pi / 2)/nPoints
		for i in range(-nPoints/2, nPoints/2):
			fSignal = math.sin(fAngle * i)
			fqSignal = 1.0*self.lib.dspLib_Math_Sin(qAngle * i)/pow(2,30)
			noise = fSignal - fqSignal
			sqnr = abs(fSignal/noise)
			if sqnr != 0:
				sqnrArray[i + (nPoints/2)] = 20*math.log10(sqnr)
				samples[i + (nPoints/2)] = fAngle * i
		fig, axis = pyplot.subplots(1, 2, sharey = True, tight_layout = True)
		axis[0].plot(samples, sqnrArray)
		axis[1].hist(sqnrArray, nPoints/10)
		pyplot.show()

	def plotSin(self, samplingFrequency, frequency, phase, numSamples):
		self.lib.dspLib_Signals_Sin.argtypes = [ctypes.c_long, ctypes.c_long, ctypes.c_long, ctypes.c_int, ctypes.POINTER(ctypes.c_long)]
		array = (ctypes.c_long * numSamples)()
		ctypes.cast(array, ctypes.POINTER(ctypes.c_long))
		phase = self.lib.dspLib_Signals_Sin(samplingFrequency, phase, frequency, numSamples, array);
		samples = range(0, numSamples)
		pyplot.plot(samples, array)
		pyplot.show()

if __name__ == "__main__":
	a = dspLib()
	a.testSin(1000)