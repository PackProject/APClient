#ifndef SPORTS2_BSK_SEQUENCE_3PT_H
#define SPORTS2_BSK_SEQUENCE_3PT_H
#include <Sports2/Sp2Types.h>

namespace Sp2 {
namespace Bsk {

// Forward declarations
namespace Lyt {
class Main;
} // namespace Lyt

class Sequence3pt /* public SequenceBase */ {
public:
    Lyt::Main* getMainLyt() const {
        return mpMainLyt;
    }

private:
    char _00[0x100];
    Lyt::Main* mpMainLyt; // at 0x100
};

} // namespace Bsk
} // namespace Sp2

#endif
