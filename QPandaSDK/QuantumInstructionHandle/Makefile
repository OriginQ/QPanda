cc       = g++ -std=c++11
CCFLAGS  = -Wall -g -fopenmp
prom     = libQuantumInstructionHandle.so
TASKPATH = .
head     = $(shell find $(TASKPATH)/ -name "*.h")
src      = $(shell find $(TASKPATH)/ -name "*.cpp")
org      = $(src:%.cpp=%.o)

all: $(prom)

$(prom): $(org)
	$(cc) -shared -fPIC -o $(bin_dir)/$@ $^ 
	cp $(bin_dir)/$@ /usr/lib/

$(org): $(src)
	$(cc) -c -fPIC $(CCFLAGS) $^ 

clean:
	-rm -rf $(TASKPATH)/*.o


