#ifndef RVL_SDK_KPAD_H
#define RVL_SDK_KPAD_H
#include <types.h>

#include <revolution/MTX.h>
#ifdef __cplusplus
extern "C" {
#endif

#define KPAD_MAX_SAMPLES 16

typedef enum {
    KPAD_RESULT_OK = 0,
} KPADResult;

typedef enum {
    KPAD_CHAN_0,
    KPAD_CHAN_1,
    KPAD_CHAN_2,
    KPAD_CHAN_3,
    KPAD_MAX_CONTROLLERS
} KPADChan;

typedef enum {
    KPAD_BTN_DLEFT = (1 << 0),
    KPAD_BTN_DRIGHT = (1 << 1),
    KPAD_BTN_DDOWN = (1 << 2),
    KPAD_BTN_DUP = (1 << 3),

    KPAD_BTN_PLUS = (1 << 4),
    KPAD_BTN_MINUS = (1 << 12),

    KPAD_BTN_1 = (1 << 9),
    KPAD_BTN_2 = (1 << 8),

    KPAD_BTN_A = (1 << 11),
    KPAD_BTN_B = (1 << 10),

    KPAD_BTN_HOME = (1 << 15),
} KPADButton;

typedef union KPADEXStatus {
    // Wii Remote ("free style")
    struct {
        Vec2 stick;    // at 0x0
        Vec acc;       // at 0x8
        f32 acc_value; // at 0x14
        f32 acc_speed; // at 0x18
    } fs;              // at 0x0

    struct {
        u32 hold;     // at 0x0
        u32 trig;     // at 0x4
        u32 release;  // at 0x8
        Vec2 lstick;  // at 0xC
        Vec2 rstick;  // at 0x14
        f32 ltrigger; // at 0x1C
        f32 rtrigger; // at 0x20
    } cl;             // at 0x0

#if defined(PACK_RESORT)
    struct {
        f64 tgc_weight;     // at 0x0
        f64 weight[4];      // at 0x8
        f64 weight_ave[4];  // at 0x28
        s32 weight_err;     // at 0x48
        s32 tgc_weight_err; // at 0x4C
    } bl;
#endif
} KPADEXStatus;

typedef struct KPADStatus {
    u32 hold;               // at 0x0
    u32 trig;               // at 0x4
    u32 release;            // at 0x8
    Vec acc;                // at 0xC
    f32 acc_value;          // at 0x18
    f32 acc_speed;          // at 0x1C
    Vec2 pos;               // at 0x20
    Vec2 vec;               // at 0x28
    f32 speed;              // at 0x30
    Vec2 horizon;           // at 0x34
    Vec2 hori_vec;          // at 0x3C
    f32 hori_speed;         // at 0x44
    f32 dist;               // at 0x48
    f32 dist_vec;           // at 0x4C
    f32 dist_speed;         // at 0x50
    Vec2 acc_vertical;      // at 0x54
    u8 dev_type;            // at 0x5C
    s8 wpad_err;            // at 0x5D
    s8 dpd_valid_fg;        // at 0x5E
    u8 data_format;         // at 0x5F
    KPADEXStatus ex_status; // at 0x60
#if defined(PACK_RESORT)
    Vec mpls_rot;     // at 0xB0
    Vec unkBC;        // at 0xBC
    Vec mpls_basis_x; // at 0xC8
    Vec mpls_basis_y; // at 0xD4
    Vec mpls_basis_z; // at 0xE0
    u32 unkEC;
#endif
} KPADStatus;

void KPADSetBtnRepeat(s32 chan, f32, f32);

void KPADSetPosParam(s32 chan, f32 playRadius, f32 sensitivity);
void KPADSetHoriParam(s32 chan, f32 playRadius, f32 sensitivity);
void KPADSetDistParam(s32 chan, f32 playRadius, f32 sensitivity);
void KPADSetAccParam(s32 chan, f32 playRadius, f32 sensitivity);

s32 KPADRead(s32 chan, KPADStatus* pSamples, s32 numSamples);

void KPADInit(void);

#ifdef __cplusplus
}
#endif
#endif
