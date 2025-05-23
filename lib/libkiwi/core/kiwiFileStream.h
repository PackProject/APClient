#ifndef LIBKIWI_CORE_FILE_STREAM_H
#define LIBKIWI_CORE_FILE_STREAM_H
#include <libkiwi/core/kiwiStreamBase.h>
#include <libkiwi/k_types.h>

namespace kiwi {
//! @addtogroup libkiwi_core
//! @{

/**
 * @brief File access type
 */
enum EOpenMode {
    EOpenMode_Read,  //!< Read-only
    EOpenMode_Write, //!< Write-only
    EOpenMode_RW     //!< Read + write
};

/**
 * @brief Stream to a physical file
 */
class FileStream : public StreamBase {
public:
    /**
     * @brief Constructor
     *
     * @param mode Open mode
     */
    explicit FileStream(EOpenMode mode) : mOpenMode(mode) {}

    /**
     * @brief Gets the size of the currently open file
     */
    virtual u32 GetSize() const = 0;

    /**
     * @brief Tests whether the stream has hit the end-of-file
     */
    virtual bool IsEOF() const {
        return mPosition >= GetSize();
    }

protected:
    EOpenMode mOpenMode; //!< File access type
};

//! @}
} // namespace kiwi

#endif
