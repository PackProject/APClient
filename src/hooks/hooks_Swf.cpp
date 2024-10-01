#include <Sports2/Sp2Cmn.h>
#include <Sports2/Sp2Snd.h>
#include <Sports2/Sp2Swf.h>
#include <core/ItemMgr.h>
#include <hooks/trampoline.h>
#include <libkiwi.h>
#include <types.h>

namespace AP {
namespace Swf {

/**
 * @brief Attempts to perform a block in Swordplay (Duel)
 *
 * @param pUserCtrl User control interface
 * @param pController Remote controller
 */
void TryBlockVs(Sp2::Swf::UserCtrl* pUserCtrl,
                const Sp2::Cmn::Controller* pController) {
    K_ASSERT(pUserCtrl != nullptr);
    K_ASSERT(pController != nullptr);

    bool pressed = pController->getCoreStatus()->trig & EGG::CORE_BTN_B;
    bool held = pController->getCoreStatus()->hold & EGG::CORE_BTN_B;

    // Blocking is controlled by the B Button
    if (!held) {
        pUserCtrl->setBlocking(false);
        return;
    }

    Sp2::Swf::SoundObject* pGuardSound =
        Sp2::Swf::Scene::getInstance().getGuardSound();

    ASSERT(pGuardSound != nullptr);

    // Don't play the sound every frame.
    // Also, the sound is disabled during certain phases of the game
    bool playSound = !pUserCtrl->isBlocking() && pGuardSound->isEnabled();

    // The ability may not be unlocked yet
    bool unlocked = ItemMgr::GetInstance().SwfVsCanBlock();

    // Determine which remote speaker to play through
    Sp2::Swf::PlayerObject* pPlayer = pUserCtrl->getPlayerObject();
    K_ASSERT(pPlayer != nullptr);
    int remote = pPlayer->getRemoteNo();

    if (unlocked) {
        pUserCtrl->setBlocking(true);

        if (playSound) {
            Sp2::SndUtil::playSound(SE_SWF_SWORD_SWING_GUARD, 1 << remote);
        }
    } else {
        pUserCtrl->setBlocking(false);

        // Rejection sound effect is only played on the initial B press
        if (pressed && playSound) {
            Sp2::SndUtil::playSound(SE_CMN_NG_01, 1 << remote);
        }
    }
}

/**
 * @brief TryBlockVs trampoline
 */
TRAMPOLINE_DEF_EXIT(0x8060E33C, 0x8060E394) {
    // clang-format off
    TRAMPOLINE_BEGIN

    mr r3, r31
    mr r4, r30
    bl TryBlockVs

    TRAMPOLINE_END
    // clang-format on
}

} // namespace Swf
} // namespace AP
