#define LIBKIWI_INTERNAL

#include <Pack/RPSystem.h>

#include <libkiwi.h>

namespace kiwi {
namespace {

/**
 * @brief Gets the current scene
 */
RPSysScene* GetCurrentScene() {
    return static_cast<RPSysScene*>(
        RP_GET_INSTANCE(RPSysSceneMgr)->getCurrentScene());
}

/**
 * @brief Gets the current scene's ID
 */
s32 GetCurrentSceneID() {
    RPSysScene* pScene = GetCurrentScene();
    K_ASSERT_PTR(pScene);
    return pScene->getSceneID();
}

/**
 * @brief Tests whether the current scene is a Pack Project scene
 */
bool IsCurrentPackScene() {
    return GetCurrentSceneID() < ESceneID_Max;
}

} // namespace

/**
 * @brief Gets the list of active hooks for the current scene
 */
TList<ISceneHook*>& SceneHookMgr::GetSceneHooks() {
    K_ASSERT_EX(IsCurrentPackScene(), "Only game scenes have hooks");
    s32 id = RP_GET_INSTANCE(RPSysSceneMgr)->getCurrentSceneID();
    return mSceneHookLists[id];
}

/**
 * @brief Registers a new hook
 *
 * @param rHook Scene hook
 */
void SceneHookMgr::AddHook(ISceneHook& rHook) {
    if (rHook.mSceneID == -1) {
        mGlobalHooks.PushBack(&rHook);
    } else {
        mSceneHookLists[rHook.mSceneID].PushBack(&rHook);
    }
}

/**
 * @brief Unregisters an existing hook
 *
 * @param rHook Scene hook
 */
void SceneHookMgr::RemoveHook(ISceneHook& rHook) {
    if (rHook.mSceneID == -1) {
        mGlobalHooks.Remove(&rHook);
    } else {
        mSceneHookLists[rHook.mSceneID].Remove(&rHook);
    }
}

/**
 * @brief Runs active hooks and scene function(s) for the Configure state
 */
void SceneHookMgr::DoConfigure() {
    SceneHookMgr& r = GetInstance();

    GetCurrentScene()->Configure();

    // Global hooks
    K_FOREACH (it, r.mGlobalHooks) {
        (*it)->Configure(GetCurrentScene());
    }

    // Hooks for game scene
    if (IsCurrentPackScene()) {
        K_FOREACH (it, r.GetSceneHooks()) {
            (*it)->Configure(GetCurrentScene());
        }
    }
}
KOKESHI_BY_PACK(KM_CALL(0x8018532c, SceneHookMgr::DoConfigure),  // Wii Sports
                KM_CALL(0x80184d24, SceneHookMgr::DoConfigure),  // Wii Play
                KM_CALL(0x8022fae4, SceneHookMgr::DoConfigure)); // Wii Sports Resort

/**
 * @brief Runs active hooks and scene function(s) for the Reset state
 */
void SceneHookMgr::DoReset() {
    SceneHookMgr& r = GetInstance();

    // Global hooks
    K_FOREACH (it, r.mGlobalHooks) {
        (*it)->BeforeReset(GetCurrentScene());
    }

    // Hooks for game scene
    if (IsCurrentPackScene()) {
        K_FOREACH (it, r.GetSceneHooks()) {
            (*it)->BeforeReset(GetCurrentScene());
        }
    }

    GetCurrentScene()->Reset();

    // Global hooks
    K_FOREACH (it, r.mGlobalHooks) {
        (*it)->AfterReset(GetCurrentScene());
    }

    // Hooks for game scene
    if (IsCurrentPackScene()) {
        K_FOREACH (it, r.GetSceneHooks()) {
            (*it)->AfterReset(GetCurrentScene());
        }
    }
}
// RPSysScene::reinit
KOKESHI_BY_PACK(KM_CALL(0x801852d8, SceneHookMgr::DoReset),  // Wii Sports
                KM_CALL(0x80184cd0, SceneHookMgr::DoReset),  // Wii Play
                KM_CALL(0x8022f9ac, SceneHookMgr::DoReset)); // Wii Sports Resort
// RPSysScene::enter
KOKESHI_BY_PACK(KM_CALL(0x801853d4, SceneHookMgr::DoReset),  // Wii Sports
                KM_CALL(0x80184dcc, SceneHookMgr::DoReset),  // Wii Play
                KM_CALL(0x8022fb54, SceneHookMgr::DoReset)); // Wii Sports Resort

/**
 * @brief Runs active hooks and scene function(s) for the LoadResource state
 */
void SceneHookMgr::DoLoadResource() {
    SceneHookMgr& r = GetInstance();

    GetCurrentScene()->LoadResource();

    // Global hooks
    K_FOREACH (it, r.mGlobalHooks) {
        (*it)->LoadResource(GetCurrentScene());
    }

    // Hooks for game scene
    if (IsCurrentPackScene()) {
        K_FOREACH (it, r.GetSceneHooks()) {
            (*it)->LoadResource(GetCurrentScene());
        }
    }
}
KOKESHI_BY_PACK(KM_CALL(0x80186944, SceneHookMgr::DoLoadResource),  // Wii Sports
                KM_CALL(0x801861e4, SceneHookMgr::DoLoadResource),  // Wii Play
                KM_CALL(0x80231198, SceneHookMgr::DoLoadResource)); // Wii Sports Resort

/**
 * @brief Runs active hooks and scene function(s) for the Calculate state
 */
void SceneHookMgr::DoCalculate() {
    SceneHookMgr& r = GetInstance();

    // Global hooks
    K_FOREACH (it, r.mGlobalHooks) {
        (*it)->BeforeCalculate(GetCurrentScene());
    }

    // Hooks for game scene
    if (IsCurrentPackScene()) {
        K_FOREACH (it, r.GetSceneHooks()) {
            (*it)->BeforeCalculate(GetCurrentScene());
        }
    }

    GetCurrentScene()->Calculate();

    // Global hooks
    K_FOREACH (it, r.mGlobalHooks) {
        (*it)->AfterCalculate(GetCurrentScene());
    }

    // Hooks for game scene
    if (IsCurrentPackScene()) {
        K_FOREACH (it, r.GetSceneHooks()) {
            (*it)->AfterCalculate(GetCurrentScene());
        }
    }
}
KOKESHI_BY_PACK(KM_CALL(0x80185110, SceneHookMgr::DoCalculate),  // Wii Sports
                KM_CALL(0x80184b08, SceneHookMgr::DoCalculate),  // Wii Play
                KM_CALL(0x8022f870, SceneHookMgr::DoCalculate)); // Wii Sports Resort

/**
 * @brief Runs active hooks and scene function(s) for the Exit state
 */
void SceneHookMgr::DoExit() {
    SceneHookMgr& r = GetInstance();

    GetCurrentScene()->Exit();

    // Global hooks
    K_FOREACH (it, r.mGlobalHooks) {
        (*it)->Exit(GetCurrentScene());
    }

    // Hooks for game scene
    if (IsCurrentPackScene()) {
        K_FOREACH (it, r.GetSceneHooks()) {
            (*it)->Exit(GetCurrentScene());
        }
    }
}
KOKESHI_BY_PACK(KM_CALL(0x80184fcc, SceneHookMgr::DoExit),  // Wii Sports
                KM_CALL(0x801849c4, SceneHookMgr::DoExit),  // Wii Play
                KM_CALL(0x8022f6d8, SceneHookMgr::DoExit)); // Wii Sports Resort

/**
 * @brief Runs active hooks and scene function(s) for entering the pause
 * menu
 */
void SceneHookMgr::DoPause() {
    SceneHookMgr& r = GetInstance();

    GetCurrentScene()->pauseCallBack(true);

    // Global hooks
    K_FOREACH (it, r.mGlobalHooks) {
        (*it)->Pause(GetCurrentScene(), true);
    }

    // Hooks for game scene
    if (IsCurrentPackScene()) {
        K_FOREACH (it, r.GetSceneHooks()) {
            (*it)->Pause(GetCurrentScene(), true);
        }
    }
}
KOKESHI_BY_PACK(KM_CALL(0x8018cec8, SceneHookMgr::DoPause), // Wii Sports
                KM_CALL(0x8018b084, SceneHookMgr::DoPause), // Wii Play
                KM_CALL(0x8022fc94,
                        SceneHookMgr::DoPause)); // Wii Sports Resort

/**
 * @brief Runs active hooks and scene function(s) for exiting the pause menu
 */
void SceneHookMgr::DoUnPause() {
    SceneHookMgr& r = GetInstance();

    GetCurrentScene()->pauseCallBack(false);

    // Global hooks
    K_FOREACH (it, r.mGlobalHooks) {
        (*it)->Pause(GetCurrentScene(), false);
    }

    // Hooks for game scene
    if (IsCurrentPackScene()) {
        K_FOREACH (it, r.GetSceneHooks()) {
            (*it)->Pause(GetCurrentScene(), false);
        }
    }
}
// 'Continue'
KOKESHI_BY_PACK(KM_CALL(0x8018d118, SceneHookMgr::DoUnPause), // Wii Sports
                KM_CALL(0x8018b174, SceneHookMgr::DoUnPause), // Wii Play
                KM_CALL(0x8022fc38,
                        SceneHookMgr::DoUnPause)); // Wii Sports Resort
// 'Start over'
KOKESHI_BY_PACK(KM_CALL(0x8018d14c, SceneHookMgr::DoUnPause), // Wii Sports
                KM_CALL(0x8018b1a8, SceneHookMgr::DoUnPause), // Wii Play
                /* WS2 only needs one patch */); // Wii Sports Resort
// 'Quit'
KOKESHI_BY_PACK(KM_CALL(0x8018d1b8, SceneHookMgr::DoUnPause), // Wii Sports
                KM_CALL(0x8018b20c, SceneHookMgr::DoUnPause), // Wii Play
                /* WS2 only needs one patch */); // Wii Sports Resort

} // namespace kiwi
