#include <libkiwi.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Header for dynamically allocated arrays generated by CodeWarrior
 */
struct NewArrayHeader {
    /* 0x0 */ u32 size;
    /* 0x4 */ u32 count;
    /* 0x8 */ u8 padding[0x10 - 0x8];
};

/**
 * @brief Signed short argument for destructors generated by CodeWarrior
 */
enum DestructorType {
    DestructorType_AllBases = -1,   // Destroy all bases
    DestructorType_NonVirtualBases, // Destory all non-virtual bases
    DestructorType_All              // Destroy all bases and delete object
};

// Destructor function signature
typedef void (*Destructor)(void* obj, s16 type);

/**
 * @brief Destroy a dynamically allocated array
 *
 * @param array Array
 * @param dtor Destructor for each element
 */
void __destroy_new_array(u8* array, Destructor dtor) {
    if (array == nullptr) {
        return;
    }

    // Header placed before contents
    const NewArrayHeader* header =
        reinterpret_cast<NewArrayHeader*>(array - sizeof(NewArrayHeader));

    if (dtor != nullptr) {
        u32 size = header->size;
        u32 count = header->count;

        // Destroyed in reverse order
        u8* obj = array + (size * count);

        // Destroy all elements
        for (u32 i = 0; i < count; i++) {
            obj -= size;
            dtor(obj, DestructorType_AllBases);
        }
    }

    // Free base memory
    delete[] (array - sizeof(NewArrayHeader));
}

/**
 * @brief Convert s64 to f64
 */
asm void __cvt_sll_dbl() {
    // clang-format off
    stwu       r1,-0x10(r1)
    rlwinm.    r5,r3,0x0,0x0,0x0
    beq        lbl_803007a8
    subfic     r4,r4,0x0
    subfze     r3,r3
lbl_803007a8:
    or.        r7,r3,r4
    li         r6,0x0
    beq        lbl_80300830
    cntlzw     r7,r3
    cntlzw     r8,r4
    rlwinm     r9,r7,0x1a,0x0,0x4
    srawi      r9,r9,0x1f
    and        r9,r9,r8
    add        r7,r7,r9
    subfic     r8,r7,0x20
    subic      r9,r7,0x20
    slw        r3,r3,r7
    srw        r10,r4,r8
    or         r3,r3,r10
    slw        r10,r4,r9
    or         r3,r3,r10
    slw        r4,r4,r7
    subf       r6,r7,r6
    rlwinm     r7,r4,0x0,0x15,0x1f
    cmpwi      r7,0x400
    addi       r6,r6,0x43e
    blt        lbl_80300818
    bgt        lbl_8030080c
    rlwinm.    r7,r4,0x0,0x14,0x14
    beq        lbl_80300818
lbl_8030080c:
    addic      r4,r4,0x800
    addze      r3,r3
    addze      r6,r6
lbl_80300818:
    rlwinm     r4,r4,0x15,0x0,0x1f
    rlwimi     r4,r3,0x15,0x0,0xa
    rlwinm     r3,r3,0x15,0xc,0x1f
    rlwinm     r6,r6,0x14,0x0,0xb
    or         r3,r6,r3
    or         r3,r5,r3
lbl_80300830:
    stw        r3,0x8(r1)
    stw        r4,0xc(r1)
    lfd        f1,0x8(r1)
    addi       r1,r1,0x10
    blr
    // clang-format on
}

/**
 * @brief Convert u64 to f64
 */
asm void __cvt_ull_dbl() {
    // clang-format off
    stwu       r1,-0x10(r1)
    or.        r7,r3,r4
    li         r6,0x0
    beq        lbl_80059700
    cntlzw     r7,r3
    cntlzw     r8,r4
    rlwinm     r9,r7,0x1a,0x0,0x4
    srawi      r9,r9,0x1f
    and        r9,r9,r8
    add        r7,r7,r9
    subfic     r8,r7,0x20
    subic      r9,r7,0x20
    slw        r3,r3,r7
    srw        r10,r4,r8
    or         r3,r3,r10
    slw        r10,r4,r9
    or         r3,r3,r10
    slw        r4,r4,r7
    subf       r6,r7,r6
    rlwinm     r7,r4,0x0,0x15,0x1f
    cmpwi      r7,0x400
    addi       r6,r6,0x43e
    blt        lbl_800596ec
    bgt        lbl_800596e0
    rlwinm.    r7,r4,0x0,0x14,0x14
    beq        lbl_800596ec
lbl_800596e0:
    addic      r4,r4,0x800
    addze      r3,r3
    addze      r6,r6
lbl_800596ec:
    rlwinm     r4,r4,0x15,0x0,0x1f
    rlwimi     r4,r3,0x15,0x0,0xa
    rlwinm     r3,r3,0x15,0xc,0x1f
    rlwinm     r6,r6,0x14,0x0,0xb
    or         r3,r6,r3
lbl_80059700:
    stw        r3,0x8(r1)
    stw        r4,0xC(r1)
    lfd        f1,0x8(r1)
    addi       r1,r1,0x10
    blr
    // clang-format on
}

/**
 * @brief Convert s64 to f32
 */
