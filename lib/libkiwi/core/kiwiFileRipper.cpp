#include <libkiwi.h>

namespace kiwi {

/**
 * @brief Rips a file's contents
 *
 * @param rPath Path to the file
 * @param where Storage device on which the file is located
 * @param rArg Ripping parameters
 * @return File data (owned by you!)
 */
void* FileRipper::Rip(const String& rPath, EStorage where,
                      const FileRipperArg& rArg) {

    switch (where) {
    case EStorage_DVD: {
        DvdStream strm(rPath);
        return Rip(strm, rArg);
    }

    case EStorage_NAND: {
        NandStream strm(rPath, EOpenMode_Read);
        return Rip(strm, rArg);
    }

    default:
        K_UNREACHABLE();
        return nullptr;
    }
}

/**
 * @brief Rips a file's contents
 *
 * @param rStrm Stream to the file
 * @param rArg Ripping parameters
 * @return File data (owned by you!)
 */
void* FileRipper::Rip(FileStream& rStrm, const FileRipperArg& rArg) {
    if (!rStrm.IsOpen()) {
        return nullptr;
    }

    // Storage device may require byte-aligned size
    u32 fileSize = rStrm.GetSize();
    u32 bufferSize = RoundUp(fileSize, rStrm.GetSizeAlign());

    // User may have specified a destination buffer...
    u8* pBuffer = static_cast<u8*>(rArg.pDst);

    // ...or ripper may be responsible for allocating one
    if (pBuffer == nullptr) {
        pBuffer = new (rStrm.GetBufferAlign(), rArg.region) u8[bufferSize];
    }

    K_ASSERT_PTR(pBuffer);

    K_ASSERT_EX(rStrm.IsBufferAlign(pBuffer),
                "Stream requires buffer aligned to %d bytes",
                rStrm.GetBufferAlign());

    // Need to read the entire file at once
    s32 result = rStrm.Read(pBuffer, bufferSize);
    K_ASSERT_EX(result > 0, "Read failed (%d)", result);

    K_ASSERT(result == bufferSize);

    if (rArg.pSize != nullptr) {
        *rArg.pSize = fileSize;
    }

    return pBuffer;
}

/**
 * @brief Rips a file's contents and opens a stream to it
 *
 * @param rPath Path to the file
 * @param where Storage device on which the file is located
 * @return File stream (owns buffer)
 */
MemStream FileRipper::Open(const String& rPath, EStorage where) {
    // Memory stream needs to know the file size
    FileRipperArg arg;
    u32 size = 0;
    arg.pSize = &size;

    void* pFile = Rip(rPath, where, arg);
    if (pFile == nullptr) {
        return MemStream();
    }

    // Force read-only for files from the DVD
    if (where == EStorage_DVD) {
        return MemStream(static_cast<const void*>(pFile), size, true);
    } else {
        return MemStream(pFile, size, true);
    }
}

} // namespace kiwi
