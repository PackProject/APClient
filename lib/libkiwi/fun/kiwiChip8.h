#ifndef LIBKIWI_FUN_CHIP8_H
#define LIBKIWI_FUN_CHIP8_H
#include <libkiwi/core/kiwiColor.h>
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiOptional.h>

#include <revolution/GX.h>
#include <revolution/OS.h>

namespace kiwi {
//! @addtogroup libkiwi_fun
//! @{
namespace chip8 {
//! @addtogroup libkiwi_fun
//! @{

/******************************************************************************
 *
 * Font
 *
 ******************************************************************************/

/**
 * @brief Font interface
 */
class IFont {
public:
    /**
     * @brief Destructor
     */
    virtual ~IFont() {}

    /**
     * @brief Gets the width (in pixels) of font characters
     */
    virtual u16 GetCharWidth() const {
        return 8;
    }
    /**
     * @brief Gets the height (in pixels) of font characters
     */
    virtual u16 GetCharHeight() const {
        return 5;
    }

    /**
     * @brief Gets the minimum supported character index
     */
    virtual u8 GetMinChar() const {
        return 0x00;
    }
    /**
     * @brief Gets the maximum supported character index
     */
    virtual u8 GetMaxChar() const {
        return 0x0F;
    }

    /**
     * @brief Gets the number of bits per pixel
     */
    virtual u8 GetBitDepth() const {
        return 1;
    }

    /**
     * @brief Gets the destination address in CHIP-8 memory
     */
    virtual u16 GetLoadAddr() const {
        return 0;
    }

    /**
     * @brief Gets the font sprite data
     */
    virtual const u8* GetSpriteData() = 0;
    /**
     * @brief Gets the size of the font sprite data
     */
    virtual const u32 GetSpriteDataSize();
};

/**
 * @brief Default ROM font
 */
class DefaultFont : public IFont {
public:
    /**
     * @brief Gets the font sprite data
     */
    virtual const u8* GetSpriteData() {
        return scSpriteData;
    }

private:
    //! Font sprite data
    static const u8 scSpriteData[];
};

/******************************************************************************
 *
 * Renderer
 *
 ******************************************************************************/

/**
 * @brief Renderer interface
 */
class IRenderer {
public:
    /**
     * @brief Rendering context
     */
    struct Arg {
        const u8* pBuffer; //!< Framebuffer (1bpp)
        u32 width;         //!< Display width
        u32 height;        //!< Display height

        Color off; //!< 'Off' pixel color
        Color on;  //!< 'On' pixel color
    };

private:
    //! Defauly Chip-8 pixel size
    static const u32 DEFAULT_PIXEL_SIZE = 8;

public:
    /**
     * @brief Constructor
     */
    IRenderer() : mPixelSize(DEFAULT_PIXEL_SIZE) {}

    /**
     * @brief Destructor
     */
    virtual ~IRenderer() {}

    /**
     * @brief Draws the emulator framebuffer
     *
     * @param rArg Rendering context
     */
    virtual void Draw(const Arg& rArg) = 0;

    /**
     * @brief Sets the size of Chip-8 pixels
     *
     * @param size Pixel size
     */
    void SetPixelSize(u8 size) {
        mPixelSize = size;
    }

protected:
    //! Chip-8 pixel size
    u8 mPixelSize;
};

/**
 * @brief GX renderer
 */
class GXRenderer : public IRenderer {
public:
    /**
     * @brief Constructor
     */
    GXRenderer();
    /**
     * @brief Destructor
     */
    virtual ~GXRenderer();

    /**
     * @brief Draws the emulator framebuffer
     *
     * @param rArg Rendering context
     */
    virtual void Draw(const Arg& rArg);

private:
    //! CI8 texture block width, in pixels
    static const u32 CI8_BLOCK_WIDTH = 8;
    //! CI8 texture block height, in pixels
    static const u32 CI8_BLOCK_HEIGHT = 4;

    //! 2 palette entries ('on'/'off' pixel color)
    static const u32 PALETTE_ENTRY_NUM = 2;

private:
    /**
     * @brief Creates CI8 texture data from the Chip-8 framebuffer
     *
     * @param rArg Rendering context
     */
    void CreateTexture(const Arg& rArg);

