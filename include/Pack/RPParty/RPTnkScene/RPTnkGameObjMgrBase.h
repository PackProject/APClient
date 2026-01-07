#ifndef RP_PARTY_TNK_GAME_OBJ_MGR_BASE_H
#define RP_PARTY_TNK_GAME_OBJ_MGR_BASE_H
#include <Pack/RPTypes.h>
#include <Pack/RPUtility/RPUtlActorBase.h>

#include <egg/core.h>

// Forward declarations
class RPTnkGameObjBase;

/**
 * @brief Tanks game object manager
 */
class RPTnkGameObjMgrBase : public RPUtlActorBase {
public:
    RPTnkGameObjMgrBase();
    virtual ~RPTnkGameObjMgrBase(); // at 0x8

    virtual void LoadResource(); // at 0x10
    virtual void Reset();        // at 0x14

    virtual RPTnkGameObjBase* Create() = 0; // at 0x24
    virtual void Reserve(u32 num);          // at 0x28
    virtual void Finalize() = 0;            // at 0x2C

    virtual void CalcMove();   // at 0x30
    virtual void FirstCalc();  // at 0x34
    virtual void SecondCalc(); // at 0x38
    virtual void ThirdCalc();  // at 0x3C

    virtual void OnCalculate();  // at 0x40
    virtual void CalcLifeTime(); // at 0x44
    virtual void CalcModel();    // at 0x48

    virtual void Init(const EGG::Vector3f& rPosition, u32 param); // at 0x4C
    virtual void Destroy();                                       // at 0x50

protected:
    typedef RPTnkGameObjBase** Iterator;
    typedef const RPTnkGameObjBase** ConstIterator;

protected:
    u32 mCapacity;                  // at 0x4
    u32 mSize;                      // at 0x8
    RPTnkGameObjBase** mppData;     // at 0xC
    RPTnkGameObjBase** mppDataFree; // at 0x10
    RPTnkGameObjBase** mppDataEnd;  // at 0x14
};

#endif
