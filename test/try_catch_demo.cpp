
// README: Traces From All Exceptions

#include <cpptrace/from_current.hpp>
#include <iostream>

static void foo() {
    throw std::runtime_error("foo failed");
}

int main(void) {
    return CPPTRACE_TRY {
        foo();
		return 0;
    } CPPTRACE_CATCH(const std::exception& e) {
        std::cerr<<"Exception: "<<e.what()<<std::endl;
        cpptrace::from_current_exception().print();
		return 66;
    }
    CPPTRACE_TRY_END;
}
