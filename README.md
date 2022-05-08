# C Unitests Library
> This repository contains the unitest library for all C based projects

## How to Install
- Clone the repo at `/opt`
- Run `dep.sh`
- Run `make`

## How to Use
- Copy the `tests` dir under examples/project to your project and add unitests under the `tests/tests/` directory
- Add the following `"${MAKE}" -j$(CPU_COUNT) -C $(TESTS_SRC_DIR)` to the final makefile rule
## Features
- Test Constructor/Destructor 
- Disable test by comment-out

## Unitests Convention
- Separate test file per component - name convention is `[module_name]_tests.c`
- Maximum test code reuse, use ctor and dtor and macros. Please see example in https://github.com/sternumiot/agent/blob/master/tests/tests/memory_protection_tests.c
