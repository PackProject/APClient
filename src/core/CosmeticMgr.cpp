#include "core/CosmeticMgr.h"

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
 * @param rBin Binary file contents
 */
void CosmeticMgr::DeserializeImpl(const Bin& rBin) {
    ;
}

/**
 * @brief Serializes binary contents (internal implementation)
 *
 * @param rBin Binary file contents
 */
void CosmeticMgr::SerializeImpl(Bin& rBin) const {
    ;
}

/**
 * @brief Clears cosmetic state
 */
void CosmeticMgr::Clear() {
    mRandomBgmFlag = false;
    for (int i = 0; i < K_LENGTHOF(mRandomBgmMapping); i++) {
        mRandomBgmMapping[i] = i;
    }

    mRandomTimeFlag = false;
    for (int i = 0; i < K_LENGTHOF(mRandomTimeMapping); i++) {
        mRandomTimeMapping[i] = RPSysScene::ETime_Auto;
    }
}

/**
 * @brief Sets debug state
 */
void CosmeticMgr::Debug() {
    kiwi::Random r;

    for (int i = 0; i < K_LENGTHOF(mRandomBgmMapping); i++) {
        mRandomBgmMapping[i] = i;
    }

    kiwi::Shuffle(mRandomBgmMapping, K_LENGTHOF(mRandomBgmMapping));
    mRandomBgmFlag = r.CoinFlip();

    mRandomTimeFlag = r.CoinFlip();
    for (int i = 0; i < LENGTHOF(mRandomTimeMapping); i++) {
        mRandomTimeMapping[i] = static_cast<RPSysScene::ETime>(r.NextU32(3));
    }
}

} // namespace AP
