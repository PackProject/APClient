// TODO(kiwi) Needs changes for WSR
#if !defined(PACK_RESORT)

// Implementation must be visible to the extension
#define private protected
#include <Pack/RPSystem/RPSysResourceManager.h>
#undef private

#include <Pack/RPKernel.h>
#include <Pack/RPParty.h>
#include <Pack/RPSystem.h>

#include <libkiwi.h>

#include <egg/core.h>

#include <nw4r/ut.h>

#include <revolution/OS.h>

#include <cstring>

namespace kiwi {
namespace {

/**
 * @brief Gets the current locale directory name
 */
String GetLocalDirectory() {
    char buffer[32];
    std::memset(buffer, 0, sizeof(buffer));

    RP_GET_INSTANCE(RPSysProjectLocal)->appendLocalDirectory(buffer);
    buffer[sizeof(buffer) - 1] = '\0';

    return String(buffer);
}

} // namespace

/**
 * @brief Patch archive file extension
 */
const char* ResourceMgr::scPatchExtension = ".wpatch";

/**
 * @brief Static/shared directory names
 */
const char* ResourceMgr::scStaticDirs[kiwi::EPackID_Max] = {
    "SportsStatic/",  // EPackID_SportsPack
    "PartyStatic/",   // EPackID_PartyPack
    "HealthStatic/",  // EPackID_HealthPack
    "MusicStatic/",   // EPackID_MusicPack
    "AllPackStatic/", // EPackID_AllPack
};

/**
 * @brief Scenes with cached archives
 */
const kiwi::ESceneID ResourceMgr::scCachedScenes[] = {
#if defined(PACK_SPORTS)
    ESceneID_RPSysPlayerSelectScene,
    ESceneID_RPSysNunchukScene,
    ESceneID_RPBsbScene,
    ESceneID_RPBowScene,
    ESceneID_RPGolScene,
    ESceneID_RPTnsScene,
    ESceneID_RPBoxScene,
    ESceneID_RPSportsTitleScene,
    ESceneID_RPSportsMenuScene,
    ESceneID_RPSportsTrainingMenuScene,
    ESceneID_RPSportsPhysicalMenuScene,
    ESceneID_RPSportsPhysicalPreviewScene,
    ESceneID_RPSportsPhysicalResultScene,
    ESceneID_RPGolSelectScene,
#elif defined(PACK_PLAY)
    ESceneID_RPSysPlayerSelectScene,
    ESceneID_RPSysNunchukScene,
    ESceneID_RPFshScene,
    ESceneID_RPHkyScene,
    ESceneID_RPDucScene,
    ESceneID_RPPnpScene,
    ESceneID_RPBilScene,
    ESceneID_RPCowScene,
    ESceneID_RPWlyScene,
    ESceneID_RPTnkScene,
    ESceneID_RPBomScene,
    ESceneID_RPPartyTitleScene,
    ESceneID_RPPartyMenuScene,
#else
#error Not yet implemented for WSR
#endif
};

/**
 * @brief Resource file cache
 */
THashMap<String, const Resource*> ResourceMgr::sResourceCache;

/**
 * @brief Decompressed resource file cache
 */
THashMap<String, const Resource*> ResourceMgr::sDecompCache;

/**
 * @brief Attempts to get the specified file from the archive
 *
 * @param pArchive Archive containing the file
 * @param pPath File path
 * @param[out] pSize File size, in bytes
 */
void* ResourceMgr::GetFileFromArchive(MultiArchive* pArchive, const char* pPath,
                                      u32* pSize) {

    K_ASSERT_PTR(pArchive);
    K_ASSERT_PTR(pPath);

    MultiArchive::FileInfo info;
    void* pFileData = pArchive->GetFile(pPath, &info);

    K_ASSERT_PTR_EX(pFileData, "Can't find file: %s", pPath);

    if (pSize != nullptr) {
        *pSize = info.length;
    }

    return pFileData;
}
KOKESHI_BY_PACK(KOKESHI_NOTIMPLEMENTED, // Wii Sports
                KM_BRANCH(0x801871E0, ResourceMgr::GetFileFromArchive), // Wii Play
                KOKESHI_NOTIMPLEMENTED); // Wii Sports Resort

/**
 * @brief Removes the specified resource file from the cache
 *
 * @param rResource Resource file
 */
void ResourceMgr::RemoveResourceFromCache(const Resource& rResource) {
    K_FOREACH (it, sResourceCache) {
        if (it->value == &rResource) {
            sResourceCache.Remove(it->key);
            break;
        }
    }

    K_FOREACH (it, sDecompCache) {
        if (it->value == &rResource) {
            sDecompCache.Remove(it->key);
            break;
        }
    }
}

/**
 * @brief Attempts to get the specified message data (BMG)
 *
 * @param pPath Message file path
 * @return Message file data
 */
void* ResourceMgr::GetMessageResource(const char* pPath) {
    return GetFileFromArchive(
        static_cast<MultiArchive*>(GetInstance().mpMessageArchive), pPath);
}
KOKESHI_BY_PACK(KOKESHI_NOTIMPLEMENTED, // Wii Sports
                KM_BRANCH(0x801871A4, ResourceMgr::GetMessageResource), // Wii Play
                KOKESHI_NOTIMPLEMENTED); // Wii Sports Resort

/**
 * @brief Attempts to load the common archive for the specified scene
 *
 * @note The "common" archive must always be named `common.carc`.
 *
 * @param scene Scene ID
 * @param pHeap Heap from which to allocate the buffer
 * @return Multi-handle archive containing any patches
 */
MultiArchive* ResourceMgr::LoadGameCommonArchive(s32 scene, EGG::Heap* pHeap) {
    if (pHeap == nullptr) {
        pHeap = EGG::Heap::getCurrentHeap();
    }

    K_ASSERT_PTR(pHeap);

    const char* pResDir = SceneCreator::GetInstance().GetSceneDirectory(scene);
    K_ASSERT_PTR(pResDir);

    const Resource* pResource = LoadDecomp( //
        Format("Common/%scommon.carc",      //
               pResDir),                    //
        pHeap);

    K_ASSERT_PTR(pResource);

    MultiArchive* pArchive = MultiArchive::Mount(*pResource, pHeap);
    K_ASSERT_PTR(pArchive);

    return pArchive;
}
KOKESHI_BY_PACK(KOKESHI_NOTIMPLEMENTED, // Wii Sports
                KM_BRANCH(0x801872D4, ResourceMgr::LoadGameCommonArchive), // Wii Play
                KOKESHI_NOTIMPLEMENTED); // Wii Sports Resort

/**
 * @brief Attempts to load the local archive for the specified scene
 *
 * @note The "local" archive must always be named `local.carc`.
 *
 * @param scene Scene ID
 * @param pHeap Heap from which to allocate the buffer
 * @return Multi-handle archive containing any patches
 */
MultiArchive* ResourceMgr::LoadGameLocalArchive(s32 scene, EGG::Heap* pHeap) {
    if (pHeap == nullptr) {
        pHeap = EGG::Heap::getCurrentHeap();
    }

    K_ASSERT_PTR(pHeap);

    const char* pResDir = SceneCreator::GetInstance().GetSceneDirectory(scene);
    K_ASSERT_PTR(pResDir);

    const Resource* pResource = LoadDecomp( //
        Format("%s%slocal.carc",            //
               GetLocalDirectory().CStr(),  //
               pResDir),                    //
        pHeap);

    K_ASSERT_PTR(pResource);

    MultiArchive* pArchive = MultiArchive::Mount(*pResource, pHeap);
    K_ASSERT_PTR(pArchive);

    return pArchive;
}
KOKESHI_BY_PACK(KOKESHI_NOTIMPLEMENTED, // Wii Sports
                KM_BRANCH(0x8018722C, ResourceMgr::LoadGameLocalArchive), // Wii Play
                KOKESHI_NOTIMPLEMENTED); // Wii Sports Resort

/**
 * @brief Loads all resources with static lifetime
 */
void ResourceMgr::LoadStaticArchives() {
    const char* pStaticDir =
        scStaticDirs[RP_GET_INSTANCE(RPSysProjectLocal)->getPack()];

    EGG::Heap* pResHeap = RP_GET_INSTANCE(RPSysSystem)->getResourceHeap();
    K_ASSERT_PTR(pResHeap);

    const Resource* pResource = nullptr;

    // Common static archive
    pResource =
        LoadDecomp(Format("Common/%scommon.carc", pStaticDir), pResHeap);

    K_ASSERT_PTR(pResource);
    mpStaticCommonArchive = MultiArchive::Mount(*pResource, pResHeap);
    K_ASSERT_PTR(mpStaticCommonArchive);

    // Locale static archive
    pResource = LoadDecomp(
        Format("%s%slocal.carc", GetLocalDirectory().CStr(), pStaticDir),
        pResHeap);

    K_ASSERT_PTR(pResource);
    mpStaticLocalArchive = MultiArchive::Mount(*pResource, pResHeap);
    K_ASSERT_PTR(mpStaticLocalArchive);

    // Message archive
    pResource = LoadDecomp(
        Format("%sMessage/message.carc", GetLocalDirectory().CStr()), pResHeap);

    K_ASSERT_PTR(pResource);
    mpMessageArchive = MultiArchive::Mount(*pResource, pResHeap);
    K_ASSERT_PTR(mpMessageArchive);

    // Font archive
    pResource = LoadDecomp(
        Format("%sFont/font.carc", GetLocalDirectory().CStr()), pResHeap);

    K_ASSERT_PTR(pResource);
    mpFontArchive = MultiArchive::Mount(*pResource, pResHeap);
    K_ASSERT_PTR(mpFontArchive);

    RPPartyBodyManager* pBodyManager = new (pResHeap) RPPartyBodyManager();
    K_ASSERT_PTR(pBodyManager);
    RP_GET_INSTANCE(RPSysKokeshiManager)->SetBodyManager(pBodyManager);

    RP_GET_INSTANCE(RPSysFontManager)->LoadResFonts();
}
KOKESHI_BY_PACK(KOKESHI_NOTIMPLEMENTED, // Wii Sports
                KM_BRANCH_MF(0x80186FA4, ResourceMgr, LoadStaticArchives), // Wii Play
                KOKESHI_NOTIMPLEMENTED); // Wii Sports Resort

/**
 * @brief Loads all cached resources
 */
void ResourceMgr::LoadCacheArchives() {
    EGG::Heap* pResHeap = RP_GET_INSTANCE(RPSysSystem)->getResourceHeap();
    K_ASSERT_PTR(pResHeap);

    for (int i = 0; i < K_LENGTHOF(scCachedScenes); i++) {
        const char* pResDir =
            SceneCreator::GetInstance().GetSceneDirectory(scCachedScenes[i]);

        K_ASSERT_PTR(pResDir);

        // Not enough memory to decompress these all ahead of time
        const Resource* pCommonResource =
            Load(Format("Common/%scommon.carc", pResDir), pResHeap);

        K_ASSERT_PTR(pCommonResource);

        // TODO(kiwi) Why only Wii Play? Are the local archives just that small?
#if defined(PACK_PLAY)
        // Not enough memory to decompress these all ahead of time
        const Resource* pLocalResource =
            Load(Format("%s%slocal.carc", GetLocalDirectory().CStr(), pResDir),
                 pResHeap);

        K_ASSERT_PTR(pLocalResource);
#endif
    }
}
KOKESHI_BY_PACK(KOKESHI_NOTIMPLEMENTED, // Wii Sports
                KM_BRANCH_MF(0x80186D54, ResourceMgr, LoadCacheArchives), // Wii Play
                KOKESHI_NOTIMPLEMENTED); // Wii Sports Resort

/**
 * @brief Loads the Kokeshi archive
 */
void ResourceMgr::LoadKokeshiArchive() {
    EGG::Heap* pResHeap = RP_GET_INSTANCE(RPSysSystem)->getResourceHeap();
    K_ASSERT_PTR(pResHeap);

    const Resource* pResource =
        LoadDecomp("Common/Kokeshi/common.carc", pResHeap);

    K_ASSERT_PTR(pResource);

    mpKokeshiArchive = MultiArchive::Mount(*pResource, pResHeap);
    K_ASSERT_PTR(mpKokeshiArchive);
}
KOKESHI_BY_PACK(KOKESHI_NOTIMPLEMENTED, // Wii Sports
                KM_BRANCH_MF(0x80186CEC, ResourceMgr, LoadKokeshiArchive), // Wii Play
                KOKESHI_NOTIMPLEMENTED); // Wii Sports Resort

/**
 * @brief Attempts to load the specified resource file
 *
 * @param pPath Archive path
 * @param pHeap Heap to use for allocations
 * @param cache Whether to cache the resource file
 * @return Resource file
 */
const Resource* ResourceMgr::Load(const char* pPath, EGG::Heap* pHeap,
                                  bool cache) {
    K_ASSERT_PTR(pPath);

    if (pHeap == nullptr) {
        pHeap = EGG::Heap::getCurrentHeap();
    }

    K_ASSERT_PTR(pHeap);

    // May have already been loaded
    const Resource* pResource = sResourceCache.Get(pPath);
    if (pResource != nullptr) {
        return pResource;
    }

    // Need to load
    FileRipperArg arg;
    arg.align = 32;
    arg.pHeap = pHeap;

    u32 fileSize = 0;
    arg.pSize = &fileSize;

    // Base file is required
    void* pBaseData = FileRipper::Rip(pPath, EStorage_DVD, arg);
    K_ASSERT_PTR_EX(pBaseData, "Can't find file: %s", pPath);

    DCFlushRange(pBaseData, fileSize);

    Resource* pNewResource = new (pHeap) Resource(pPath, fileSize, pBaseData);
    K_ASSERT_PTR(pNewResource);

    // Patch file is optional
    String patchPath = String(pPath) + scPatchExtension;
    void* pPatchData = FileRipper::Rip(patchPath, EStorage_DVD, arg);

    if (pPatchData != nullptr) {
        RPSysFile* pPatchFile =
            new (pHeap) RPSysFile(patchPath, fileSize, pPatchData);

        K_ASSERT_PTR(pPatchFile);
        pNewResource->RegistPatch(*pPatchFile);
    }

    if (cache) {
        sResourceCache.Insert(pPath, pNewResource);
    }

    return pNewResource;
}

/**
 * @brief Attempts to load and decompress the specified resource file
 *
 * @param pPath Archive path
 * @param pHeap Heap to use for allocations
 * @return Resource file
 */
const Resource* ResourceMgr::LoadDecomp(const char* pPath, EGG::Heap* pHeap) {
    K_ASSERT_PTR(pPath);

    if (pHeap == nullptr) {
        pHeap = EGG::Heap::getCurrentHeap();
    }

    K_ASSERT_PTR(pHeap);

    // May have already been decompressed
    const Resource* pResource = sDecompCache.Get(pPath);
    if (pResource != nullptr) {
        return pResource;
    }

    // May have already been loaded, but not decompressed yet
    pResource = sResourceCache.Get(pPath);

    // Don't cache it because we will decompress it
    if (pResource == nullptr) {
        pResource = Load(pPath, pHeap, false);
    }

    K_ASSERT_PTR(pResource);

    const Resource* pDecompResource = DecompResource(*pResource, pHeap);
    K_ASSERT_PTR(pDecompResource);

    // Can release compressed resource
    if (pDecompResource != pResource) {
        delete pResource;
    }

    sDecompCache.Insert(pPath, pDecompResource);
    return pDecompResource;
}

/**
 * @brief Attempts to decompress the specified resource file
 *
 * @param rResource Resource file
 * @param pHeap Heap to use for allocations
 * @return Decompressed resource
 */
const Resource* ResourceMgr::DecompResource(const Resource& rResource,
                                            EGG::Heap* pHeap) {

    if (pHeap == nullptr) {
        pHeap = EGG::Heap::getCurrentHeap();
    }

    K_ASSERT_PTR(pHeap);

    RPSysFile* pBaseFile = DecompFile(rResource.GetBaseFile(), pHeap);
    K_ASSERT_PTR(pBaseFile);

    Resource* pDecompResource = new (pHeap) Resource(
        pBaseFile->GetPath(), pBaseFile->GetSize(), pBaseFile->GetData());
    K_ASSERT_PTR(pDecompResource);

    K_FOREACH (it, rResource.GetPatchFiles()) {
        RPSysFile* pPatchFile = DecompFile(**it, pHeap);

        K_ASSERT_PTR(pPatchFile);
        pDecompResource->RegistPatch(*pPatchFile);
    }

    return pDecompResource;
}

/**
 * @brief Attempts to decompress the specified file
 *
 * @param rFile File to decompress
 * @param pHeap Heap to use for allocations
 * @return Decompressed file
 */
RPSysFile* ResourceMgr::DecompFile(const RPSysFile& rFile, EGG::Heap* pHeap) {
    if (pHeap == nullptr) {
        pHeap = EGG::Heap::getCurrentHeap();
    }

    K_ASSERT_PTR(pHeap);

    u8* pBaseData = const_cast<u8*>(rFile.GetData());
    K_ASSERT_PTR(pBaseData);

    // Resource may not actually be compressed
    if (EGG::Decomp::checkCompressed(pBaseData) ==
        EGG::Decomp::cCompress_None) {

        return const_cast<RPSysFile*>(&rFile);
    }

    s32 expandSize = EGG::Decomp::getExpandSize(pBaseData);
    u8* pExpandData = new (32, pHeap) u8[expandSize];

    K_ASSERT_PTR(pExpandData);
    s32 decompSize = EGG::Decomp::decode(pBaseData, pExpandData);

    K_ASSERT_EX(decompSize <= expandSize, "Decomp buffer overflow!");
    DCFlushRange(pExpandData, decompSize);

    RPSysFile* pDecompFile =
        new (pHeap) RPSysFile(rFile.GetPath(), decompSize, pExpandData);
    K_ASSERT_PTR(pDecompFile);

    return pDecompFile;
}

} // namespace kiwi

#endif