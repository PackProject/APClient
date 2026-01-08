#include "core/CheckMgr.h"
#include "core/CosmeticMgr.h"
#include "core/EchoSocket.h"
#include "core/ItemMgr.h"
#include "core/const.h"
#include <Pack/RPSystem.h>

#include <libkiwi.h>

#include <kokeshi.hpp>

/**
 * Mod entrypoint
 */
void KokeshiMain() {
#ifndef NDEBUG
    // Setup libkiwi debugging utilities
    kiwi::Nw4rException::CreateInstance();
    kiwi::MapFile::CreateInstance();
    kiwi::MapFile::GetInstance().Open(kokeshi::MAPFILE_PATH,
                                      kiwi::MapFile::ELinkType_Relocatable);
#endif

    // Initialize network socket system
    kiwi::LibSO::Initialize();

    // Archipelago initialization
    AP::ItemMgr::CreateInstance();
    AP::CosmeticMgr::CreateInstance();
    AP::CheckMgr::CreateInstance();

    // TODO: Move to debug menu eventually
#ifndef NDEBUG
    AP::ItemMgr::GetInstance().Debug();
    AP::CosmeticMgr::GetInstance().Debug();
    AP::CheckMgr::GetInstance().Debug();
#endif

    // Register debug menu
    kiwi::SceneCreator::GetInstance().RegistDebugRoot(
        AP::ESceneID_DebugRootScene);

    // Enter first scene
    kiwi::SceneCreator::GetInstance().ChangeBootScene();

    AP::EchoSocket::CreateInstance();

    // Enter game loop
    RP_GET_INSTANCE(RPSysSystem)->mainLoop();

    // Main function should never return
    ASSERT(false);
}
KOKESHI_BY_PACK(KM_CALL(0x80183b6c, KokeshiMain),  // Wii Sports
                KM_CALL(0x80183784, KokeshiMain),  // Wii Play
                KM_CALL(0x8022df10, KokeshiMain)); // Wii Sports Resort
