INCLUDE_PATH = -I"../inc/math"
INCLUDE_PATH += -I"../inc/signals"
CFLAGS = -g

all : main_sine shared_lib

main_sine : test_sine.o dspLib_Math.o dspLib_Signals.o
	gcc $(CFLAGS) -o main_sine.exe test_sine.o dspLib_Math.o dspLib_Signals.o $(INCLUDE_PATH)

test_sine.o :
	gcc $(CFLAGS) -c test_sine.c $(INCLUDE_PATH)

dspLib_Math.o :
	gcc $(CFLAGS) -c ../src/math/dspLib_Math.c $(INCLUDE_PATH)
	
dspLib_Signals.o :
	gcc $(CFLAGS) -c ../src/signals/dspLib_Signals.c $(INCLUDE_PATH)

shared_lib : dspLib_Math.o dspLib_Signals.o
	gcc -shared -o libDspLib.so dspLib_Math.o dspLib_Signals.o

clean:
	rm -rf *.o *.so *.exe