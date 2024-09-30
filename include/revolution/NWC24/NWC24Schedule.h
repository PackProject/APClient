#ifndef RVL_SDK_NWC24_SCHEDULE_H
#define RVL_SDK_NWC24_SCHEDULE_H
#include <revolution/NWC24/NWC24Schedule.h>
#include <revolution/NWC24/NWC24Types.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

//! @addtogroup rvl_nwc24
//! @{

s32 NWC24SuspendScheduler(void);
s32 NWC24ResumeScheduler(void);
NWC24Err NWC24iRequestGenerateUserId(u64* idOut, u32* arg1);
NWC24Err NWC24iTrySuspendForOpenLib(void);
NWC24Err NWC24iResumeForCloseLib(void);

//! @}

#ifdef __cplusplus
}
#endif
#endif
