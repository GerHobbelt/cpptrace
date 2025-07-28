
#pragma once

#if defined(BUILD_MONOLITHIC)

#ifdef __cplusplus
extern "C" {
#endif

int cpptrace_asi_test_main(void);
int cpptrace_benchmark_main(int argc, const char** argv);
int cpptrace_ctrace_demo_main(void);
int cpptrace_demo_main(void);
int cpptrace_fci_test_main(void);
int cpptrace_fpi_test_main(void);
int cpptrace_integration_main(void);
int cpptrace_signal_demo_main(void);
int cpptrace_signal_tracer_main(void);
int cpptrace_tests_main(int argc, const char** argv);
int cpptrace_try_catch_demo_main(void);
int cpptrace_load_library_test_main(void);
int cpptrace_link_test_main(void);

int cpptrace_dwarfdump_tool_main(int argc, const char** argv);
int cpptrace_resolver_tool_main(int argc, const char** argv);
int cpptrace_symbol_tables_tool_main(int argc, const char** argv);

#ifdef __cplusplus
}
#endif

#endif
