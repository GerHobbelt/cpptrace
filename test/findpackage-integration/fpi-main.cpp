#include <cpptrace/cpptrace.hpp>

#include <cpptrace/monolithic_examples.h>

namespace {

void trace(void) {
    cpptrace::generate_trace().print();
}

void foo(int) {
    trace();
}

} // namespace

#if defined(BUILD_MONOLITHIC)
#define main  cpptrace_fpi_test_main
#endif

extern "C"
int main(void) {
    foo(0);
		return 0;
}
