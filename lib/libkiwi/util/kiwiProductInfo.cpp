#include <libkiwi.h>

namespace kiwi {

/**
 * @brief Gets the date and time at which the module was built
 */
const char* GetBuildDate() {
    return __DATE__ " " __TIME__;
}

/**
 * @brief Gets the pack for which the module was built
 */
const char* GetBuildPack() {
    // clang-format off
    return KOKESHI_BY_PACK("Wii Sports",
                           "Wii Play",
                           "Wii Sports Resort");
    // clang-format on
}

/**
 * @brief Gets the target for which the module was built
 */
const char* GetBuildTarget() {
#if defined(NDEBUG)
    return "Release";
#else
    return "Debug";
#endif
}

/**
 * @brief Gets the hash (shortened) of the latest Git commit
 */
const char* GetGitCommitHash() {
#if defined(GIT_COMMIT_HASH)
    return K_STRINGITIZE(GIT_COMMIT_HASH);
#else
    return "";
#endif
}

} // namespace kiwi
