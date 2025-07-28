#include "cpptrace/basic.hpp"
#include "cpptrace/utils.hpp"
#include "mydll.hpp"

#include <windows.h>

#include <iostream>

#include <cpptrace/from_current.hpp>

#include <cpptrace/monolithic_examples.h>

#if defined(BUILD_MONOLITHIC)
#define main  cpptrace_load_library_test_main
#endif

extern "C"
int main(void) {
#if defined(_WIN32)
	// generate a trace before LoadLibraryA to initialize dbghelp
    cpptrace::generate_trace().print();

    HMODULE lib = LoadLibraryA("mydll.dll");
    if (!lib) {
        std::cerr << "Failed to load DLL\n";
        return 1;
    }

    auto foo = reinterpret_cast<decltype(::foo)*>(GetProcAddress(lib, "foo"));
    if (!foo) {
        std::cerr << "Failed to get symbol\n";
        return 1;
    }

    cpptrace::load_symbols_for_file("mydll.dll");

    CPPTRACE_TRY {
        foo();
    } CPPTRACE_CATCH(...) {
        cpptrace::from_current_exception().print();
    }

    FreeLibrary(lib);

	return 0;
#else
	std::cerr << "LoadLibrary demo not implemented for your platform, sorry!\n";
	return 1;
#endif
}
