#ifndef SPORTS2_SND_UTIL_H
#define SPORTS2_SND_UTIL_H
#include <Sports2/Sp2Types.h>

namespace Sp2 {
namespace Snd {

void startBgm(u32 id);
void startSe(u32 id);
void startSeWithRemote(u32 id, u32 spkFlag);

} // namespace Snd
} // namespace Sp2

#endif
