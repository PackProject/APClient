#ifndef APCLIENT_CORE_COSMETIC_MGR_H
#define APCLIENT_CORE_COSMETIC_MGR_H
#include <types.h>

#include "core/const.h"
#include <Sports2/Sp2Cmn.h>
#include <Sports2/Sp2Snd.h>

#include <libkiwi.h>

namespace AP {

/**
 * @brief Archipelago cosmetic manager
 */
class CosmeticMgr : public kiwi::DynamicSingleton<CosmeticMgr> {
    friend class kiwi::DynamicSingleton<CosmeticMgr>;

public:
    /**
     * @brief Resets the cosmetic state to the default settings
     */
    void Clear();
    /**
     * @brief Randomizes the cosmetic state for debugging purposes
     */
    void Debug();

    /**
     * @brief Tests whether the specified sound ID is a BGM ID
     *
     * @param id Sound ID
     */
    static bool IsBgm(u32 id) {
        return id >= BGM_ID_MIN && id < BGM_ID_MAX;
    }

    /**
     * @brief Tests whether music randomization is enabled
     */
    bool IsRandomBgm() const {
        return mRandomBgmFlag;
    }

    /**
     * @brief Gets the random music ID that should be played instead of the
     * provided ID
     *
     * @param id Standard music ID
     */
    u32 GetRandomBgm(u32 id) const {
        ASSERT(IsBgm(id));
        return mRandomBgmMapping[id - BGM_ID_MIN];
    }

    /**
     * @brief Tests whether Mii favorite color randomization is enabled
     */
    bool IsRandomFavoriteColor() const {
        return mRandomFavoriteColor;
    }

    /**
     * @brief Tests whether island time randomization is enabled
     */
    bool IsRandomTime() const {
        return mRandomTimeFlag;
    }

    /**
     * @brief Gets the random island time that should be used instead of the
     * current one
     *
     * @param group Scene group ID
     */
    RPSysScene::ETime GetRandomTime(s32 group) const {
        ASSERT(group < Sp2::Cmn::EGroupID_Max);
        return mRandomTimeMapping[1 + group];
    }

private:
    //! Minimum sound ID for music randomization (inclusive)
    static const int BGM_ID_MIN = STM_TITLE_BASE;
    //! Maximum sound ID for music randomization (exclusive)
    static const int BGM_ID_MAX = STM_SILENT;

private:
    /**
     * @brief Constructor
     */
    CosmeticMgr();

private:
    //! Random music enabled
    bool mRandomBgmFlag;
    //! Random music mapping table
    u32 mRandomBgmMapping[BGM_ID_MAX - BGM_ID_MIN];

    //! Random Mii favorite color enabled
    bool mRandomFavoriteColor;

    //! Random island time enabled
    bool mRandomTimeFlag;
    //! Random island time mapping table (+1 for Cmn group)
    RPSysScene::ETime mRandomTimeMapping[Sp2::Cmn::EGroupID_Max + 1];
};

} // namespace AP

#endif
