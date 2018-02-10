cc       = g++ -std=c++11
CCFLAGS  = -Wall -g
prom     = QRunesParser.a
TASKPATH = .
head     = $(shell find $(TASKPATH)/ -name "*.h")
src      = $(shell find $(TASKPATH)/ -name "*.cpp")
org      = $(src:%.cpp=%.o)

all: $(prom)

$(prom): $(org)
	ar r $(bin_dir)/$@ $^

$(org): $(src)
	$(cc) -c $(CCFLAGS) $^  
	
clean:
	-rm -rf $(TASKPATH)/*.o



