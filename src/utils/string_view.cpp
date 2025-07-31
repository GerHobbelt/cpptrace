#include "utils/string_view.hpp"

#include "utils/error.hpp"
#include "utils/microfmt.hpp"

#include <algorithm>
#include <cstring>

// -----------------------------------------------------------------------------
// C++ Version Check
// -----------------------------------------------------------------------------

// Enforce C++17 as the minimum.
#if defined(_MSVC_LANG)
#if _MSVC_LANG < 201703L
#error "C++ versions less than C++17 are not supported."
#endif  // _MSVC_LANG < 201703L
#elif defined(__cplusplus)
#if __cplusplus < 201703L
#error "C++ versions less than C++17 are not supported."
#endif  // __cplusplus < 201703L
#endif

CPPTRACE_BEGIN_NAMESPACE
namespace detail {
	// warning C5041: 'npos': out-of-line definition for constexpr static data member is not needed and is deprecated in C++17
#if 0
	constexpr std::size_t string_view::npos;
#endif

    char string_view::operator[](size_t i) const {
        ASSERT(i < size());
        return ptr[i];
    }
    char string_view::at(size_t i) const {
        if(i >= size()) {
            throw std::runtime_error(microfmt::format("Out of bounds access {} >= {}", i, size()));
        }
        return ptr[i];
    }

    bool string_view::starts_with(string_view str) const {
        return substr(0, str.size()) == str;
    }

    bool string_view::ends_with(string_view str) const {
        if(size() < str.size()) {
            return false;
        }
        return substr(size() - str.size(), str.size()) == str;
    }

    std::size_t string_view::find_last_of(string_view chars) const {
        if(empty() || chars.empty()) {
            return npos;
        }
        std::size_t pos = size();
        while(pos-- > 0) {
            if(std::find(chars.begin(), chars.end(), ptr[pos]) != chars.end()) {
                return pos;
            }
        }
        return npos;
    }

    bool operator==(string_view a, string_view b) {
        return a.size() == b.size() && std::memcmp(a.data(), b.data(), a.size()) == 0;
    }

	// warning C5041: 'npos': out-of-line definition for constexpr static data member is not needed and is deprecated in C++17
#if 0
	constexpr std::size_t cstring_view::npos;
#endif

    cstring_view cstring_view::substr(std::size_t pos) const {
        ASSERT(pos <= count);
        return {ptr + pos, count - pos};
    }

    void cstring_view::check_null() const {
        ASSERT(ptr[count] == 0);
    }
}
CPPTRACE_END_NAMESPACE
