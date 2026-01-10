#include <libkiwi.h>

namespace kiwi {
namespace detail {

/**
 * @brief Constructor
 */
NetConnectionMgr::NetConnectionMgr() {
    mpThread = new Thread(&NetConnectionMgr::ThreadFunc, *this);
}

/**
 * @brief Destructor
 */
NetConnectionMgr::~NetConnectionMgr() {
    delete mpThread;
    mpThread = nullptr;
}

/**
 * @brief Thread function
 */
void NetConnectionMgr::ThreadFunc() {
    while (true) {
        K_FOREACH (it, mConnectionList) {
            (*it)->Calc();
        }
    }
}

} // namespace detail
} // namespace kiwi