#ifndef RP_UTILITY_GAME_OBJ_BASE_H
#define RP_UTILITY_GAME_OBJ_BASE_H
#include <Pack/RPGraphics.h>
#include <Pack/RPTypes.h>
#include <Pack/RPUtility/RPUtlActorBase.h>

#include <egg/math.h>

/**
 * @brief Basic game object actor
 */
class RPUtlGameObjBase : public RPUtlActorBase {
public:
    RPUtlGameObjBase();
    virtual ~RPUtlGameObjBase(); // at 0x8

    virtual void Calculate(); // at 0x18
    virtual void UserDraw();  // at 0x20

    virtual void CalcModel(); // at 0x24

    virtual void CreateModel(const char* pName, u16 arg1, u16 arg2); // at 0x28
    virtual void CreateModel(u16 rd);                                // at 0x2C
    virtual void CreateAnm(RPGrpModelAnm::Anm anm, u16 num);         // at 0x30

    virtual void BindAnm(const char* pName, u16 arg1, RPGrpModelAnm::Anm anm,
                         u16 no);                                 // at 0x34
    virtual void BindAnm(RPGrpModelAnm::Anm anm, u16 no, u16 rd); // at 0x38

    virtual void StartAnm(RPGrpModelAnm::Anm anm, u16 no,
                          f32 frame); // at 0x3C
    virtual void StartAnmBlend(RPGrpModelAnm::Anm anm, u16 no, f32 frame,
                               f32 weight); // at 0x40

    virtual void CancelAnm(RPGrpModelAnm::Anm anm, u16 no); // at 0x44

    virtual void SetAnmUpdateRate(RPGrpModelAnm::Anm anm, u16 no,
                                  f32 rate); // at 0x48

    virtual f32 GetAnmFrame(RPGrpModelAnm::Anm anm, u16 no) const;    // at 0x4C
    virtual f32 GetAnmNumFrame(RPGrpModelAnm::Anm anm, u16 no) const; // at 0x50

    virtual void InitModel(bool arg0); // at 0x54

    const EGG::Vector3f& GetPosition() const {
        return mPosition;
    }
    const EGG::Vector3f& GetScale() const {
        return mScale;
    }
    const EGG::Matrix33f& GetTransform() const {
        return mTransform;
    }

    RPGrpModel* GetModel() const {
        return mpModel;
    }

private:
    EGG::Vector3f mPosition;   // at 0x4
    EGG::Vector3f mScale;      // at 0x10
    EGG::Matrix33f mTransform; // at 0x1C
    bool _40;
    RPGrpModel* mpModel; // at 0x44
};

DECOMP_SIZE_ASSERT(RPUtlGameObjBase, 0x48);

#endif
