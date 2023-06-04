#v1.0
print-%	: ; @echo $* = $($*)

C_INCLUDES =  $(addprefix -I, $(HEADER_DIRS))
C_SOURCES := $(shell find $(LOCAL_TESTS_DIR) -type f -regex ".*\.c")
HEADER_FILES := $(shell find $(HEADER_DIRS) -type f -regex ".*\.h")

CFLAGS = $(C_INCLUDES) $(UT_CFLAGS)
LINKER_FLAGS = $(UT_LDFLAGS) $(TARGET_ARCHIVE)


# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o))) $(UT_PLAN_PATH:.c=.o)
vpath %.c $(sort $(dir $(C_SOURCES)))


$(BUILD_DIR)/%.o: %.c Makefile $(HEADER_FILES)
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $< -o $@


.PHONY: all
all : $(BUILD_DIR)/$(OUTPUT_FILE)


.PHONY: clean
ifndef BUILD_DIR
$(error If BUILD_DIR is not set `/` will be deleted)
endif
clean: $(BUILD_DIR) 
	@rm -fr $^/*


define sternum_analyse
	@echo "################################# Running Valgrind #################################"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $(1) 2>&1 | tee $(2)
	@echo "###################################################################################"
	
	@echo "################################# Running gcov #################################"
endef

# Always try to build UT incase it was updated
.PHONY: $(UT_ARCHIVE_PATH)
$(UT_ARCHIVE_PATH):
		@${MAKE} -C $(UT_INFRA_INSTALL_PATH)

$(UT_PLAN_PATH): $(C_SOURCES) $(HEADER_FILES) $(UT_GENERATOR_SCRIPT)
	@echo Generated Test Plan
	@python $(UT_GENERATOR_SCRIPT) "tests/" $@ || (echo $(UT_GENERATOR_SCRIPT) "failed with code: $$?"; exit 1)


# If make gets a fatal signal while a shell is executing, it may delete the target file. Setting .PRECIOUS target prevents that
.PRECIOUS: $(BUILD_DIR)/$(OUTPUT_FILE)
$(BUILD_DIR)/$(OUTPUT_FILE): $(OBJECTS) $(TARGET_ARCHIVE) $(UT_ARCHIVE_PATH)
	$(CC) $^ -o $@ $(LINKER_FLAGS)

	@echo "###################################################################################"
	@echo "################################## Running tests ##################################"
	@echo "###################################################################################"
	@echo ""
	@$(BUILD_DIR)/$(OUTPUT_FILE) 2>&1 | tee $(UT_OUTPUT)
	$(call sternum_analyse, $(BUILD_DIR)/$(OUTPUT_FILE), $(UT_VALGRIND_OUTPUT))
	@echo ""
	@echo "###################################################################################"


