#ifndef LIBKIWI_DEBUG_DEBUG_MENU_H
#define LIBKIWI_DEBUG_DEBUG_MENU_H
#include <Pack/RPGraphics.h>
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiStack.h>
#include <libkiwi/prim/kiwiVector.h>

namespace kiwi {
//! @addtogroup libkiwi_debug
//! @{

// Forward declarations
class DebugOptionBase;
class DebugPage;

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
     *
     * @param pRootPage Menu root page
     */
    DebugMenu(DebugPage* pRootPage);

    /**
     * @brief Destructor
     */
    virtual ~DebugMenu() {}

    /**
     * @brief Updates the menu state
     * @return Result of actions
     */
    virtual EResult Calculate();

    /**
     * @brief User-level render pass
     */
    virtual void UserDraw();

protected:
    //! Menu page hierarchy
    TStack<DebugPage> mPageStack;
};

/**
 * @brief Debug menu page
 */
class DebugPage {
public:
    //! Default options limit
    static const u32 DEFAULT_MAX_OPTIONS = 16;

public:
    /**
     * @brief Constructor
     *
     * @param maxOptions Maximum number of options on the page
     */
    DebugPage(u32 maxOptions = DEFAULT_MAX_OPTIONS)
        : mCursor(0), mMaxOptions(maxOptions) {}

    /**
     * @brief Appends a new option to the page
     *
     * @param pOption Debug option
     * @return Success
     */
    bool AddOption(DebugOptionBase* pOption);

    /**
     * @brief Updates the menu state
     * @return Result of actions
     */
    virtual DebugMenu::EResult Calculate();

    /**
     * @brief User-level render pass
     */
    virtual void UserDraw();

protected:
    //! Cursor position
    u32 mCursor;
    //! Maximum number of options
    u32 mMaxOptions;
    //! Option list
    TVector<DebugOptionBase*> mOptions;
};

//! @}
} // namespace kiwi

#endif
