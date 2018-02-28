cc       = g++ -std=c++11
CCFLAGS  = -Wall -g
prom     = libQPandaAPI.so
TASKPATH = .
head     = $(shell find $(TASKPATH)/ -name "*.h")
src      = $(shell find $(TASKPATH)/ -name "*.cpp")
org      = $(src:%.cpp=%.o)

all : $(prom)

$(prom): $(org)
	$(cc) -shared -fpic -o $(bin_dir)/$@  $(obj_dir)/$^

$(org): $(src)
	$(cc) -c -fpic $(CCFLAGS) $^ -o $(obj_dir)/$@

clean:
