#include <Sports2/Sp2Cmn.h>
#include <Sports2/Sp2Snd.h>
#include <Sports2/Sp2Swf.h>
#include <core/ItemMgr.h>
#include <hooks/hooks_Swf.h>
#include <hooks/trampoline.h>
#include <libkiwi.h>
#include <types.h>

namespace AP {
namespace Swf {

/******************************************************************************
 *
 * Swordplay (Duel)
 *
 ******************************************************************************/

/**
 * @brief Attempts to perform a block in Swordplay (Duel)
 *
 * @param pUserCtrl User control interface
 * @param pController Remote controller
 */
void TryBlock(Sp2::Swf::UserCtrl* pUserCtrl,
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

    bool unlocked = false;
    u32 sequence = RP_GET_INSTANCE(Sp2::Cmn::StaticMem)->getSequence();

    // Check the appropriate AP item to see if blocking is allowed
    switch (sequence) {
    case Sp2::Cmn::ESeq_Swf_Vs: {
        unlocked = ItemMgr::GetInstance().IsSwfVsBlock();
        break;
    }

    case Sp2::Cmn::ESeq_Swf_Sgl: {
        unlocked = ItemMgr::GetInstance().IsSwfSglBlock();
        break;
    }

    case Sp2::Cmn::ESeq_Swf_Prc: {
        unlocked = true;
        break;
    }

    default: {
        K_ASSERT_EX(false, "Invalid sequence %d", sequence);
        break;
    }
    }

    // Don't play the sound every frame.
    // Also, the sound is disabled during certain phases of the game
    Sp2::Swf::SoundObject* pSound =
        RP_GET_INSTANCE(Sp2::Swf::Scene)->getGuardSoundObject();

    ASSERT(pSound != nullptr);
    bool playSound = !pUserCtrl->isBlocking() && pSound->isEnabled();

    if (playSound) {
        Sp2::Swf::PlayerObject* pPlayer = pUserCtrl->getPlayerObject();
        K_ASSERT(pPlayer != nullptr);

        // Determine which remote speaker to play through
        int remote = pPlayer->getRemoteNo();

        if (unlocked) {
            Sp2::SndUtil::playSound(SE_SWF_SWORD_SWING_GUARD, 1 << remote);
        }
        // Rejection sound effect is only played on the initial B press
        else if (pressed) {
            Sp2::SndUtil::playSound(SE_CMN_NG_01, 1 << remote);
        }
    }

    pUserCtrl->setBlocking(unlocked);
}

/**
 * @brief TryBlock trampoline
 */
TRAMPOLINE_DEF(0x8060E33C, 0x8060E394) {
    // clang-format off
    TRAMPOLINE_BEGIN

    mr r3, r31
    mr r4, r30
    bl TryBlock

    TRAMPOLINE_END
    // clang-format on
}

/******************************************************************************
 *
 * Swordplay (Speed Slice)
 *
 ******************************************************************************/

/**
 * @brief Tests whether an object is currently falling in Swordplay (Speed
 * Slice)
 */
bool PrcIsObjFalling() {
    Sp2::Swf::PrcRuleObject* pRuleObject =
        RP_GET_INSTANCE(Sp2::Swf::Scene)->getPrcRuleObject();
    K_ASSERT(pRuleObject != nullptr);

    Sp2::Swf::TrainerObject* pTrainerObject = pRuleObject->getTrainerObject();
    K_ASSERT(pTrainerObject != nullptr);

    switch (pTrainerObject->getState()) {
    case Sp2::Swf::TrainerObject::EState_PrepareThrow:
    case Sp2::Swf::TrainerObject::EState_Throw:
    case Sp2::Swf::TrainerObject::EState_ThrowJump:
    case Sp2::Swf::TrainerObject::EState_WaitFall:
    case Sp2::Swf::TrainerObject::EState_Judge:
    case Sp2::Swf::TrainerObject::EState_JudgeResult:  {
        return true;
    }

    case Sp2::Swf::TrainerObject::EState_None:
    case Sp2::Swf::TrainerObject::EState_Wait:
    default:                                   {
        return false;
    }
    }
}

/******************************************************************************
 *
 * Swordplay (Showdown)
 *
 ******************************************************************************/

/**
 * @brief Sets the number of hearts in Swordplay (Showdown)
 *
 * @param pPlayer Player object
 */
void SglSetHeartNum(Sp2::Swf::SglPlayerObject* pPlayer) {
    K_ASSERT(pPlayer != nullptr);

    int heartNum = ItemMgr::GetInstance().GetSwfSglHeartNum();
    pPlayer->setHeartNum(heartNum);
}

/**
 * @brief SglSetHeartNum trampoline
 */
TRAMPOLINE_DEF(0x8063A010, 0x8063A014){
    // clang-format off
    TRAMPOLINE_BEGIN

    bl SglSetHeartNum
    li r0, 0

    TRAMPOLINE_END
    // clang-format on
}

/**
 * @brief Tests whether the specified stage is unlocked in Swordplay (Showdown)
 *
 * @param id Stage ID
 */
Sp2::Cmn::EUnlockState SglGetStageState(UNKWORD, UNKWORD, u32 id) {
    bool unlock = ItemMgr::GetInstance().IsSwfSglStageUnlock(id);

    return unlock ? Sp2::Cmn::EUnlockState_Unlocked
                  : Sp2::Cmn::EUnlockState_Locked;
}
KM_BRANCH(0x802E4848, SglGetStageState);

} // namespace Swf
} // namespace AP
