#include <libkiwi.h>

#include <egg/gfx.h>

#include <revolution/OS.h>

#include <cstring>

namespace kiwi {
namespace chip8 {
namespace {

/**
 * @brief Converts a color to the packed RGBA565 format
 *
 * @param c RGBA color
 * @return RGBA565 encoded color
 */
u16 ColorToRgba565(Color c) {
    u8 r = c.r >> 3;
    u8 g = c.g >> 2;
    u8 b = c.b >> 3;
    return r << 11 | g << 5 | b;
}

} // namespace

/******************************************************************************
 *
 * IFont
 *
 ******************************************************************************/

/**
 * @brief Gets the size of the font sprite data
 */
const u32 IFont::GetSpriteDataSize() {
    K_ASSERT(GetMaxChar() >= GetMinChar());

    u32 range = GetMaxChar() - GetMinChar() + 1;
    u32 oneSize = GetCharWidth() * GetCharHeight() * GetBitDepth();

    return range * oneSize;
}

/******************************************************************************
 *
 * DefaultFont
 *
 ******************************************************************************/

/**
 * @brief Font sprite data
 */
const u8 DefaultFont::scSpriteData[] = {
    0b11110000, // ****
    0b10010000, // *  *
    0b10010000, // *  *
    0b10010000, // *  *
    0b11110000, // ****

    0b00100000, //   *
    0b01100000, //  **
    0b00100000, //   *
    0b00100000, //   *
    0b01110000, //  ***

    0b11110000, // ****
    0b00010000, //    *
    0b11110000, // ****
    0b10000000, // *
    0b11110000, // ****

    0b11110000, // ****
    0b00010000, //    *
    0b11110000, // ****
    0b00010000, //    *
    0b11110000, // ****

    0b10010000, // *  *
    0b10010000, // *  *
    0b11110000, // ****
    0b00010000, //    *
    0b00010000, //    *

    0b11110000, // ****
    0b10000000, // *
    0b11110000, // ****
    0b00010000, //    *
    0b11110000, // ****

    0b11110000, // ****
    0b10000000, // *
    0b11110000, // ****
    0b10010000, // *  *
    0b11110000, // ****

    0b11110000, // ****
    0b00010000, //    *
    0b00100000, //   *
    0b01000000, //  *
    0b01000000, //  *

    0b11110000, // ****
    0b10010000, // *  *
    0b11110000, // ****
    0b10010000, // *  *
    0b11110000, // ****

    0b11110000, // ****
    0b10010000, // *  *
    0b11110000, // ****
    0b00010000, //    *
    0b11110000, // ****

    0b11110000, // ****
    0b10010000, // *  *
    0b11110000, // ****
    0b10010000, // *  *
    0b10010000, // *  *

    0b11100000, // ***
    0b10010000, // *  *
    0b11100000, // ***
    0b10010000, // *  *
    0b11100000, // ***

    0b11110000, // ****
    0b10000000, // *
    0b10000000, // *
    0b10000000, // *
    0b11110000, // ****

    0b11100000, // ***
    0b10010000, // *  *
    0b10010000, // *  *
    0b10010000, // *  *
    0b11100000, // ***

    0b11110000, // ****
    0b10000000, // *
    0b11110000, // ****
    0b10000000, // *
    0b11110000, // ****

    0b11110000, // ****
    0b10000000, // *
    0b11110000, // ****
    0b10000000, // *
    0b10000000, // *
};

/******************************************************************************
 *
 * GXRenderer
 *
 ******************************************************************************/

/**
 * @brief Constructor
 */
GXRenderer::GXRenderer()
    : mpTexture(nullptr), mpPalette(nullptr), mTextureSize(0) {

    // 16-bit color
    mpPalette = new (32) u8[sizeof(u16) * 2];
    K_ASSERT_PTR(mpPalette);
}

/**
 * @brief Destructor
 */
GXRenderer::~GXRenderer() {
    delete[] mpTexture;
    mpTexture = nullptr;

    delete[] mpPalette;
    mpPalette = nullptr;
}

/**
 * @brief Draws the emulator framebuffer
 *
 * @param rArg Rendering context
 */
void GXRenderer::Draw(const IRenderer::Arg& rArg) {
    K_ASSERT_PTR(rArg.pBuffer);

    CreateTexture(rArg);
    CreatePalette(rArg);

    // Screen texture uses palette/color index due to simplicity
    GXInitTexObjCI(&mTexObj, mpTexture, rArg.width, rArg.height,
                   static_cast<GXTexFmt>(GX_TF_C8), GX_CLAMP, GX_CLAMP,
                   GX_FALSE, GX_TLUT0);
    GXLoadTexObj(&mTexObj, GX_TEXMAP0);

    // Palette is RGB565 because we don't need alpha
    GXInitTlutObj(&mTlutObj, mpPalette, GX_TL_RGB565, PALETTE_ENTRY_NUM);
    GXLoadTlut(&mTlutObj, GX_TLUT0);

    EGG::DrawGX::BeginDrawQuad(EGG::DrawGX::COLORCHAN_COLOR,
                               EGG::DrawGX::ZMODE_ALWAYS,
                               EGG::DrawGX::BLEND_NORMAL, true, false);

    EGG::Matrix34f ident;
    ident.makeIdentity();
    EGG::DrawGX::DrawDLWorld(EGG::DrawGX::DL_QUAD_TEXTURE, ident);
}

/**
 * @brief Creates CI8 texture data from the Chip-8 framebuffer
 *
 * @param rArg Rendering context
 */
void GXRenderer::CreateTexture(const Arg& rArg) {
    K_ASSERT_PTR(rArg.pBuffer);
    K_ASSERT(rArg.width % CI8_BLOCK_WIDTH == 0);
    K_ASSERT(rArg.height % CI8_BLOCK_HEIGHT == 0);

    // Textures are stored in blocks so we must round up to the nearest
    u32 textureWidth = RoundUp(rArg.width, CI8_BLOCK_WIDTH);
    u32 textureHeight = RoundUp(rArg.width, CI8_BLOCK_HEIGHT);
    u32 textureSize = textureWidth * textureHeight;

    // Number of 8x8 blocks required to encode the texture
    u32 blocksPerRow = textureWidth / CI8_BLOCK_WIDTH;
    u32 blocksPerCol = textureHeight / CI8_BLOCK_HEIGHT;

    // Need to realloc to fit the screen texture
    if (mpTexture == nullptr || textureSize > mTextureSize) {
        delete[] mpTexture;
        mpTexture = new (32) u8[textureSize];
        mTextureSize = textureSize;
    }

    K_ASSERT_PTR(mpTexture);
    K_ASSERT(textureSize <= mTextureSize);

    // Clear with the OFF color
    std::memset(mpTexture, 0, mTextureSize);

    for (u32 y = 0; y < rArg.height; y++) {
        for (u32 x = 0; x < rArg.width; x++) {

            // "Source" position inside framebuffer
            u32 src =            //
                y * rArg.width + //
                x;

            // "Desintation" position inside texture
            u32 dst =                                     //
                (y + y % CI8_BLOCK_HEIGHT) * rArg.width + //
                (x + x % CI8_BLOCK_WIDTH);

            // On/off pixels use the 1/0 palette entries, respectively
            mpTexture[dst] = rArg.pBuffer[src] ? 1 : 0;
        }
    }

    K_LOG_EX("bufferData: %p, bufferSize: %08X\n", rArg.pBuffer,
             rArg.width * rArg.height);
    K_LOG_EX("texData: %p, texSize: %08X\n", mpTexture, mTextureSize);
    K_LOG_EX("plttData: %p, plttSize: %08X\n", mpPalette, sizeof(u16) * 2);
}

/**
 * @brief Creates RGB565 palette data from the Chip-8 framebuffer
 *
 * @param rArg Rendering context
 */
void GXRenderer::CreatePalette(const Arg& rArg) {
    reinterpret_cast<u16*>(mpPalette)[0] = ColorToRgba565(rArg.off);
    reinterpret_cast<u16*>(mpPalette)[1] = ColorToRgba565(rArg.on);
}

/******************************************************************************
 *
 * System
 *
 ******************************************************************************/

/**
 * @brief Opcode group handler functions
 */
const System::OpcodeFunc System::scOpcodeGroupFuncs[] = {
    /* 0x0XXX */ &System::Opcode_0XXX,
    /* 0x1XXX */ &System::Opcode_JP_NNN,
    /* 0x2XXX */ &System::Opcode_CALL_NNN,
    /* 0x3XXX */ &System::Opcode_SE_VX_KK,
    /* 0x4XXX */ &System::Opcode_SNE_VX_KK,
    /* 0x5XXX */ &System::Opcode_SE_VX_VY,
    /* 0x6XXX */ &System::Opcode_LD_VX_KK,
    /* 0x7XXX */ &System::Opcode_ADD_VX_KK,
    /* 0x8XXX */ &System::Opcode_8XXX,
    /* 0x9XXX */ &System::Opcode_SNE_VX_VY,
    /* 0xAXXX */ &System::Opcode_LD_I_NNN,
    /* 0xBXXX */ &System::Opcode_JP_V0_NNN,
    /* 0xCXXX */ &System::Opcode_RND,
    /* 0xDXXX */ &System::Opcode_DRW,
    /* 0xEXXX */ &System::Opcode_EXXX,
    /* 0xFXXX */ &System::Opcode_FXXX,
};

/**
 * @brief Keyboard button map
 */
const u32 System::scButtonMap[] = {
    EButton_Left,  // 0x00
    EButton_Right, // 0x01
    EButton_Down,  // 0x02
    EButton_Up,    // 0x03
    EButton_A,     // 0x04
    EButton_B,     // 0x05
    EButton_1,     // 0x06
    EButton_2,     // 0x07
    EButton_Plus,  // 0x08
    EButton_Minus, // 0x09
};

/**
 * @brief Corax+ test ROM
 */
const u8 System::scTestRom[] = {
    0x12, 0x0A, 0x60, 0x01, 0x00, 0xEE, 0x60, 0x02, 0x12, 0xA6, 0x00, 0xE0,
    0x68, 0x32, 0x6B, 0x1A, 0xA4, 0xF1, 0xD8, 0xB4, 0x68, 0x3A, 0xA4, 0xF5,
    0xD8, 0xB4, 0x68, 0x02, 0x69, 0x06, 0x6A, 0x0B, 0x6B, 0x01, 0x65, 0x2A,
    0x66, 0x2B, 0xA4, 0xB5, 0xD8, 0xB4, 0xA4, 0xED, 0xD9, 0xB4, 0xA4, 0xA5,
    0x36, 0x2B, 0xA4, 0xA1, 0xDA, 0xB4, 0x6B, 0x06, 0xA4, 0xB9, 0xD8, 0xB4,
    0xA4, 0xED, 0xD9, 0xB4, 0xA4, 0xA1, 0x45, 0x2A, 0xA4, 0xA5, 0xDA, 0xB4,
    0x6B, 0x0B, 0xA4, 0xBD, 0xD8, 0xB4, 0xA4, 0xED, 0xD9, 0xB4, 0xA4, 0xA1,
    0x55, 0x60, 0xA4, 0xA5, 0xDA, 0xB4, 0x6B, 0x10, 0xA4, 0xC5, 0xD8, 0xB4,
    0xA4, 0xED, 0xD9, 0xB4, 0xA4, 0xA1, 0x76, 0xFF, 0x46, 0x2A, 0xA4, 0xA5,
    0xDA, 0xB4, 0x7B, 0x05, 0xA4, 0xCD, 0xD8, 0xB4, 0xA4, 0xED, 0xD9, 0xB4,
    0xA4, 0xA1, 0x95, 0x60, 0xA4, 0xA5, 0xDA, 0xB4, 0x7B, 0x05, 0xA4, 0xAD,
    0xD8, 0xB4, 0xA4, 0xED, 0xD9, 0xB4, 0xA4, 0xA5, 0x12, 0x90, 0xA4, 0xA1,
    0xDA, 0xB4, 0x68, 0x12, 0x69, 0x16, 0x6A, 0x1B, 0x6B, 0x01, 0xA4, 0xB1,
    0xD8, 0xB4, 0xA4, 0xED, 0xD9, 0xB4, 0x60, 0x00, 0x22, 0x02, 0xA4, 0xA5,
    0x40, 0x00, 0xA4, 0xA1, 0xDA, 0xB4, 0x7B, 0x05, 0xA4, 0xA9, 0xD8, 0xB4,
    0xA4, 0xE1, 0xD9, 0xB4, 0xA4, 0xA5, 0x40, 0x02, 0xA4, 0xA1, 0x30, 0x00,
    0xDA, 0xB4, 0x7B, 0x05, 0xA4, 0xC9, 0xD8, 0xB4, 0xA4, 0xA9, 0xD9, 0xB4,
    0xA4, 0xA1, 0x65, 0x2A, 0x67, 0x00, 0x87, 0x50, 0x47, 0x2A, 0xA4, 0xA5,
    0xDA, 0xB4, 0x7B, 0x05, 0xA4, 0xC9, 0xD8, 0xB4, 0xA4, 0xAD, 0xD9, 0xB4,
    0xA4, 0xA1, 0x66, 0x0B, 0x67, 0x2A, 0x87, 0x61, 0x47, 0x2B, 0xA4, 0xA5,
    0xDA, 0xB4, 0x7B, 0x05, 0xA4, 0xC9, 0xD8, 0xB4, 0xA4, 0xB1, 0xD9, 0xB4,
    0xA4, 0xA1, 0x66, 0x78, 0x67, 0x1F, 0x87, 0x62, 0x47, 0x18, 0xA4, 0xA5,
    0xDA, 0xB4, 0x7B, 0x05, 0xA4, 0xC9, 0xD8, 0xB4, 0xA4, 0xB5, 0xD9, 0xB4,
    0xA4, 0xA1, 0x66, 0x78, 0x67, 0x1F, 0x87, 0x63, 0x47, 0x67, 0xA4, 0xA5,
    0xDA, 0xB4, 0x68, 0x22, 0x69, 0x26, 0x6A, 0x2B, 0x6B, 0x01, 0xA4, 0xC9,
    0xD8, 0xB4, 0xA4, 0xB9, 0xD9, 0xB4, 0xA4, 0xA1, 0x66, 0x8C, 0x67, 0x8C,
    0x87, 0x64, 0x47, 0x18, 0xA4, 0xA5, 0xDA, 0xB4, 0x7B, 0x05, 0xA4, 0xC9,
    0xD8, 0xB4, 0xA4, 0xBD, 0xD9, 0xB4, 0xA4, 0xA1, 0x66, 0x8C, 0x67, 0x78,
    0x87, 0x65, 0x47, 0xEC, 0xA4, 0xA5, 0xDA, 0xB4, 0x7B, 0x05, 0xA4, 0xC9,
    0xD8, 0xB4, 0xA4, 0xC5, 0xD9, 0xB4, 0xA4, 0xA1, 0x66, 0x78, 0x67, 0x8C,
    0x87, 0x67, 0x47, 0xEC, 0xA4, 0xA5, 0xDA, 0xB4, 0x7B, 0x05, 0xA4, 0xC9,
    0xD8, 0xB4, 0xA4, 0xC1, 0xD9, 0xB4, 0xA4, 0xA1, 0x66, 0x0F, 0x86, 0x66,
    0x46, 0x07, 0xA4, 0xA5, 0xDA, 0xB4, 0x7B, 0x05, 0xA4, 0xC9, 0xD8, 0xB4,
    0xA4, 0xE1, 0xD9, 0xB4, 0xA4, 0xA1, 0x66, 0xE0, 0x86, 0x6E, 0x46, 0xC0,
    0xA4, 0xA5, 0xDA, 0xB4, 0x7B, 0x05, 0xA4, 0xE5, 0xD8, 0xB4, 0xA4, 0xC1,
    0xD9, 0xB4, 0xA4, 0x9E, 0xF1, 0x65, 0xA4, 0xA5, 0x30, 0xAA, 0xA4, 0xA1,
    0x31, 0x55, 0xA4, 0xA1, 0xDA, 0xB4, 0x68, 0x32, 0x69, 0x36, 0x6A, 0x3B,
    0x6B, 0x01, 0xA4, 0xE5, 0xD8, 0xB4, 0xA4, 0xBD, 0xD9, 0xB4, 0xA4, 0x9E,
    0x60, 0x00, 0x61, 0x30, 0xF1, 0x55, 0xA4, 0x9E, 0xF0, 0x65, 0x81, 0x00,
    0xA4, 0x9F, 0xF0, 0x65, 0xA4, 0xA5, 0x30, 0x30, 0xA4, 0xA1, 0x31, 0x00,
    0xA4, 0xA1, 0xDA, 0xB4, 0x7B, 0x05, 0xA4, 0xE5, 0xD8, 0xB4, 0xA4, 0xB5,
    0xD9, 0xB4, 0xA4, 0x9E, 0x66, 0x89, 0xF6, 0x33, 0xF2, 0x65, 0xA4, 0xA1,
    0x30, 0x01, 0x14, 0x32, 0x31, 0x03, 0x14, 0x32, 0x32, 0x07, 0x14, 0x32,
    0xA4, 0x9E, 0x66, 0x41, 0xF6, 0x33, 0xF2, 0x65, 0xA4, 0xA1, 0x30, 0x00,
    0x14, 0x32, 0x31, 0x06, 0x14, 0x32, 0x32, 0x05, 0x14, 0x32, 0xA4, 0x9E,
    0x66, 0x04, 0xF6, 0x33, 0xF2, 0x65, 0xA4, 0xA1, 0x30, 0x00, 0x14, 0x32,
    0x31, 0x00, 0x14, 0x32, 0x32, 0x04, 0x14, 0x32, 0xA4, 0xA5, 0xDA, 0xB4,
    0x7B, 0x05, 0xA4, 0xE5, 0xD8, 0xB4, 0xA4, 0xE1, 0xD9, 0xB4, 0xA4, 0xA1,
    0x66, 0x04, 0xF6, 0x1E, 0xDA, 0xB4, 0x7B, 0x05, 0xA4, 0xE9, 0xD8, 0xB4,
    0xA4, 0xED, 0xD9, 0xB4, 0xA4, 0xA5, 0x66, 0xFF, 0x76, 0x0A, 0x36, 0x09,
    0xA4, 0xA1, 0x86, 0x66, 0x36, 0x04, 0xA4, 0xA1, 0x66, 0xFF, 0x60, 0x0A,
    0x86, 0x04, 0x36, 0x09, 0xA4, 0xA1, 0x86, 0x66, 0x36, 0x04, 0xA4, 0xA1,
    0x66, 0xFF, 0x86, 0x6E, 0x86, 0x66, 0x36, 0x7F, 0xA4, 0xA1, 0x86, 0x66,
    0x86, 0x6E, 0x36, 0x7E, 0xA4, 0xA1, 0x66, 0x05, 0x76, 0xF6, 0x36, 0xFB,
    0xA4, 0xA1, 0x66, 0x05, 0x86, 0x05, 0x36, 0xFB, 0xA4, 0xA1, 0x66, 0x05,
    0x80, 0x67, 0x30, 0xFB, 0xA4, 0xA1, 0xDA, 0xB4, 0x14, 0x9C, 0xAA, 0x55,
    0x00, 0x00, 0xA0, 0x40, 0xA0, 0x00, 0xA0, 0xC0, 0x80, 0xE0, 0xA0, 0xA0,
    0xE0, 0xC0, 0x40, 0x40, 0xE0, 0xE0, 0x20, 0xC0, 0xE0, 0xE0, 0x60, 0x20,
    0xE0, 0xA0, 0xE0, 0x20, 0x20, 0xE0, 0xC0, 0x20, 0xC0, 0x60, 0x80, 0xE0,
    0xE0, 0xE0, 0x20, 0x40, 0x40, 0xE0, 0xE0, 0xA0, 0xE0, 0xE0, 0xE0, 0x20,
    0xC0, 0x40, 0xA0, 0xE0, 0xA0, 0xC0, 0xE0, 0xA0, 0xE0, 0xE0, 0x80, 0x80,
    0xE0, 0xC0, 0xA0, 0xA0, 0xC0, 0xE0, 0xC0, 0x80, 0xE0, 0xE0, 0x80, 0xC0,
    0x80, 0x00, 0xA0, 0xA0, 0x40, 0xA0, 0x40, 0xA0, 0xA0, 0x0A, 0xAE, 0xA2,
    0x42, 0x38, 0x08, 0x30, 0xB8,
};

/**
 * @brief Constructor
 *
 * @param pRenderer Renderer
 */
System::System(IRenderer* pRenderer)
    : mpRenderer(pRenderer),
      mpFont(new DefaultFont()),
      mpIllegalInstCallback(DefaultIllegalInstCallback),
      mClockSpeed(DEFAULT_CLOCK_SPEED),
      mOffColor(Color::BLACK),
      mOnColor(Color::WHITE) {

    K_ASSERT_PTR(mpRenderer);
    K_ASSERT_PTR(mpFont);

    Reset();
}

/**
 * @brief Destructor
 */
System::~System() {
    delete mpRenderer;
    mpRenderer = nullptr;

    delete mpFont;
    mpFont = nullptr;
}

/**
 * @brief Resets the emulator state
 * @note This does not re-load the ROM.
 */
void System::Reset() {
    K_ASSERT_PTR(mpFont);
    K_ASSERT_EX(mpFont->GetLoadAddr() + mpFont->GetSpriteDataSize() <
                    MEMORY_SIZE,
                "Font sprite data is too big");

    std::memcpy(mMemory + mpFont->GetLoadAddr(), mpFont->GetSpriteData(),
                mpFont->GetSpriteDataSize());

    std::memset(mMemory, 0, sizeof(mMemory));
    std::memset(mFrameBuffer, 0, sizeof(mFrameBuffer));

    std::memset(V, 0, sizeof(V));
    I = 0;
    PC = 0;

    std::memset(mStack, 0, sizeof(mStack));
    SP = 0;

    mDelayTimer = 0;
    mSoundTimer = 0;
}

/**
 * @brief Performs one frame of execution
 */
void System::Calculate() {
    // Program stalling for keypress
    if (mWaitKeyPressReg) {
        CalculateWaitKey();
        return;
    }

    // Perform one initial cycle
    if (!mPrevOSTick) {
        mPrevOSTick = OSGetTick();
        Update(static_cast<u32>(1));
        return;
    }

    s64 deltaTick = OS_TICKS_DELTA(OSGetTick(), *mPrevOSTick);
    f32 deltaTime = OS_TICKS_TO_USEC(deltaTick) / 1000000.0f;
    Update(deltaTime);
}

/**
 * @brief Draws the latest frame
 */
void System::Draw() {
    K_ASSERT_PTR(mpRenderer);

    IRenderer::Arg arg;
    arg.pBuffer = mFrameBuffer;
    arg.width = FRAMEBUFFER_WIDTH;
    arg.height = FRAMEBUFFER_HEIGHT;
    arg.off = mOffColor;
    arg.on = mOnColor;

    mpRenderer->Draw(arg);
}

/**
 * @brief Loads a ROM binary
 *
 * @param pBinary Binary data
 * @param binarySize Binary data size
 */
void System::LoadROM(const void* pBinary, u32 binarySize) {
    K_ASSERT_PTR(pBinary);
    K_ASSERT(PROG_ADDR + binarySize < MEMORY_SIZE);

    Reset();
    std::memcpy(mMemory + PROG_ADDR, pBinary, binarySize);

    PC = PROG_ADDR;
}

/**
 * @brief Loads the test ROM binary
 */
void System::LoadTestROM() {
    LoadROM(scTestRom, sizeof(scTestRom));
}

/**
 * @brief Performs the specified amount of CPU cycles
 *
 * @param cycles Cycle count
 */
void System::Update(u32 cycles) {
    for (u32 i = 0; i < cycles; i++) {
        K_ASSERT_EX(PC <= MEMORY_SIZE - 2, "Program counter overflow!");

        mOpcode.raw = mMemory[PC++] << 8 | mMemory[PC++];
        (this->*scOpcodeGroupFuncs[mOpcode.type])();
    }
}

/**
 * @brief Updates waiting for keypress state
 */
void System::CalculateWaitKey() {
    K_ASSERT(mWaitKeyPressReg.HasValue());

    const kiwi::WiiCtrl& rCtrl =
        kiwi::CtrlMgr::GetInstance().GetWiiCtrl(kiwi::EPlayer_1);

    for (u32 i = 0; i < K_LENGTHOF(scButtonMap); i++) {
        if (!rCtrl.IsHold(scButtonMap[i])) {
            continue;
        }

        V[*mWaitKeyPressReg] = static_cast<u8>(i);
        mWaitKeyPressReg.Reset();
        break;
    }
}

/**
 * @brief Default illegal instruction callback
 *
 * @param opcode Illegal instruction opcode
 * @param V Register state (mutable)
 */
void System::DefaultIllegalInstCallback(u16 opcode, u8 V[VREG_NUM]) {
    K_ASSERT_PTR(V);

    K_ASSERT_EX(false, "Unhandled illegal instruction (%04X)", opcode);
}

/**
 * @brief Executes an opcode in the 0XXX group
 */
void System::Opcode_0XXX() {
    switch (mOpcode.kk) {
    case 0xE0: {
        Opcode_CLS();
        break;
    }

    case 0xEE: {
        Opcode_RET();
        break;
    }

    default: {
        Opcode_Illegal();
        break;
    }
    }
}

/**
 * @brief Executes an opcode in the 8XXX group
 */
void System::Opcode_8XXX() {
    static const OpcodeFunc table[] = {
        &System::Opcode_LD_VX_VY,  &System::Opcode_OR,
        &System::Opcode_AND,       &System::Opcode_XOR,
        &System::Opcode_ADD_VX_VY, &System::Opcode_SUB,
        &System::Opcode_SHR,       &System::Opcode_SUBN,
        &System::Opcode_Illegal,   &System::Opcode_Illegal,
        &System::Opcode_Illegal,   &System::Opcode_Illegal,
        &System::Opcode_Illegal,   &System::Opcode_Illegal,
        &System::Opcode_SHL,       &System::Opcode_Illegal};

    (this->*table[mOpcode.n])();
}

/**
 * @brief Executes an opcode in the EXXX group
 */
void System::Opcode_EXXX() {
    switch (mOpcode.kk) {
    case 0x9E: {
        Opcode_SKP();
        break;
    }

    case 0xA1: {
        Opcode_SKNP();
        break;
    }

    default: {
        Opcode_Illegal();
        break;
    }
    }
}

/**
 * @brief Executes an opcode in the FXXX group
 */
void System::Opcode_FXXX() {
    switch (mOpcode.kk) {
    case 0x07: {
        Opcode_LD_VX_DT();
        break;
    }

    case 0x0A: {
        Opcode_LD_VX_K();
        break;
    }

    case 0x15: {
        Opcode_LD_DT_VX();
        break;
    }

    case 0x18: {
        Opcode_LD_ST_VX();
        break;
    }

    case 0x1E: {
        Opcode_ADD_I_VX();
        break;
    }

    case 0x29: {
        Opcode_LD_F_VX();
        break;
    }

    case 0x33: {
        Opcode_LD_B_VX();
        break;
    }

    case 0x55: {
        Opcode_LD_I_VX();
        break;
    }

    case 0x65: {
        Opcode_LD_VX_I();
        break;
    }

    default: {
        Opcode_Illegal();
        break;
    }
    }
}

/**
 * @brief Handler for illegal opcodes
 */
void System::Opcode_Illegal() {
    if (mpIllegalInstCallback != nullptr) {
        mpIllegalInstCallback(mOpcode.raw, V);
    } else {
        // Catch unhandled exceptions in debug
        K_UNREACHABLE();
    }
}

/**
 * @brief 00E0 - CLS
 * @details Clear the display.
 */
void System::Opcode_CLS() {
    std::memset(mFrameBuffer, 0, sizeof(mFrameBuffer));
}

/**
 * @brief 00EE - RET
 * @details Return from a subroutine.
 */
void System::Opcode_RET() {
    K_ASSERT_EX(SP > 0, "Stack underflow!");
    K_ASSERT(SP < STACK_LENGTH);
    PC = mStack[SP--];
}

/**
 * @brief 1nnn - JP addr
 * @details Jump to location nnn.
 */
void System::Opcode_JP_NNN() {
    PC = mOpcode.nnn;
}

/**
 * @brief 2nnn - CALL addr
 * @details Call subroutine at nnn.
 */
void System::Opcode_CALL_NNN() {
    K_ASSERT_EX(SP < STACK_LENGTH - 1, "Stack overflow!");
    mStack[++SP] = PC;
    PC = mOpcode.nnn;
}

/**
 * @brief 3xkk - SE Vx, byte
 * @details Skip next instruction if Vx = kk.
 */
void System::Opcode_SE_VX_KK() {
    if (V[mOpcode.x] == mOpcode.kk) {
        PC += sizeof(u16);
    }
}

/**
 * @brief 4xkk - SNE Vx, byte
 * @details Skip next instruction if Vx != kk.
 */
void System::Opcode_SNE_VX_KK() {
    if (V[mOpcode.x] != mOpcode.kk) {
        PC += sizeof(u16);
    }
}

/**
 * @brief 5xy0 - SE Vx, Vy
 * @details Skip next instruction if Vx = Vy.
 */
void System::Opcode_SE_VX_VY() {
    if (V[mOpcode.x] == V[mOpcode.y]) {
        PC += sizeof(u16);
    }
}

/**
 * @brief 6xkk - LD Vx, byte
 * @details Set Vx = kk.
 */
void System::Opcode_LD_VX_KK() {
    V[mOpcode.x] = mOpcode.kk;
}

/**
 * @brief 7xkk - LD Vx, byte
 * @details Set Vx = Vx + kk.
 */
void System::Opcode_ADD_VX_KK() {
    V[mOpcode.x] += mOpcode.kk;
}

/**
 * @brief 8xy0 - LD Vx, Vy
 * @details Set Vx = Vy.
 */
void System::Opcode_LD_VX_VY() {
    V[mOpcode.x] = V[mOpcode.y];
}

/**
 * @brief 8xy1 - OR Vx, Vy
 * @details Set Vx = Vx OR Vy.
 */
void System::Opcode_OR() {
    V[mOpcode.x] |= V[mOpcode.y];
}

/**
 * @brief 8xy2 - AND Vx, Vy
 * @details Set Vx = Vx AND Vy.
 */
void System::Opcode_AND() {
    V[mOpcode.x] &= V[mOpcode.y];
}

/**
 * @brief 8xy3 - XOR Vx, Vy
 * @details Set Vx = Vx XOR Vy.
 */
void System::Opcode_XOR() {
    V[mOpcode.x] ^= V[mOpcode.y];
}

/**
 * @brief 8xy4 - ADD Vx, Vy
 * @details Set Vx = Vx + Vy, set VF = carry.
 */
void System::Opcode_ADD_VX_VY() {
    VF = V[mOpcode.x] + V[mOpcode.y] > 0xFF ? 1 : 0;
    V[mOpcode.x] += V[mOpcode.y];
}

/**
 * @brief 8xy5 - SUB Vx, Vy
 * @details Set Vx = Vx - Vy, set VF = NOT borrow.
 */
void System::Opcode_SUB() {
    VF = V[mOpcode.x] > V[mOpcode.y] ? 1 : 0;
    V[mOpcode.x] -= V[mOpcode.y];
}

/**
 * @brief 8xy6 - SHR Vx {, Vy}
 * @details Set Vx = Vx SHR 1.
 */
void System::Opcode_SHR() {
    VF = V[mOpcode.x] & 0b00000001;
    V[mOpcode.x] >>= 1;
}

/**
 * @brief 8xy7 - SUBN Vx, Vy
 * @details Set Vx = Vy - Vx, set VF = NOT borrow.
 */
void System::Opcode_SUBN() {
    VF = V[mOpcode.y] > V[mOpcode.x];
    V[mOpcode.y] -= V[mOpcode.x];
}

/**
 * @brief 8xyE - SHL Vx {, Vy}
 * @details Set Vx = Vx SHL 1.
 */
void System::Opcode_SHL() {
    VF = V[mOpcode.x] & 0b10000000;
    V[mOpcode.x] <<= 1;
}

/**
 * @brief 9xy0 - SNE Vx, Vy
 * @details Skip next instruction if Vx != Vy.
 */
void System::Opcode_SNE_VX_VY() {
    if (V[mOpcode.x] != V[mOpcode.y]) {
        PC += sizeof(u16);
    }
}

/**
 * @brief Annn - LD I, addr
 * @details Set I = nnn.
 */
void System::Opcode_LD_I_NNN() {
    I = mOpcode.nnn;
}

/**
 * @brief Bnnn - JP V0, addr
 * @details Jump to location nnn + V0.
 */
void System::Opcode_JP_V0_NNN() {
    PC = mOpcode.nnn + V[0];
}

/**
 * @brief Cxkk - RND Vx, byte
 * @details Set Vx = random byte AND kk.
 */
void System::Opcode_RND() {
    V[mOpcode.x] = mRandom.NextU32() & mOpcode.kk;
}

/**
 * @brief Dxyn - DRW Vx, Vy, nibble
 * @details Display n-byte sprite starting at memory location I at (Vx, Vy), set
 * VF = collision.
 */
void System::Opcode_DRW() {
    K_ASSERT(I < MEMORY_SIZE);

#if 0
    VF = false;

    u8 x = V[mOpcode.x] % FRAMEBUFFER_WIDTH;
    u8 y = V[mOpcode.y] % FRAMEBUFFER_HEIGHT;

    // Sprite dimensions is Nx8
    for (u32 i = 0; i < mOpcode.n; i++, y++) {
        K_ASSERT(I + i < MEMORY_SIZE);
        K_ASSERT(y * (FRAMEBUFFER_WIDTH / 8) + (x / 8) < MEMORY_SIZE);

        // Sprite row at 1bpp
        u8 row = mMemory[I + i];
        // Sprite position in memory
        u8* p = &mMemory[y * (FRAMEBUFFER_WIDTH / 8) + (x / 8)];

        // Sprites are clamped at edges
        for (u32 i = 0; i < Min(SPRITE_WIDTH, FRAMEBUFFER_WIDTH - x);
             i++, row >>= 1, x++) {

            // Next pixel is off
            if (!(row & 1)) {
                continue;
            }

            VF |= *p & (1 << i);
            *p ^= 1 << i;
        }
    }
#else
    VF = false;

    u8 x = V[mOpcode.x] % FRAMEBUFFER_WIDTH;
    u8 y = V[mOpcode.y] % FRAMEBUFFER_HEIGHT;

    // Sprite dimensions is Nx8
    for (u32 i = 0; i < mOpcode.n; i++, y++) {
        K_ASSERT(I + i < MEMORY_SIZE);
        K_ASSERT(y * FRAMEBUFFER_WIDTH + x < MEMORY_SIZE);

        // Sprite row at 1bpp
        u8 row = mMemory[I + i];
        // Sprite position in memory
        u8* p = &mFrameBuffer[y * FRAMEBUFFER_WIDTH + x];

        // Sprites are clamped at edges
        for (u32 j = 0; j < Min(SPRITE_WIDTH, FRAMEBUFFER_WIDTH - x); j++) {
            // Next pixel is off
            if (!(row & (0b10000000 >> j))) {
                continue;
            }

            VF |= p[j] != 0;
            p[j] ^= 1;
        }
    }
#endif
}

/**
 * @brief Ex9E - SKP Vx
 * @details Skip next instruction if key with the value of Vx is pressed.
 */
void System::Opcode_SKP() {
    // Not all buttons are mapped
    if ((V[mOpcode.x]) >= K_LENGTHOF(scButtonMap)) {
        return;
    }

    u32 mask = scButtonMap[V[mOpcode.x]];

    const kiwi::WiiCtrl& rCtrl =
        kiwi::CtrlMgr::GetInstance().GetWiiCtrl(kiwi::EPlayer_1);

    if (rCtrl.IsConnected() && rCtrl.IsHold(mask)) {
        PC += sizeof(u16);
    }
}

/**
 * @brief Ex9E - SKNP Vx
 * @details Skip next instruction if key with the value of Vx is not pressed.
 */
void System::Opcode_SKNP() {
    // Not all buttons are mapped
    if ((V[mOpcode.x]) >= K_LENGTHOF(scButtonMap)) {
        return;
    }

    u32 mask = scButtonMap[V[mOpcode.x]];

    const kiwi::WiiCtrl& rCtrl =
        kiwi::CtrlMgr::GetInstance().GetWiiCtrl(kiwi::EPlayer_1);

    if (rCtrl.IsConnected() && !rCtrl.IsHold(mask)) {
        PC += sizeof(u16);
    }
}

/**
 * @brief Fx07 - LD Vx, DT
 * @details Set Vx = delay timer value.
 */
void System::Opcode_LD_VX_DT() {
    V[mOpcode.x] = mDelayTimer;
}

/**
 * @brief Fx0A - LD Vx, K
 * @details Wait for a keypress, store the value of the key in Vx.
 */
void System::Opcode_LD_VX_K() {
    // TODO (kiwi): Narrowing happens here!!!
    mWaitKeyPressReg = mOpcode.x;
}

/**
 * @brief Fx15 - LD DT, Vx
 * @details Set delay timer = Vx.
 */
void System::Opcode_LD_DT_VX() {
    mDelayTimer = V[mOpcode.x];
}

/**
 * @brief Fx18 - LD ST, Vx
 * @details Set sound timer = Vx.
 */
void System::Opcode_LD_ST_VX() {
    mSoundTimer = V[mOpcode.x];
}

/**
 * @brief Fx1E - ADD I, Vx
 * @details Set I = I + Vx.
 */
void System::Opcode_ADD_I_VX() {
    I += V[mOpcode.x];
}

/**
 * @brief Fx29 - LD F, Vx
 * @details Set I = location of font sprite for digit Vx.
 */
void System::Opcode_LD_F_VX() {
    K_ASSERT_PTR(mpFont);

    u8 index = V[mOpcode.x];
    K_ASSERT(index >= mpFont->GetMinChar());
    K_ASSERT(index < mpFont->GetMaxChar());

    // Avoid potentially reading memory outside of the emulator
    if (index < mpFont->GetMinChar() || index >= mpFont->GetMaxChar()) {
        I = 0;
        return;
    }

    const u8* pSpriteData = mpFont->GetSpriteData();
    K_ASSERT_PTR(pSpriteData);

    u32 oneSize = mpFont->GetCharWidth() * mpFont->GetBitDepth() *
                  mpFont->GetCharHeight();
    I = mpFont->GetLoadAddr() + index * oneSize;
}

/**
 * @brief Fx33 - LD B, Vx
 * @details Store BCD representation of Vx in memory locations I, I+1, and I+2.
 */
void System::Opcode_LD_B_VX() {
    K_ASSERT(I <= MEMORY_SIZE - 3);

    u32 value = V[mOpcode.x];

    for (int i = 0; i < 3; i++, value /= 10) {
        mMemory[I + (2 - i)] = value % 10;
    }
}

/**
 * @brief Fx55 - LD [I], Vx
 * @details Store registers V0 through Vx in memory starting at location I.
 */
void System::Opcode_LD_I_VX() {
    u32 regNum = mOpcode.x;
    K_ASSERT(I <= MEMORY_SIZE - (regNum - 1));

    for (u32 i = 0; i < regNum; i++) {
        mMemory[I + i] = V[i];
    }
}

/**
 * @brief Fx65 - LD Vx, [I]
 * @details Read registers V0 through Vx from memory starting at location I.
 */
void System::Opcode_LD_VX_I() {
    u32 regNum = mOpcode.x;
    K_ASSERT(I <= MEMORY_SIZE - (regNum - 1));

    for (u32 i = 0; i < regNum; i++) {
        V[i] = mMemory[I + i];
    }
}

} // namespace chip8
} // namespace kiwi
