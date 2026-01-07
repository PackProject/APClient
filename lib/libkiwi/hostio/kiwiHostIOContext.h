#ifndef LIBKIWI_HOSTIO_HOST_IO_CONTEXT_H
#define LIBKIWI_HOSTIO_HOST_IO_CONTEXT_H
#include <libkiwi/core/kiwiMemStream.h>
#include <libkiwi/k_types.h>

namespace kiwi {
//! @addtogroup libkiwi_hostio
//! @{
namespace hostio {
//! @addtogroup libkiwi_hostio
//! @{

// Forward declarations
class IControl;
class Reflexible;

/**
 * @brief Host I/O server message context
 */
class Context {
public:
    /**
     * @brief Constructor
     */
    Context();

    /**
     * @brief Destructor
     */
    virtual ~Context();

    /**
     * @brief Resets the message context
     */
    void Reset();

    /**
     * @brief Starts generation of a node message
     *
     * @param rNode Host I/O node
     */
    void StartGenNode(const Reflexible& rNode);
    /**
     * @brief Ends generation of a node message
     *
     * @param rNode Host I/O node
     */
    void EndGenNode(const Reflexible& rNode);

    /**
     * @brief Generates a control message
     *
     * @param rControl Host I/O control
     */
    void GenControl(IControl& rControl);

    /**
     * @brief Accesses the message data stream
     */
    MemStream& GetMessageStream() {
        return mMessageStream;
    }
    /**
     * @brief Accesses the message data stream (const-view)
     */
    const MemStream& GetMessageStream() const {
        return mMessageStream;
    }

private:
    /**
     * @brief Message command type
     */
    enum ECommand {
        ECommand_StartGenNode, //!< Begin node data
        ECommand_EndGenNode,   //!< End node data

        ECommand_Max
    };

private:
    //! Client message buffer size
    static const u32 MESSAGE_BUFFER_SIZE = K_MEM_KB_TO_B(64);

private:
    //! Message data buffer
    u8* mpMessageBuffer;
    //! Message data stream
    MemStream mMessageStream;
};

//! @}
} // namespace hostio
//! @}
} // namespace kiwi

#endif
