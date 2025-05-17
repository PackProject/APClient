#ifndef LIBKIWI_SUPPORT_LIBSSL_H
#define LIBKIWI_SUPPORT_LIBSSL_H
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiString.h>
#include <libkiwi/util/kiwiIosDevice.h>
#include <libkiwi/util/kiwiIosObject.h>

#include <cstring>

namespace kiwi {
//! @addtogroup libkiwi_support
//! @{

/**
 * @brief SSL library wrapper/extension
 */
class LibSSL {
public:
    ;

private:
    //! SSL device
    static IosDevice sDevNetSsl;
};

//! @}
} // namespace kiwi

#endif
