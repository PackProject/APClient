#ifndef LIBKIWI_TEST_UNIT_TEST_MGR_H
#define LIBKIWI_TEST_UNIT_TEST_MGR_H
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiList.h>
#include <libkiwi/prim/kiwiString.h>
#include <libkiwi/test/kiwiIUnitTest.h>
#include <libkiwi/util/kiwiStaticSingleton.h>

namespace kiwi {
//! @addtogroup libkiwi_test
//! @{

// Forward declarations
namespace detail {
template <typename T> class UnitTestDecl;
} // namespace detail

/**
 * @brief Unit test manager
 */
class UnitTestMgr : public StaticSingleton<UnitTestMgr> {
    friend class StaticSingleton<UnitTestMgr>;

    //! Only UnitTestDecl is allowed to register unit tests
    template <typename> friend class detail::UnitTestDecl;

public:
    /**
     * @brief Runs all registered unit tests
     *
     * @returns Whether every test passed
     */
    bool Run();

private:
    /**
     * @brief Registers a new unit test
     *
     * @param pTest Unit test
     */
    void RegistTest(detail::IUnitTest* pTest) {
        K_ASSERT_PTR(pTest);
        mUnitTests.PushBack(pTest);
    }

private:
    //! List of all unit tests
    TList<detail::IUnitTest*> mUnitTests;
};

namespace detail {
//! @addtogroup libkiwi_test
//! @{

/**
 * @brief Unit test declaration
 * @details Registers an instance of the test with the test manager
 *
 * @tparam T Unit test class type
 */
template <typename T> class UnitTestDecl {
public:
    UnitTestDecl() {
        IUnitTest* pTest = new T();
        K_ASSERT_PTR(pTest);

        UnitTestMgr::GetInstance().RegistTest(pTest);
    }
};

//! @}
} // namespace detail

//! @}
} // namespace kiwi

#endif