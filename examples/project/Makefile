#v1.0

include unitests_config.mk
include quality_tools.mk
print-%	: ; @echo $* = $($*)

C_INCLUDES =  $(addprefix -I, $(HEADERS_DIR))
C_SOURCES := $(shell find $(LOCAL_TESTS_DIR) -type f -regex ".*\.c")
HEADER_FILES := $(shell find $(HEADERS_DIR) -type f -regex ".*\.h")

CFLAGS = $(C_INCLUDES) $(UT_CFLAGS)
LINKER_FLAGS = $(UT_LDFLAGS)


# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o))) $(UT_PLAN_PATH:.c=.o) $(TARGET_ARCHIVE)
vpath %.c $(sort $(dir $(C_SOURCES)))


$(BUILD_DIR)/%.o: %.c Makefile $(HEADER_FILES)
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $< -o $@


.PHONY: all
all : $(BUILD_DIR)/$(OUTPUT_FILE)


.PHONY: clean
ifndef BUILD_DIR
.ABORT 	# If BUILD_DIR is not set / will be deleted
endif
clean: $(BUILD_DIR) 
	@rm -fr $^/*


$(UT_PLAN_PATH): $(C_SOURCES) $(HEADER_FILES) $(UT_GENERATOR_SCRIPT) $(UT_ARCHIVE_PATH)
	@echo Generated Test Plan
	@python $(UT_GENERATOR_SCRIPT) "tests/*.c" $@ || (echo $(UT_GENERATOR_SCRIPT) "failed with code: $$?"; exit 1)


$(BUILD_DIR)/$(OUTPUT_FILE): $(OBJECTS)
	$(CC) $^ -o $@ $(LINKER_FLAGS)

	@echo "###################################################################################"
	@echo "################################## Running tests ##################################"
	@echo "###################################################################################"
	@echo ""
	@$(BUILD_DIR)/$(OUTPUT_FILE) 2>&1 | tee $(UT_OUTPUT)
	$(call sternum_analyse, $(BUILD_DIR)/$(OUTPUT_FILE), $(UT_VALGRIND_OUTPUT))
	@echo ""
	@echo "###################################################################################"


