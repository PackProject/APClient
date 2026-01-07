#ifndef LIBKIWI_CORE_FILE_RIPPER_H
#define LIBKIWI_CORE_FILE_RIPPER_H
#include <libkiwi/core/kiwiMemoryMgr.h>
#include <libkiwi/k_types.h>

#include <egg/core.h>

namespace kiwi {
//! @addtogroup libkiwi_core
//! @{

// Forward declarations
class FileStream;
class MemStream;

/**
 * @brief File storage devices
 */
enum EStorage {
    EStorage_DVD,  //!< Game disc (ROM)
    EStorage_NAND, //!< System flash memory
};

/**
 * @brief File ripper parameters
 */
struct FileRipperArg {
    /**
     * @brief Where the file contents are stored
     * @details Leave this as NULL (default) to have the ripper allocate memory.
     */
    void* pDst;

    /**
     * @brief Where the file size is stored
     * @details Leave this as NULL (default) if you don't need this information.
     */
    u32* pSize;

    /**
     * @brief Heap to use for ripper memory allocation
     * @note Overrides `region` setting.
     */
    EGG::Heap* pHeap;

    /**
     * @brief Memory region to use for ripper memory allocation
     * @details Defaults to MEM2.
     * @note Ignored when heap is specified with `pHeap`.
     */
    EMemory region;

    /**
     * @brief Byte alignment to use for ripper memory allocation
     * @details Defaults to 4.
     */
    s32 align;

    /**
     * @brief Constructor
     */
    FileRipperArg()
        : pDst(nullptr),
          pSize(nullptr),
          pHeap(nullptr),
          region(EMemory_MEM2),
          align(4) {}
};

/**
 * @brief File ripper/loader
 */
class FileRipper {
public:
    /**
     * @brief Rips a file's contents
     *
     * @param rPath Path to the file
     * @param where Storage device on which the file is located
     * @param rArg Ripping parameters
     * @return File data (owned by you!)
     */
    static void* Rip(const String& rPath, EStorage where,
                     const FileRipperArg& rArg = FileRipperArg());

    /**
     * @brief Rips a file's contents
     *
     * @param rStrm Stream to the file
     * @param rArg Ripping parameters
     * @return File data (owned by you!)
     */
    static void* Rip(FileStream& rStrm,
                     const FileRipperArg& rArg = FileRipperArg());

    /**
     * @brief Rips a file's contents and opens a stream to it
     *
     * @param rPath Path to the file
     * @param where Storage device on which the file is located
     * @return File stream (owns buffer)
     */
    static MemStream Open(const String& rPath, EStorage where = EStorage_DVD);
};

//! @}
} // namespace kiwi

#endif
