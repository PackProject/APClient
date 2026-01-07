namespace LibWorkBench.Formats.Revolution.GX.Types
{
    public enum GXAlphaOp
    {
        GX_AOP_AND,
        GX_AOP_OR,
        GX_AOP_XOR,
        GX_AOP_XNOR,

        GX_MAX_ALPHAOP
    }

    public enum GXBlendFactor
    {
        GX_BL_ZERO,
        GX_BL_ONE,
        GX_BL_SRCCLR,
        GX_BL_INVSRCCLR,
        GX_BL_SRCALPHA,
        GX_BL_INVSRCALPHA,
        GX_BL_DSTALPHA,
        GX_BL_INVDSTALPHA,

        GX_BL_DSTCLR = GX_BL_SRCCLR,
        GX_BL_INVDSTCLR = GX_BL_INVSRCCLR
    }

    public enum GXBlendMode
    {
        GX_BM_NONE,
        GX_BM_BLEND,
        GX_BM_LOGIC,
        GX_BM_SUBTRACT,

        GX_MAX_BLENDMODE
    }

    public enum GXChannelID
    {
        GX_COLOR0,
        GX_COLOR1,
        GX_ALPHA0,
        GX_ALPHA1,
        GX_COLOR0A0,
        GX_COLOR1A1,
        GX_COLOR_ZERO,
        GX_ALPHA_BUMP,
        GX_ALPHA_BUMPN,

        GX_COLOR_NULL = 255
    }

    public enum GXColorSrc
    {
        GX_SRC_REG,
        GX_SRC_VTX
    }

    public enum GXCompare
    {
        GX_NEVER,
        GX_LESS,
        GX_EQUAL,
        GX_LEQUAL,
        GX_GREATER,
        GX_NEQUAL,
        GX_GEQUAL,
        GX_ALWAYS
    }

    public enum GXIndTexAlphaSel
    {
        GX_ITBA_OFF,
        GX_ITBA_S,
        GX_ITBA_T,
        GX_ITBA_U,

        GX_MAX_ITBALPHA
    }

    public enum GXIndTexBiasSel
    {
        GX_ITB_NONE,
        GX_ITB_S,
        GX_ITB_T,
        GX_ITB_ST,
        GX_ITB_U,
        GX_ITB_SU,
        GX_ITB_TU,
        GX_ITB_STU,

        GX_MAX_ITBIAS
    }

    public enum GXIndTexFormat
    {
        GX_ITF_8,
        GX_ITF_5,
        GX_ITF_4,
        GX_ITF_3,

        GX_MAX_ITFORMAT
    }

    public enum GXIndTexMtxID
    {
        GX_ITM_OFF,
        GX_ITM_0,
        GX_ITM_1,
        GX_ITM_2,

        GX_ITM_S0 = 5,
        GX_ITM_S1,
        GX_ITM_S2,

        GX_ITM_T0 = 9,
        GX_ITM_T1,
        GX_ITM_T2
    }

    public enum GXIndTexScale
    {
        GX_ITS_1,
        GX_ITS_2,
        GX_ITS_4,
        GX_ITS_8,
        GX_ITS_16,
        GX_ITS_32,
        GX_ITS_64,
        GX_ITS_128,
        GX_ITS_256,

        GX_MAX_ITSCALE
    }

    public enum GXIndTexStageID
    {
        GX_INDTEXSTAGE0,
        GX_INDTEXSTAGE1,
        GX_INDTEXSTAGE2,
        GX_INDTEXSTAGE3,

        GX_MAX_INDTEXSTAGE
    }

    public enum GXIndTexWrap
    {
        GX_ITW_OFF,
        GX_ITW_256,
        GX_ITW_128,
        GX_ITW_64,
        GX_ITW_32,
        GX_ITW_16,
        GX_ITW_0,

        GX_MAX_ITWRAP
    }

    public enum GXLogicOp
    {
        GX_LO_CLEAR,
        GX_LO_AND,
        GX_LO_REVAND,
        GX_LO_COPY,
        GX_LO_INVAND,
        GX_LO_NOOP,
        GX_LO_XOR,
        GX_LO_OR,
        GX_LO_NOR,
        GX_LO_EQUIV,
        GX_LO_INV,
        GX_LO_REVOR,
        GX_LO_INVCOPY,
        GX_LO_INVOR,
        GX_LO_NAND,
        GX_LO_SET
    }

    public enum GXTevAlphaArg
    {
        GX_CA_APREV,
        GX_CA_A0,
        GX_CA_A1,
        GX_CA_A2,
        GX_CA_TEXA,
        GX_CA_RASA,
        GX_CA_KONST,
        GX_CA_ZERO,
        GX_CA_ONE
    }

    public enum GXTevBias
    {
        GX_TB_ZERO,
        GX_TB_ADDHALF,
        GX_TB_SUBHALF,

        GX_MAX_TEVBIAS
    }

    public enum GXTevColorArg
    {
        GX_CC_CPREV,
        GX_CC_APREV,
        GX_CC_C0,
        GX_CC_A0,
        GX_CC_C1,
        GX_CC_A1,
        GX_CC_C2,
        GX_CC_A2,
        GX_CC_TEXC,
        GX_CC_TEXA,
        GX_CC_RASC,
        GX_CC_RASA,
        GX_CC_ONE,
        GX_CC_HALF,
        GX_CC_KONST,
        GX_CC_ZERO,
        GX_CC_TEXRRR,
        GX_CC_TEXGGG,
        GX_CC_TEXBBB,

        GX_CC_QUARTER = GX_CC_KONST
    }

    public enum GXTevColorChan
    {
        GX_CH_RED,
        GX_CH_GREEN,
        GX_CH_BLUE,
        GX_CH_ALPHA
    }

    public enum GXTevOp
    {
        GX_TEV_ADD,
        GX_TEV_SUB,

        GX_TEV_COMP_R8_GT = 8,
        GX_TEV_COMP_R8_EQ,
        GX_TEV_COMP_GR16_GT,
        GX_TEV_COMP_GR16_EQ,
        GX_TEV_COMP_BGR24_GT,
        GX_TEV_COMP_BGR24_EQ,
        GX_TEV_COMP_RGB8_GT,
        GX_TEV_COMP_RGB8_EQ,

        GX_TEV_COMP_A8_GT = GX_TEV_COMP_RGB8_GT,
        GX_TEV_COMP_A8_EQ = GX_TEV_COMP_RGB8_EQ
    }

    public enum GXTevRegID
    {
        GX_TEVPREV,
        GX_TEVREG0,
        GX_TEVREG1,
        GX_TEVREG2,

        GX_MAX_TEVREG
    }

    public enum GXTevScale
    {
        GX_CS_SCALE_1,
        GX_CS_SCALE_2,
        GX_CS_SCALE_4,
        GX_CS_DIVIDE_2,

        GX_MAX_TEVSCALE
    }

    public enum GXTevStageID
    {
        GX_TEVSTAGE0,
        GX_TEVSTAGE1,
        GX_TEVSTAGE2,
        GX_TEVSTAGE3,
        GX_TEVSTAGE4,
        GX_TEVSTAGE5,
        GX_TEVSTAGE6,
        GX_TEVSTAGE7,
        GX_TEVSTAGE8,
        GX_TEVSTAGE9,
        GX_TEVSTAGE10,
        GX_TEVSTAGE11,
        GX_TEVSTAGE12,
        GX_TEVSTAGE13,
        GX_TEVSTAGE14,
        GX_TEVSTAGE15,

        GX_MAX_TEVSTAGE
    }

    public enum GXTevSwapSel
    {
        GX_TEV_SWAP0,
        GX_TEV_SWAP1,
        GX_TEV_SWAP2,
        GX_TEV_SWAP3,

        GX_MAX_TEVSWAP
    }

    public enum GXTevKAlphaSel
    {
        GX_TEV_KASEL_8_8,
        GX_TEV_KASEL_7_8,
        GX_TEV_KASEL_6_8,
        GX_TEV_KASEL_5_8,
        GX_TEV_KASEL_4_8,
        GX_TEV_KASEL_3_8,
        GX_TEV_KASEL_2_8,
        GX_TEV_KASEL_1_8,

        GX_TEV_KASEL_1 = 0,
        GX_TEV_KASEL_3_4 = 2,
        GX_TEV_KASEL_1_2 = 4,
        GX_TEV_KASEL_1_4 = 6,

        GX_TEV_KASEL_K0_R = 16,
        GX_TEV_KASEL_K1_R,
        GX_TEV_KASEL_K2_R,
        GX_TEV_KASEL_K3_R,
        GX_TEV_KASEL_K0_G,
        GX_TEV_KASEL_K1_G,
        GX_TEV_KASEL_K2_G,
        GX_TEV_KASEL_K3_G,
        GX_TEV_KASEL_K0_B,
        GX_TEV_KASEL_K1_B,
        GX_TEV_KASEL_K2_B,
        GX_TEV_KASEL_K3_B,
        GX_TEV_KASEL_K0_A,
        GX_TEV_KASEL_K1_A,
        GX_TEV_KASEL_K2_A,
        GX_TEV_KASEL_K3_A
    }

    public enum GXTevKColorSel
    {
        GX_TEV_KCSEL_8_8,
        GX_TEV_KCSEL_7_8,
        GX_TEV_KCSEL_6_8,
        GX_TEV_KCSEL_5_8,
        GX_TEV_KCSEL_4_8,
        GX_TEV_KCSEL_3_8,
        GX_TEV_KCSEL_2_8,
        GX_TEV_KCSEL_1_8,

        GX_TEV_KCSEL_1 = 0,
        GX_TEV_KCSEL_3_4 = 2,
        GX_TEV_KCSEL_1_2 = 4,
        GX_TEV_KCSEL_1_4 = 6,

        GX_TEV_KCSEL_K0 = 12,
        GX_TEV_KCSEL_K1,
        GX_TEV_KCSEL_K2,
        GX_TEV_KCSEL_K3,
        GX_TEV_KCSEL_K0_R,
        GX_TEV_KCSEL_K1_R,
        GX_TEV_KCSEL_K2_R,
        GX_TEV_KCSEL_K3_R,
        GX_TEV_KCSEL_K0_G,
        GX_TEV_KCSEL_K1_G,
        GX_TEV_KCSEL_K2_G,
        GX_TEV_KCSEL_K3_G,
        GX_TEV_KCSEL_K0_B,
        GX_TEV_KCSEL_K1_B,
        GX_TEV_KCSEL_K2_B,
        GX_TEV_KCSEL_K3_B,
        GX_TEV_KCSEL_K0_A,
        GX_TEV_KCSEL_K1_A,
        GX_TEV_KCSEL_K2_A,
        GX_TEV_KCSEL_K3_A
    }

    public enum GXTexCoordID
    {
        GX_TEXCOORD0,
        GX_TEXCOORD1,
        GX_TEXCOORD2,
        GX_TEXCOORD3,
        GX_TEXCOORD4,
        GX_TEXCOORD5,
        GX_TEXCOORD6,
        GX_TEXCOORD7,

        GX_MAX_TEXCOORD,
        GX_TEXCOORD_NULL = 255
    }

    public enum GXTexGenSrc
    {
        GX_TG_POS,
        GX_TG_NRM,
        GX_TG_BINRM,
        GX_TG_TANGENT,
        GX_TG_TEX0,
        GX_TG_TEX1,
        GX_TG_TEX2,
        GX_TG_TEX3,
        GX_TG_TEX4,
        GX_TG_TEX5,
        GX_TG_TEX6,
        GX_TG_TEX7,
        GX_TG_TEXCOORD0,
        GX_TG_TEXCOORD1,
        GX_TG_TEXCOORD2,
        GX_TG_TEXCOORD3,
        GX_TG_TEXCOORD4,
        GX_TG_TEXCOORD5,
        GX_TG_TEXCOORD6,
        GX_TG_COLOR0,
        GX_TG_COLOR1
    }

    public enum GXTexGenType
    {
        GX_TG_MTX3x4,
        GX_TG_MTX2x4,
        GX_TG_BUMP0,
        GX_TG_BUMP1,
        GX_TG_BUMP2,
        GX_TG_BUMP3,
        GX_TG_BUMP4,
        GX_TG_BUMP5,
        GX_TG_BUMP6,
        GX_TG_BUMP7,
        GX_TG_SRTG
    }

    public enum GXTexMapID
    {
        GX_TEXMAP0,
        GX_TEXMAP1,
        GX_TEXMAP2,
        GX_TEXMAP3,
        GX_TEXMAP4,
        GX_TEXMAP5,
        GX_TEXMAP6,
        GX_TEXMAP7,
        GX_MAX_TEXMAP,

        GX_TEXMAP_NULL = 255,
        GX_TEX_DISABLE
    }

    public enum GXTexMtx
    {
        // Any dimension (in standard XF matrix memory)
        // Enum represents base row of matrix
        GX_TEXMTX0 = 30,
        GX_TEXMTX1 = 33,
        GX_TEXMTX2 = 36,
        GX_TEXMTX3 = 39,
        GX_TEXMTX4 = 42,
        GX_TEXMTX5 = 45,
        GX_TEXMTX6 = 48,
        GX_TEXMTX7 = 51,
        GX_TEXMTX8 = 54,
        GX_TEXMTX9 = 57,
        GX_IDENTITY = 60
    }

    public enum GXTexWrapMode
    {
        GX_CLAMP,
        GX_REPEAT,
        GX_MIRROR,

        GX_MAX_TEXWRAPMODE
    }
}
