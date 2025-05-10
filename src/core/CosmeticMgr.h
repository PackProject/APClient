#ifndef APCLIENT_CORE_COSMETIC_MGR_H
#define APCLIENT_CORE_COSMETIC_MGR_H
#include <types.h>

#include "core/const.h"

#include <Sports2/Sp2Snd.h>

#include <libkiwi.h>

namespace AP {

class CosmeticMgr : public kiwi::DynamicSingleton<CosmeticMgr>,
                    public kiwi::IBinary {
    friend class kiwi::DynamicSingleton<CosmeticMgr>;

public:
    /**
     * @brief Sets debug state
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
        K_ASSERT(IsBgm(id));
        return mRandomBgmMapping[id - BGM_ID_MIN];
    }

private:
    //! Binary file magic
    static const u32 SIGNATURE = 'COSM';
    //! Binary file version
    static const int VERSION = K_VERSION(1, 0);
    //! Binary file path
    static const char* PATH;

    //! Minimum sound ID for music randomization (inclusive)
    static const int BGM_ID_MIN = STM_TITLE_BASE;
    //! Maximum sound ID for music randomization (exclusive)
    static const int BGM_ID_MAX = STM_SILENT;

private:
    /**
     * @brief Binary file structure
     */
#pragma pack(push, 1)
    struct Bin : kiwi::IBinary::Block {
        // clang-format off
        /* 0x00:0  */ u8 randomBgmFlag : 1;                           //!< Random music enabled
        /* 0x01:0  */ u8 randomBgmMapping[BGM_ID_MAX - BGM_ID_MIN]; //!< Random music mapping table
        // . . .
        // clang-format on
    };
#pragma pack(pop)

private:
    /**
     * @brief Constructor
     */
    CosmeticMgr();

    /**
     * @brief Gets the kind/magic of this object
     */
    virtual u32 GetBinaryKind() const {
        return SIGNATURE;
    }
    /**
     * @brief Gets the serialized size of this object
     */
    virtual u32 GetBinarySize() const {
        return sizeof(Bin);
    }
    /**
     * @brief Gets the expected version of this object
     */
    virtual u16 GetVersion() const {
        return VERSION;
    }

    /**
     * @brief Deserializes binary contents (internal implementation)
     *
     * @param rHeader Binary file header
     */
    virtual void DeserializeImpl(const Header& rHeader);
    /**
     * @brief Serializes binary contents (internal implementation)
     *
     * @param rHeader Binary file header
     */
    virtual void SerializeImpl(Header& rHeader) const;

    /**
     * @brief Clears cosmetic state
     */
    void Clear();

private:
    //! Random music enabled
    bool mRandomBgmFlag;
    //! Random music mapping table
    u32 mRandomBgmMapping[BGM_ID_MAX - BGM_ID_MIN];
};

} // namespace AP

#endif