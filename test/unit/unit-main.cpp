#include <gtest/gtest.h>

#ifdef TEST_MODULE
import cpptrace;
#else
#include <cpptrace/cpptrace.hpp>
#endif

#include "monolithic_examples.h"

#if defined(BUILD_MONOLITHIC)
#define main  cpptrace_tests_main
#endif

extern "C"
int main(int argc, const char** argv) {
    testing::InitGoogleTest(&argc, argv);
    cpptrace::absorb_trace_exceptions(false);
    cpptrace::use_default_stderr_logger();
    return RUN_ALL_TESTS();
}
