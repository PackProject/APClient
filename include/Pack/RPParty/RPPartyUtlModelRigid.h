#ifndef RP_PARTY_UTL_MODEL_RIGID_H
#define RP_PARTY_UTL_MODEL_RIGID_H
#include <types.h>

#include <Pack/RPParty/RPPartyUtlModel.h>

#include <egg/math.h>

// Forward declarations
class RPGrpModel;

/**
 * @brief Party Pack rigid body physics utility
 */
class RPPartyUtlModelRigid : public RPPartyUtlModel {
public:
    struct RigidParam {
        s32 id;      // at 0x0
        f32 mass;    // at 0x4
        f32 gravity; // at 0x8
        f32 radius;  // at 0xC
        f32 _10;
        f32 friction; // at 0x14
        f32 _18;
        f32 _1C;
    };

    struct RigidBounding {
        EGG::Vector3f min; // at 0x0
        EGG::Vector3f max; // at 0xC
    };

public:
    RPPartyUtlModelRigid(const RigidParam& rParam);
    virtual ~RPPartyUtlModelRigid();

    void Calculate();

    bool isStopped() const;

    f32 getFriction() const {
        return mParam.friction;
    }

    f32 getRadius() const {
        return mParam.radius;
    }

private:
    RigidParam mParam; // at 0x60

    EGG::Matrix34f _80;
    EGG::Matrix34f _B0;
    EGG::Vector3f mAngularVel; // at 0xE0
    char _EC[0xFC - 0xEC];

    RigidBounding* _FC;
    RigidBounding* _100;
    RigidBounding* _104;
};

#endif
