#ifndef LIBKIWI_CORE_CONSOLE_OUT_H
#define LIBKIWI_CORE_CONSOLE_OUT_H
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiString.h>
#include <libkiwi/util/kiwiNonCopyable.h>

namespace kiwi {
//! @addtogroup libkiwi_core
//! @{

namespace detail {
//! @addtogroup libkiwi_core
//! @{

struct Hex {};
struct Dec {};

/**
 * @brief Console text output stream
 * @see kiwi::cout
 */
class ConsoleOut : private NonCopyable {
public:
    /**
     * @brief Constructor
     */
    ConsoleOut() : mHexFormat(false) {}

    /**
     * @brief Logs output to the console
     *
     * @param rValue Value (converted to string)
     * @return Self for method chaining
     */
    template <typename T> const ConsoleOut& operator<<(const T& rValue) const {
        K_LOG(mHexFormat ? ToHexString(rValue) : ToString(rValue));
        return *this;
    }

    /**
     * @brief Applies decimal formatting to the stream (default)
     * @return Self for method chaining
     */
    ConsoleOut& operator<<(Dec) {
        mHexFormat = false;
        return *this;
    }
    /**
     * @brief Applies hexadecimal formatting to the stream
     * @return Self for method chaining
     */
    ConsoleOut& operator<<(Hex) {
        mHexFormat = true;
        return *this;
    }

private:
    bool mHexFormat; //!< Whether to display values as hex
};

//! @}
} // namespace detail

//! Global console handle
extern const detail::ConsoleOut cout;

//! Newline character
static const char endl = '\n';

//! Decimal display modifier (default)
static const detail::Dec dec = detail::Dec();
//! Hexadecimal display modifier
static const detail::Hex hex = detail::Hex();

//! @}
} // namespace kiwi

#endif
