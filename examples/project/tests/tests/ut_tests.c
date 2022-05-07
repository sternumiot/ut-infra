#include "test.h"
#include "dummy.h"

/* Optional Methods */
CTOR_METHOD(init) {
    // Dummy
    dummy();
}
DTOR_METHOD(fini) {
    // Dummy
}
/* **************** */

TEST_METHOD(ut_test1) {
    ASSERT_EQUAL(1, 1);
}

TEST_METHOD(ut_test2, init) {
    ASSERT_NOT_EQUAL(1, 1);
}

TEST_METHOD(ut_test3, init, fini) {
    ASSERT_NOT_EQUAL(1, 1);
}

// TEST_METHOD(ut_test4, init, fini) {
//     ASSERT_NOT_EQUAL(1, 1);
// }


/*TEST_METHOD(ut_test4, init, fini) {
    ASSERT_NOT_EQUAL(1, 1);
}
*/