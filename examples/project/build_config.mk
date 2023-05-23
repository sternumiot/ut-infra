OUTPUT_FILE = dummy.a
EXTERNAL_HEADERS_SRC =

CC = gcc
FINAL_STAGE = @ar srv $@ $^

TESTS_SRC_DIR = tests
SRC_DIR = src
HEADERS_DIR = include
BUILD_DIR = build

C_INCLUDES = -I$(HEADERS_DIR)
C_DEFS =
CFLAGS = $(C_DEFS) $(C_INCLUDES) -Wa,-aln=$(@:.o=.s)  -g -O0
