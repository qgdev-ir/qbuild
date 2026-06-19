QSON_OBJECTS := $(patsubst qson/%,$(BUILD_DIR)/obj/qson/%.o,$(call RESOLVE_SOURCES,qson,.c))

$(BUILD_DIR)/obj/qson/%.c.o: qson/%.c
	$(info > Compiling $@)
	mkdir -p $(@D)
	gcc $(GCC_FLAGS) -c $< -o $@

$(BUILD_DIR)/libqson.a: $(QSON_OBJECTS)
	$(info > Linking $@)
	ar rcs $@ $^

BUILD_TARGETS += $(BUILD_DIR)/libqson.a

