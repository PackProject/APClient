#ifndef RP_PARTY_BIL_TABLE_H
#define RP_PARTY_BIL_TABLE_H
#include <Pack/RPTypes.h>

#include <egg/math.h>

class RPBilTable {
    RP_SINGLETON_DECL(RPBilTable);

public:
    bool IsValidPlaceFoul(const EGG::Vector3f& rPos, f32 radius) const;

    static EGG::Vector3f GetFootSpotPos();
};

#endif
