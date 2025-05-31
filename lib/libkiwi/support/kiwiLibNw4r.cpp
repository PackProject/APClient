#include <nw4r/g3d.h>

#include <libkiwi.h>

namespace nw4r {
namespace g3d {

/******************************************************************************
 *
 * ResTev
 *
 ******************************************************************************/
void ResTev::GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a,
                             GXTevColorArg b, GXTevColorArg c,
                             GXTevColorArg d) {

    u8* pCmd = ref()
                   .dl.dl.var[stage / TEV_STAGES_PER_DL]
                   .dl.tevColorCalc[stage % TEV_STAGES_PER_DL];

    // clang-format off
    detail::ResWriteBPCmd(pCmd,
        (d << GX_BP_TEVCOLORCOMBINER_D_SHIFT) |
        (c << GX_BP_TEVCOLORCOMBINER_C_SHIFT) |
        (b << GX_BP_TEVCOLORCOMBINER_B_SHIFT) |
        (a << GX_BP_TEVCOLORCOMBINER_A_SHIFT) |
        ((GX_BP_REG_TEVCOLORCOMBINER0 + stage * 2)
            << GX_BP_OPCODE_SHIFT),

        ~(GX_BP_TEVCOLORCOMBINER_DEST_MASK |
          GX_BP_TEVCOLORCOMBINER_SCALE_OR_COMPARE_MODE_MASK |
          GX_BP_TEVCOLORCOMBINER_CLAMP_MASK |
          GX_BP_TEVCOLORCOMBINER_OP_OR_COMPARISON_MASK |
          GX_BP_TEVCOLORCOMBINER_BIAS_MASK));
    // clang-format on
}

void ResTev::GXSetTevColorOp(GXTevStageID stage, GXTevOp op, GXTevBias bias,
                             GXTevScale scale, GXBool clamp,
                             GXTevRegID output) {

    u8* pCmd = ref()
                   .dl.dl.var[stage / TEV_STAGES_PER_DL]
                   .dl.tevColorCalc[stage % TEV_STAGES_PER_DL];

    // Operation
    if (op <= GX_TEV_SUB) {
        // clang-format off
        detail::ResWriteBPCmd(pCmd,
            (bias << GX_BP_TEVCOLORCOMBINER_BIAS_SHIFT) |
            ((op & 1) << GX_BP_TEVCOLORCOMBINER_OP_OR_COMPARISON_SHIFT) |
            (clamp << GX_BP_TEVCOLORCOMBINER_CLAMP_SHIFT) |
            (scale << GX_BP_TEVCOLORCOMBINER_SCALE_OR_COMPARE_MODE_SHIFT) |
            (output << GX_BP_TEVCOLORCOMBINER_DEST_SHIFT) |
            ((GX_BP_REG_TEVCOLORCOMBINER0 + stage * 2)
                << GX_BP_OPCODE_SHIFT),

            ~(GX_BP_TEVCOLORCOMBINER_D_MASK |
            GX_BP_TEVCOLORCOMBINER_C_MASK |
            GX_BP_TEVCOLORCOMBINER_B_MASK |
            GX_BP_TEVCOLORCOMBINER_A_MASK));
        // clang-format on
    }
    // Compare
    else {
        // clang-format off
        detail::ResWriteBPCmd(pCmd,
            ((op & 1) << GX_BP_TEVCOLORCOMBINER_OP_OR_COMPARISON_SHIFT) |
            (GX_MAX_TEVBIAS << GX_BP_TEVCOLORCOMBINER_BIAS_SHIFT) |
            (clamp << GX_BP_TEVCOLORCOMBINER_CLAMP_SHIFT) |
            ((op >> 1 & 3) << GX_BP_TEVCOLORCOMBINER_SCALE_OR_COMPARE_MODE_SHIFT) |
            (output << GX_BP_TEVCOLORCOMBINER_DEST_SHIFT) |
            ((GX_BP_REG_TEVCOLORCOMBINER0 + stage * 2)
                << GX_BP_OPCODE_SHIFT),

            // op CONST clamp op output 

            ~(GX_BP_TEVCOLORCOMBINER_D_MASK |
            GX_BP_TEVCOLORCOMBINER_C_MASK |
            GX_BP_TEVCOLORCOMBINER_B_MASK |
            GX_BP_TEVCOLORCOMBINER_A_MASK));
        // clang-format on
    }
}

/******************************************************************************
 *
 * CopiedMatAccess
 *
 ******************************************************************************/
ResGenMode ScnMdl::CopiedMatAccess::GetResGenMode(bool markDirty) {
    if (mpScnMdl != NULL && mGenMode.IsValid()) {
        if (markDirty) {
            mpScnMdl->MatBufferDirty(mMatID, ScnMdl::BUFFER_RESGENMODE);
        }

        return mGenMode;
    }

    return ResGenMode(NULL);
}

ResMatTevColor ScnMdl::CopiedMatAccess::GetResMatTevColor(bool markDirty) {
    if (mpScnMdl != NULL && mTevColor.IsValid()) {
        if (markDirty) {
            mpScnMdl->MatBufferDirty(mMatID, ScnMdl::BUFFER_RESTEVCOLOR);
        }

        return mTevColor;
    }

    return ResMatTevColor(NULL);
}

ResTev ScnMdl::CopiedMatAccess::GetResTev(bool markDirty) {
    if (mpScnMdl != NULL && mTev.IsValid()) {
        if (markDirty) {
            mpScnMdl->MatBufferDirty(mMatID, ScnMdl::BUFFER_RESTEV);
        }

        return mTev;
    }

    return ResTev(NULL);
}

} // namespace g3d
} // namespace nw4r
