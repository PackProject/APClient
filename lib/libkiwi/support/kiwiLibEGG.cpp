#include <libkiwi.h>

#include <egg/core.h>

namespace EGG {

/******************************************************************************
 *
 * Archive
 *
 ******************************************************************************/
Archive::Archive() {
    mRefCount = 1;
    mMountType = MOUNT_TYPE_NONE;
    std::memset(&mHandle, 0, sizeof(ARCHandle));
    appendList(this);
}

void Archive::appendList(Archive* pArchive) {
    if (!sIsArchiveListInitialized) {
        NW4R_UT_LIST_INIT(sArchiveList, Archive);
        sIsArchiveListInitialized = true;
    }

    nw4r::ut::List_Append(&sArchiveList, pArchive);
}

} // namespace EGG
