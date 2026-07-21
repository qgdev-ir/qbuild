CLI_OBJECTS := $(patsubst cli/%,$(BUILD_DIR)/obj/cli/%.o,$(call RESOLVE_SOURCES,cli,.c))

$(BUILD_DIR)/obj/cli/%.c.o: cli/%.c
	$(info > Compiling $@)
	mkdir -p $(@D)
	gcc $(GCC_FLAGS) -c $< -o $@

$(BUILD_DIR)/qbuild: $(CLI_OBJECTS) | $(BUILD_DIR)/libqbuild.so
	$(info > Linking $@)
	gcc $(GCC_FLAGS) -pie $^ -o $@ -lqbuild

BUILD_TARGETS += $(BUILD_DIR)/qbuild

