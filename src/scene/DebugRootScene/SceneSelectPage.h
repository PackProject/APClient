#ifndef APCLIENT_SCENE_DEBUGROOTSCENE_SCENE_SELECT_PAGE_H
#define APCLIENT_SCENE_DEBUGROOTSCENE_SCENE_SELECT_PAGE_H
#include <types.h>

#include "scene/DebugRootScene/SeqSelectPage.h"

#include <libkiwi.h>

namespace AP {
namespace DebugRoot {

/**
 * @brief Debug menu scene select
 */
class SceneSelectPage : public kiwi::DebugPage {
public:
    //! First scene ID (inclusive)
    static const u32 FIRST_SCENE_ID = kiwi::ESceneID_Sp2TitleScene;
    //! Last scene ID (exclusive)
    static const u32 LAST_SCENE_ID = kiwi::ESceneID_Sp2OmkScene + 1;

public:
    /**
     * @brief Constructor
     *
     * @param rMenu Parent menu
     */
    SceneSelectPage(kiwi::DebugMenu& rMenu);
    /**
     * @brief Destructor
     */
    virtual ~SceneSelectPage();

    /**
     * @brief Option select callback
     *
     * @param pArg Callback user argument
     * @return Result of action
     */
    static kiwi::EDebugMenuResult SelectProc(void* pArg);

private:
    //! Number of menu options
    static const u32 scOptionNum = LAST_SCENE_ID - FIRST_SCENE_ID;

private:
    //! Scene selection options
    kiwi::DebugProcOption* mpSceneOptions[scOptionNum];

    //! Sequence select
    SeqSelectPage mSeqSelectPage;
};

} // namespace DebugRoot
} // namespace AP

#endif
