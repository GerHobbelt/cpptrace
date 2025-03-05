#include "platform/platform.hpp"

#if IS_WINDOWS

#include "platform/dbghelp_utils.hpp"

#if defined(CPPTRACE_UNWIND_WITH_DBGHELP) \
    || defined(CPPTRACE_GET_SYMBOLS_WITH_DBGHELP) \
    || defined(CPPTRACE_DEMANGLE_WITH_WINAPI)

#include "utils/error.hpp"
#include "utils/microfmt.hpp"
#include "utils/utils.hpp"

#include <unordered_map>

#ifndef WIN32_LEAN_AND_MEAN
 #define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <dbghelp.h>

namespace cpptrace {
namespace detail {
    dbghelp_syminit_info::dbghelp_syminit_info(void* handle, bool should_sym_cleanup, bool should_close_handle)
        : handle(handle), should_sym_cleanup(should_sym_cleanup), should_close_handle(should_close_handle) {}

    dbghelp_syminit_info::~dbghelp_syminit_info() {
        release();
    }

    void dbghelp_syminit_info::release() {
        if(!handle) {
            return;
        }
        if(should_sym_cleanup) {
            if(!SymCleanup(handle)) {
                throw internal_error("SymCleanup failed with code {}\n", GetLastError());
            }
        }
        if(should_close_handle) {
            if(!CloseHandle(handle)) {
                throw internal_error("CloseHandle failed with code {}\n", GetLastError());
            }
        }
    }

    dbghelp_syminit_info dbghelp_syminit_info::make_not_owned(void* handle) {
        return dbghelp_syminit_info(handle, false, false);
    }

    dbghelp_syminit_info dbghelp_syminit_info::make_owned(void* handle, bool should_close_handle) {
        return dbghelp_syminit_info(handle, true, should_close_handle);
    }

    dbghelp_syminit_info::dbghelp_syminit_info(dbghelp_syminit_info&& other) {
        handle = exchange(other.handle, nullptr);
        should_sym_cleanup = other.should_sym_cleanup;
        should_close_handle = other.should_close_handle;
    }

    dbghelp_syminit_info& dbghelp_syminit_info::operator=(dbghelp_syminit_info&& other) {
        release();
        handle = exchange(other.handle, nullptr);
        should_sym_cleanup = other.should_sym_cleanup;
        should_close_handle = other.should_close_handle;
        return *this;
    }

    void* dbghelp_syminit_info::get_process_handle() const {
        return handle;
    }

    dbghelp_syminit_info dbghelp_syminit_info::make_non_owning_view() const {
        return make_not_owned(handle);
    }

    std::unordered_map<HANDLE, dbghelp_syminit_info>& get_syminit_cache() {
        static std::unordered_map<HANDLE, dbghelp_syminit_info> syminit_cache;
        return syminit_cache;
    }

    dbghelp_syminit_info ensure_syminit() {
        auto lock = get_dbghelp_lock(); // locking around the entire access of the cache unordered_map
        HANDLE proc = GetCurrentProcess();
        if(get_cache_mode() == cache_mode::prioritize_speed) {
            auto& syminit_cache = get_syminit_cache();
            auto it = syminit_cache.find(proc);
            if(it != syminit_cache.end()) {
                return it->second.make_non_owning_view();
            }
        }

        auto duplicated_handle = raii_wrap<void*>(nullptr, [] (void* handle) {
            if(handle) {
                if(!CloseHandle(handle)) {
                    throw internal_error("CloseHandle failed with code {}\n", GetLastError());
                }
            }
        });
        // https://github.com/jeremy-rifkin/cpptrace/issues/204
        // https://github.com/jeremy-rifkin/cpptrace/pull/206
        // https://learn.microsoft.com/en-us/windows/win32/debug/initializing-the-symbol-handler
        // Apparently duplicating the process handle is the idiomatic thing to do and this avoids issues of
        // SymInitialize being called twice.
        // TODO: Fallback on failure
        if(!DuplicateHandle(proc, proc, proc, &duplicated_handle.get(), 0, FALSE, DUPLICATE_SAME_ACCESS)) {
            throw internal_error("DuplicateHandle failed{}", GetLastError());
        }
        if(!SymInitialize(duplicated_handle.get(), NULL, TRUE)) {
            throw internal_error("SymInitialize failed{}", GetLastError());
        }

        auto info = dbghelp_syminit_info::make_owned(exchange(duplicated_handle.get(), nullptr), true);
        // either cache and return a view or return the owning wrapper
        if(get_cache_mode() == cache_mode::prioritize_speed) {
            auto& syminit_cache = get_syminit_cache();
            auto pair = syminit_cache.insert({proc, std::move(info)});
            VERIFY(pair.second);
            return pair.first->second.make_non_owning_view();
        } else {
            return info;
        }
    }

    std::recursive_mutex dbghelp_lock;

    std::unique_lock<std::recursive_mutex> get_dbghelp_lock() {
        return std::unique_lock<std::recursive_mutex>{dbghelp_lock};
    }

}
}

#endif

#endif
