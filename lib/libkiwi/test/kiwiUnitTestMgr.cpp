#include <libkiwi.h>

namespace kiwi {

/**
 * @brief Runs all registered unit tests
 */
bool UnitTestMgr::Run() {
    int testNum = mUnitTests.Size();
    int passNum = 0;

    K_LOG("[UnitTestMgr]\n");
    K_LOG_EX("Running %d test cases\n", testNum);

    K_FOREACH (it, mUnitTests) {
        K_ASSERT_PTR(*it);

        // Show fully-qualified test name
        K_LOG_EX(">>>>> %s.%s\n", (*it)->GetSuiteName().CStr(),
                 (*it)->GetTestName().CStr());

        (*it)->Run();
        passNum += !(*it)->IsFailed() ? 1 : 0;

        // Show failure information
        if ((*it)->IsFailed()) {
            K_LOG_EX("  FAILED: %s\n", (*it)->GetFailedExpr().CStr());
        }
    }

    K_LOG("Complete!\n");
    K_LOG_EX("Passed: %d, Total: %d\n", passNum, testNum);

    return passNum == testNum;
}

} // namespace kiwi