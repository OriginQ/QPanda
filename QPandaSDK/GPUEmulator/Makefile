cc       = g++ -shared -o 
nvcc     = nvcc -std=c++11
compiler = -w --compiler-options \"-fPIC\" -c
nvcc_arc = -arch compute_30
prom     = GPUEmulator.so
src      = $(shell find ./ -name "*.cu")
org      = $(src:%.cu=%.o)

all : $(org)
	$(cc) $(bin_dir)/$(prom) $^

$(org) : $(src)
	$(nvcc) $(nvcc_arc) $(compiler) $^

clean : 
	rm -f *.o *.so
