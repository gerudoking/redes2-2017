all: run

SCR_DIR = src
#Apos ter sua copia do makefile, mude aonde esta localizado seu ns3. No entanto, procure manter o makefile no .gitignore
NS3_DIR =/mnt/c/ns-allinone-3.27/ns-allinone-3.27/ns-3.27
PROGRAM_NAME = base

validate_ns3_dir:
ifeq ("$(NS3_DIR)", "")
	$(error Please provide the NS3_DIR parameter, e.g. make NS3_DIR=~/ns-allinone-3.16/ns-3.16/)
endif
ifeq ($(wildcard $(NS3_DIR)/waf), )
	$(error The provided NS3_DIR parameter is not valid. NS3_DIR must contain the waf file. See README for more details)
endif

run: validate_ns3_dir
		rm -rf $(NS3_DIR)/scratch/$(SCR_DIR)
		cp -r src/. $(NS3_DIR)/scratch/
		cd $(NS3_DIR); \
		./waf configure --build-profile=debug --enable-examples --enable-tests; \
		./waf --run $(PROGRAM_NAME)
