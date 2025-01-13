#ifndef _WIN32
#include <unistd.h>
#else
#endif

#include <cstdio>
#include <iostream>

#include <cpptrace/cpptrace.hpp>

#include "monolithic_examples.h"

#if defined(BUILD_MONOLITHIC)
#define main  cpptrace_signal_tracer_main
#endif

extern "C"
int main(void) {
    cpptrace::object_trace trace;
    while(true) {
        cpptrace::safe_object_frame frame;
        std::size_t res = fread(&frame, sizeof(frame), 1, stdin);
        if(res == 0) {
            break;
        } else if(res != 1) {
            std::cerr<<"Oops, size mismatch "<<res<<" "<<sizeof(frame)<<std::endl;
            break;
        } else {
            trace.frames.push_back(frame.resolve());
        }
    }
    trace.resolve().print();
		return 0;
}
