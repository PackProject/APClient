#ifndef LIBKIWI_CORE_RUNTIME_H
#define LIBKIWI_CORE_RUNTIME_H
#include <libkiwi/k_types.h>
#include <libkiwi/math/kiwiAlgorithm.h>

#include <revolution/OS.h>

//! @addtogroup libkiwi_core
//! @{

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name Linker Generated Symbols (for your module)
 */
/**@{*/
extern funcptr_t __ctor_loc;
extern funcptr_t __ctor_end;

extern u8 _f_init[];
extern u8 _e_init[];

extern u8 _f_text[];
extern u8 _e_text[];

extern u8 _f_ctors[];
extern u8 _e_ctors[];

extern u8 _f_dtors[];
extern u8 _e_dtors[];

extern u8 _f_rodata[];
extern u8 _e_rodata[];

extern u8 _f_data[];
extern u8 _e_data[];
/**@}*/

/**
 * @name Linker Generated Symbols (for the base DOL)
 */
/**@{*/
extern u8 _f_dol_init[];
extern u8 _e_dol_init[];

extern u8 _f_dol_text[];
extern u8 _e_dol_text[];

extern u8 _f_dol_ctors[];
extern u8 _e_dol_ctors[];

extern u8 _f_dol_dtors[];
extern u8 _e_dol_dtors[];

extern u8 _f_dol_rodata[];
extern u8 _e_dol_rodata[];

extern u8 _f_dol_data[];
extern u8 _e_dol_data[];

extern u8 _stack_addr[];
extern u8 _stack_end[];
/**@}*/

#ifdef __cplusplus
}
#endif

//! @}

