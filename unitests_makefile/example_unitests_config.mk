#v1.0

# UT User Configuration
#######################

# Project Specific
HEADER_DIRS = ../include
TARGET_ARCHIVE = ../build/out/dummy.a

BUILD_DIR = ../build/tests
LOCAL_TESTS_DIR = tests/

UT_USER_CFLAGS = -g -O0
UT_USER_LDFLAGS =

UT_RUN_EXTRA_ANALYSIS=1 # Runs Valgrind, gcov, etc.

# Host Specific
UT_INFRA_INSTALL_PATH = ../../../

############################################
# UT System Configuration - Edit Cautiously
############################################
UT_ARCHIVE_PATH=$(UT_INFRA_INSTALL_PATH)/build/out/libunitests.a
UT_HEADER_PATH=$(UT_INFRA_INSTALL_PATH)/include
UT_GENERATOR_SCRIPT = $(UT_INFRA_INSTALL_PATH)/scripts/TestPlanGenerator.py
UT_PLAN_PATH = $(BUILD_DIR)/test_plan.c

UT_VALGRIND_OUTPUT = $(BUILD_DIR)/valgrind_output.txt
UT_OUTPUT = $(BUILD_DIR)/unitests_output.txt

UT_CFLAGS=-I$(UT_HEADER_PATH) $(UT_USER_CFLAGS) 
UT_LDFLAGS= $(UT_ARCHIVE_PATH) $(UT_USER_LDFLAGS) -lpthread 

OUTPUT_FILE = test_executable

# Define TOOLCHAIN to make sure your unitests will be compiled exactly as your target archive
ifdef TOOLCHAIN
CC=$(TOOLCHAIN)-gcc
else
CC=gcc
endif
