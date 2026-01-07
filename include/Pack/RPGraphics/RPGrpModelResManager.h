#ifndef RP_GRAPHICS_MODEL_RES_MANAGER_H
#define RP_GRAPHICS_MODEL_RES_MANAGER_H
#include <RPTypes.h>

class RPGrpModelResManager {
public:
    enum Type {
        Type_0Bh = 0xB,

        Type_ResFile,
        Type_ResMdl,
        Type_ResPltt,
        Type_ResTex,
        Type_ResAnmChr,
        Type_ResAnmVis,
        Type_ResAnmClr,
        Type_ResAnmTexPat,
        Type_ResAnmTexSrt,
        Type_ResAnmShp,
        Type_ResAnmScn,

        Type_Max
    };

protected:
    struct ResHolder {
        void* pResFileData; // at 0x0
    };

    struct Res {
        Type type;             // at 0x0
        void* pData;           // at 0x4
        ResHolder* pResHolder; // at 0x8
        char _0C[0x10 - 0xC];
    };

protected:
    Res* mResourceList; // at 0x0
    u16 mResourceNum;   // at 0x4

    static RPGrpModelResManager* spCurrent;

public:
    static RPGrpModelResManager* GetCurrent() {
        return spCurrent;
    }

    void CreateResourceList(u16 capacity);

    u16 CreateData(Type type, void* pData, u32 arg2 = 0);

    void* GetPtr(Type type, u16 file, int index) const;
    void* GetPtr(Type type, u16 file, const char* pName) const;

    template <typename T> T GetData(u16 file, int index) const;
    template <typename T> T GetData(u16 file, const char* pName) const;

public:
    RPGrpModelResManager();
    virtual ~RPGrpModelResManager();
};

template <>
inline nw4r::g3d::ResFile
RPGrpModelResManager::GetData<nw4r::g3d::ResFile>(u16 file,
                                                  int /* index */) const {
    return nw4r::g3d::ResFile(mResourceList[file].pResHolder->pResFileData);
}

#define GET_DATA_FUNC_IMPL(T)                                                  \
    template <>                                                                \
    inline nw4r::g3d::T RPGrpModelResManager::GetData<nw4r::g3d::T>(           \
        u16 file, int index) const {                                           \
                                                                               \
        const nw4r::g3d::ResFile resFile(                                      \
            mResourceList[file].pResHolder->pResFileData);                     \
                                                                               \
        return resFile.Get##T(index);                                          \
    }                                                                          \
    template <>                                                                \
    inline nw4r::g3d::T RPGrpModelResManager::GetData<nw4r::g3d::T>(           \
        u16 file, const char* pName) const {                                   \
                                                                               \
        const nw4r::g3d::ResFile resFile(                                      \
            mResourceList[file].pResHolder->pResFileData);                     \
                                                                               \
        return resFile.Get##T(pName);                                          \
    }

GET_DATA_FUNC_IMPL(ResMdl);
GET_DATA_FUNC_IMPL(ResPltt);
GET_DATA_FUNC_IMPL(ResTex);
GET_DATA_FUNC_IMPL(ResAnmChr);
GET_DATA_FUNC_IMPL(ResAnmVis);
GET_DATA_FUNC_IMPL(ResAnmClr);
GET_DATA_FUNC_IMPL(ResAnmTexPat);
GET_DATA_FUNC_IMPL(ResAnmTexSrt);
GET_DATA_FUNC_IMPL(ResAnmShp);
GET_DATA_FUNC_IMPL(ResAnmScn);

#undef GET_DATA_FUNC_IMPL

#endif
