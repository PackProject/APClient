#include <Pack/RPSystem.h>

#include <libkiwi.h>

namespace kiwi {

/**
 * @brief Resource font name table
 */
const char* FontMgr::FONT_NAMES[EResFont_Max] = {
#if defined(PACK_SPORTS) || defined(PACK_PLAY)
    "pac_nRodDb_32_I4.brfnt",  "pac_nRodDb_32_IA4.brfnt",
    "pac_nRodDb_62_IA4.brfnt", "pac_nRodDb_200_IA4.brfnt",
    "pac_nRodEb_32_I4.brfnt",  "pac_nRodEb_70_IA4.brfnt",
#elif defined(PACK_RESORT)
    "00_WS2_nRodB_32_IA4.brfnt", "01_WS2_nRodEb_60_IA4.brfnt"
#endif
};

/**
 * @brief Constructor
 */
FontMgr::FontMgr() : mpRomFont(nullptr) {
    mpRomFont = RP_GET_INSTANCE(RPSysFontManager)->GetRomFont();
    K_ASSERT_PTR(mpRomFont);

    for (int i = 0; i < EResFont_Max; i++) {
        mpResFonts[i] = RP_GET_INSTANCE(RPSysFontManager)->GetResFont(i);
        K_ASSERT_PTR(mpResFonts[i]);
    }
}

/**
 * @brief Gets the specified resource font by name
 *
 * @param rName Font name
 */
const nw4r::ut::ResFont* FontMgr::GetResFont(const String& rName) {
    for (int i = 0; i < EResFont_Max; i++) {
        if (rName == FONT_NAMES[i]) {
            return GetResFont(static_cast<EResFont>(i));
        }
    }

    K_LOG_EX("Unknown resource font: %s", rName.CStr());
    return nullptr;
}

} // namespace kiwi
