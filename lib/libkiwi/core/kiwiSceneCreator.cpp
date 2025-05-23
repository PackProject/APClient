#define LIBKIWI_INTERNAL

#include <Pack/RPSystem.h>

#include <libkiwi.h>

namespace kiwi {

/**
 * @brief Pack Project scenes
 */
const SceneCreator::Info SceneCreator::scPackScenes[] = {
// clang-format off
#if defined(PACK_SPORTS)
    {nullptr, "Logo",                         "RPCommon/",             kiwi::ESceneID_RPSysBootScene,               kiwi::EPackID_AllPack,    kiwi::ECreateType_Standard, kiwi::EExitType_Sibling,  true},
    {nullptr, "Player Select",                "RPCommon/",             kiwi::ESceneID_RPSysPlayerSelectScene,       kiwi::EPackID_AllPack,    kiwi::ECreateType_Standard, kiwi::EExitType_2,        true},
    {nullptr, "Nunchuk Check",                "RPCommon/",             kiwi::ESceneID_RPSysNunchukScene,            kiwi::EPackID_AllPack,    kiwi::ECreateType_Sibling,  kiwi::EExitType_3,        false},
    {nullptr, "Baseball",                     "RPBsbScene/",           kiwi::ESceneID_RPBsbScene,                   kiwi::EPackID_SportsPack, kiwi::ECreateType_Sibling,  kiwi::EExitType_Standard, false},
    {nullptr, "Bowling",                      "RPBowScene/",           kiwi::ESceneID_RPBowScene,                   kiwi::EPackID_SportsPack, kiwi::ECreateType_Sibling,  kiwi::EExitType_Standard, false},
    {nullptr, "Golf",                         "RPGolScene/",           kiwi::ESceneID_RPGolScene,                   kiwi::EPackID_SportsPack, kiwi::ECreateType_Sibling,  kiwi::EExitType_Standard, false},
    {nullptr, "Tennis",                       "RPTnsScene/",           kiwi::ESceneID_RPTnsScene,                   kiwi::EPackID_SportsPack, kiwi::ECreateType_Sibling,  kiwi::EExitType_Standard, false},
    {nullptr, "Boxing",                       "RPBoxScene/",           kiwi::ESceneID_RPBoxScene,                   kiwi::EPackID_SportsPack, kiwi::ECreateType_Sibling,  kiwi::EExitType_Standard, false},
    {nullptr, "Sports Pack",                  "RPSportsTitle/",        kiwi::ESceneID_RPSportsTitleScene,           kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Sibling,  true},
    {nullptr, "Sports Menu Select",           "RPSportsCommon/",       kiwi::ESceneID_RPSportsMenuScene,            kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_2,        true},
    {nullptr, "Training Menu",                "RPSportsTrainingMenu/", kiwi::ESceneID_RPSportsTrainingMenuScene,    kiwi::EPackID_SportsPack, kiwi::ECreateType_Sibling,  kiwi::EExitType_3,        true},
    {nullptr, "Physical Measure Menu",        "RPSportsPhysical/",     kiwi::ESceneID_RPSportsPhysicalMenuScene,    kiwi::EPackID_SportsPack, kiwi::ECreateType_Sibling,  kiwi::EExitType_3,        true},
    {nullptr, "Physical Measure Explanation", "RPSportsPhysical/",     kiwi::ESceneID_RPSportsPhysicalPreviewScene, kiwi::EPackID_SportsPack, kiwi::ECreateType_Sibling,  kiwi::EExitType_3,        true},
    {nullptr, "Physical Measure Results",     "RPSportsPhysical/",     kiwi::ESceneID_RPSportsPhysicalResultScene,  kiwi::EPackID_SportsPack, kiwi::ECreateType_Sibling,  kiwi::EExitType_3,        true},
    {nullptr, "Golf Course Select",           "RPGolScene/",           kiwi::ESceneID_RPGolSelectScene,             kiwi::EPackID_SportsPack, kiwi::ECreateType_Sibling,  kiwi::EExitType_Standard, false},
#elif defined(PACK_PLAY)
    {nullptr, "Logo",                         "RPCommonParty/",        kiwi::ESceneID_RPSysBootScene,               kiwi::EPackID_AllPack,    kiwi::ECreateType_Standard, kiwi::EExitType_Sibling,  true},
    {nullptr, "Player Select",                "RPCommonParty/",        kiwi::ESceneID_RPSysPlayerSelectScene,       kiwi::EPackID_AllPack,    kiwi::ECreateType_Standard, kiwi::EExitType_2,        true},
    {nullptr, "Nunchuk Check",                "RPCommonParty/",        kiwi::ESceneID_RPSysNunchukScene,            kiwi::EPackID_AllPack,    kiwi::ECreateType_Sibling,  kiwi::EExitType_3,        false},
    {nullptr, "Fishing",                      "RPFshScene/",           kiwi::ESceneID_RPFshScene,                   kiwi::EPackID_PartyPack,  kiwi::ECreateType_Sibling,  kiwi::EExitType_Standard, false},
    {nullptr, "Hockey",                       "RPHkyScene/",           kiwi::ESceneID_RPHkyScene,                   kiwi::EPackID_PartyPack,  kiwi::ECreateType_Sibling,  kiwi::EExitType_Standard, false},
    {nullptr, "Shooting",                     "RPDucScene/",           kiwi::ESceneID_RPDucScene,                   kiwi::EPackID_PartyPack,  kiwi::ECreateType_Sibling,  kiwi::EExitType_Standard, false},
    {nullptr, "Table Tennis",                 "RPPnpScene/",           kiwi::ESceneID_RPPnpScene,                   kiwi::EPackID_PartyPack,  kiwi::ECreateType_Sibling,  kiwi::EExitType_Standard, false},
    {nullptr, "Billiards",                    "RPBilScene/",           kiwi::ESceneID_RPBilScene,                   kiwi::EPackID_PartyPack,  kiwi::ECreateType_Sibling,  kiwi::EExitType_Standard, false},
    {nullptr, "Cow Race",                     "RPCowScene/",           kiwi::ESceneID_RPCowScene,                   kiwi::EPackID_PartyPack,  kiwi::ECreateType_Sibling,  kiwi::EExitType_Standard, false},
    {nullptr, "Wally",                        "RPWlyScene/",           kiwi::ESceneID_RPWlyScene,                   kiwi::EPackID_PartyPack,  kiwi::ECreateType_Sibling,  kiwi::EExitType_Standard, false},
    {nullptr, "Tank",                         "RPTnkScene/",           kiwi::ESceneID_RPTnkScene,                   kiwi::EPackID_PartyPack,  kiwi::ECreateType_Sibling,  kiwi::EExitType_Standard, false},
    {nullptr, "Bomb",                         "RPBomScene/",           kiwi::ESceneID_RPBomScene,                   kiwi::EPackID_PartyPack,  kiwi::ECreateType_Sibling,  kiwi::EExitType_Standard, false},
    {nullptr, "Party Pack",                   "RPPartyTitle/",         kiwi::ESceneID_RPPartyTitleScene,            kiwi::EPackID_PartyPack,  kiwi::ECreateType_Standard, kiwi::EExitType_Sibling,  true},
    {nullptr, "Tour Menu",                    "RPPartyCommon/",        kiwi::ESceneID_RPPartyMiiLoadScene,          kiwi::EPackID_PartyPack,  kiwi::ECreateType_Standard, kiwi::EExitType_Child,    true},
    {nullptr, "Tour Menu",                    "RPPartyCommon/",        kiwi::ESceneID_RPPartyMenuScene,             kiwi::EPackID_PartyPack,  kiwi::ECreateType_Sibling,  kiwi::EExitType_3,        true},
#elif defined(PACK_RESORT)
    {nullptr, "Strap",                        "StrapScene/",           kiwi::ESceneID_Sp2StrapScene,           false, kiwi::EGroupID_Cmn,   kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Standard, true},
    {nullptr, "SaveDataLoad",                 "SeqScene1/",            kiwi::ESceneID_Sp2SaveDataLoadScene,    false, kiwi::EGroupID_Cmn,   kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Standard, true},
    {nullptr, "Title",                        "SeqScene1/",            kiwi::ESceneID_Sp2TitleScene,           false, kiwi::EGroupID_Cmn,   kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Standard, true},
    {nullptr, "MiiSelect",                    "SeqScene2/",            kiwi::ESceneID_Sp2MiiSelectScene,       false, kiwi::EGroupID_Cmn,   kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Standard, true},
    {nullptr, "Swf(Chambara)",                "SwfScene/",             kiwi::ESceneID_Sp2SwfScene,             true,  kiwi::EGroupID_Swf,   kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Standard, true},
    {nullptr, "Jsk(JetSki)",                  "JskScene/",             kiwi::ESceneID_Sp2JskScene,             true,  kiwi::EGroupID_Jsk,   kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Standard, true},
    {nullptr, "Arc(Archery)",                 "ArcScene/",             kiwi::ESceneID_Sp2ArcScene,             true,  kiwi::EGroupID_Arc,   kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Standard, true},
    {nullptr, "Fld(Frisbee)",                 "FldScene/",             kiwi::ESceneID_Sp2FldScene,             true,  kiwi::EGroupID_Fld,   kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Standard, true},
    {nullptr, "Bsk(Basket)",                  "BskScene/",             kiwi::ESceneID_Sp2BskScene,             true,  kiwi::EGroupID_Bsk,   kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Standard, true},
    {nullptr, "Bwl(Bowling)",                 "BwlScene/",             kiwi::ESceneID_Sp2BwlScene,             true,  kiwi::EGroupID_Bwl,   kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Standard, true},
    {nullptr, "Can(Canoe)",                   "CanScene/",             kiwi::ESceneID_Sp2CanScene,             true,  kiwi::EGroupID_Can,   kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Standard, true},
    {nullptr, "Png(PingPong)",                "PngScene/",             kiwi::ESceneID_Sp2PngScene,             true,  kiwi::EGroupID_Png,   kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Standard, true},
    {nullptr, "Wkb(Wakeboard)",               "JskScene/",             kiwi::ESceneID_Sp2WkbScene,             true,  kiwi::EGroupID_Wkb,   kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Standard, true},
    {nullptr, "Pln(Plane)",                   "PlnScene/",             kiwi::ESceneID_Sp2PlnScene,             true,  kiwi::EGroupID_Pln,   kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Standard, true},
    {nullptr, "Glf(Golf)",                    "GlfScene/",             kiwi::ESceneID_Sp2GlfScene,             true,  kiwi::EGroupID_Glf,   kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Standard, true},
    {nullptr, "Dgl(DiscGolf)",                "DglScene/",             kiwi::ESceneID_Sp2DglScene,             true,  kiwi::EGroupID_Dgl,   kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Standard, true},
    {nullptr, "Bic(Bicycle)",                 "BicScene/",             kiwi::ESceneID_Sp2BicScene,             true,  kiwi::EGroupID_Bic,   kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Standard, true},
    {nullptr, "Omk(Omake)",                   "OmkScene/",             kiwi::ESceneID_Sp2OmkScene,             true,  kiwi::EGroupID_Omk,   kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Standard, true},
    {nullptr, "DebugRoot",                    "TestScene1/",           kiwi::ESceneID_Sp2DebugRootScene,       false, kiwi::EGroupID_Cmn,   kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Sibling,  true},
    {nullptr, "SaveDataDebug",                "TestScene1/",           kiwi::ESceneID_Sp2SaveDataDebugScene,   false, kiwi::EGroupID_Cmn,   kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Sibling,  true},
    {nullptr, "ContestMiiDebug",              "TestScene1/",           kiwi::ESceneID_Sp2ContestMiiDebugScene, false, kiwi::EGroupID_Cmn,   kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Sibling,  true},
    {nullptr, "MessageCheck",                 "TestScene1/",           kiwi::ESceneID_Sp2MessageCheckScene,    false, kiwi::EGroupID_Cmn,   kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Sibling,  true},
    {nullptr, "LayoutCheck",                  "TestScene2/",           kiwi::ESceneID_Sp2LayoutCheckScene,     false, kiwi::EGroupID_Debug, kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Sibling,  true},
    {nullptr, "LayoutCheck2",                 "TestScene3/",           kiwi::ESceneID_Sp2LayoutCheck2Scene,    false, kiwi::EGroupID_Debug, kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Sibling,  true},
    {nullptr, "NkjTest1",                     "TestScene3/",           kiwi::ESceneID_Sp2NkjTestScene,         false, kiwi::EGroupID_Debug, kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Sibling,  true},
    {nullptr, "LayoutTest1",                  "TestScene1/",           kiwi::ESceneID_Sp2LayoutTestScene,      false, kiwi::EGroupID_Cmn,   kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Sibling,  true},
    {nullptr, "SoundTest1",                   "TestScene1/",           kiwi::ESceneID_Sp2SoundTestScene,       false, kiwi::EGroupID_Cmn,   kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Sibling,  true},
    {nullptr, "CPUMii",                       "TestScene1/",           kiwi::ESceneID_Sp2CpuMiiScene,          false, kiwi::EGroupID_Cmn,   kiwi::EPackID_SportsPack, kiwi::ECreateType_Standard, kiwi::EExitType_Sibling,  true},
#endif
    // clang-format on
};

/**
 * @brief User-registered scenes
 */
TMap<s32, SceneCreator::Info> SceneCreator::sUserScenes;

/**
 * @brief Root debug menu scene ID
 */
s32 SceneCreator::sDebugRootID = -1;

/**
 * @brief Whether to boot into the root debug menu
 */
bool SceneCreator::sDebugRootBootUp = false;

/**
 * @brief Button combination required to be held to access the root debug menu
 */
u16 SceneCreator::sDebugRootButtons = 0xFFFF;

/**
 * @brief Gets information on the specified scene
 *
 * @param id Scene ID
 */
const SceneCreator::Info* SceneCreator::GetSceneInfo(s32 id) {
    const Info* pInfo;

    // Supply -1 to use the current scene ID
    if (id < 0) {
        id = RP_GET_INSTANCE(RPSysSceneMgr)->getCurrentSceneID();
    }

    pInfo = sUserScenes.Find(id);
    if (pInfo != nullptr) {
        return pInfo;
    }

    for (int i = 0; i < K_LENGTHOF(scPackScenes); i++) {
        pInfo = &scPackScenes[i];
        if (pInfo->id == id) {
            return pInfo;
        }
    }

    return nullptr;
}

/**
 * @brief Registers user scene class
 *
 * @param rInfo Scene info
 */
void SceneCreator::RegistScene(const Info& rInfo) {
    K_ASSERT_EX(rInfo.id >= 0, "Invalid scene ID");

    // Don't allow duplicate scene IDs
    const Info* pInfo = GetSceneInfo(rInfo.id);
    K_ASSERT_EX(pInfo == nullptr, "Scene ID %d already used: %s",
                pInfo->name.CStr());

    if (pInfo == nullptr) {
        sUserScenes.Insert(rInfo.id, rInfo);
    }
}

/**
 * @brief Registers root debug menu information
 * @details The debug root scene is entered when transitioning to the main
 * menu while the specified button mask is held, or always on first boot
 * if the bootUp flag is set.
 *
 * @param id Debug root scene ID (-1 to disable)
 * @param bootUp Whether to boot into the debug root scene
 * @param buttons Buttons that must be held to visit the debug root scene
 * (defaults to B+MINUS)
 */
void SceneCreator::RegistDebugRoot(s32 id, bool bootUp, u16 buttons) {
    K_ASSERT_EX(id >= 0 || id == -1, "Invalid scene ID");

    sDebugRootID = id;
    sDebugRootBootUp = bootUp;
    sDebugRootButtons = buttons;
}

/**
 * @brief Gets the scene ID of the main menu scene
 */
s32 SceneCreator::GetMenuScene() {
#if defined(PACK_SPORTS)
    return kiwi::ESceneID_RPSportsMenuScene;
#elif defined(PACK_PLAY)
    return kiwi::ESceneID_RPPartyMenuScene;
#elif defined(PACK_RESORT)
    return kiwi::ESceneID_Sp2TitleScene;
#else
    return -1;
#endif
}

/**
 * @brief Gets the scene ID of the bootup scene
 */
s32 SceneCreator::GetBootScene() {
#if defined(PACK_SPORTS) || defined(PACK_PLAY)
    return kiwi::ESceneID_RPSysBootScene;
#elif defined(PACK_RESORT)
    return kiwi::ESceneID_Sp2StrapScene;
#else
    return -1;
#endif
}

#if defined(PACK_SPORTS) || defined(PACK_PLAY)
/**
 * @brief Fades out into a new scene
 *
 * @param id Scene ID
 * @param reload Reload the current scene
 * @return Success
 */
bool SceneCreator::ChangeSceneAfterFade(s32 id, bool reload) {
    // Ensure all threads are idle
    if (!RP_GET_INSTANCE(RPSysSceneMgr)->isTaskFinished()) {
        return false;
    }

    // Optionally reload current scene
    s32 current = RP_GET_INSTANCE(RPSysSceneMgr)->getCurrentSceneID();
    if (reload) {
        id = current;
    }

    // Visit debug root instead of menu if buttons are held
    if (id == GetMenuScene() && current != sDebugRootID) {
        for (int i = 0; i < EPlayer_Max; i++) {
            const WiiCtrl& rCtrl = CtrlMgr::GetInstance().GetWiiCtrl(i);

            // Visit on boot
            bool visit = sDebugRootBootUp;

            // Always visit (no button combo)
            visit |= sDebugRootButtons == 0;

            // Button combo held
            visit |= rCtrl.IsConnected() && rCtrl.IsHold(sDebugRootButtons);

            if (visit) {
                sDebugRootBootUp = false;
                id = sDebugRootID;
                break;
            }
        }
    }

    // Send request to scene manager
    bool success =
        RP_GET_INSTANCE(RPSysSceneMgr)->changeNextSceneAfterFade(id, reload);

    // Fade out common sounds if we are switching sound archives
    if (IsSceneCommonSound(id) != IsSceneCommonSound(current)) {
        s16 frame = RP_GET_INSTANCE(RPSysSceneMgr)->getSceneFadeFrame();
        RP_GET_INSTANCE(RPSndAudioMgr)->setSystemSeFadeInFrame(frame);
    }

    // Update last scene for exiting
    if (GetSceneExitType(id) != EExitType_Child) {
        mLastSceneID = current;
    }

    return success;
}
#elif defined(PACK_RESORT)
/**
 * @brief Fades out into a new scene
 *
 * @param id Scene ID
 * @param pColor Fade color
 * @return Success
 */
bool SceneCreator::ChangeSceneAfterFade(s32 id, const nw4r::ut::Color* pColor) {
    // Ensure all threads are idle
    if (!RP_GET_INSTANCE(RPSysSceneMgr)->isTaskFinished()) {
        return false;
    }

    // Optionally reload current scene
    s32 current = RP_GET_INSTANCE(RPSysSceneMgr)->getCurrentSceneID();
    if (id == -1) {
        id = current;
    }

    // WS2 debug menu is replaced
    if (id == ESceneID_Sp2DebugRootScene) {
        id = sDebugRootID;
    }

    // Visit debug root instead of menu if on boot, or if buttons are held
    if (id == GetMenuScene() && current != sDebugRootID) {
        for (int i = 0; i < EPlayer_Max; i++) {
            const WiiCtrl& rCtrl = CtrlMgr::GetInstance().GetWiiCtrl(i);

            // Visit on boot
            bool visit = sDebugRootBootUp;

            // Always visit (no button combo)
            visit |= sDebugRootButtons == 0;

            // Button combo held
            visit |= rCtrl.IsConnected() && rCtrl.IsHold(sDebugRootButtons);

            if (visit) {
                sDebugRootBootUp = false;
                id = sDebugRootID;
                break;
            }
        }
    }

    // Send request to scene manager
    bool success =
        RP_GET_INSTANCE(RPSysSceneMgr)->changeNextSceneAfterFade(id, true);

    if (success && current >= 0) {
        // Fade out common sound effects
        s16 frame = RP_GET_INSTANCE(RPSysSceneMgr)->getSceneFadeFrame();
        RP_GET_INSTANCE(RPSndAudioMgr)->setSystemSeFadeInFrame(frame);

        // Update last scene for exiting
        mLastSceneID = current;

        if (pColor != nullptr) {
            RP_GET_INSTANCE(RPSysSceneMgr)->setMgrFadeColor(*pColor);
        }
    }

    return success;
}
#endif

KOKESHI_BY_PACK(KM_BRANCH_MF(0x80184ba4, SceneCreator, ChangeSceneAfterFade),  // Wii Sports
                KM_BRANCH_MF(0x8018459c, SceneCreator, ChangeSceneAfterFade),  // Wii Play
                KM_BRANCH_MF(0x8022edfc, SceneCreator, ChangeSceneAfterFade)); // Wii Sports Resort

/**
 * @brief Gets the specified scene's name
 * @details The ID defaults to the current scene (-1).
 *
 * @param id Scene ID
 */
const char* SceneCreator::GetSceneName(s32 id) const {
    const Info* pInfo = GetSceneInfo(id);
    return pInfo->name;
}

/**
 * @brief Gets the specified scene's resource directory name
 * @details The ID defaults to the current scene (-1).
 *
 * @param id Scene ID
 */
const char* SceneCreator::GetSceneDirectory(s32 id) const {
    const Info* pInfo = GetSceneInfo(id);
    return pInfo->dir;
}
KOKESHI_BY_PACK(KM_BRANCH_MF(0x80184758, SceneCreator, GetSceneDirectory),  // Wii Sports
                KM_BRANCH_MF(0x80184124, SceneCreator, GetSceneDirectory),  // Wii Play
                KM_BRANCH_MF(0x8022ebe8, SceneCreator, GetSceneDirectory)); // Wii Sports Resort

#if defined(PACK_RESORT)
/**
 * @brief Tests whether the specified scene should display the warning
 * screen while loading
 * @details The ID defaults to the current scene (-1).
 *
 * @param id Scene ID
 */
bool SceneCreator::IsSceneWarnAsLoading(s32 id) const {
    const Info* pInfo = GetSceneInfo(id);
    K_ASSERT_PTR(pInfo);
    return pInfo->warnAsSceneLoading;
}
KM_BRANCH_MF(0x8022eaf8, SceneCreator, IsSceneWarnAsLoading); // Wii Sports Resort

/**
 * @brief Gets the specified scene's group
 * @details The ID defaults to the current scene (-1).
 *
 * @param id Scene ID
 */
EGroupID SceneCreator::GetSceneGroup(s32 id) const {
    const Info* pInfo = GetSceneInfo(id);
    K_ASSERT_PTR(pInfo);
    return pInfo->group;
}
KM_BRANCH_MF(0x8022eb78, SceneCreator, GetSceneGroup); // Wii Sports Resort
#endif

/**
 * @brief Gets the specified scene's target pack
 * @details The ID defaults to the current scene (-1).
 *
 * @param id Scene ID
 */
EPackID SceneCreator::GetScenePack(s32 id) const {
    const Info* pInfo = GetSceneInfo(id);
    K_ASSERT_PTR(pInfo);
    return pInfo->pack;
}

/**
 * @brief Gets the specified scene's create type
 * @details The ID defaults to the current scene (-1).
 *
 * @param id Scene ID
 */
ECreateType SceneCreator::GetSceneCreateType(s32 id) const {
    const Info* pInfo = GetSceneInfo(id);
    K_ASSERT_PTR(pInfo);
    return pInfo->create;
}
KOKESHI_BY_PACK(KM_BRANCH_MF(0x801845f4, SceneCreator, GetSceneCreateType), // Wii Sports
                KM_BRANCH_MF(0x8018402c, SceneCreator, GetSceneCreateType), // Wii Play
                /* not applicable */); // Wii Sports Resort

/**
 * @brief Gets the specified scene's exit type
 * @details The ID defaults to the current scene (-1).
 *
 * @param id Scene ID
 */
EExitType SceneCreator::GetSceneExitType(s32 id) const {
    const Info* pInfo = GetSceneInfo(id);
    K_ASSERT_PTR(pInfo);
    return pInfo->exit;
}
KOKESHI_BY_PACK(KM_BRANCH_MF(0x80184558, SceneCreator, GetSceneExitType),  // Wii Sports
                KM_BRANCH_MF(0x80183f90, SceneCreator, GetSceneExitType),  // Wii Play
                KM_BRANCH_MF(0x8022eac4, SceneCreator, GetSceneExitType)); // Wii Sports Resort

/**
 * @brief Tests whether the specified scene requires the RP common sound
 * archive
 * @details The ID defaults to the current scene (-1).
 *
 * @param id Scene ID
 */
bool SceneCreator::IsSceneCommonSound(s32 id) const {
    const Info* pInfo = GetSceneInfo(id);
    K_ASSERT_PTR(pInfo);
    return pInfo->common;
}
KOKESHI_BY_PACK(KM_BRANCH_MF(0x801844bc, SceneCreator, IsSceneCommonSound), // Wii Sports
                KM_BRANCH_MF(0x80183ef4, SceneCreator, IsSceneCommonSound), // Wii Play
                /* not applicable */); // Wii Sports Resort

/**
 * @brief Creates a new scene by ID
 *
 * @param id Scene ID
 */
RPSysScene* SceneCreator::Create(s32 id) {
    RPSysScene* pScene = nullptr;

    // Check for user scene ID
    if (id >= ESceneID_Max) {
        pScene = CreateUserScene(id);
    } else {
#if defined(PACK_SPORTS) || defined(PACK_PLAY)
        switch (GetScenePack(id)) {
        case EPackID_SportsPack:
        case EPackID_PartyPack: {
            pScene = CreatePackScene(id);
            break;
        }

        case EPackID_AllPack: {
            pScene = CreateSystemScene(id);
            break;
        }

        case EPackID_MusicPack:
        case EPackID_HealthPack: {
            K_NOT_IMPLEMENTED();
            return nullptr;
        }

        default: {
            K_UNREACHABLE();
            return nullptr;
        }
        }
#elif defined(PACK_RESORT)
        pScene = CreatePackScene(id);
#endif
    }

    K_ASSERT_PTR(pScene);

#if defined(PACK_SPORTS) || defined(PACK_PLAY)
    if (GetSceneExitType(id) == EExitType_Child) {
        pScene->setEnterFast();
    }
#endif

#if defined(PACK_RESORT)
    if (IsSceneWarnAsLoading(id)) {
        pScene->enableLoadMessage();
    }
#endif

    pScene->setCreatorSceneID(mLastSceneID);
    return pScene;
}
KOKESHI_BY_PACK(KM_BRANCH_MF(0x80184838, SceneCreator, Create),  // Wii Sports
                KM_BRANCH_MF(0x80184230, SceneCreator, Create),  // Wii Play
                KM_BRANCH_MF(0x8022ec90, SceneCreator, Create)); // Wii Sports Resort

/**
 * @brief Creates a new system scene by ID
 *
 * @param id Scene ID
 */
RPSysScene* SceneCreator::CreateSystemScene(s32 id) {
#if defined(PACK_RESORT)
    K_NOT_IMPLEMENTED();
    return nullptr;
#else
    switch (id) {
    case ESceneID_RPSysBootScene: {
        return new RPSysBootScene();
    }

    case ESceneID_RPSysPlayerSelectScene: {
        return new RPSysPlayerSelectScene();
    }

    case ESceneID_RPSysNunchukScene: {
        return new RPSysNunchukScene();
    }

    default: {
        return nullptr;
    }
    }
#endif
}

/**
 * @brief Creates a new game scene by ID
 *
 * @param id Scene ID
 */
RPSysScene* SceneCreator::CreatePackScene(s32 id) {
    EGG::Scene* pScene = nullptr;

#if defined(PACK_SPORTS)
    pScene = RPSysSceneCreator::createSportsScene(id);
#elif defined(PACK_PLAY)
    pScene = RPSysSceneCreator::createPartyScene(id);
#elif defined(PACK_RESORT)
    pScene = RPSysSceneCreator::createSp2Scene(id);
#endif

    K_ASSERT_PTR(pScene);
    return static_cast<RPSysScene*>(pScene);
}

/**
 * @brief Creates a new user scene by ID
 *
 * @param id Scene ID
 */
RPSysScene* SceneCreator::CreateUserScene(s32 id) {
    const Info* pInfo = GetSceneInfo(id);
    K_ASSERT_PTR(pInfo);
    return pInfo->pCt();
}

} // namespace kiwi
