#include <libkiwi.h>

namespace kiwi {

/**
 * @brief Opens stream to DVD file
 *
 * @param rPath File path
 * @return Success
 */
bool DvdStream::Open(const String& rPath) {
    if (IsOpen()) {
        Close();
    }

    // Need to get the file entry number from the FST
    s32 entryNum = DVDConvertPathToEntrynum(rPath);
    if (entryNum < 0) {
        return false;
    }

    bool success = DVDFastOpen(entryNum, &mFileInfo);
    K_ASSERT(success);

    if (!success) {
        return false;
    }

    mIsOpen = true;
    return true;
}

/**
 * @brief Closes the stream
 */
void DvdStream::Close() {
    if (!IsOpen()) {
        return;
    }

    DVDClose(&mFileInfo);
    mIsOpen = false;
}

/**
 * @brief Gets the size of the currently open file
 */
u32 DvdStream::GetSize() const {
    return mFileInfo.size;
}

/**
 * @brief Advances this stream's position (internal implementation)
 *
 * @param dir Seek direction
 * @param offset Seek offset
 */
void DvdStream::SeekImpl(ESeekDir dir, s32 offset) {
    switch (dir) {
    case ESeekDir_Begin: {
        K_ASSERT_EX(offset >= 0, "Can't seek backwards from the beginning");
        mPosition = offset;
        break;
    }

    case ESeekDir_Current: {
        mPosition += offset;
        break;
    }

    case ESeekDir_End: {
        K_ASSERT_EX(offset < 0, "Can't seek forward from the end");
        K_ASSERT_EX(offset > -GetSize(), "Seeking too far backwards");
        mPosition = GetSize() + offset;
        break;
    }

    default: {
        K_UNREACHABLE();
        return;
    }
    }

    K_ASSERT_EX(mPosition < GetSize(), "Can't seek past end of file");
}

/**
 * @brief Reads data from this stream (internal implementation)
 *
 * @param pDst Destination buffer
 * @param size Number of bytes to read
 * @return Number of bytes read, or DVD error code
 */
s32 DvdStream::ReadImpl(void* pDst, u32 size) {
    K_ASSERT_PTR(pDst);
    return DVDReadPrio(&mFileInfo, pDst, size, mPosition, DVD_PRIO_MEDIUM);
}

/**
 * @brief Writes data to this stream (internal implementation)
 *
 * @param pSrc Source buffer
 * @param size Number of bytes to write
 * @return Number of bytes written, or DVD error code
 */
s32 DvdStream::WriteImpl(const void* pSrc, u32 size) {
    K_ASSERT_PTR(pSrc);
    K_ASSERT_EX(false, "DVD is immutable");
    return DVD_RESULT_FATAL_ERROR;
}

/**
 * @brief Reads data from this stream without advancing the stream's
 * position (internal implementation)
 *
 * @param pDst Destination buffer
 * @param size Number of bytes to read
 * @return Number of bytes read, or DVD error code
 */
s32 DvdStream::PeekImpl(void* pDst, u32 size) {
    K_ASSERT_PTR(pDst);
    return ReadImpl(pDst, size);
}

} // namespace kiwi
