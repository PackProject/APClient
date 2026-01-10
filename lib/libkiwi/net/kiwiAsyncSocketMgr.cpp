#include <libkiwi.h>

namespace kiwi {
namespace detail {

/**
 * @brief Constructor
 */
AsyncSocketMgr::AsyncSocketMgr() {
    mpThread = new Thread(&AsyncSocketMgr::ThreadFunc, *this);
}

/**
 * @brief Destructor
 */
AsyncSocketMgr::~AsyncSocketMgr() {
    delete mpThread;
    mpThread = nullptr;
}

/**
 * @brief Thread function
 */
void AsyncSocketMgr::ThreadFunc() {
    while (true) {
        K_FOREACH (it, mSocketList) {
            K_ASSERT((*it)->IsOpen());
            (*it)->Calc();
        }
    }
}

} // namespace detail
} // namespace kiwi