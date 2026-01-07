#include <libkiwi.h>

namespace kiwi {
namespace hostio {

/**
 * @brief Generates object info for host client
 *
 * @param rContext Message context
 */
void Reflexible::GenMessage(Context& rContext) {
    MemStream& rStrm = rContext.GetMessageStream();

    rContext.StartGenNode(*this);
    {
        rStrm.Write_string(mName);
        GenMessageImpl(rContext);
    }
    rContext.EndGenNode(*this);
}

/**
 * @brief Event callback
 *
 * @param pEvent Event structure from the host
 */
void Reflexible::OnEvent(const Event* pEvent) {
    K_ASSERT_PTR(pEvent);

    switch (pEvent->type) {
    case Event::EType_GenObjectInfo: {
        GenMessage(Server::GetInstance().GetMessageContext());
        break;
    }

    case Event::EType_Property: {
        if (pEvent->size != sizeof(PropertyEvent)) {
            K_LOG_EX("Wrong PropertyEvent size (%d)\n", pEvent->size);
            return;
        }

        const PropertyEvent* pPropertyEvent =
            static_cast<const PropertyEvent*>(pEvent);

        ListenPropertyEvent(*pPropertyEvent);

        // Property event may change at most one control ID
        K_FOREACH (it, mControls) {
            if ((*it)->GetID() == pPropertyEvent->id) {
                (*it)->ListenPropertyEvent(*pPropertyEvent);
            }
        }

        // Target node could be further down the tree
        K_FOREACH (it, mChildren) {
            (*it)->ListenPropertyEvent(*pPropertyEvent);
        }
        break;
    }
    }
}

} // namespace hostio
} // namespace kiwi