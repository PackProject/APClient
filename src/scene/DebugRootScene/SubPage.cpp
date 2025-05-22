#include "scene/DebugRootScene/SubPage.h"

#include <libkiwi.h>

namespace AP {
namespace DebugRoot {

/**
 * @brief Constructor
 */
SubPage::SubPage()
    : mDummyProcOption("Nothing here - press B to close page", DummyProc) {

    AddOption(mDummyProcOption);
}

/**
 * @brief Placeholder procedure
 */
kiwi::EDebugMenuResult SubPage::DummyProc(void* pArg) {
    return kiwi::EDebugMenuResult_Invalid;
}

} // namespace DebugRoot
} // namespace AP
