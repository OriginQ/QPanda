sub_dir := QRunesParser \
		   QuantumInstructionHandle \
		   QPandaAPI\
		   GPUEmulator		   


top_dir = $(PWD)

bin_dir = $(top_dir)/linuxlib

obj_dir = $(top_dir)/obj

export top_dir bin_dir obj_dir

all : mkdir $(sub_dir) 

mkdir: 
	mkdir -p $(bin_dir)
	mkdir -p $(obj_dir)

$(sub_dir) : echo
	make -C $@

echo : mkdir
	@echo $(sub_dir)
	@echo begin compile


clean : 
	-rm -rf $(bin_dir)/* $(obj_dir)/*
	-rm -rf ./QRunesParser/*.o
	-rm -rf ./GPUEmulator/*.o
	-rm -rf ./QuantumInstructionHandle/*.o
