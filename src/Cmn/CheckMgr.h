#ifndef APCLIENT_CMN_CHECK_MGR_H
#define APCLIENT_CMN_CHECK_MGR_H
#include <types.h>

#include "const.h"

#include <libkiwi.h>

namespace AP {
namespace Cmn {

/**
 * @brief Archipelago check manager
 */
class CheckMgr : public kiwi::DynamicSingleton<CheckMgr> {
    friend class kiwi::DynamicSingleton<CheckMgr>;

public:
    //! @brief Number of i-points needed for each i-point group check
    static const u32 PLN_POINT_GROUP_NUM = 5;

public:
    /**
     * @brief Gets the readable name of the specified check ID
     *
     * @param id Item ID
     */
    static kiwi::String GetCheckName(CheckID id);

    /**
     * @brief Calculates the number of i-point checks that should be awarded
     *
     * @param iPointNum Total number of i-points collected
     */
    static u32 GetIPointGroupCheckNum(u32 iPointNum) {
        return iPointNum / PLN_POINT_GROUP_NUM;
    }

    /**
     * @brief Resets the check state to the default settings
     */
    void Clear();

    /**
     * @brief Randomizes the check state for debugging purposes
     */
    void Debug();

    /**
     * @brief Gets the current state of the specified check
     *
     * @param id Check ID
     * @return Whether the check has been completed
     */
    bool GetCheckState(CheckID id) const;

    /**
     * @brief Sets the current state of the specified check
     *
     * @param id Check ID
     * @param state Whether the check has been completed
     */
    void SetCheckState(CheckID id, bool state);

    /**
     * @brief Gets the item mapped to the specified check
     *
     * @param id Check ID
     * @return Item obtained from the check
     */
    ItemID GetCheckItem(CheckID id) const;

    /**
     * @brief Maps an item to the specified check
     *
     * @param id Check ID
     * @param item Item ID
     */
    void SetCheckItem(CheckID id, ItemID item);

    /**
     * @brief Awards the item mapped to the specified check
     *
     * @param id Check ID
     */
    void GiveCheckItem(CheckID id) const;

private:
    /**
     * @brief Constructor
     */
    CheckMgr();

private:
    //! Check state
    kiwi::THashMap<CheckID, bool> mCheckState;
    //! Check to item mapping
    kiwi::THashMap<CheckID, ItemID> mCheckToItemID;
};

} // namespace Cmn
} // namespace AP

#endif
