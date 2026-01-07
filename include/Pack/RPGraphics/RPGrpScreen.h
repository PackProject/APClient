#ifndef RP_GRAPHICS_SCREEN_H
#define RP_GRAPHICS_SCREEN_H
#include "RPTypes.h"
#include <egg/gfx/eggScreen.h>

class RPGrpScreen : public EGG::Screen {
public:
    RPGrpScreen() {
        SetFarZ(100000.0f);
    }

    RPGrpScreen(f32 x, f32 y, f32 width, f32 height,
                const Screen* pParent = NULL,
                CanvasMode canvasMode = CANVASMODE_LU)
        : EGG::Screen(x, y, width, height, pParent, canvasMode) {}

    virtual ~RPGrpScreen();

private:
};

#endif
