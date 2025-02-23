#include <cpptrace/cpptrace.hpp>

#include "monolithic_examples.h"

namespace {

void trace(void) {
    cpptrace::generate_trace().print();
}

void foo(int) {
    trace();
}

} // namespace

#if defined(BUILD_MONOLITHIC)
#define main  cpptrace_fci_test_main
#endif

extern "C"
int main(void) {
    foo(0);
		return 0;
}
