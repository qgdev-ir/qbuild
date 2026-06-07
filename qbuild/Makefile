QBUILD_OBJECTS := $(patsubst qbuild/%,$(BUILD_DIR)/obj/qbuild/%.o,$(wildcard qbuild/*.c))

$(BUILD_DIR)/obj/qbuild/%.c.o: qbuild/%.c
	$(info > Compiling $@)
	mkdir -p $(@D)
	gcc $(GCC_FLAGS) -c $< -o $@

$(BUILD_DIR)/qbuild: $(QBUILD_OBJECTS) | $(BUILD_DIR)/libqson.so
	$(info > Linking $@)
	gcc $(GCC_FLAGS) -lqson -pie $^ -o $@

BUILD_TARGETS += $(BUILD_DIR)/qbuild

