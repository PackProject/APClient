#ifndef LIBKIWI_HOSTIO_HOST_IO_BUTTON_CONTROL_H
#define LIBKIWI_HOSTIO_HOST_IO_BUTTON_CONTROL_H
#include <libkiwi/hostio/kiwiHostIOIControl.h>
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiString.h>

namespace kiwi {
//! @addtogroup libkiwi_hostio
//! @{
namespace hostio {
//! @addtogroup libkiwi_hostio
//! @{

/**
 * @brief Button UI control
 */
class ButtonControl : public IControl {
public:
    /**
     * @brief Button click callback function
     *
     * @param pInvoker Button that invoked this callback
     * @param pArg User argument
     */
    typedef void (*Callback)(ButtonControl* pInvoker, void* pArg);

public:
    /**
     * @brief Constructor
     *
     * @param rName Name
     * @param id Unique ID
     * @param pCallback Callback function
     * @param pCallbackArg Callback function user argument (optional)
     */
    ButtonControl(const String& rName, u32 id, Callback pCallback,
                  void* pCallbackArg = nullptr);

    /**
     * @brief Destructor
     */
    virtual ~ButtonControl() {}

    /**
     * @brief Handles property event from host client
     *
     * @param rEvent Event structure from the host
     */
    virtual void ListenPropertyEvent(const PropertyEvent& rEvent);

private:
    //! Callback function
    Callback mpCallback;
    //! Callback function user argument
    void* mpCallbackArg;
};

//! @}
} // namespace hostio
//! @}
} // namespace kiwi

#endif
