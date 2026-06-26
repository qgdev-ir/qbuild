QSTRUCT_OBJECTS := $(patsubst qstruct/%,$(BUILD_DIR)/obj/qstruct/%.o,$(call RESOLVE_SOURCES,qstruct,.c))

$(BUILD_DIR)/obj/qstruct/%.c.o: qstruct/%.c
	$(info > Compiling $@)
	mkdir -p $(@D)
	gcc $(GCC_FLAGS) -c $< -o $@

$(BUILD_DIR)/libqstruct.a: $(QSTRUCT_OBJECTS)
	$(info > Linking $@)
	ar rcs $@ $^

BUILD_TARGETS += $(BUILD_DIR)/libqstruct.a

