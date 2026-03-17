#ifndef RP_GRAPHICS_RENDERER_H
#define RP_GRAPHICS_RENDERER_H
#include <Pack/types_pack.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpScreen;
class RPGrpCamera;
class RPGrpView;

/**
 * @brief Rendering engine
 */
class RPGrpRenderer {
public:
    enum EDrawPass {
        EDrawPass_DrawBefore,
        EDrawPass_1,
        EDrawPass_2,
        EDrawPass_3,
        EDrawPass_DrawAfter,
        EDrawPass_Draw2D,
        EDrawPass_Effect0,
        EDrawPass_Effect1,
        EDrawPass_Effect3,
        EDrawPass_Effect4,
        EDrawPass_Effect2,
        EDrawPass_Begin,
        EDrawPass_End,
        EDrawPass_Null
    };

public:
    static void Begin();
    static void End();

    void AppendDrawObject(IRPGrpDrawObject*);

    void CreateView2D(u8 id, RPGrpScreen* pScreen);
    void CreateView3D(u8 id, RPGrpCamera* pCamera, RPGrpScreen* pScreen);

    void CorrectView();

    static void SetEfbClearColor(u8 r, u8 g, u8 b);

    static EDrawPass GetDrawPass() {
        return sDrawPass;
    }
    static u8 GetViewID() {
        return sCurrentViewID;
    }

    /**
     * @brief Gets the currently active manager instance
     */
    static RPGrpRenderer* GetCurrent() {
        return spCurrent;
    }

    RPGrpView* GetView(u32 no) const {
        return mDrawViews[no];
    }

    /**
     * @brief Gets the screen currently being rendered to
     */
    static RPGrpScreen* GetCurrentScreen() {
        return spCurrentScreen;
    }

    static bool IsLytDraw() {
        return sDrawPass == EDrawPass_Draw2D;
    }

private:
    static const int MAX_VIEW = 32;

private:
    char UNK_0x0[0xC];
    IRPGrpDrawObject* mDrawObjects; // at 0xC
    char _10[0x4];
    RPGrpView* mDrawViews[MAX_VIEW]; // at 0x14

    static EDrawPass sDrawPass;
    static u8 sCurrentViewID;

    //! Allocator used for model-related allocations
    static RPGrpRenderer* spCurrent;

    //! Screen currently being rendered to
    static RPGrpScreen* spCurrentScreen;
};

//! @}

#endif
