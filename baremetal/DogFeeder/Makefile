# you can set this to 1 to see all commands that are being run
VERBOSE ?= 1

# Output directory
INT_BUILD ?= IntegrationTest
# Output directory
REL_BUILD ?= Release

ifeq ($(VERBOSE),1)
export Q :=
export VERBOSE := 1
else
export Q := @
export VERBOSE := 0
endif

# make all : format the code using clang-tiny, document by doxygen, apply unittest coverage and zip everythin up

all: inst_sip_int inst_sip_rel default_int default_rel

Integration: inst_sip_int default_int #flash_int
Int_Flash : inst_sip_int default_int flash_int

Release: inst_sip_rel default_rel package_rel #flash_rel


# install sip lib for integration target
.PHONY: inst_sip_int
inst_sip_int:
	if [ -d "$(INT_BUILD)/build" ]; then \
	$(Q) cd $(INT_BUILD)/build;  ninja install_sip_lib; \
	fi



# build integration target
.PHONY: default_int
default_int: | $(INT_BUILD)
	$(Q) cd $(INT_BUILD);  idf.py build;
# flash integration target
.PHONY: flash_int
flash_int: | $(INT_BUILD)
	$(Q) cd $(INT_BUILD);  idf.py -p /dev/ttyUSB0 flash monitor;

# flash integration target slow
.PHONY: flash_int_slow
flash_int_slow: | $(INT_BUILD)
	$(Q) cd $(INT_BUILD);  idf.py -b 115200 -p /dev/ttyUSB0 flash monitor;

# install sip lib for release target
.PHONY: inst_sip_rel
inst_sip_rel:
	if [ -d "$(REL_BUILD)/build" ]; then \
	$(Q) cd $(REL_BUILD)/build;  ninja install_sip_lib; \
	fi


# build release target
.PHONY: default_rel
default_rel: | $(REL_BUILD)
	$(Q) cd $(REL_BUILD);  idf.py build;

# .zip release target
.PHONY: package_rel
package_rel: |
	$(Q)cd $(REL_BUILD)/build; ninja package_source;

# flash release target
.PHONY: flash_rel
flash_rel: | $(REL_BUILD)
	$(Q) cd $(REL_BUILD);  idf.py -p /dev/ttyUSB0 flash monitor;


