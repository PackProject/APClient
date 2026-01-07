#ifndef RP_GRAPHICS_VIEW_H
#define RP_GRAPHICS_VIEW_H
#include <Pack/RPTypes.h>

// Forward declarations
class RPGrpCamera;

class RPGrpView {
protected:
    u8 mViewNo;    // at 0x0
    u8 mDrawScene; // at 0x1
    char _02[0x1C - 0x2];

public:
    virtual ~RPGrpView();                                // at 0x8
    virtual UNKTYPE VF_0xC(UNKTYPE) = 0;                 // at 0xC
    virtual void AttachCamera(RPGrpCamera* pCamera) = 0; // at 0x10

    void SetDrawScene(u8 scene) {
        mDrawScene = scene;
    }

private:
    ;
};

#endif
