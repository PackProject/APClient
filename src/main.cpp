#include "Cmn/System.h"
#include "const.h"
#include <Pack/RPSystem.h>

#include <libkiwi.h>

#include <kokeshi.hpp>

/**
 * Mod entrypoint
 */
void KokeshiMain() {
    // Setup libkiwi debugging utilities
#if !defined(NDEBUG)
    kiwi::Nw4rException::CreateInstance();

    kiwi::MapFile::CreateInstance();
    kiwi::MapFile::GetInstance().Open(kokeshi::MAPFILE_PATH,
                                      kiwi::MapFile::ELinkType_Relocatable);

    kiwi::DebugConsole::CreateInstance();
#endif

    // Initialize network socket system
    kiwi::LibSO::Initialize();

    // Archipelago initialization
    AP::Cmn::System::Initialize();

    // Register debug menu
    kiwi::SceneCreator::GetInstance().RegistDebugRoot(
        AP::ESceneID_DebugRootScene);

    // Enter first scene
    kiwi::SceneCreator::GetInstance().ChangeBootScene();

    // Enter game loop
    RP_GET_INSTANCE(RPSysSystem)->mainLoop();

    // Main function should never return
    ASSERT(false);
}
KOKESHI_BY_PACK(KM_CALL(0x80183b6c, KokeshiMain),  // Wii Sports
                KM_CALL(0x80183784, KokeshiMain),  // Wii Play
                KM_CALL(0x8022df10, KokeshiMain)); // Wii Sports Resort
