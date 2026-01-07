#ifndef LIBKIWI_UTIL_NON_CONSTRUCTABLE_H
#define LIBKIWI_UTIL_NON_CONSTRUCTABLE_H
#include <libkiwi/debug/kiwiAssert.h>
#include <libkiwi/k_types.h>

namespace kiwi {
//! @addtogroup libkiwi_util
//! @{

/**
 * @brief Non-constructable mix-in
 */
class NonConstructable {
private:
    NonConstructable() {
        K_UNREACHABLE();
    }
    ~NonConstructable() {
        K_UNREACHABLE();
    }
    NonConstructable(const NonConstructable& /* rOther */) {
        K_UNREACHABLE();
    }
    NonConstructable& operator=(const NonConstructable& /* rOther */) {
        K_UNREACHABLE();
        return *this;
    }
};

//! @}
} // namespace kiwi

#endif
