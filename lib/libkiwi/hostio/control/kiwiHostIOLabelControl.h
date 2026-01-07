#ifndef LIBKIWI_HOSTIO_HOST_IO_LABEL_CONTROL_H
#define LIBKIWI_HOSTIO_HOST_IO_LABEL_CONTROL_H
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
 * @brief Label UI control
 */
class LabelControl : public IControl {
public:
    /**
     * @brief Constructor
     *
     * @param rName Name
     * @param id Unique ID
     */
    LabelControl(const String& rName, u32 id)
        : IControl(EType_Label, rName, id) {}
};

//! @}
} // namespace hostio
//! @}
} // namespace kiwi

#endif
