# test for dspLib in python
import os
import datetime
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

		# Create the directory for saving the test results
		timeNow = datetime.datetime.now()
		self.testResDir = self.libPath + 'test_result_python/' + 'Y' + str(timeNow.year) + '_M' + str(timeNow.month) + '_D' + str(timeNow.day) + '_H' + str(timeNow.hour) + '_M' + str(timeNow.minute) + '_S' + str(timeNow.second)
		if(not os.path.isdir(self.libPath + 'test_result_python/')):
			os.mkdir(self.libPath + 'test_result_python/')
		if(not os.path.isdir(self.testResDir)):
			os.mkdir(self.testResDir)

	def test_dspLib_Math_Sin(self, nPoints):
		resDir = self.testResDir + '/test_dspLib_Math_Sin/'
		if(not os.path.isdir(resDir)):
			os.mkdir(resDir)

		sqnrArray = nPoints*[0]
		samples = nPoints*[0]
		qAngle = (self.pi / 2)/nPoints
		fAngle = (math.pi / 2)/nPoints
		for i in range(-nPoints/2, nPoints/2):
			fSignal = math.sin(fAngle * i)
			fqSignal = 1.0*self.lib.dspLib_Math_Sin(qAngle * i)/pow(2,30)
			noise = fSignal - fqSignal
			try:
				sqnr = abs(fSignal/noise)
				sqnrArray[i + (nPoints/2)] = 20*math.log10(sqnr)
			except ValueError:
				# the signal value is zero
				sqnr = abs(1/noise)
				sqnrArray[i + (nPoints/2)] = 20*math.log10(sqnr)
			except ZeroDivisionError:
				# the noise is zero
				sqnrArray[i + (nPoints/2)] = (6.02 * 30) + 1.76		# maximum SQNR for Q30 format

			samples[i + (nPoints/2)] = fAngle * i
		fig, axis = pyplot.subplots(1, 2, sharey = True, tight_layout = True)
		axis[0].plot(samples, sqnrArray)
		axis[1].hist(sqnrArray, nPoints/10)
		pyplot.savefig(resDir + 'test_dspLib_Math_Sin.png', dpi=300)

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
	a.test_dspLib_Math_Sin(1000
