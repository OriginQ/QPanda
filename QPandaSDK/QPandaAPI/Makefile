cc       = g++ -std=c++11
CCFLAGS  = -Wall -g
prom     = QParserSDK.a
TASKPATH = .
head     = $(shell find $(TASKPATH)/ -name "*.h")
src      = $(shell find $(TASKPATH)/ -name "*.cpp")
org      = $(src:%.cpp=%.o)

all : $(prom)

$(prom): $(org)
	ar r $(bin_dir)/$@  $(obj_dir)/$^

$(org): $(src)
	$(cc) -c $(CCFLAGS) $^ -o $(obj_dir)/$@

clean:



