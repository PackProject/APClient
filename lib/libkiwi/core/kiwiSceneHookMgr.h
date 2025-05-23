#ifndef LIBKIWI_CORE_SCENE_HOOK_MGR_H
#define LIBKIWI_CORE_SCENE_HOOK_MGR_H
#include <Pack/RPSystem.h>
#include <libkiwi/core/kiwiSceneCreator.h>
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiArray.h>
#include <libkiwi/prim/kiwiLinkList.h>
#include <libkiwi/util/kiwiStaticSingleton.h>

namespace kiwi {
//! @addtogroup libkiwi_core
//! @{

// Forward declarations
class ISceneHook;

/**
 * @brief Scene hook manager
 */
class SceneHookMgr : public StaticSingleton<SceneHookMgr> {
    friend class StaticSingleton<SceneHookMgr>;

public:
    /**
     * @brief Registers a new hook
     *
     * @param rHook Scene hook
     */
    void AddHook(ISceneHook& rHook);
    /**
     * @brief Unregisters an existing hook
     *
     * @param rHook Scene hook
     */
    void RemoveHook(const ISceneHook& rHook);

private:
    LIBKIWI_KAMEK_PUBLIC

    /**
     * @brief Runs active hooks and scene function(s) for the Configure state
     */
    static void DoConfigure();
    /**
     * @brief Runs active hooks and scene function(s) for the Reset state
     */
    static void DoReset();
    /**
     * @brief Runs active hooks and scene function(s) for the LoadResource state
     */
    static void DoLoadResource();
    /**
     * @brief Runs active hooks and scene function(s) for the Calculate state
     */
    static void DoCalculate();
    /**
     * @brief Runs active hooks and scene function(s) for the Exit state
     */
    static void DoExit();

    /**
     * @brief Runs active hooks and scene function(s) for entering the pause
     * menu
     */
    static void DoPause();
    /**
     * @brief Runs active hooks and scene function(s) for exiting the pause menu
     */
    static void DoUnPause();

    /**
     * @brief Gets the list of active hooks for the current scene
     */
    TList<ISceneHook>& GetSceneHooks();

private:
    //! Lists of scene hooks
    TArray<TList<ISceneHook>, ESceneID_Max> mSceneHookLists;
    //! Global hooks (always active)
    TList<ISceneHook> mGlobalHooks;
};

/**
 * @brief Scene hook interface
 */
class ISceneHook {
    friend class SceneHookMgr;

public:
    /**
     * @brief Constructor
     * @details The scene ID defaults to all scenes (-1).
     *
     * @param id Scene ID (-1 for all scenes)
     */
    explicit ISceneHook(s32 id = -1) : mSceneID(id) {
        K_ASSERT_EX(id == -1 || id < ESceneID_Max,
                    "Only RP scene IDs and -1 (all scenes) are supported");

        SceneHookMgr::GetInstance().AddHook(*this);
    }
    /**
     * @brief Destructor
     */
    virtual ~ISceneHook() {
        SceneHookMgr::GetInstance().RemoveHook(*this);
    }

    /**
     * @brief Configure callback
     * @details Ran once on initial scene setup
     *
     * @param pScene Current scene
     */
    virtual void Configure(RPSysScene* pScene) {}

    /**
     * @brief LoadResource callback
     * @details Ran once on asset loading
     *
     * @param pScene Current scene
     */
    virtual void LoadResource(RPSysScene* pScene) {}

    /**
     * @brief Reset callback (before game logic)
     * @details Ran once on initial scene setup and on every restart
     *
     * @param pScene Current scene
     */
    virtual void BeforeReset(RPSysScene* pScene) {}
    /**
     * @brief Reset callback (after game logic)
     * @details Ran once on initial scene setup and on every restart
     *
     * @param pScene Current scene
     */
    virtual void AfterReset(RPSysScene* pScene) {}

    /**
     * @brief Calculate callback (before game logic)
     * @details Ran once per frame
     *
     * @param pScene Current scene
     */
    virtual void BeforeCalculate(RPSysScene* pScene) {}
    /**
     * @brief Calculate callback (after game logic)
     * @details Ran once per frame
     *
     * @param pScene Current scene
     */
    virtual void AfterCalculate(RPSysScene* pScene) {}

    /**
     * @brief Exit callback
     * @details Ran once on scene exit (including restarts)
     *
     * @param pScene Current scene
     */
    virtual void Exit(RPSysScene* pScene) {}

    /**
     * @brief Pause callback
     * @details Ran on pause menu open/close
     *
     * @param pScene Current scene
     * @param enter Whether the pause menu is opening
     */
    virtual void Pause(RPSysScene* pScene, bool enter) {}

private:
    //! Scene to which this hook belongs
    s32 mSceneID;
};

//! @}
} // namespace kiwi

#endif
