#ifndef RP_UTILITY_LYT_BASE_H
#define RP_UTILITY_LYT_BASE_H
#include "RPTypes.h"

#include <egg/core.h>

// Forward declarations
class RPSysLytResAccessor;

class RPUtlLytBase {
public:
    RPUtlLytBase();

    virtual void LoadResource(EGG::Archive* pArchive); // at 0x8
    virtual void Reset();                              // at 0xC
    virtual void Calculate();                          // at 0x10
    virtual void VF_14();                              // at 0x14
    virtual void VF_18();                              // at 0x18

    static void mountArchive(EGG::Archive* pArchive, const char* pPath,
                             RPSysLytResAccessor* pAccessor);

protected:
    RPSysLytResAccessor* mAccessor; // at 0x4
};

#endif
