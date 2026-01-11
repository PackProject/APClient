#ifndef APCLIENT_CMN_SYSTEM_H
#define APCLIENT_CMN_SYSTEM_H
#include <types.h>

namespace AP {
namespace Cmn {

/**
 * @brief App initialization
 */
class System {
public:
    /**
     * @brief Performs initialization for required objects
     */
    static void Initialize();
};

} // namespace Cmn
} // namespace AP

#endif