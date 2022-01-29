# you can set this to 1 to see all commands that are being run
VERBOSE ?= 0

# Output directory
BUILDRESULTS ?= build

# build options
OPTIONS ?=

INTERNAL_OPTIONS =

# This skeleton is built for CMake's Ninja generator
export CMAKE_GENERATOR=Ninja

ifeq ($(VERBOSE),1)
export Q :=
export VERBOSE := 1
else
export Q := @
export VERBOSE := 0
endif

# make all : format the code using clang-tiny, document by doxygen, apply unittest coverage and zip everythin up

all: format document complexity complexity-html cppcheck-html coverage package

test: format default cppUTest

test-specific: format default cppUTest complexity-specific tidy-specific cppcheck-specific

# default build target
.PHONY: default
default: | $(BUILDRESULTS)/build.ninja
	$(Q)ninja -C $(BUILDRESULTS) 

# default build target
.PHONY: cppUTest
cppUTest: | $(BUILDRESULTS)/build.ninja
	$(Q)ninja -C $(BUILDRESULTS) simple_test
# default build target
.PHONY: cppcheck
cppcheck: | $(BUILDRESULTS)/build.ninja
	$(Q)ninja -C $(BUILDRESULTS) cppcheck
	.PHONY: cppcheck-html
cppcheck-html: | $(BUILDRESULTS)/build.ninja
	$(Q)ninja -C $(BUILDRESULTS) cppcheck-html
# default build target
.PHONY: complexity
complexity: | $(BUILDRESULTS)/build.ninja
	$(Q)ninja -C $(BUILDRESULTS) complexity
# default build target
.PHONY: complexity-html
complexity-html: | $(BUILDRESULTS)/build.ninja
	$(Q)ninja -C $(BUILDRESULTS) complexity-html
# default build target
.PHONY: complexity-specific
complexity-specific: | $(BUILDRESULTS)/build.ninja
	$(Q)ninja -C $(BUILDRESULTS) complexity-specific

# default build target
.PHONY: tidy-specific
tidy-specific: | $(BUILDRESULTS)/build.ninja
	$(Q)ninja -C $(BUILDRESULTS) tidy-specific

# default build target
.PHONY: cppcheck-specific
cppcheck-specific: | $(BUILDRESULTS)/build.ninja
	$(Q)ninja -C $(BUILDRESULTS) cppcheck-specific
	
# RULE: run cmake .. inside $(BUILDRESULTS) if build is not configured
$(BUILDRESULTS)/build.ninja:
	$(Q) cmake -B ${BUILDRESULTS} 


# default build target
.PHONY: format
format: | $(BUILDRESULTS)/build.ninja
	$(Q)ninja -C $(BUILDRESULTS) $(OPTIONS) format

# default build target
.PHONY: document
document: | $(BUILDRESULTS)/build.ninja
	$(Q)ninja -C $(BUILDRESULTS) $(OPTIONS) docs


# default build target
.PHONY: coverage
coverage: | $(BUILDRESULTS)/build.ninja
	$(Q)ninja -C $(BUILDRESULTS) $(OPTIONS) coverage

# default build target
.PHONY: package
package: | $(BUILDRESULTS)/build.ninja
	$(Q)ninja -C $(BUILDRESULTS) $(OPTIONS) package_source


# clean the build
.PHONY: clean
clean:
	$(Q) if [ -d "$(BUILDRESULTS)" ]; then ninja -C $(BUILDRESULTS) clean; fi
# remove folder ${BUILDRESULTS}
.PHONY: distclean
distclean:
	$(Q) rm -rf $(BUILDRESULTS)

# Manually Reconfigure a target, esp. with new options
.PHONY: reconfig
reconfig:
	$(Q) cmake -B $(BUILDRESULTS) $(OPTIONS)

