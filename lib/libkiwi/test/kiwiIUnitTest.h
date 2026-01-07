#ifndef LIBKIWI_TEST_I_UNIT_TEST_H
#define LIBKIWI_TEST_I_UNIT_TEST_H
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiString.h>

/**
 * @brief Defines a unit test and registers it with the test manager
 */
#define KT_TEST(SUITE_NAME, TEST_NAME)                                         \
    class KT_##SUITE_NAME##_##TEST_NAME : public kiwi::detail::IUnitTest {     \
    public:                                                                    \
        KT_##SUITE_NAME##_##TEST_NAME()                                        \
            : kiwi::detail::IUnitTest(#SUITE_NAME, #TEST_NAME) {}              \
                                                                               \
    private:                                                                   \
        virtual void Run();                                                    \
                                                                               \
    private:                                                                   \
        static kiwi::detail::UnitTestDecl<KT_##SUITE_NAME##_##TEST_NAME>       \
            sTestDecl;                                                         \
    };                                                                         \
                                                                               \
    kiwi::detail::UnitTestDecl<KT_##SUITE_NAME##_##TEST_NAME>                  \
        KT_##SUITE_NAME##_##TEST_NAME::sTestDecl;                              \
                                                                               \
    void KT_##SUITE_NAME##_##TEST_NAME::Run()

//! Asserts that the specified expression holds true
#define KT_ASSERT(EXPR) __KT_ASSERT_UNARY(EXPR)

//! Asserts that the two expressions are equal
#define KT_ASSERT_EQ(X, Y) __KT_ASSERT_BINARY(X, ==, Y)
//! Asserts that the two expressions are not equal
#define KT_ASSERT_NE(X, Y) __KT_ASSERT_BINARY(X, !=, Y)

//! Asserts that expression X is less-than-or-equal-to Y
#define KT_ASSERT_LE(X, Y) __KT_ASSERT_BINARY(X, <=, Y)
//! Asserts that expression X is less than Y
#define KT_ASSERT_LT(X, Y) __KT_ASSERT_BINARY(X, <, Y)

//! Asserts that expression X is greater-than-or-equal-to Y
#define KT_ASSERT_GE(X, Y) __KT_ASSERT_BINARY(X, >=, Y)
//! Asserts that expression X is greater than Y
#define KT_ASSERT_GT(X, Y) __KT_ASSERT_BINARY(X, >, Y)

namespace kiwi {
//! @addtogroup libkiwi_test
//! @{

namespace detail {
//! @addtogroup libkiwi_test
//! @{

/**
 * @brief Unit test interface
 */
class IUnitTest {
public:
    /**
     * @brief Constructor
     *
     * @param rSuiteName Test suite name
     * @param rTestName Test case name
     */
    IUnitTest(const String& rSuiteName, const String& rTestName)
        : mSuiteName(rSuiteName), mTestName(rTestName), mIsFailed(false) {}

    /**
     * @brief Runs the unit test
     */
    virtual void Run() = 0;

    /**
     * @brief Gets the test suite name
     */
    const String& GetSuiteName() const {
        return mSuiteName;
    }
    /**
     * @brief Gets the test case name
     */
    const String& GetTestName() const {
        return mTestName;
    }

    /**
     * @brief Tests whether the test case failed
     */
    bool IsFailed() const {
        return mIsFailed;
    }
    /**
     * @brief Gets the assertion expression that caused the failure
     */
    const String& GetFailedExpr() const {
        return mFailedExpr;
    }

protected:
    //! Test suite name
    String mSuiteName;
    //! Test case name
    String mTestName;

    //! Whether this test failed
    bool mIsFailed;
    //! Expression that caused the failure
    String mFailedExpr;
};

//! @}
} // namespace detail

//! @}
} // namespace kiwi

//! Internal macro for unary expressions
// clang-format off
#define __KT_ASSERT_UNARY(VAL)                                                 \
    __KT_ASSERT_INNER(                                                         \
        (VAL),                                                                 \
        kiwi::Format(                                                          \
            /* "%s (%s)", */                                                   \
            "%s",                                                              \
            #VAL                                                               \
            /* kiwi::ToString(VAL).CStr() */                                   \
        )                                                                      \
    )
// clang-format on

//! Internal macro for binary expressions
// clang-format off
#define __KT_ASSERT_BINARY(VALX, OP, VALY)                                     \
    __KT_ASSERT_INNER(                                                         \
        ((VALX) OP (VALY)),                                                    \
        kiwi::Format(                                                          \
            /* "%s %s %s (%s %s %s)", */                                       \
            "%s %s %s",                                                        \
            #VALX, #OP, #VALY                                                  \
            /* kiwi::ToString(VALX).CStr(), #OP, kiwi::ToString(VALY).CStr() */\
        )                                                                      \
    )
// clang-format on

/**
 * @brief Internal test assertion macro
 */
#define __KT_ASSERT_INNER(EXPR, STR)                                           \
    do {                                                                       \
        if (!(EXPR)) {                                                         \
            mIsFailed = true;                                                  \
            mFailedExpr = STR;                                                 \
            return;                                                            \
        }                                                                      \
    } while (0);

#endif