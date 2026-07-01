# TODO: replace this simple build system with qbuild before first release

.SILENT:
.SECONDARY:

RESOLVE_SOURCES = $(shell find qson $1 -name "*$2")

BUILD_DIR := build
export LD_LIBRARY_PATH := $(BUILD_DIR)
GCC_FLAGS := -O1 -fPIC -L$(BUILD_DIR) -I.

include qson/Makefile
include qstruct/Makefile
include qbuild/Makefile
include test/Makefile

BUILD_TARGETS ?=

.DEFAULT_GOAL := build
.PHONY: build
build: $(BUILD_TARGETS)

.PHONY: clean
clean:
	rm -fr build

.PHONY: run
run: $(BUILD_DIR)/qbuild
	 $(BUILD_DIR)/qbuild

.PHONY: test
test: $(BUILD_DIR)/test
	 $(BUILD_DIR)/test

