#include <libkiwi.h>

namespace kiwi {
namespace hostio {

/**
 * @brief Generates object info for host client
 *
 * @param rContext Message context
 */
void IControl::GenMessage(Context& rContext) {
    MemStream& rStrm = rContext.GetMessageStream();

    rStrm.Write_u8(GetType());
    rStrm.Write_string(GetName());
    rStrm.Write_u32(GetID());

    // Generate derived control message
    GenMessageImpl(rContext);
}

} // namespace hostio
} // namespace kiwi