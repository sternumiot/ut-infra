OUTPUT_FILE = dummy.a
# Files that will be copied to the build dir
EXTERNAL_HEADERS_SRC =

CC = gcc
FINAL_STAGE = @ar srv $@ $^

TESTS_SRC_DIR = tests
SRC_DIR = src
HEADER_DIRS = include
BUILD_DIR = build

C_INCLUDES =  $(addprefix -I, $(HEADER_DIRS))
C_DEFS =
CFLAGS = $(C_DEFS) $(C_INCLUDES) -Wa,-aln=$(@:.o=.s)  -g -O0
