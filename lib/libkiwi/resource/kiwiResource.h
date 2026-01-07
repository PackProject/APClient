#ifndef LIBKIWI_RESOURCE_RESOURCE_H
#define LIBKIWI_RESOURCE_RESOURCE_H
#include <Pack/RPKernel.h>
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiList.h>

#include <egg/core.h>

#include <revolution/FS.h>

namespace kiwi {
//! @addtogroup libkiwi_resource
//! @{

/**
 * @brief In-memory resource file
 */
class Resource : public EGG::Disposer {
public:
    /**
     * @brief Constructor
     *
     * @param pPath Archive file path
     * @param size Archive file size
     * @param pData Archive file data
     */
    Resource(const char* pPath, u32 size, const void* pData);
    /**
     * @brief Destructor
     */
    virtual ~Resource();

    /**
     * @brief Registers a new patch file
     *
     * @param rPatchFile New patch file
     */
    void RegistPatch(RPSysFile& rPatchFile) {
        K_ASSERT_PTR(rPatchFile.GetData());
        mPatchFiles.PushBack(&rPatchFile);
    }

    /**
     * @brief Gets the base file for this resource
     */
    const RPSysFile& GetBaseFile() const {
        return mBaseFile;
    }

    /**
     * @brief Gets the list of patch files for this resource
     */
    const TList<RPSysFile*>& GetPatchFiles() const {
        return mPatchFiles;
    }

private:
    //! Maximum file path length
    static const int PATH_MAX = FS_MAX_PATH;

private:
    //! Base archive file
    RPSysFile mBaseFile;

    //! Patch archive files
    TList<RPSysFile*> mPatchFiles;
};

//! @}
} // namespace kiwi

#endif