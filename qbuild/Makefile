QBUILD_OBJECTS := $(patsubst qbuild/%,$(BUILD_DIR)/obj/qbuild/%.o,$(call RESOLVE_SOURCES,qbuild,.c))

$(BUILD_DIR)/obj/qbuild/%.c.o: qbuild/%.c
	$(info > Compiling $@)
	mkdir -p $(@D)
	gcc $(GCC_FLAGS) -c $< -o $@

$(BUILD_DIR)/libqbuild.so: $(QBUILD_OBJECTS)
	$(info > Linking $@)
	gcc $(GCC_FLAGS) --shared $^ -o $@ -lqson -lqstruct

BUILD_TARGETS += $(BUILD_DIR)/libqbuild.so

