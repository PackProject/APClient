#ifndef LIBKIWI_DEBUG_DEBUG_MENU_H
#define LIBKIWI_DEBUG_DEBUG_MENU_H
#include <Pack/RPGraphics.h>
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiVector.h>

namespace kiwi {
//! @addtogroup libkiwi_debug
//! @{

// Forward declarations
class DebugOptionBase;

/**
 * @brief Debug menu
 */
class DebugMenu : public IRPGrpDrawObject {
public:
    /**
     * @brief Option action result
     */
    enum EResult {
        EResult_None,    //!< Nothing happened
        EResult_Invalid, //!< State failed to change
        EResult_Change,  //!< State changed
        EResult_Close,   //!< Request to close menu
    };

public:
    /**
     * @brief Constructor
     */
    DebugMenu() : mCursor(0) {}
    /**
     * @brief Destructor
     */
    virtual ~DebugMenu() {
        mOptions.Clear();
    }

    /**
     * @brief Updates the menu state
     */
    virtual void Calculate();
    /**
     * @brief User-level render pass
     */
    virtual void UserDraw();

    /**
     * @brief Updates the menu state (for sub-classes)
     */
    virtual void OnCalculate() {}
    /**
     * @brief Render pass (for sub-classes)
     */
    virtual void OnUserDraw() {}

protected:
    //! Cursor position
    u32 mCursor;

    //! Option list
    TVector<DebugOptionBase*> mOptions;
};

//! @}
} // namespace kiwi

#endif
