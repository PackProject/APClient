#ifndef LIBKIWI_NET_VARIABLE_PACKET_H
#define LIBKIWI_NET_VARIABLE_PACKET_H
#include <libkiwi/k_types.h>
#include <libkiwi/net/packet/kiwiPacketBase.h>
#include <libkiwi/util/kiwiStateMachine.h>

#include <revolution/SO.h>

namespace kiwi {
//! @addtogroup libkiwi_net
//! @{

/**
 * @brief Network packet of a variable size
 */
class VariablePacket : public PacketBase {
public:
    /**
     * @brief Constructor
     *
     * @param pPeerAddr Peer socket address
     */
    explicit VariablePacket(const SockAddrAny* pPeerAddr = nullptr);

    /**
     * @brief Gets the size of the overhead needed for the packet header
     */
    virtual u32 GetOverhead() const {
        return 0;
    }

    /**
     * @brief Gets the current capacity of the packet buffer
     */
    virtual u32 GetSize() const {
        return mBuffer.Size();
    }

    /**
     * @brief Sets the packet content
     *
     * @param pContent Packet content
     * @param size Content size
     */
    virtual void SetContent(const void* pContent, u32 size);

    /**
     * @brief Receives the packet over the specified socket
     *
     * @param pSocket Network socket
     */
    virtual void Recv(SocketBase* pSocket);

    /**
     * @brief Sends the packet over the specified socket
     *
     * @param pSocket Network socket
     */
    virtual void Send(SocketBase* pSocket);

    /**
     * @brief Updates the packet state
     *
     * @return Whether the previous operation has just completed
     */
    virtual bool Calc();

    /**
     * @brief Updates the packet in the Idle state
     */
    K_STATE_DECL(Idle);

    /**
     * @brief Updates the packet in the Recv state
     */
    K_STATE_DECL(Recv);

    /**
     * @brief Updates the packet in the Send state
     */
    K_STATE_DECL(Send);

private:
    /**
     * @brief State machine state
     */
    enum EState {
        EState_Idle, //!< Waiting for request
        EState_Recv, //!< Trying to receive packet
        EState_Send, //!< Trying to send packet

        EState_Max
    };

private:
    /**
     * @brief Buffer transfer callback
     *
     * @param result Socket library result
     * @param size Transfer size
     * @param pArg Callback user argument
     */
    static void BufferCallback(SOResult result, u32 size, void* pArg);

private:
    //! Network socket
    SocketBase* mpSocket;
    //! Logic state machine
    StateMachine<VariablePacket> mStateMachine;
};

//! @}
} // namespace kiwi

#endif
