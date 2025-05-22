#ifndef APCLIENT_SCENE_DEBUGROOTSCENE_SUB_PAGE_H
#define APCLIENT_SCENE_DEBUGROOTSCENE_SUB_PAGE_H
#include "core/const.h"

#include <libkiwi.h>

namespace AP {
namespace DebugRoot {

/**
 * @brief Debug menu example sub-page
 */
class SubPage : public kiwi::DebugPage {
public:
    /**
     * @brief Constructor
     */
    SubPage();

    /**
     * @brief Destructor
     */
    virtual ~SubPage() {}

    /**
     * @brief Placeholder procedure
     */
    static kiwi::EDebugMenuResult DummyProc(void* pArg);

private:
    //! Example procedure option (doesn't actually do anything)
    kiwi::DebugProcOption mDummyProcOption;
};

} // namespace DebugRoot
} // namespace AP

#endif
