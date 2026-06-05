QSON_OBJECTS := $(patsubst qson/%,$(BUILD_DIR)/obj/qson/%.o,$(wildcard qson/*.c))

$(BUILD_DIR)/obj/qson/%.c.o: qson/%.c
	$(info > Compiling $@)
	mkdir -p $(@D)
	gcc -fPIC -c $< -o $@

$(BUILD_DIR)/libqson.so: $(QSON_OBJECTS)
	$(info > Linking $@)
	gcc -shared $^ -o $@

BUILD_TARGETS += $(BUILD_DIR)/libqson.so

