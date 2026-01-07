#include <libkiwi.h>

namespace kiwi {
namespace hostio {

/**
 * @brief Handles property event from host client
 *
 * @param rEvent Event structure from the host
 */
void ButtonControl::ListenPropertyEvent(const PropertyEvent& rEvent) {
    if (mpCallback != nullptr) {
        mpCallback(this, mpCallbackArg);
    }
}

} // namespace hostio
} // namespace kiwi