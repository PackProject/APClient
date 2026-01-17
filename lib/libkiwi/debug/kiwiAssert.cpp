#include <libkiwi.h>

#include <revolution/OS.h>

#include <cstdio>
#include <cstring>

/**
 * @brief Logs a message to the console
 *
 * @param pMsg Message
 * @param ... Format string arguments
 */
void kiwi_log(const char* pMsg, ...) {
    char msgBuf[1024];
    std::va_list list;

    va_start(list, pMsg);
    std::vsnprintf(msgBuf, sizeof(msgBuf), pMsg, list);
    va_end(list);

    if (kiwi::DebugConsole::IsCreateInstance()) {
        kiwi::DebugConsole::GetInstance().Printf(msgBuf);
    } else {
        OSReport(msgBuf);
    }
}

/**
 * @brief Halts the program and displays an error message to the screen/console
 *
 * @param pFile Source file name where assertion failed
 * @param line Source file line where assertion failed
 * @param pMsg Assertion message
 * @param ... Format string arguments
 */
void kiwi_fail_assert(const char* pFile, int line, const char* pMsg, ...) {
    static bool firstTime = true;

    char msgBuf[1024];
    std::va_list list;

    va_start(list, pMsg);
    std::vsnprintf(msgBuf, sizeof(msgBuf), pMsg, list);
    va_end(list);

    // Stuck in an assertion loop if this is not our first time
    bool recursive = !firstTime;
    // Early enough assertion can happen before the handler is created
    bool noHandler = !kiwi::Nw4rException::IsCreateInstance();

    // Need to avoid using Nw4rException when it could recurse/OOM
    if (recursive || noHandler) {
        char fatalBuf[2048];

        std::snprintf(fatalBuf, sizeof(fatalBuf),             //
                      "******** ASSERTION FAILED! ********\n" //
                      "%s\n"                                  //
                      "Source: %s(%d)\n",                     //
                      msgBuf, pFile, line);

        if (recursive) {
            std::strncat(fatalBuf, "(Recursive assertion)\n", sizeof(fatalBuf));
        } else {
            std::strncat(fatalBuf, "(Before exception handler created)\n",
                         sizeof(fatalBuf));
        }

        OSFatal(kiwi::Color(kiwi::Color::WHITE), kiwi::Color(kiwi::Color::BLUE),
                fatalBuf);
    }

    firstTime = false;
    kiwi::Nw4rException::GetInstance().FailAssert(pFile, line, msgBuf);
}
// Catch EGG_ASSERT
KOKESHI_BY_PACK(KM_BRANCH(0x800a1f08, kiwi_fail_assert), // Wii Sports
                KM_BRANCH(0x800a17d8, kiwi_fail_assert), // Wii Play
                /* not applicable */); // Wii Sports Resort
// Catch OSPanic
KOKESHI_BY_PACK(KM_BRANCH(0x800eefa8, kiwi_fail_assert),  // Wii Sports
                KM_BRANCH(0x800eec30, kiwi_fail_assert),  // Wii Play
                KM_BRANCH(0x80047150, kiwi_fail_assert)); // Wii Sports Resort
