#ifndef APCLIENT_SCENE_DEBUGROOTSCENE_ROOT_PAGE_H
#define APCLIENT_SCENE_DEBUGROOTSCENE_ROOT_PAGE_H
#include "core/const.h"
#include "scene/DebugRootScene/SceneSelectPage.h"

#include <libkiwi.h>

namespace AP {
namespace DebugRoot {

/**
 * @brief Root debug menu page
 */
class RootPage : public kiwi::DebugPage {
public:
    /**
     * @brief Constructor
     *
     * @param rMenu Parent menu
     */
    RootPage(kiwi::DebugMenu& rMenu);

private:
    //! Debug scene select
    kiwi::DebugOpenPageOption mSceneSelect;
    SceneSelectPage mSceneSelectPage;
};

} // namespace DebugRoot
} // namespace AP

#endif
