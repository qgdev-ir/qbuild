# TODO: replace this simple build system with qbuild before first release

.SILENT:
.SECONDARY:

BUILD_DIR := build
export LD_LIBRARY_PATH := $(BUILD_DIR)

include qson/Makefile
include qbuild/Makefile

BUILD_TARGETS ?=

.DEFAULT_GOAL := build
.PHONY: build
build: $(BUILD_TARGETS)

.PHONY: clean
clean:
	rm -fr build

.PHONY: run
run:
	 $(BUILD_DIR)/qbuild