    /**
     * @brief Creates RGB565 palette data from the Chip-8 framebuffer
     *
     * @param rArg Rendering context
     */
    void CreatePalette(const Arg& rArg);

private:
    //! Texture data
    u8* mpTexture;
    //! Texture data size
    u32 mTextureSize;

    //! Palette data
    u8* mpPalette;

    //! GX texture object
    GXTexObj mTexObj;
    //! GX palette object
    GXTlutObj mTlutObj;
};

/******************************************************************************
 *
 * System
 *
 ******************************************************************************/

/**
 * @brief Emulator system
 */
class System {
    //! Number of general purpose registers
    static const u32 VREG_NUM = 16;

    /**
     * @brief Illegal instruction handler
     * @note This is useful for catching user-defined opcodes.
     *
     * @param opcode Illegal instruction opcode
     * @param V Register state (mutable)
     */
    typedef void (*IllegalInstCallback)(u16 opcode, u8 V[VREG_NUM]);

public:
    /**
     * @brief Constructor
     *
     * @param pRenderer Renderer
     */
    System(IRenderer* pRenderer);

    /**
     * @brief Destructor
     */
    ~System();

    /**
     * @brief Resets the emulator state
     * @note This does not re-load the ROM.
     */
    void Reset();

    /**
     * @brief Performs one frame of execution
     */
    void Calculate();

    /**
     * @brief Draws the latest frame
     */
    void Draw();

    /**
     * @brief Loads a ROM binary
     *
     * @param pBinary Binary data
     * @param binarySize Binary data size
     */
    void LoadROM(const void* pBinary, u32 binarySize);

    /**
     * @brief Loads the test ROM binary
     */
    void LoadTestROM();

    /**
     * @brief Sets the emulator renderer
     *
     * @param pRenderer New renderer
     */
    void SetRenderer(IRenderer* pRenderer) {
        K_ASSERT_PTR(pRenderer);
        mpRenderer = pRenderer;
    }

    /**
     * @brief Sets the emulator font
     *
     * @param pFont New font
     */
    void SetFont(IFont* pFont) {
        K_ASSERT_PTR(pFont);
        mpFont = pFont;
    }

    /**
     * @brief Sets the illegal instruction callback
     * @details Supply NULL to switch back to the default callback.
     * @note This is useful for catching user-defined opcodes.
     *
     * @param pCallback Callback function
     */
    void SetIllegalInstCallback(IllegalInstCallback pCallback) {
        mpIllegalInstCallback =
            pCallback != nullptr ? pCallback : DefaultIllegalInstCallback;
    }

    /**
     * @brief Sets the emulator clock speed, in Hz
     *
     * @param clockSpeed New clock speed (Hz)
     */
    void SetClockSpeed(u32 clockSpeed) {
        mClockSpeed = clockSpeed;
    }

    /**
     * @brief Sets the emulator color palette
     *
     * @param off 'Off' pixel color
     * @param on 'On' pixel color
     */
    void SetColorPalette(Color off, Color on) {
        mOffColor = off;
        mOnColor = on;
    }

private:
    /**
     * @brief Opcode handler function
     */
    typedef void (System::*OpcodeFunc)();

    //! Sprite width, in pixels
    static const u32 SPRITE_WIDTH = 8;

    //! RAM size
    static const u32 MEMORY_SIZE = OS_MEM_KB_TO_B(4);
    //! Font location in RAM
    static const u32 FONT_ADDR = 0x000;
    //! ROM location in RAM
    static const u32 PROG_ADDR = 0x200;

    //! Framebuffer width
    static const u32 FRAMEBUFFER_WIDTH = 64;
    //! Framebuffer height
    static const u32 FRAMEBUFFER_HEIGHT = 32;

    //! Framebuffer size
    static const u32 FRAMEBUFFER_SIZE =
        FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT /* / 8 */;

    //! Stack memory size
    static const u32 STACK_SIZE = OS_MEM_KB_TO_B(1);
    //! Stack array length
    static const u32 STACK_LENGTH = STACK_SIZE / sizeof(u16);

    //! Default clock speed, in Hz
    static const u32 DEFAULT_CLOCK_SPEED = 700;

private:
    /**
     * @brief Performs the amount of CPU cycles corresponding to the specified
     * time duration
     *
     * @param dt Delta time
     */
    void Update(f32 dt) {
        Update(static_cast<u32>(mClockSpeed * dt));
    }

