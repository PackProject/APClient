#ifndef APCLIENT_CORE_CHECK_MGR_H
#define APCLIENT_CORE_CHECK_MGR_H
#include <types.h>

#include "core/checks.h"
#include "core/const.h"
#include <Sports2/Sp2Cmn.h>

#include <libkiwi.h>

namespace AP {

#define X(ID, IDENT, STR) CHECK_##IDENT = ID,
enum CheckID { AP_CHECKS_LIST COUNT };
#undef X

/**
 * @brief Archipelago check manager
 */
class CheckMgr : public kiwi::DynamicSingleton<CheckMgr> {
    friend class kiwi::DynamicSingleton<CheckMgr>;

public:
    /**
     * @brief Gets the readable name of the specified check ID
     */
    static kiwi::String GetCheckName(CheckID id);

    /**
     * @brief Sets debug state
     */
    void Debug();

    /**
     * @brief Clears check state
     */
    void Clear();

    /**
     * @brief Gets the check state
     *
     * @param id Check ID
     * @return Check state
     */
    bool GetCheckState(CheckID id) const;

    /**
     * @brief Sets the check state
     *
     * @param id Check ID
     * @param state Check state
     */
    void SetCheckState(CheckID id, bool state);

    /**
     * @brief Gets the item ID for a check
     *
     * @param id Check ID
     * @return Item ID
     */
    u16 GetItemID(CheckID id) const;

    /**
     * @brief Sets the item ID for a check
     *
     * @param id Check ID
     * @param itemID Item ID
     */
    void SetItemID(CheckID id, u16 itemID);

    /**
     *
     * @brief gives proper item from check ID
     *
     * @param id Check ID
     */
    void GiveItemFromCheck(CheckID id);

private:
    /**
     * @brief Constructor
     */
    CheckMgr();

public:
    /**
     * @brief returns number of groups of i point checks obtained
     */
    int GetNumGroupIPointObtained(int numIPoints) {
        if (numIPoints >= 5)
            return numIPoints / 5;
        else
            return 99;
    }

private:
    kiwi::THashMap<CheckID, bool> mCheckState;   //!< Check state
    kiwi::THashMap<CheckID, u16> mCheckToItemID; //!< Check to item mapping
};

} // namespace AP

#endif // APCLIENT_CORE_CHECK_MGR_H
