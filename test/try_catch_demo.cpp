
// README: Traces From All Exceptions

#include <cpptrace/from_current.hpp>
#include <iostream>

#include <cpptrace/monolithic_examples.h>

static void foo() {
    throw std::runtime_error("foo failed");
}

#if defined(BUILD_MONOLITHIC)
#define main  cpptrace_try_catch_demo_main
#endif

int main(void) {
	int rv = 1;
    CPPTRACE_TRY {
        foo();
		rv = 0;
    } CPPTRACE_CATCH(const std::exception& e) {
        std::cerr<<"Exception: "<<e.what()<<std::endl;
        cpptrace::from_current_exception().print();
		rv = 66;
    }
	return rv;
}
