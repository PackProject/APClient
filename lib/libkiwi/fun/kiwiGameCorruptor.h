#ifndef LIBKIWI_FUN_GAME_CORRUPTOR_H
#define LIBKIWI_FUN_GAME_CORRUPTOR_H
#include <Pack/RPSystem.h>
#include <libkiwi/k_types.h>
#include <libkiwi/util/kiwiDynamicSingleton.h>

#include <egg/core.h>

#include <revolution/OS.h>

namespace kiwi {
//! @addtogroup libkiwi_fun
//! @{

/**
 * @brief Corruption domain
 */
enum ECorruptDomain {
    ECorruptDomain_DolCode = (1 << 0), //!< Corrupt DOL code sections
    ECorruptDomain_DolData = (1 << 1), //!< Corrupt DOL data sections

    ECorruptDomain_Mem1 = (1 << 2), //!< Corrupt MEM1 region of RAM
    ECorruptDomain_Mem2 = (1 << 3), //!< Corrupt MEM2 region of RAM

    ECorruptDomain_Scene = (1 << 4), //!< Corrupt the current scene's memory
};

/**
 * @brief Real-time code/memory corruptor
 */
class GameCorruptor : public DynamicSingleton<GameCorruptor> {
    friend class DynamicSingleton<GameCorruptor>;

public:
    /**
     * @brief Sets the interval between corruptions
     *
     * @param seconds Interval time, in seconds
     */
    void SetInterval(u32 seconds) {
        K_ASSERT(seconds > 0);
        mInterval = seconds;
    }

    /**
     * @brief Sets the allowed corruption domain(s)
     * @see ECorruptDomain
     *
     * @param flags Bitmask of domains to allow
     */
    void SetCorruptDomain(u32 flags) {
        mDomainFlag = flags;
    }

    /**
     * @brief Sets the number of instructions/data pieces to corrupt
     *
     * @param num Number of points to corrupt
     */
    void SetCorruptNum(u32 num) {
        mCorruptNum = num;
    }

    /**
     * @brief Begins the corruption process
     */
    void Begin();

private:
    /**
     * @brief Constructor
     */
    GameCorruptor();
    /**
     * @brief Destructor
     */
    virtual ~GameCorruptor();

    /**
     * @brief Performs one corruption cycle
     */
    void Corrupt() const;

    /**
     * @brief Corrupts some code instructions in the specified range
     *
     * @param pBegin Beginning of range
     * @param pEnd End of range
     */
    void CorruptCode(const void* pBegin, const void* pEnd) const;

    /**
     * @brief Corrupts some pieces of data in the specified range
     *
     * @param pBegin Beginning of range
     * @param pEnd End of range
     */
    void CorruptData(const void* pBegin, const void* pEnd) const;

    /**
     * @brief Corrupts some pieces of data in the specified heap
     *
     * @param pHeap Heap to corrupt
     */
    void CorruptData(EGG::Heap* pHeap) const;

    /**
     * @brief Corruption alarm handler
     *
     * @param pAlarm OS alarm
     * @param pCtx Alarm context
     */
    static void AlarmHandler(OSAlarm* pAlarm, OSContext* pCtx);

private:
    u32 mDomainFlag; //!< Allowed corruption domain
    u32 mCorruptNum; //!< Number of instructions/data to corrupt
    u32 mInterval;   //!< Corruption interval, in seconds
    OSAlarm mAlarm;  //!< Alarm to trigger corruption

    //! Default corruption interval, in seconds
    static const u32 scDefaultInterval = 15;
    //! Default number of points to corrupt
    static const u32 scDefaultNum = 300;
};

//! @}
} // namespace kiwi

#endif
