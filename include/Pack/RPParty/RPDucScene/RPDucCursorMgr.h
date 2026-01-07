#ifndef RP_PARTY_DUC_CURSOR_MGR_H
#define RP_PARTY_DUC_CURSOR_MGR_H
#include <Pack/RPParty/RPDucScene/RPDucCursor.h>

#include <RPTypes.h>

// Forward declarations
class RPDucCursor;

class RPDucCursorMgr {
    RP_SINGLETON_DECL(RPDucCursorMgr);

public:
    virtual UNKTYPE FUN_801b6b74(UNKTYPE); // at 0xC
    virtual UNKTYPE FUN_80244a40(UNKTYPE); // at 0x10

    virtual void Reset();     // at 0x14
    virtual void Calculate(); // at 0x18
    virtual void Exit();      // at 0x1C

    virtual UNKTYPE FUN_80244790(UNKTYPE); // at 0x20

    void PlayCursorOnSfx(s32 idx);
    void SetEffectState(s32 idx, RPDucCursor::EEffectState state);

    void CreateCursors(u32 num);

private:
    static const int MAX_CURSORS = 4;

    u32 mCursorCapacity;                 // at 0x4
    u32 mCursorNum;                      // at 0x8
    RPDucCursor* mpCursors[MAX_CURSORS]; // at 0xC
};

#if defined(__KOKESHI__)
DECL_WEAK inline RPDucCursorMgr::RPDucCursorMgr() {}
#endif

#endif
