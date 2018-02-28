cc       = g++ -std=c++11
CCFLAGS  = -Wall -g
prom     = libQParserSDK.so
TASKPATH = .
head     = $(shell find $(TASKPATH)/ -name "*.h")
src      = $(shell find $(TASKPATH)/ -name "*.cpp")
org      = $(src:%.cpp=%.o)

all : $(prom) QPandaAPI.py

$(prom): QPandaAPI_wrap.o QPandaAPI.o 
	$(cc) -shared -fPIC $(obj_dir)/QPandaAPI_wrap.o $(obj_dir)/QPandaAPI.o -lpython2.7 -L$(bin_dir) -lQRunesParser -lQuantumInstructionHandle  -o $(bin_dir)/$@

QPandaAPI_wrap.o: QPandaAPI_wrap.cxx QPandaAPI.h
	$(cc) -fPIC QPandaAPI_wrap.cxx -c -g -I/usr/include/python2.7 -o $(obj_dir)/$@ 

QPandaAPI_wrap.cxx: QPandaAPI.i
	swig -c++ -python $^

QPandaAPI.py: QPandaAPI.i
	swig -c++ -python $^

QPandaAPI.o: QPandaAPI.cpp QPandaAPI.h
	$(cc) -fPIC QPandaAPI.cpp -c -g -Wno-deprecated -o $(obj_dir)/$@

clean:



