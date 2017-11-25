all: install

SCR_DIR = redes22017
NS3_DIR = /mnt/c/ns-allinone-3.27/ns-3.27

install: rm -rf $(NS3_DIR)/src/$(SCR_DIR)
		cp -r redes22017 $(NS3_DIR)/src
		cd $(NS3_DIR); \
		./waf configure --enable-examples --enable-tests; \
		./waf build
		