namespace kiwi {
//! @addtogroup libkiwi_core
//! @{

namespace {
//! @addtogroup libkiwi_core
//! @{

/**
 * @brief Gets the start address of the stack
 * @note Stack grows upwards
 */
K_INLINE const void* GetStackStart() {
    return _stack_addr;
}
/**
 * @brief Gets the end address of the stack
 * @note Stack grows upwards
 */
K_INLINE const void* GetStackEnd() {
    return _stack_end;
}

/**
 * @name Module section information
 */
/**@{*/
/**
 * @brief Gets the start address of the module ELF
 */
K_INLINE const void* GetModuleStart() {
    return kokeshi::CURRENT_MODULE.start;
}
/**
 * @brief Gets the size of the module ELF
 */
K_INLINE u32 GetModuleSize() {
    return kokeshi::CURRENT_MODULE.size;
}
/**
 * @brief Gets the end address of the module ELF
 */
K_INLINE const void* GetModuleEnd() {
    return AddToPtr(GetModuleStart(), GetModuleSize());
}

/**
 * @brief Gets the start address of the .init ELF section
 */
K_INLINE const void* GetModuleInitStart() {
    return _f_init;
}
/**
 * @brief Gets the end address of the .init ELF section
 */
K_INLINE const void* GetModuleInitEnd() {
    return _e_init;
}
/**
 * @brief Gets the size of the .init ELF section
 */
K_INLINE u32 GetModuleInitSize() {
    return PtrDistance(GetModuleInitStart(), GetModuleInitEnd());
}

/**
 * @brief Gets the start address of the .text ELF section
 */
K_INLINE const void* GetModuleTextStart() {
    return _f_text;
}
/**
 * @brief Gets the end address of the .text ELF section
 */
K_INLINE const void* GetModuleTextEnd() {
    return _e_text;
}
/**
 * @brief Gets the size of the .text ELF section
 */
K_INLINE u32 GetModuleTextSize() {
    return PtrDistance(GetModuleTextStart(), GetModuleTextEnd());
}

/**
 * @brief Gets the start address of the .ctors ELF section
 */
K_INLINE const void* GetModuleCtorsStart() {
    return _f_ctors;
}
/**
 * @brief Gets the end address of the .ctors ELF section
 */
K_INLINE const void* GetModuleCtorsEnd() {
    return _e_ctors;
}
/**
 * @brief Gets the size of the .ctors ELF section
 */
K_INLINE u32 GetModuleCtorsSize() {
    return PtrDistance(GetModuleCtorsStart(), GetModuleCtorsEnd());
}

/**
 * @brief Gets the start address of the .dtors ELF section
 */
K_INLINE const void* GetModuleDtorsStart() {
    return _f_dtors;
}
/**
 * @brief Gets the end address of the .dtors ELF section
 */
K_INLINE const void* GetModuleDtorsEnd() {
    return _e_dtors;
}
/**
 * @brief Gets the size of the .dtors ELF section
 */
K_INLINE u32 GetModuleDtorsSize() {
    return PtrDistance(GetModuleDtorsStart(), GetModuleDtorsEnd());
}

/**
 * @brief Gets the start address of the .rodata ELF section
 */
K_INLINE const void* GetModuleRodataStart() {
    return _f_rodata;
}
/**
 * @brief Gets the end address of the .rodata ELF section
 */
K_INLINE const void* GetModuleRodataEnd() {
    return _e_rodata;
}
/**
 * @brief Gets the size of the .rodata ELF section
 */
K_INLINE u32 GetModuleRodataSize() {
    return PtrDistance(GetModuleRodataStart(), GetModuleRodataEnd());
}

/**
 * @brief Gets the start address of the .data ELF section
 */
K_INLINE const void* GetModuleDataStart() {
    return _f_data;
}
/**
 * @brief Gets the end address of the .data ELF section
 */
K_INLINE const void* GetModuleDataEnd() {
    return _e_data;
}
/**
 * @brief Gets the size of the .data ELF section
 */
K_INLINE u32 GetModuleDataSize() {
    return PtrDistance(GetModuleDataStart(), GetModuleDataEnd());
}
/**@}*/

/**
 * @name DOL section information
 */
/**@{*/
/**
 * @brief Gets the start address of the .init DOL section
 */
K_INLINE const void* GetDolInitStart() {
    return _f_dol_init;
}
/**
 * @brief Gets the end address of the .init DOL section
 */
K_INLINE const void* GetDolInitEnd() {
    return _e_dol_init;
}
/**
 * @brief Gets the size of the .init DOL section
 */
K_INLINE u32 GetDolInitSize() {
    return PtrDistance(GetDolInitStart(), GetDolInitEnd());
}

/**
 * @brief Gets the start address of the .text DOL section
 */
K_INLINE const void* GetDolTextStart() {
    return _f_dol_text;
}
/**
 * @brief Gets the end address of the .text DOL section
 */
K_INLINE const void* GetDolTextEnd() {
    return _e_dol_text;
}
/**
 * @brief Gets the size of the .text DOL section
 */
K_INLINE u32 GetDolTextSize() {
    return PtrDistance(GetDolTextStart(), GetDolTextEnd());
}

/**
 * @brief Gets the start address of the .ctors DOL section
 */
K_INLINE const void* GetDolCtorsStart() {
    return _f_dol_ctors;
}
/**
 * @brief Gets the end address of the .ctors DOL section
 */
K_INLINE const void* GetDolCtorsEnd() {
    return _e_dol_ctors;
}
/**
 * @brief Gets the size of the .ctors DOL section
 */
K_INLINE u32 GetDolCtorsSize() {
    return PtrDistance(GetDolCtorsStart(), GetDolCtorsEnd());
}

/**
 * @brief Gets the start address of the .dtors DOL section
 */
K_INLINE const void* GetDolDtorsStart() {
    return _f_dol_dtors;
}
/**
 * @brief Gets the end address of the .dtors DOL section
 */
K_INLINE const void* GetDolDtorsEnd() {
    return _e_dol_dtors;
}
/**
 * @brief Gets the size of the .dtors DOL section
 */
K_INLINE u32 GetDolDtorsSize() {
    return PtrDistance(GetDolDtorsStart(), GetDolDtorsEnd());
}

/**
 * @brief Gets the start address of the .rodata DOL section
 */
K_INLINE const void* GetDolRodataStart() {
    return _f_dol_rodata;
}
/**
 * @brief Gets the end address of the .rodata DOL section
 */
K_INLINE const void* GetDolRodataEnd() {
    return _e_dol_rodata;
}
/**
 * @brief Gets the size of the .rodata DOL section
 */
K_INLINE u32 GetDolRodataSize() {
    return PtrDistance(GetDolRodataStart(), GetDolRodataEnd());
}

/**
 * @brief Gets the start address of the .data DOL section
 */
K_INLINE const void* GetDolDataStart() {
    return _f_dol_data;
}
/**
 * @brief Gets the end address of the .data DOL section
 */
K_INLINE const void* GetDolDataEnd() {
    return _e_dol_data;
}
/**
 * @brief Gets the size of the .data DOL section
 */
K_INLINE u32 GetDolDataSize() {
    return PtrDistance(GetDolDataStart(), GetDolDataEnd());
}
/**@}*/

//! @}
} // namespace

//! @}
} // namespace kiwi

#endif
