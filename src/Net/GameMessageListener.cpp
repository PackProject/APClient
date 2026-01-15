#include "Net/GameMessageListener.h"

#include "Cmn/CheckMgr.h"
#include "Cmn/ItemMgr.h"
#include "Cmn/SceneHook.h"
#include "Cmn/TextDisplay.h"
#include "Net/Define.h"
#include "Net/NetworkMgr.h"
#include "Net/msg/AuthMsg.h"
#include "Net/msg/ConnectMsg.h"
#include "Net/msg/ItemMsg.h"
#include "Net/msg/PrintMsg.h"
#include "checks.h"

#include <libkiwi.h>

namespace AP {
namespace Net {

/**
 * @brief Callback for receiving a network message
 *
 * @param pMessage Network message
 */
void GameMessageListener::OnReceiveMessage(kiwi::ap::IMessage* pMessage) {
    ASSERT_PTR(pMessage);

    switch (pMessage->GetType()) {
    // PC client is attempting to connect
    case Define::EMsgType_Connect: {
        ConnectMsg* pConnectMsg = static_cast<ConnectMsg*>(pMessage);
        NetworkMgr::GetInstance().SetPeerAddr(pConnectMsg->GetPeerAddr());
        break;
    }

    // PC client has disconnected
    case Define::EMsgType_Disconnect: {
        NetworkMgr::GetInstance().ResetPeerAddr();
        break;
    }

    // PC client is sending authentication details
    case Define::EMsgType_Auth: {
        AuthMsg* pAuthMsg = static_cast<AuthMsg*>(pMessage);
        Net::NetworkMgr::GetInstance().SetPlayerName(pAuthMsg->GetPlayerName());
        break;
    }

    // PC client wants to display a message
    case Define::EMsgType_Print: {
        PrintMsg* pPrintMsg = static_cast<PrintMsg*>(pMessage);

        K_FOREACH (it, pPrintMsg->GetMessageList()) {
            Cmn::SceneHook::GetInstance().GetTextDisplay()->EnqueueText(*it);
        }
        break;
    }

    // PC client wants to award an item
    case Define::EMsgType_Item: {
        ItemMsg* pItemMsg = static_cast<ItemMsg*>(pMessage);
        Cmn::ItemMgr::GetInstance().SetItemState(pItemMsg->GetItemID(), true);
        break;
    }

    // PC client is requesting a list of completed locations/checks
    case Define::EMsgType_Location: {
        break;
    }

    default: {
        ASSERT_EX(false, "Unknown message type: %d", pMessage->GetType());
        break;
    }
    }
}

/**
 * @brief Callback for responding to a network message
 *
 * @param pMessage Network message
 * @param pConnection Network connection
 */
void GameMessageListener::OnRespondMessage(kiwi::ap::IMessage* pMessage,
                                           kiwi::NetConnection* pConnection) {
    ASSERT_PTR(pMessage);
    ASSERT_PTR(pConnection);

    // We must provide the peer address, this is a UDP socket
    const kiwi::SockAddrAny& rPeerAddr =
        NetworkMgr::GetInstance().GetPeerAddr();

    ASSERT(rPeerAddr.IsValid());

    switch (pMessage->GetType()) {
    // PC client is requesting a list of completed locations/checks
    case Define::EMsgType_Location: {
        kiwi::TVector<u16> locations;

#define X(ID, IDENTIFIER, STR)                                                 \
    if (Cmn::CheckMgr::GetInstance().GetCheckState(                            \
            static_cast<CheckID>(ID))) {                                       \
                                                                               \
        locations.PushBack(static_cast<u16>(ID));                              \
    }

        AP_CHECKS_X_MACRO;

#undef X

        // Can't send an empty packet, so we send a sentinel value
        if (locations.Empty()) {
            locations.PushBack(CHECK_INVALID);
        }

        pConnection->Send(locations.Data(), locations.Size() * sizeof(u16),
                          &rPeerAddr);
        break;
    }

    // Other messages require only a simple acknowledgement
    default: {
        pConnection->Send(Net::Define::ACK, &rPeerAddr);
        break;
    }
    }
}

} // namespace Net
} // namespace AP