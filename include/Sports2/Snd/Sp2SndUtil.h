#ifndef SPORTS2_SND_UTIL_H
#define SPORTS2_SND_UTIL_H
#include <Sports2/Sp2Types.h>

namespace Sp2 {

class SndUtil {
public:
    static void playBgm(u32 id);
    static void playSound(u32 id, u32 spkFlag);
};

} // namespace Sp2

#endif