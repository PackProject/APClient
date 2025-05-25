#include "scene/DebugRootScene/RootPage.h"

#include <libkiwi.h>

namespace AP {
namespace DebugRoot {

/**
 * @brief Constructor
 *
 * @param rMenu Parent menu
 */
RootPage::RootPage(kiwi::DebugMenu& rMenu)
    : kiwi::DebugPage(rMenu),
      mSceneSelect(rMenu, "Scene Debug", mSceneSelectPage),
      mSceneSelectPage(rMenu),
      mItemDebug(rMenu, "Item Debug", *this),
      mCheckDebug(rMenu, "Check Debug", *this),
      mCosmeticDebug(rMenu, "Cosmetic Debug", *this) {

    mOptions.PushBack(&mSceneSelect);
    mOptions.PushBack(&mItemDebug);
    mOptions.PushBack(&mCheckDebug);
    mOptions.PushBack(&mCosmeticDebug);

    // TODO: Not yet implemented
    mItemDebug.SetEnabled(false);
    mCheckDebug.SetEnabled(false);
    mCosmeticDebug.SetEnabled(false);
}

} // namespace DebugRoot
} // namespace AP
