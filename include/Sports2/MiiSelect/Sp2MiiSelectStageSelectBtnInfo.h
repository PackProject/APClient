#ifndef SPORTS2_MIISELECT_STAGE_SELECT_BTN_INFO_H
#define SPORTS2_MIISELECT_STAGE_SELECT_BTN_INFO_H
#include <Sports2/Sp2Types.h>

namespace Sp2 {
namespace MiiSelect {

class StageSelectBtnInfo {
public:
    enum EState { EState_Open, EState_New, EState_Locked };

    static const u32 BUTTON_MAX = 7;

public:
    void setBtnState(u32 idx, EState state) {
        mButtonStates[idx] = state;
    }

private:
    char _00[0x18];
    EState mButtonStates[BUTTON_MAX]; // at 0x18
};

} // namespace MiiSelect
} // namespace Sp2

#endif
