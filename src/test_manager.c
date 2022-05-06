#include <stdio.h>
#include <time.h>
#include <pthread.h>

#include "test.h"
 
extern TestPlan g_test_plan;
void execute_test(TestCase* test_case);

static size_t test_index = 0;
static size_t tests_passed_count = 0;
static double ut_runtime = 0;
static double total_ut_runtime = 0;

void assert_failed(const char* assert_type, const char* expression, const char* file_name, int line_number, const char* function) {
    printf("[\033[0;31mFAILED\033[0m] | assert [%s] failed with expression [%s] at %s:%d [%s]\n", assert_type, expression, file_name, line_number, function);
    pthread_exit((void*)1);
}

void compare_assert_failed(const char* assert_type, const char* arg1_name, size_t arg1, const char* arg2_name, size_t arg2, const char* expression, const char* file_name, int line_number, const char* function) {
    printf("[\033[0;31mFAILED\033[0m] | assert [%s] failed with expression %s(%zx) %s %s(%zx) at %s:%d [%s]\n", assert_type, arg1_name, arg1, expression, arg2_name, arg2, file_name, line_number, function);
    pthread_exit((void*)1);
}

void* test_wrapper(void* arg) {
    struct timespec start, end;

    TestCase* test_case = (TestCase*)arg;

    if (test_case->constructor != NULL) {
        test_case->constructor();
    }
    clock_gettime(CLOCK_REALTIME, &start);
    test_case->function(); /* The assert function will set the thread exit code */
    clock_gettime(CLOCK_REALTIME, &end);
    
    if (test_case->destructor != NULL) {
        test_case->destructor();
    }

    ut_runtime = ((double)end.tv_sec + (double)end.tv_nsec / 1000000000.0) - ((double)start.tv_sec + (double)start.tv_nsec / 1000000000.0);
    total_ut_runtime += ut_runtime;

    return NULL;
}

void execute_test(TestCase* test_case) {
    test_index++;
    printf("Running Test |%4d|  %-64s | ", test_index, test_case->function_name);
    fflush(stdout);

    if (test_case->function) {
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, test_wrapper, (void*)test_case);
        int exit_code = 0;
        pthread_join(thread_id, (void*)&exit_code);

        if (exit_code == 0) {
            // If we got here the test passed
            printf("time: %6.2lf seconds | [\033[0;32mPASSED\033[0m]\n", ut_runtime);
            tests_passed_count++;
        }
    } else {
        printf("[\033[0;33mTEST DISABLED\033[0m]");
    }    
}


int main(int argc, char **argv) {
    for(size_t i = 0 ; i < g_test_plan.count ; i++) {
        execute_test(g_test_plan.tests + i);
    }

    if (tests_passed_count != g_test_plan.count) {
        printf("[\033[0;31mFAILED - Tests Stats: %zd/%zd Total Runtime: %f secondsFAILED\033[0m]\n", tests_passed_count, test_index, total_ut_runtime);
        return -1;
    }
    printf("[\033[0;32mPASSED - Tests Stats: %zd/%zd Total Runtime: %f seconds\033[0m]\n", tests_passed_count, test_index, total_ut_runtime);

    return 0;
 }
 