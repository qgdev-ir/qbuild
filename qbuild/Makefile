QBUILD_OBJECTS := $(patsubst qbuild/%,$(BUILD_DIR)/obj/qbuild/%.o,$(call RESOLVE_SOURCES,qbuild,.c))

$(BUILD_DIR)/obj/qbuild/%.c.o: qbuild/%.c
	$(info > Compiling $@)
	mkdir -p $(@D)
	gcc $(GCC_FLAGS) -c $< -o $@

$(BUILD_DIR)/qbuild: $(QBUILD_OBJECTS) | $(BUILD_DIR)/libqstruct.a
	$(info > Linking $@)
	gcc $(GCC_FLAGS) -pie $^ -o $@ -lqson -lqstruct

BUILD_TARGETS += $(BUILD_DIR)/qbuild

