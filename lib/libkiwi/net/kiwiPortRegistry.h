#ifndef LIBKIWI_NET_PORT_REGISTRY_H
#define LIBKIWI_NET_PORT_REGISTRY_H
#include <libkiwi/k_types.h>

namespace kiwi {
//! @addtogroup libkiwi_net
//! @{
namespace port {
//! @addtogroup libkiwi_net
//! @{

//! Port reserved for host I/O communications
static const u32 HOST_IO = 50000;

//! Port reserved for Archipelago communications
static const u32 AP_COMM = 51234;

//! @}
} // namespace port
//! @}
} // namespace kiwi

#endif
