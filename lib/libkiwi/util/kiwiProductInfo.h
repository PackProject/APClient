#ifndef LIBKIWI_UTIL_PRODUCT_INFO_H
#define LIBKIWI_UTIL_PRODUCT_INFO_H
#include <libkiwi/debug/kiwiAssert.h>
#include <libkiwi/k_types.h>

namespace kiwi {
//! @addtogroup libkiwi_util
//! @{

const char* GetBuildDate();
const char* GetBuildPack();
const char* GetBuildTarget();

//! @}
} // namespace kiwi

#endif
