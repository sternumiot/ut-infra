#v1.0

# UT User Configuration
#######################

# Project Specific
HEADERS_DIR = ../include
TARGET_ARCHIVE = ../build/out/dummy.a

BUILD_DIR = ../build/tests
LOCAL_TESTS_DIR = tests/

UT_USER_CFLAGS = -g -O0
UT_USER_LDFLAGS =



############################################
# UT System Configratuion - Edit Cautiously
############################################
UT_INSTALL_PATH = ../../../

UT_ARCHIVE_PATH=$(UT_INSTALL_PATH)/build/out/libunitests.a
UT_HEADER_PATH=$(UT_INSTALL_PATH)/build/out
UT_GENERATOR_SCRIPT = $(UT_INSTALL_PATH)/scripts/TestPlanGenerator.py
UT_PLAN_PATH = $(BUILD_DIR)/test_plan.c

UT_VALGRIND_OUTPUT = $(BUILD_DIR)/valgrind_output.txt
UT_OUTPUT = $(BUILD_DIR)/unitests_output.txt

UT_CFLAGS=-I$(UT_HEADER_PATH) $(UT_USER_CFLAGS) 
UT_LDFLAGS= $(UT_ARCHIVE_PATH) $(UT_USER_LDFLAGS) -lpthread 

OUTPUT_FILE = test_executable
CC = gcc