    /**
     * @brief Performs the specified amount of CPU cycles
     *
     * @param cycles Cycle count
     */
    void Update(u32 cycles);

    /**
     * @brief Updates waiting for keypress state
     */
    void CalculateWaitKey();

    /**
     * @brief Default illegal instruction callback
     *
     * @param opcode Illegal instruction opcode
     * @param V Register state (mutable)
     */
    static void DefaultIllegalInstCallback(u16 opcode, u8 V[VREG_NUM]);

    /**
     * @name Opcode group functions
     */
    /**@{*/
    void Opcode_0XXX();
    void Opcode_8XXX();
    void Opcode_EXXX();
    void Opcode_FXXX();
    /**@}*/

    /**
     * @name Opcode handler functions
     */
    /**@{*/
    void Opcode_Illegal();
    void Opcode_CLS();
    void Opcode_RET();
    void Opcode_JP_NNN();
    void Opcode_CALL_NNN();
    void Opcode_SE_VX_KK();
    void Opcode_SNE_VX_KK();
    void Opcode_SE_VX_VY();
    void Opcode_LD_VX_KK();
    void Opcode_ADD_VX_KK();
    void Opcode_LD_VX_VY();
    void Opcode_OR();
    void Opcode_AND();
    void Opcode_XOR();
    void Opcode_ADD_VX_VY();
    void Opcode_SUB();
    void Opcode_SHR();
    void Opcode_SUBN();
    void Opcode_SHL();
    void Opcode_SNE_VX_VY();
    void Opcode_LD_I_NNN();
    void Opcode_JP_V0_NNN();
    void Opcode_RND();
    void Opcode_DRW();
    void Opcode_SKP();
    void Opcode_SKNP();
    void Opcode_LD_VX_DT();
    void Opcode_LD_VX_K();
    void Opcode_LD_DT_VX();
    void Opcode_LD_ST_VX();
    void Opcode_ADD_I_VX();
    void Opcode_LD_F_VX();
    void Opcode_LD_B_VX();
    void Opcode_LD_I_VX();
    void Opcode_LD_VX_I();
    /**@}*/

private:
    //! Random number generator
    Random mRandom;

    //! Renderer
    IRenderer* mpRenderer;
    //! System font
    IFont* mpFont;

    //! Illegal instruction callback
    IllegalInstCallback mpIllegalInstCallback;

    //! Clock speed, in Hz
    u32 mClockSpeed;
    //! Previous tick OSTick
    Optional<u32> mPrevOSTick;

    //! 'Off' pixel color
    Color mOffColor;
    //! 'On' pixel color
    Color mOnColor;

    //! Memory space
    u8 mMemory[MEMORY_SIZE];
    //! Display framebuffer
    u8 mFrameBuffer[FRAMEBUFFER_SIZE];

    //! Current opcode
    union {
        //! Entire value
        u16 raw;

        //! nnn/addr nibbles
        struct {
            u16 type : 4;
            u16 nnn : 12;
        };

        //! x/y/n nibbles
        struct {
            u16 _1 : 4;
            u16 x : 4;
            u16 y : 4;
            u16 n : 4;
        };

        //! kk/byte nibbles
        struct {
            u16 _2 : 8;
            u16 kk : 8;
        };
    } mOpcode;

    //! General purpose registers
    union {
        u8 V[VREG_NUM];

        //! 'VF' alias for last register
        struct {
            u8 _[VREG_NUM - 1];
            u8 VF;
        };
    };

    //! Index register
    u16 I;
    //! Program counter
    u16 PC;

    //! Stack memory
    u16 mStack[STACK_LENGTH];
    //! Stack pointer
    u16 SP;

    //! 60Hz delay timer
    u8 mDelayTimer;
    //! Sound/beeping timer
    u8 mSoundTimer;

    //! Register which is stalling execution for a keypress
    Optional<u8> mWaitKeyPressReg;

private:
    //! Opcode group handler functions
    static const OpcodeFunc scOpcodeGroupFuncs[];

    //! Keyboard button map
    static const u32 scButtonMap[];

    //! Corax+ test ROM
    static const u8 scTestRom[];
};

//! @}
} // namespace chip8
//! @}
} // namespace kiwi

#endif