asm void __cvt_sll_flt() {
    // clang-format off
    stwu r1, -0x10(r1)
    rlwinm. r5, r3, 0, 0, 0
    beq lbl_80322DB4
    subfic r4, r4, 0
    subfze r3, r3
lbl_80322DB4:
    or. r7, r3, r4
    li r6, 0
    beq lbl_80322E3C
    cntlzw r7, r3
    cntlzw r8, r4
    rlwinm r9, r7, 0x1a, 0, 4
    srawi r9, r9, 0x1f
    and r9, r9, r8
    add r7, r7, r9
    subfic r8, r7, 0x20
    addic r9, r7, -32
    slw r3, r3, r7
    srw r10, r4, r8
    or r3, r3, r10
    slw r10, r4, r9
    or r3, r3, r10
    slw r4, r4, r7
    subf r6, r7, r6
    clrlwi r7, r4, 0x15
    cmpwi r7, 0x400
    addi r6, r6, 0x43e
    blt lbl_80322E24
    bgt lbl_80322E18
    rlwinm. r7, r4, 0, 0x14, 0x14
    beq lbl_80322E24
lbl_80322E18:
    addic r4, r4, 0x800
    addze r3, r3
    addze r6, r6
lbl_80322E24:
    rotlwi r4, r4, 0x15
    rlwimi r4, r3, 0x15, 0, 0xa
    rlwinm r3, r3, 0x15, 0xc, 0x1f
    slwi r6, r6, 0x14
    or r3, r6, r3
    or r3, r5, r3
lbl_80322E3C:
    stw r3, 8(r1)
    stw r4, 0xc(r1)
    lfd f1, 8(r1)
    frsp f1, f1
    addi r1, r1, 0x10
    blr
    // clang-format on
}

/**
 * @brief Convert u64 to f32
 */
asm void __cvt_ull_flt() {
    // clang-format off
    stwu       r1,-0x10(r1)
    or.        r7,r3,r4
    li         r6,0x0
    beq        lbl_80059850
    cntlzw     r7,r3
    cntlzw     r8,r4
    rlwinm     r9,r7,0x1a,0x0,0x4
    srawi      r9,r9,0x1f
    and        r9,r9,r8
    add        r7,r7,r9
    subfic     r8,r7,0x20
    subic      r9,r7,0x20
    slw        r3,r3,r7
    srw        r10,r4,r8
    or         r3,r3,r10
    slw        r10,r4,r9
    or         r3,r3,r10
    slw        r4,r4,r7
    subf       r6,r7,r6
    rlwinm     r7,r4,0x0,0x15,0x1f
    cmpwi      r7,0x400
    addi       r6,r6,0x43e
    blt        lbl_8005983c
    bgt        lbl_80059830
    rlwinm.    r7,r4,0x0,0x14,0x14
    beq        lbl_8005983c
lbl_80059830:
    addic      r4,r4,0x800
    addze      r3,r3
    addze      r6,r6
lbl_8005983c:
    rlwinm     r4,r4,0x15,0x0,0x1f
    rlwimi     r4,r3,0x15,0x0,0xa
    rlwinm     r3,r3,0x15,0xc,0x1f
    rlwinm     r6,r6,0x14,0x0,0xb
    or         r3,r6,r3
lbl_80059850:
    stw        r3,0x8(r1)
    stw        r4,0xC(r1)
    lfd        f1,0x8(r1)
    frsp       f1,f1
    addi       r1,r1,0x10
    blr
    // clang-format on
}

/**
 * @brief Convert f64 to u64
 */
asm void __cvt_dbl_usll() {
    // clang-format off
    stwu r1, -0x10(r1)
    stfd f1, 8(r1)
    lwz r3, 8(r1)
    lwz r4, 0xc(r1)
    rlwinm r5, r3, 0xc, 0x15, 0x1f
    cmplwi r5, 0x3ff
    bge lbl_80322E7C
    li r3, 0
    li r4, 0
    b lbl_80322F18
lbl_80322E7C:
    mr r6, r3
    clrlwi r3, r3, 0xc
    oris r3, r3, 0x10
    addi r5, r5, -1075
    cmpwi r5, 0
    bge lbl_80322EBC
    neg r5, r5
    subfic r8, r5, 0x20
    addic r9, r5, -32
    srw r4, r4, r5
    slw r10, r3, r8
    or r4, r4, r10
    srw r10, r3, r9
    or r4, r4, r10
    srw r3, r3, r5
    b lbl_80322F08
lbl_80322EBC:
    cmpwi r5, 0xa
    ble+ lbl_80322EE8
    rlwinm. r6, r6, 0, 0, 0
    beq lbl_80322ED8
    lis r3, 0x8000
    li r4, 0
    b lbl_80322F18
lbl_80322ED8:
    lis r3, 0x7FFFFFFF@h
    ori r3, r3, 0x7FFFFFFF@l
    li r4, -1
    b lbl_80322F18
lbl_80322EE8:
    subfic r8, r5, 0x20
    addic r9, r5, -32
    slw r3, r3, r5
    srw r10, r4, r8
    or r3, r3, r10
    slw r10, r4, r9
    or r3, r3, r10
    slw r4, r4, r5
lbl_80322F08:
    rlwinm. r6, r6, 0, 0, 0
    beq lbl_80322F18
    subfic r4, r4, 0
    subfze r3, r3
lbl_80322F18:
    addi r1, r1, 0x10
    blr
    // clang-format on
}

/**
 * @brief Null PTMF constant
 */
u8 __ptmf_null[0xC] = {};

#ifdef __cplusplus
}
#endif
