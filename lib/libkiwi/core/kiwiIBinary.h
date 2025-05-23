#ifndef LIBKIWI_CORE_I_BINARY_H
#define LIBKIWI_CORE_I_BINARY_H
#include <libkiwi/debug/kiwiAssert.h>
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiString.h>

//! Helper for creating version numbers
#define K_BIN_VERSION(major, minor) (((major & 0xFF) << 8) | minor & 0xFF)

namespace kiwi {
//! @addtogroup libkiwi_core
//! @{

/**
 * @brief Interface for binary file serialization/deserialization
 * @details The binary file structure in the derived class must be named
 * 'BinData'.
 *
 * @tparam T Derived type (CRTP)
 */
template <typename T> class IBinary {
public:
#pragma pack(push, 1)
    /**
     * @brief Generic binary file block/section
     */
    struct Block {
        /**
         * @brief Interprets kind as a string
         */
        String Kind() const {
            return String(reinterpret_cast<const char*>(kind), sizeof(u32));
        }

        /* 0x00 */ u32 kind; //!< Block magic/signature
        /* 0x04 */ u32 size; //!< Block size (header + content)
    };

    /**
     * @brief Generic file header block
     */
    struct Header {
        /* 0x00 */ Block block;   //!< Block information
        /* 0x08 */ u16 version;   //!< Format version
        /* 0x0A */ u16 numBlocks; //!< Number of child blocks
    };

    /**
     * @brief Binary file structure
     */
    struct Bin {
        /* 0x00 */ Header header;            //!< File header
        /* 0x0C */ typename T::BinData data; //!< File data
    };
#pragma pack(pop)

public:
    /**
     * @brief Destructor
     */
    virtual ~IBinary() {}

    /**
     * @brief Gets the kind/magic of this object
     */
    virtual u32 GetBinaryKind() const = 0;
    /**
     * @brief Gets the serialized size of this object
     */
    virtual u32 GetBinarySize() const {
        return sizeof(Bin);
    }
    /**
     * @brief Gets the expected version of this object
     */
    virtual u16 GetVersion() const = 0;

    /**
     * @brief Deserializes binary contents after performing debug checks
     *
     * @param pBin Binary contents
     */
    void Deserialize(const void* pBin) {
        K_ASSERT_PTR(pBin);
        const Bin& rBin = *static_cast<const Bin*>(pBin);

        K_ASSERT_EX(GetBinaryKind() == rBin.header.block.kind,
                    "Not for this class. Got %08X (%s)", rBin.header.block.kind,
                    rBin.header.block.Kind());

        K_ASSERT_EX(GetVersion() == rBin.header.version,
                    "Not for this version. Got %02X (%d.%d)",
                    rBin.header.version, rBin.header.version >> 8 & 0xFF,
                    rBin.header.version >> 0 & 0xFF);

        DeserializeImpl(rBin);
    }

    /**
     * @brief Serializes binary contents
     *
     * @param pBin Binary contents
     */
    void Serialize(void* pBin) const {
        K_ASSERT_PTR(pBin);
        Bin& rBin = *static_cast<Bin*>(pBin);

        rBin.header.version = GetVersion();
        rBin.header.block.kind = GetBinaryKind();

        SerializeImpl(rBin);
    }

private:
    /**
     * @brief Deserializes binary contents (internal implementation)
     *
     * @param rBin Binary file contents
     */
    virtual void DeserializeImpl(const Bin& rBin) = 0;
    /**
     * @brief Serializes binary contents (internal implementation)
     *
     * @param rBin Binary file contents
     */
    virtual void SerializeImpl(Bin& rBin) const = 0;
};

//! @}
} // namespace kiwi

#endif
