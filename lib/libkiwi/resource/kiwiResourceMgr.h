#ifndef LIBKIWI_RESOURCE_RESOURCE_MGR_H
#define LIBKIWI_RESOURCE_RESOURCE_MGR_H
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiHashMap.h>
#include <libkiwi/prim/kiwiString.h>
#include <libkiwi/util/kiwiExtension.h>

#include <egg/core.h>

namespace kiwi {
//! @addtogroup libkiwi_resource
//! @{

// Forward declarations
class MultiArchive;
class Resource;

/**
 * @brief Pack Project resource manager extension
 */
class ResourceMgr : public ExtSingletonPtr<RPSysResourceManager, ResourceMgr> {
public:
    /**
     * @brief Attempts to get the specified file from the archive
     *
     * @param pArchive Archive containing the file
     * @param pPath File path
     * @param[out] pSize File size, in bytes
     */
    static void* GetFileFromArchive(MultiArchive* pArchive, const char* pPath,
                                    u32* pSize = nullptr);

    /**
     * @brief Removes the specified resource file from the cache
     *
     * @param rResource Resource file
     */
    static void RemoveResourceFromCache(const Resource& rResource);

    /**
     * @brief Attempts to get the specified message data (BMG)
     *
     * @param pPath Message file path
     * @return Message file data
     */
    static void* GetMessageResource(const char* pPath);

#if defined(PACK_RESORT)
    // TODO(kiwi) FUN_80232228
    // TODO(kiwi) FUN_80231fe4
    static MultiArchive* LoadArchiveWS2(...);
#endif

    /**
     * @brief Attempts to load the common archive for the specified scene
     *
     * @note The "common" archive must always be named `common.carc`.
     *
     * @param scene Scene ID
     * @param pHeap Heap from which to allocate the buffer
     * @return Multi-handle archive containing any patches
     */
    static MultiArchive* LoadGameCommonArchive(s32 scene = -1,
                                               EGG::Heap* pHeap = nullptr);

    /**
     * @brief Attempts to load the local archive for the specified scene
     *
     * @note The "local" archive must always be named `local.carc`.
     *
     * @param scene Scene ID
     * @param pHeap Heap from which to allocate the buffer
     * @return Multi-handle archive containing any patches
     */
    static MultiArchive* LoadGameLocalArchive(s32 scene = -1,
                                              EGG::Heap* pHeap = nullptr);

    /**
     * @brief Loads all resources with static lifetime
     */
    void LoadStaticArchives();

    /**
     * @brief Loads all cached resources
     */
    void LoadCacheArchives();

    /**
     * @brief Loads the Kokeshi archive
     */
    void LoadKokeshiArchive();

private:
    LIBKIWI_KAMEK_PUBLIC

    /**
     * @brief Loads the static lifetime common archive
     */
    void LoadStaticCommonArchive();

    /**
     * @brief Loads the static lifetime local archive
     */
    void LoadStaticLocalArchive();

    /**
     * @brief Loads the message archive
     */
    void LoadMessageArchive();

    /**
     * @brief Loads the font archive
     */
    void LoadFontArchive();

    /**
     * @brief Attempts to load the specified resource file
     *
     * @param pPath Archive path
     * @param pHeap Heap to use for allocations
     * @param cache Whether to cache the resource file
     * @return Resource file
     */
    static const Resource* Load(const char* pPath, EGG::Heap* pHeap = nullptr,
                                bool cache = false);

    /**
     * @brief Attempts to load and decompress the specified resource file
     *
     * @param pPath Archive path
     * @param pHeap Heap to use for allocations
     * @return Resource file
     */
    static const Resource* LoadDecomp(const char* pPath,
                                      EGG::Heap* pHeap = nullptr);

    /**
     * @brief Attempts to decompress the specified resource file
     *
     * @param rResource Resource file
     * @param pHeap Heap to use for allocations
     * @return Decompressed resource
     */
    static const Resource* DecompResource(const Resource& rResource,
                                          EGG::Heap* pHeap = nullptr);

    /**
     * @brief Attempts to decompress the specified file
     *
     * @param rFile File to decompress
     * @param pHeap Heap to use for allocations
     * @return Decompressed file
     */
    static RPSysFile* DecompFile(const RPSysFile& rFile,
                                 EGG::Heap* pHeap = nullptr);

private:
    //! Patch archive file extension
    static const char* PATCH_EXTENSION;

#if !defined(PACK_RESORT)
    //! Scenes with cached archives
    static const kiwi::ESceneID CACHED_SCENES[];
#endif

    //! Raw resource file cache
    static THashMap<String, const Resource*> sResourceCache;
    //! Decompressed resource file cache
    static THashMap<String, const Resource*> sDecompCache;
};

//! @}
} // namespace kiwi

#endif