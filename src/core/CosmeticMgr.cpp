#include <core/CosmeticMgr.h>
#include <libkiwi.h>

K_DYNAMIC_SINGLETON_IMPL(AP::CosmeticMgr);

namespace AP {

/**
 * @brief Binary file path
 */
const char* CosmeticMgr::PATH = "cosmetic.bin";

/**
 * @brief Constructor
 *
 */
CosmeticMgr::CosmeticMgr() {
    Clear();
}

/**
 * @brief Deserializes binary contents (internal implementation)
 *
 * @param rHeader Binary file header
 */
void CosmeticMgr::DeserializeImpl(const Header& rHeader) {
    ;
}

/**
 * @brief Serializes binary contents (internal implementation)
 *
 * @param rHeader Binary file header
 */
void CosmeticMgr::SerializeImpl(Header& rHeader) const {
    ;
}

/**
 * @brief Clears cosmetic state
 */
void CosmeticMgr::Clear() {
    mRandomBgmFlag = false;
    for (int i = 0; i < BGM_ID_MAX - BGM_ID_MIN; i++) {
        mRandomBgmMapping[i] = i;
    }
}

} // namespace AP
