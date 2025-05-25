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
      mSceneSelect(rMenu, "Scene Select", mSceneSelectPage),
      mSceneSelectPage(rMenu) {

    mOptions.PushBack(&mSceneSelect);
}

} // namespace DebugRoot
} // namespace AP
