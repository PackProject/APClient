// TODO(kiwi) Needs changes for WSR
#if !defined(PACK_RESORT)

#ifndef LIBKIWI_RESOURCE_MULTI_ARCHIVE_H
#define LIBKIWI_RESOURCE_MULTI_ARCHIVE_H
#include <Pack/RPKernel.h>
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiList.h>
#include <libkiwi/resource/kiwiResource.h>

#include <egg/core.h>

namespace kiwi {
//! @addtogroup libkiwi_resource
//! @{

/**
 * @brief Multi-handle archive
 */
class MultiArchive : public EGG::Archive {
public:
    /**
     * @brief Archive file info
     */
    struct FileInfo {
        u32 offset; //! File offset into the archive
        u32 length; //! File size, in bytes

        /**
         * @brief Constructor
         */
        FileInfo() : offset(0), length(0) {}
    };

public:
    /**
     * @brief Attempts to mount a resource file
     *
     * @param rResource Resource file
     * @param pHeap Heap to use for archive allocation (defaults to current
     * heap)
     * @param align Alignment to use for archive allocation
     */
    static MultiArchive* Mount(const Resource& rResource,
                               EGG::Heap* pHeap = nullptr, s32 align = 4);

    /**
     * @brief Destructor
     */
    virtual ~MultiArchive();

    /**
     * @brief Attempts to get a file from one of the open archives
     * @details The patch archives take precedence over the base archive.
     * @note The hierarchy of patch archives is the order they were mounted.
     *
     * @param pPath File path
     * @param[out] pInfo File info
     * @return File data
     */
    void* GetFile(const char* pPath, FileInfo* pInfo = nullptr);

private:
    /**
     * @brief Constructor
     *
     * @param rResource Mounted resource file
     */
    MultiArchive(const Resource& rResource) : mrResource(rResource) {
        K_ASSERT_PTR(rResource.GetBaseFile().GetData());
    }

    /**
     * @brief Attempts to find the archive mounting the specified resource file
     *
     * @param rResource Resource file
     * @return Cached archive (if it exists)
     */
    static MultiArchive* FindArchive(const Resource& rResource);

private:
    //! Currently mounted resource file (non-owning view)
    const Resource& mrResource;

    //! Patched/delta resource archives
    TList<EGG::Archive*> mPatchArchives;
};

//! @}
} // namespace kiwi

#endif

#endif