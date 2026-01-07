#include <libkiwi.h>

namespace kiwi {

/**
 * @brief Saves floating-point registers to the context
 *
 * @param pCtx OS context
 */
void LibOS::FillFPUContext(register OSContext* pCtx) {
    K_ASSERT_PTR(pCtx);

    // clang-format off
    asm volatile {
        mfmsr r5
        ori r5, r5, MSR_FP
        mtmsr r5
        isync

        stfd f0,  pCtx->fprs[0]
        stfd f1,  pCtx->fprs[1]
        stfd f2,  pCtx->fprs[2]
        stfd f3,  pCtx->fprs[3]
        stfd f4,  pCtx->fprs[4]
        stfd f5,  pCtx->fprs[5]
        stfd f6,  pCtx->fprs[6]
        stfd f7,  pCtx->fprs[7]
        stfd f8,  pCtx->fprs[8]
        stfd f9,  pCtx->fprs[9]
        stfd f10, pCtx->fprs[10]
        stfd f11, pCtx->fprs[11]
        stfd f12, pCtx->fprs[12]
        stfd f13, pCtx->fprs[13]
        stfd f14, pCtx->fprs[14]
        stfd f15, pCtx->fprs[15]
        stfd f16, pCtx->fprs[16]
        stfd f17, pCtx->fprs[17]
        stfd f18, pCtx->fprs[18]
        stfd f19, pCtx->fprs[19]
        stfd f20, pCtx->fprs[20]
        stfd f21, pCtx->fprs[21]
        stfd f22, pCtx->fprs[22]
        stfd f23, pCtx->fprs[23]
        stfd f24, pCtx->fprs[24]
        stfd f25, pCtx->fprs[25]
        stfd f26, pCtx->fprs[26]
        stfd f27, pCtx->fprs[27]
        stfd f28, pCtx->fprs[28]
        stfd f29, pCtx->fprs[29]
        stfd f30, pCtx->fprs[30]
        stfd f31, pCtx->fprs[31]

        mffs f0
        stfd f0, pCtx->fpscr_pad
        lfd f0, pCtx->fprs[0]

        mfhid2 r5
        rlwinm. r5, r5, 3, 31, 31 // HID2_PSE
        beq _exit

        psq_st f0,  OSContext.psfs[0](pCtx),  0, 0
        psq_st f1,  OSContext.psfs[1](pCtx),  0, 0
        psq_st f2,  OSContext.psfs[2](pCtx),  0, 0
        psq_st f3,  OSContext.psfs[3](pCtx),  0, 0
        psq_st f4,  OSContext.psfs[4](pCtx),  0, 0
        psq_st f5,  OSContext.psfs[5](pCtx),  0, 0
        psq_st f6,  OSContext.psfs[6](pCtx),  0, 0
        psq_st f7,  OSContext.psfs[7](pCtx),  0, 0
        psq_st f8,  OSContext.psfs[8](pCtx),  0, 0
        psq_st f9,  OSContext.psfs[9](pCtx),  0, 0
        psq_st f10, OSContext.psfs[10](pCtx), 0, 0
        psq_st f11, OSContext.psfs[11](pCtx), 0, 0
        psq_st f12, OSContext.psfs[12](pCtx), 0, 0
        psq_st f13, OSContext.psfs[13](pCtx), 0, 0
        psq_st f14, OSContext.psfs[14](pCtx), 0, 0
        psq_st f15, OSContext.psfs[15](pCtx), 0, 0
        psq_st f16, OSContext.psfs[16](pCtx), 0, 0
        psq_st f17, OSContext.psfs[17](pCtx), 0, 0
        psq_st f18, OSContext.psfs[18](pCtx), 0, 0
        psq_st f19, OSContext.psfs[19](pCtx), 0, 0
        psq_st f20, OSContext.psfs[20](pCtx), 0, 0
        psq_st f21, OSContext.psfs[21](pCtx), 0, 0
        psq_st f22, OSContext.psfs[22](pCtx), 0, 0
        psq_st f23, OSContext.psfs[23](pCtx), 0, 0
        psq_st f24, OSContext.psfs[24](pCtx), 0, 0
        psq_st f25, OSContext.psfs[25](pCtx), 0, 0
        psq_st f26, OSContext.psfs[26](pCtx), 0, 0
        psq_st f27, OSContext.psfs[27](pCtx), 0, 0
        psq_st f28, OSContext.psfs[28](pCtx), 0, 0
        psq_st f29, OSContext.psfs[29](pCtx), 0, 0
        psq_st f30, OSContext.psfs[30](pCtx), 0, 0
        psq_st f31, OSContext.psfs[31](pCtx), 0, 0

    _exit:
    }
    // clang-format on
}

} // namespace kiwi
