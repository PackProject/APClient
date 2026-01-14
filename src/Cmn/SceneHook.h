#ifndef APCLIENT_CMN_SCENE_HOOK_H
#define APCLIENT_CMN_SCENE_HOOK_H
#include <types.h>

#include "Net/GameMessageListener.h"

#include <libkiwi.h>

namespace AP {
namespace Cmn {

// Forward declarations
class TextDisplay;

/**
 * @brief Common scene hook
 */
class SceneHook : public kiwi::DynamicSingleton<SceneHook>,
                  public kiwi::ISceneHook {
public:
    /**
     * @brief Constructor
     */
    SceneHook();

    /**
     * @brief Destructor
     */
    virtual ~SceneHook();

    /**
     * @brief Handles scene Configure event
     *
     * @param pScene Current scene
     */
    virtual void Configure(RPSysScene* pScene);

    /**
     * @brief Handles scene Calculate event
     *
     * @param pScene Current scene
     */
    virtual void AfterCalculate(RPSysScene* pScene);

    /**
     * @brief Accesses the scene text message writer
     */
    TextDisplay* GetTextDisplay() const {
        return mpTextDisplay;
    }

private:
    //! AP message listener
    Net::GameMessageListener* mpListener;
    //! AP message text writer
    TextDisplay* mpTextDisplay;
};

} // namespace Cmn
} // namespace AP

#endif
