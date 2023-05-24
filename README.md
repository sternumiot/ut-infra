# C Unitests Library
> This repository contains the unitest library for all C based projects.
  The repository is configured to link with a archive file and test it's functionality

## How to Install
- Clone the repo at `/opt/ut-infra` or inside your project as a submodule. Please note the git submodules
- Run `dep.sh`
- Run `make`

## How to Use 
- Copy the `unitests_makefile/example_unitests_config.mk` file to your `tests` and name it `unitests_config.mk`
- Under the `tests` dir, create a file called `Makefile` which imports your `unitests_config.mk` and `unitests_makefile/Makefile`
  Please see example in `examples/project/tests`
- Under the `tests` dir, create another `tests` dir. There you'll need to place your unitests. Please see example in `examples/project/tests`
- To adjust to a new tested project, please only modify the first section of `unitests_config.mk`
- If your project's makefile is using makefile_base repo, the tests will be invoked automatically. If not please refer to the `tests` rule in the makefile_base
## Features
- Test Constructor/Destructor 
- Disable test by comment-out

## Unitests Convention
- Separate test file per component - name convention is `[module_name]_tests.c`
- Maximum test code reuse, use ctor and dtor and macros. Please see example in https://github.com/sternumiot/agent/blob/master/tests/tests/memory_protection_tests.c
