#ifndef LIBKIWI_HOSTIO_HOST_IO_EVENT_H
#define LIBKIWI_HOSTIO_HOST_IO_EVENT_H
#include <libkiwi/k_types.h>

namespace kiwi {
//! @addtogroup libkiwi_hostio
//! @{
namespace hostio {
//! @addtogroup libkiwi_hostio
//! @{

/**
 * @brief Event from client PC to server
 */
struct Event {
    /**
     * @brief Event type
     */
    enum EType {
        EType_GenObjectInfo, //!< Host client is requesting the node layout
        EType_Property,      //!< Host client has changed a property

        EType_Max,
    };

    u8 type;        //! Event type
    u8 reserved[3]; //! Reserved space
    u32 size;       //! Event size
};

/**
 * @brief Property change event
 */
struct PropertyEvent : Event {
    //! Control ID designated for this event
    u32 id;

    //! New property value
    union {
        u32 value;
    };
};

//! @}
} // namespace hostio
//! @}
} // namespace kiwi

#endif
