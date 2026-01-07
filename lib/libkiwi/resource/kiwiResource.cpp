#include <Pack/RPKernel.h>

#include <libkiwi.h>

#include <egg/core.h>

#include <cstring>

namespace kiwi {

/**
 * @brief Constructor
 *
 * @param pPath Archive file path
 * @param size Archive file size
 * @param pData Archive file data
 */
Resource::Resource(const char* pPath, u32 size, const void* pData)
    : mBaseFile(pPath, size, static_cast<const u8*>(pData)) {

    K_ASSERT_PTR(pPath);
    K_ASSERT_PTR(pData);

    u32 pathLen = std::strlen(pPath);
    K_ASSERT(pathLen <= PATH_MAX);

    K_ASSERT(!PtrUtil::IsLibKiwi(pData));
}

/**
 * @brief Destructor
 */
Resource::~Resource() {
    ResourceMgr::RemoveResourceFromCache(*this);

    K_FOREACH (it, mPatchFiles) {
        delete *it;
    }
}

} // namespace kiwi