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
 * @brief Debug menu action result
 */
enum EDebugMenuResult {
    EDebugMenuResult_None,    //!< Nothing happened
    EDebugMenuResult_Invalid, //!< State failed to change
    EDebugMenuResult_Cursor,  //!< Cursor changed
    EDebugMenuResult_Change,  //!< State changed
    EDebugMenuResult_Select,  //!< Button selected
    EDebugMenuResult_Back,    //!< Request to close page
    EDebugMenuResult_Exit,    //!< Request to exit menu
};

/**
 * @brief Debug menu
 */
class DebugMenu : public IRPGrpDrawObject {
public:
    /**
     * @brief Destructor
     */
    virtual ~DebugMenu() {}

    /**
     * @brief Opens a new menu page
     *
     * @param rPage Menu page
     */
    void OpenPage(DebugPage& rPage) {
        mPageStack.Push(&rPage);
    }

    /**
     * @brief Updates the menu state
     * @return Result of actions
     */
    virtual EDebugMenuResult Calculate();

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
    static const u32 DEFAULT_MAX_OPTIONS = 20;

public:
    /**
     * @brief Constructor
     *
     * @param rMenu Parent menu
     * @param maxOptions Maximum number of options on the page
     */
    DebugPage(DebugMenu& rMenu, u32 maxOptions = DEFAULT_MAX_OPTIONS)
        : mrMenu(rMenu), mCursor(0), mMaxOptions(maxOptions) {}

    /**
     * @brief Gets the page's parent menu
     */
    DebugMenu& GetMenu() const {
        return mrMenu;
    }

    /**
     * @brief Updates the page state
     * @return Result of actions
     */
    virtual EDebugMenuResult Calculate();

    /**
     * @brief User-level render pass
     */
    virtual void UserDraw();

protected:
    //! Parent menu
    DebugMenu& mrMenu;

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
