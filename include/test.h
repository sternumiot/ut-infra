// v1.0

#ifndef __TEST_H__
#define __TEST_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdlib.h>
#include <stdbool.h>


void assert_failed(const char* assert_type, const char* expression, const char* file_name, int line_number, const char* function);
void assert_failed_message(const char* assert_type, const char* expression, const char* message, const char* file_name, int line_number, const char* function);
void compare_assert_failed(const char* assert_type, const char* arg1_name, size_t arg1, const char* arg2_name, size_t arg2, const char* expression, const char* file_name, int line_number, const char* function);

#define ASSERT_TRUE(expr) \
    if (!(expr)) { \
        assert_failed("ASSERT_TRUE", #expr, __FILE__, __LINE__, __FUNCTION__); \
    }

#define ASSERT_FALSE(expr) \
    if (expr) { \
        assert_failed("ASSERT_FALSE", #expr, __FILE__, __LINE__, __FUNCTION__); \
    }

#define ASSERT_TRUE_MESSAGE(expr, message) \
    if (!(expr)) { \
        assert_failed_message("ASSERT_TRUE", #expr, message, __FILE__, __LINE__, __FUNCTION__); \
    }

#define ASSERT_FALSE_MESSAGE(expr, message ) \
    if (expr) { \
        assert_failed_message("ASSERT_FALSE", #expr, message, __FILE__, __LINE__, __FUNCTION__); \
    }

#define ASSERT_EQUAL(ACTUAL, EXPECTED) \
    if ((ACTUAL) != (EXPECTED)) { \
        compare_assert_failed("ASSERT_EQUAL", #ACTUAL, (size_t)ACTUAL, #EXPECTED, (size_t)EXPECTED, "!=", __FILE__, __LINE__, __FUNCTION__); \
    }

#define ASSERT_NOT_EQUAL(ACTUAL, EXPECTED) \
    if ((ACTUAL) == (EXPECTED)) { \
        compare_assert_failed("ASSERT_NOT_EQUAL", #ACTUAL, (size_t)ACTUAL, #EXPECTED, (size_t)EXPECTED, "==", __FILE__, __LINE__, __FUNCTION__); \
    }

#define ASSERT_NULL(ACTUAL, EXPECTED) \
    if ((ACTUAL) != NULL) { \
        compare_assert_failed("ASSERT_NULL", #ACTUAL, (size_t)ACTUAL, "NULL", (size_t)EXPECTED, "!=", __FILE__, __LINE__, __FUNCTION__); \
    }

#define ASSERT_NOT_NULL(ACTUAL, EXPECTED) \
    if ((ACTUAL) == NULL) { \
        compare_assert_failed("ASSERT_NOT_NULL", #ACTUAL, (size_t)ACTUAL, "NULL", (size_t)EXPECTED, "==", __FILE__, __LINE__, __FUNCTION__); \
    }


typedef void (*function)(void);

typedef struct TestCase {
	function function;
	char* function_name;
    function constructor;
    function destructor;
} TestCase;

typedef struct TestPlan {
	TestCase* tests;
    size_t count;
} TestPlan;

#define METHOD(FUNCTION) void FUNCTION(void)
#define TEST_METHOD(FUNCTION, ...)  METHOD(FUNCTION)
#define CTOR_METHOD(FUNCTION) METHOD(FUNCTION)
#define DTOR_METHOD(FUNCTION) METHOD(FUNCTION)

#define DECLARE_FUNCTION(FUNCTION) extern TEST_METHOD(FUNCTION)


#ifdef __cplusplus
}
#endif

#endif /* __TEST_H__ */
