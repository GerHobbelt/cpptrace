
#include <cpptrace/monolithic_examples.h>

// define a name for the monolith
#define USAGE_NAME   "cpptrace"

// load the monolithic definitions which you need for the dispatch table:
#include "monolithic_main_internal_defs.h"

// declare your own monolith dispatch table:
MONOLITHIC_CMD_TABLE_START()

{ "benchmark", { .f = cpptrace_benchmark_main } },
{ "asi_test", { .f = cpptrace_asi_test_main } },
{ "ctrace_demo", { .f = cpptrace_ctrace_demo_main } },
{ "demo", { .f = cpptrace_demo_main } },
{ "fci_test", { .f = cpptrace_fci_test_main } },
{ "fpi_test", { .f = cpptrace_fpi_test_main } },
{ "integration", { .f = cpptrace_integration_main } },
{ "signal_demo", { .f = cpptrace_signal_demo_main } },
{ "signal_tracer", { .f = cpptrace_signal_tracer_main } },
{ "try_catch_demo", { .f = cpptrace_try_catch_demo_main } },
{ "tests", { .f = cpptrace_tests_main } },

{ "dwarfdump", { .fa = cpptrace_dwarfdump_tool_main } },
{ "resolver", { .fa = cpptrace_resolver_tool_main } },
{ "symbol_tables", { .fa = cpptrace_symbol_tables_tool_main } },

MONOLITHIC_CMD_TABLE_END();

// load the monolithic core dispatcher
#include "monolithic_main_tpl.h"
