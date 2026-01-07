#ifndef LIBKIWI_HOSTIO_HOST_IO_REFLEXIBLE_H
#define LIBKIWI_HOSTIO_HOST_IO_REFLEXIBLE_H
#include <libkiwi/core/kiwiMemStream.h>
#include <libkiwi/hostio/kiwiHostIOContext.h>
#include <libkiwi/hostio/kiwiHostIOEvent.h>
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiList.h>

namespace kiwi {
//! @addtogroup libkiwi_hostio
//! @{
namespace hostio {
//! @addtogroup libkiwi_hostio
//! @{

// Forward declarations
class IControl;

/**
 * @brief Host I/O node
 */
class Reflexible {
    friend class Server;

public:
    /**
     * @brief Constructor
     *
     * @param rName Node name
     */
    explicit Reflexible(const String& rName) : mName(rName) {}

    /**
     * @brief Destructor
     */
    virtual ~Reflexible() {}

    /**
     * @brief Generates object info for host client
     *
     * @param rContext Message context
     */
    void GenMessage(Context& rContext);

    /**
     * @brief Handles property event from host client
     * @note Property events automatically propogate to children
     *
     * @param rEvent Event structure from the host
     */
    virtual void ListenPropertyEvent(const PropertyEvent& rEvent) {}

    /**
     * @brief Adds a new UI control to this node
     *
     * @param pControl UI control
     */
    void AddControl(IControl* pControl) {
        K_ASSERT_PTR(pControl);
        mControls.PushBack(pControl);
    }

    /**
     * @brief Adds a new child to this node
     *
     * @param pNode Child node
     */
    void AddChild(Reflexible* pNode) {
        K_ASSERT_PTR(pNode);
        mChildren.PushBack(pNode);
    }

    /**
     * @brief Accesses this node's name
     */
    const String& GetName() const {
        return mName;
    }

private:
    /**
     * @brief Generates object info for host client (derived implementation)
     *
     * @param rContext Message context
     */
    virtual void GenMessageImpl(Context& rContext) {}

    /**
     * @brief Event callback
     *
     * @param pEvent Event structure from the host
     */
    virtual void OnEvent(const Event* pEvent);

protected:
    //! Node name
    String mName;

    //! UI controls
    TList<IControl*> mControls;
    //! Children nodes
    TList<Reflexible*> mChildren;
};

//! @}
} // namespace hostio
//! @}
} // namespace kiwi

#endif
