#ifndef LIBKIWI_UTIL_STATE_MACHINE_H
#define LIBKIWI_UTIL_STATE_MACHINE_H
#include <libkiwi/debug/kiwiAssert.h>
#include <libkiwi/k_types.h>

/**
 * @brief Declares state calc/exit functions
 */
#define K_STATE_DECL(NAME)                                                     \
    void State_##NAME##_calc();                                                \
    void State_##NAME##_exit();

/**
 * @brief Declares state calc/exit functions with a custom return type
 */
#define K_STATE_DECL_EX(RETURN, NAME)                                          \
    RETURN State_##NAME##_calc();                                              \
    RETURN State_##NAME##_exit();

namespace kiwi {
//! @addtogroup libkiwi_util
//! @{

/**
 * @brief Logic state machine
 *
 * @tparam TActor Actor object type
 * @tparam TStateReturn State function return type
 */
template <typename TActor, typename TStateReturn = void> class StateMachine {
public:
    //! State member function
    typedef TStateReturn (TActor::*StateFunc)();

public:
    /**
     * @brief Constructor
     *
     * @param pObject Actor object
     * @param stateNum Number of possible states
     * @param initial Initial state (defaults to zero)
     */
    StateMachine(TActor* pObject, u32 stateNum, s32 initial = 0)
        : mpObject(pObject),
          mState(initial),
          mStateNum(stateNum),
          mDuration(0),
          mPrevState(0),
          mNextState(0),
          mEntering(true),
          mExiting(false),
          mpCalcFunctions(nullptr),
          mpExitFunctions(nullptr) {

        K_ASSERT_PTR(mpObject);
        K_ASSERT(mStateNum > 0);

        mpCalcFunctions = new StateFunc[mStateNum];
        K_ASSERT_PTR(mpCalcFunctions);

        mpExitFunctions = new StateFunc[mStateNum];
        K_ASSERT_PTR(mpExitFunctions);
    }

    /**
     * @brief Destructor
     */
    virtual ~StateMachine() {}

    /**
     * @brief Tests whether the current state is in its first step/tick
     */
    bool IsFirstStep() const {
        return mDuration == 0;
    }

    /**
     * @brief Registers a function for the specified state
     *
     * @param state State ID
     * @param pCalcFunc State calc function
     * @param pExitFunc State exit function (optional)
     */
    void RegistState(s32 state, StateFunc pCalcFunc, StateFunc pExitFunc = 0) {
        K_ASSERT(state < mStateNum);
        K_ASSERT(pCalcFunc);

        mpCalcFunctions[state] = pCalcFunc;
        mpExitFunctions[state] = pExitFunc;
    }

    /**
     * @brief Changes to a new state
     *
     * @param state New state ID
     */
    void ChangeState(s32 state) {
        K_ASSERT(state < mStateNum);

        mNextState = state;
        mEntering = true;
        mExiting = true;
    }

    /**
     * @brief Tests whether the machine is in the specified state
     *
     * @param state State ID
     */
    bool IsState(s32 state) const {
        return mState == state || mNextState == state && mEntering;
    }

    /**
     * @brief Advances the state machine one step
     */
    TStateReturn Calculate() {
        K_ASSERT(mState < mStateNum);

        if (mEntering) {
            if (mExiting) {
                if (mpExitFunctions[mState]) {
                    (mpObject->*mpExitFunctions[mState])();
                }

                mExiting = false;
            }

            mPrevState = mState;
            mState = mNextState;

            mDuration = 0;
            mEntering = false;
        }

        K_ASSERT(mpCalcFunctions[mState]);
        TStateReturn result = (mpObject->*mpCalcFunctions[mState])();

        mDuration++;
        return result;
    }

private:
    TActor* mpObject; //!< Actor object

    s32 mState;    //!< Current state
    u32 mStateNum; //!< Number of possible states

    u32 mDuration;  //!< Current state duration
    s32 mPrevState; //!< Previous state
    s32 mNextState; //!< Next state

    bool mEntering; //!< Whether to call the enter function
    bool mExiting;  //!< Whether to call the enter function

    StateFunc* mpCalcFunctions; //!< State update functions
    StateFunc* mpExitFunctions; //!< State update functions
};

//! @}
} // namespace kiwi

#endif
