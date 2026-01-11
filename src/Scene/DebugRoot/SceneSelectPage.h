#ifndef APCLIENT_SCENE_DEBUGROOTSCENE_SCENE_SELECT_PAGE_H
#define APCLIENT_SCENE_DEBUGROOTSCENE_SCENE_SELECT_PAGE_H
#include <types.h>

#include "scene/DebugRoot/SeqSelectPage.h"

#include <libkiwi.h>

namespace AP {
namespace DebugRoot {

/**
 * @brief Debug menu scene select
 */
class SceneSelectPage : public kiwi::DebugPage {
public:
    /**
     * @brief Constructor
     *
     * @param rMenu Parent menu
     */
    explicit SceneSelectPage(kiwi::DebugMenu& rMenu);
    /**
     * @brief Destructor
     */
    virtual ~SceneSelectPage();

    /**
     * @brief Option select callback
     *
     * @param pInvoker Callback invoker
     * @param pArg Callback user argument
     * @return Result of action
     */
    static kiwi::EDebugMenuResult SelectProc(kiwi::DebugOptionBase* pInvoker,
                                             void* pArg);

private:
    // TODO(kiwi) Implement debug menu scrolling
    static const u32 SCENE_NUM = kiwi::ESceneID_Sp2DebugRootScene;

private:
    //! Scene selection options
    kiwi::DebugProcOption* mpSceneOptions[SCENE_NUM];

    //! Sequence select
    SeqSelectPage mSeqSelectPage;
};

} // namespace DebugRoot
} // namespace AP

#endif
