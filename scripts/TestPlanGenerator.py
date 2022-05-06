import os
import argparse
import glob
import re
import traceback



C_HEADER_PROLOGUE = """
#ifndef __TEST_PLAN_H__
#define __TEST_PLAN_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* AUTO GENERATED - DO NOT CHANGE THIS FILE MANUALLY */
#include "test.h"
#include <stdbool.h>
"""

C_HEADER_EPILOGUE = """
#ifdef __cplusplus
}
#endif

#endif /* __TEST_PLAN_H__ */
"""

TEST_FUNCTION_DECLARATION_REGEX = "TEST_METHOD\((?P<function_name>\w*)[, ]*(?P<constructor>\w*)[, ]*(?P<destructor>\w*).*\)"
FIND_COMMENTED_CODE_REGEX = "((\/\*([^*]|[\r\n]|(\*+([^*\/]|[\r\n])))*\*+\/)|(\/\/.*))"

TEST_PLAN_ARRAY_PROLOGUE = "TestCase tests[] = {\n"
TEST_PLAN_ARRAY_EPILOGUE = "};\n"


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('path', help='The name of the file or dir with file pattern i.e. \"dir/*\"')
    parser.add_argument('output', help='The name of output header file')

    args = parser.parse_args()
    try:
        test_cases = []
        inactive_test_cases = []
        for fPath in glob.glob(args.path):
            with open(fPath, 'r') as f:
                file_content = f.read()
                commented_code = re.findall(FIND_COMMENTED_CODE_REGEX, file_content)
                matched_unitests = re.findall(TEST_FUNCTION_DECLARATION_REGEX, file_content)
                for function_name, constructor, destructor in matched_unitests:
                    matching = [s for s in commented_code if function_name in s[0]]
                    if len(matching) == 0:
                        test_cases += [(function_name, constructor, destructor)]

        c_header_string = C_HEADER_PROLOGUE
        detected_utility_functions = []
        for (function_name, constructor, destructor) in test_cases:
            for utility_func in [constructor, destructor]:
                if utility_func is not '' and utility_func != "NULL" and utility_func not in detected_utility_functions:
                    c_header_string += ("DECLARE_FUNCTION({});\n".format(utility_func))
                    detected_utility_functions.append(utility_func)
            c_header_string += ("DECLARE_FUNCTION({});\n".format(function_name))

        c_header_string += "\n{}".format(TEST_PLAN_ARRAY_PROLOGUE)
        for function_name, constructor, destructor in test_cases:
            if constructor is '':
                constructor = "NULL"
            if destructor is '':
                destructor = "NULL"
            c_header_string += ("{}, \"{}\", {}, {},\n").format(function_name, function_name, constructor, destructor))

        for function_name, constructor, destructor in inactive_test_cases:
            c_header_string += ("(NULL, \"{}\", NULL, NULL),\n".format(function_name))

        c_header_string += TEST_PLAN_ARRAY_EPILOGUE

        c_header_string += C_HEADER_EPILOGUE
        if os.path.exists(args.output):
            os.remove(args.output)
        with open(args.output, 'w') as c_header_file:
            c_header_file.write(c_header_string)

    except Exception as e:
        print(e)
        print(traceback.format_exc())
        if os.path.exists(args.output):
            os.remove(args.output)
        exit(1)


if __name__ == "__main__":
    main()


