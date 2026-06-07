TEST_OBJECTS := $(patsubst test/%,$(BUILD_DIR)/obj/test/%.o,$(wildcard test/*.c))

$(BUILD_DIR)/obj/test/%.c.o: test/%.c
	$(info > Compiling $@)
	mkdir -p $(@D)
	gcc $(GCC_FLAGS) -c $< -o $@

$(BUILD_DIR)/test: $(TEST_OBJECTS) | $(BUILD_DIR)/libqson.so
	$(info > Linking $@)
	gcc $(GCC_FLAGS) -lqson -pie $^ -o $@

BUILD_TARGETS += $(BUILD_DIR)/test

