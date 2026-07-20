TEST_OBJECTS := $(patsubst test/%,$(BUILD_DIR)/obj/test/%.o,$(call RESOLVE_SOURCES,test,.c))

$(BUILD_DIR)/obj/test/%.c.o: test/%.c
	$(info > Compiling $@)
	mkdir -p $(@D)
	gcc $(GCC_FLAGS) -c $< -o $@

$(BUILD_DIR)/test: $(TEST_OBJECTS)
	$(info > Linking $@)
	gcc $(GCC_FLAGS) -pie $^ -o $@

BUILD_TARGETS += $(BUILD_DIR)/test

