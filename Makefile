# ------------------------------------------------
# Generic Makefile (based on gcc)
# ------------------------------------------------

#Makefile debugging. usage: make print-VARIABLE
print-%	: ; @echo $* = $($*)


#######################################
# Makefile Configuration
#######################################
CC = gcc
AR = ar

OUTPUT_FILE = libsternum_unitests.a
RECOMPILATION_DEPENDENCIES := Makefile $(HEADER_FILES)

# Paths
SRC_DIR = src
HEADERS_DIR = include
BUILD_DIR= build

# C Defs
C_INCLUDES = -I$(HEADERS_DIR)
C_DEFS =
#-m32
CFLAGS = $(C_DEFS) $(C_INCLUDES) -Wa,-aln=$(@:.o=.s)  -g -O0

#######################################
# Rules
#######################################

C_SOURCES :=  $(shell find $(SRC_DIR) -type f -regex ".*\.c")
ASM_SOURCES := $(shell find $(SRC_DIR)/ -type f -regex ".*\.S")
HEADER_FILES := $(shell find $(HEADERS_DIR) -type f -regex ".*\.h")

OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.S=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
vpath %.S $(sort $(dir $(ASM_SOURCES)))


$(BUILD_DIR)/%.o: %.S $(RECOMPILATION_DEPENDENCIES)
	@mkdir -p $(@D)
	@$(CC) -c $(CFLAGS) $< -o $@


$(BUILD_DIR)/%.o: %.c $(RECOMPILATION_DEPENDENCIES)
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $(BUILD_IDENTIFIER_LDFLAGS) $< -o $@

$(BUILD_DIR)/$(OUTPUT_FILE): $(OBJECTS)
	@mkdir -p $(@D)
	@$(AR) srv $@ $^

.PHONY: all
all : $(BUILD_DIR)/$(OUTPUT_FILE)


.PHONY: clean
clean: $(BUILD_DIR) 
	@rm -fr $^/*

