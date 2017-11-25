all: install

SCR_DIR = redesSrc
NS3_DIR = /mnt/c/ns-allinone-3.27/ns-3.27
PROGRAM_NAME = base

validate_ns3_dir:
ifeq ("$(NS3_DIR)", "")
	$(error Please provide the NS3_DIR parameter, e.g. make NS3_DIR=~/ns-allinone-3.16/ns-3.16/)
endif
ifeq ($(wildcard $(NS3_DIR)/waf), )
	$(error The provided NS3_DIR parameter is not valid. NS3_DIR must contain the waf file. See README for more details)
endif

install: validate_ns3_dir
		rm -rf $(NS3_DIR)/src/$(SCR_DIR)
		cp -r redesSrc $(NS3_DIR)/src
		cd $(NS3_DIR); \
		#./waf configure --enable-examples --enable-tests; \
		./waf --run src/$(SCR_DIR)/$(PROGRAM_NAME)
