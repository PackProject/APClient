#ifndef APCLIENT_SCENE_DEBUGROOTSCENE_MAIN_PAGE_H
#define APCLIENT_SCENE_DEBUGROOTSCENE_MAIN_PAGE_H
#include "core/const.h"

#include <libkiwi.h>

namespace AP {
namespace DebugRoot {

/**
 * @brief Main debug menu page
 */
class MainPage : public kiwi::DebugPage {
public:
    MainPage() : mDummyIntOption("test0", 0, 1), mDummyBoolOption("test1") {}

private:
    kiwi::DebugIntOption mDummyIntOption;
    kiwi::DebugBoolOption mDummyBoolOption;
};

} // namespace DebugRoot
} // namespace AP

#endif
