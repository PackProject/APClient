// TODO(kiwi) Needs changes for WSR
#if !defined(PACK_RESORT)

// Implementation must be visible to the extension
#define private protected
#include <egg/core/eggArchive.h>
#undef private

#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>

#include <libkiwi.h>

#include <nw4r/ut.h>

#include <revolution/ARC.h>

namespace kiwi {

/**
 * @brief Destructor
 */
MultiArchive::~MultiArchive() {
    K_FOREACH (it, mPatchArchives) {
        delete *it;
    }
}

/**
 * @brief Attempts to mount a resource file
 *
 * @param rResource Resource file
 * @param pHeap Heap to use for archive allocation (defaults to current
 * heap)
 * @param align Alignment to use for archive allocation
 */
MultiArchive* MultiArchive::Mount(const Resource& rResource, EGG::Heap* pHeap,
                                  s32 align) {

    if (pHeap == nullptr) {
        pHeap = EGG::Heap::getCurrentHeap();
    }

    K_ASSERT_PTR(pHeap);

    MultiArchive* pArchive = FindArchive(rResource);
    if (pArchive != nullptr) {
        pArchive->mRefCount++;
        return pArchive;
    }

    pArchive = new (align, pHeap) MultiArchive(rResource);
    K_ASSERT_PTR(pArchive);

    const void* pBaseData = rResource.GetBaseFile().GetData();
    K_ASSERT_PTR(pBaseData);

    bool success = ARCInitHandle(pBaseData, &pArchive->mHandle);
    K_ASSERT(success);

    pArchive->mMountType = success ? MOUNT_TYPE_MEM : MOUNT_TYPE_NONE;

    K_FOREACH (it, rResource.GetPatchFiles()) {
        K_ASSERT_PTR(*it);

        void* pPatchData = const_cast<void*>((*it)->GetData());

        EGG::Archive* pPatchArchive =
            EGG::Archive::mount(pPatchData, pHeap, align);

        K_ASSERT_PTR(pPatchArchive);
        pArchive->mPatchArchives.PushBack(pPatchArchive);
    }

    return pArchive;
}

/**
 * @brief Attempts to get a file from one of the open archives
 * @details The patch archives take precedence over the base archive.
 * @note The hierarchy of patch archives is the order they were mounted.
 *
 * @param pPath File path
 * @param[out] pInfo File info
 * @return File data
 */
void* MultiArchive::GetFile(const char* pPath, FileInfo* pInfo) {
    K_ASSERT_PTR(pPath);
    K_ASSERT_EX(mMountType != MOUNT_TYPE_NONE,
                "Please mount a base archive first");

    void* pFileData = nullptr;
    EGG::Archive::FileInfo eggInfo;

    // Patch archives take precedence over the base archive
    K_FOREACH (it, mPatchArchives) {
        K_ASSERT_PTR(*it);

        if ((pFileData = (*it)->getFile(pPath, &eggInfo))) {
            if (pInfo != nullptr) {
                pInfo->offset = eggInfo.getStartOffset();
                pInfo->length = eggInfo.getLength();
            }

            return pFileData;
        }
    }

    if ((pFileData = EGG::Archive::getFile(pPath, &eggInfo))) {
        if (pInfo != nullptr) {
            pInfo->offset = eggInfo.getStartOffset();
            pInfo->length = eggInfo.getLength();
        }

        return pFileData;
    }

    return nullptr;
}

/**
 * @brief Attempts to find the archive mounting the specified resource file
 *
 * @param rResource Resource file
 * @return Cached archive (if it exists)
 */
MultiArchive* MultiArchive::FindArchive(const Resource& rResource) {
    if (!sIsArchiveListInitialized) {
        return nullptr;
    }

    // Mounted archive will have a handle to the base data
    const void* pBaseData = rResource.GetBaseFile().GetData();

    NW4R_UT_LIST_FOREACH(Archive, it, sArchiveList, {
        K_ASSERT_PTR(it);
        MultiArchive* pArchive = static_cast<MultiArchive*>(it);
        
        if (pArchive->mHandle.archiveStartAddr == pBaseData) {
            return pArchive;
        }
    });

    return nullptr;
}

} // namespace kiwi

#endif