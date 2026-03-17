#ifndef RP_AUDIO_SND_OBJECT_H
#define RP_AUDIO_SND_OBJECT_H
#include <Pack/types_pack.h>

#include <Pack/RPAssert.h>
#include <Pack/RPAudio/RPSndMoveParam.h>

#include <egg/audio.h>
#include <egg/core.h>

#include <nw4r/snd.h>
#include <nw4r/ut.h>

//! @addtogroup rp_audio
//! @{

/******************************************************************************
 *
 * RPSndAudioActorBase
 *
 ******************************************************************************/

/**
 * @brief Base class for managed audio actors
 */
class RPSndAudioActorBase : public EGG::Disposer {
    friend class RPSndObjMgr;

public:
    RPSndAudioActorBase(UNKWORD arg0) : mIsSilenced(false), WORD_0x14(arg0) {
        nw4r::ut::List_Append(&sActorList, this);
    }

    virtual ~RPSndAudioActorBase() { // at 0x8
        nw4r::ut::List_Remove(&sActorList, this);
    }

    virtual void stopSound(u32 id, int frames) = 0;            // at 0xC
    virtual void stopSound(unsigned int id, int frames) = 0;   // at 0x10
    virtual void stopSound(const char* pName, int frames) = 0; // at 0x14
    virtual void stopAllSound(int frames) = 0;                 // at 0x18

    virtual void setActorVolume(f32 volume, int frames) = 0; // at 0x1C
    virtual void update() = 0;                               // at 0x20

    static void initList() {
        NW4R_UT_LIST_INIT(sActorList, RPSndAudioActorBase);
    }

    static nw4r::ut::List& getActorList() {
        return sActorList;
    }

protected:
    bool mIsSilenced;  // at 0x10
    UNKWORD WORD_0x14; // at 0x14

public:
    NW4R_UT_LIST_LINK_DECL(); // at 0x18

private:
    RPSndMoveValueF32 mVolume; // at 0x20

private:
    static nw4r::ut::List sActorList;
};

/******************************************************************************
 *
 * TRPSndAudioHandles
 *
 ******************************************************************************/

template <int N> class TRPSndAudioHandles {
public:
    TRPSndAudioHandles() {
        mHandleCount = N;
        unkC = N;
    }

    ~TRPSndAudioHandles() {
        mHandleCount = 0;
        unkC = 0;
    }

    virtual f32 getOuterVolume() {
        return 1.0f;
    } // at 0x8

    virtual f32 getOuterPitch() {
        return 1.0f;
    } // at 0xC

protected:
    s32 mHandleCount;
    s32 unkC;
    nw4r::snd::SoundHandle mSoundHandles[N];
};

/******************************************************************************
 *
 * TRPSndAudioActorBaseWithHandles
 *
 ******************************************************************************/

template <int N1, int N2>
class TRPSndAudioActorBaseWithHandles : public RPSndAudioActorBase,
                                        public TRPSndAudioHandles<N1 + N2> {
public:
    TRPSndAudioActorBaseWithHandles(UNKWORD arg0) : RPSndAudioActorBase(arg0) {}

    virtual const nw4r::math::VEC3* get3DPosition(int /* idx */) { // at 0x10
        return NULL;
    }
};

/******************************************************************************
 *
 * TRPSndAudio3DActor
 *
 ******************************************************************************/

template <int N>
class TRPSndAudio3DActor : public EGG::AudioSoundActorBaseWithCamera<N> {
public:
    TRPSndAudio3DActor(nw4r::snd::SoundArchivePlayer& rPlayer) {
        for (int i = 0; i < N; i++) {

// TODO(kiwi) Fix this...
#if defined(__KOKESHI__)
#define smCommon3DManager                                                      \
    (EGG::AudioSoundActorBaseWithCamera<N>::smCommon3DManager)
#endif

#line 375
            RP_ASSERT(smCommon3DManager[i]);

            mSound3DActors[i] =
                new nw4r::snd::Sound3DActor(rPlayer, *smCommon3DManager[i]);
        }
    }

#if defined(__KOKESHI__)
#undef smCommon3DManager
#endif

protected:
    nw4r::snd::Sound3DActor* mSound3DActors[N];
};

/******************************************************************************
 *
 * TRPSndObject
 *
 ******************************************************************************/

template <int N>
class TRPSndObject : public TRPSndAudio3DActor<N>,
                     public TRPSndAudioActorBaseWithHandles<N, N> {
public:
    enum RemoteFlag {
        FLAG_REMOTE_1 = 1 << 0,
        FLAG_REMOTE_2 = 1 << 1,
        FLAG_REMOTE_3 = 1 << 2,
        FLAG_REMOTE_4 = 1 << 3,

        FLAG_REMOTE_ALL =
            FLAG_REMOTE_1 | FLAG_REMOTE_2 | FLAG_REMOTE_3 | FLAG_REMOTE_4
    };

public:
    TRPSndObject(nw4r::snd::SoundArchivePlayer& rPlayer,
                 nw4r::snd::Sound3DManager& /* rManager */,
                 u32 remoteFlag = FLAG_REMOTE_ALL)
        : TRPSndAudio3DActor<N>(rPlayer),
          TRPSndAudioActorBaseWithHandles<N, N>(0),
          unk7C(false),
          mRemoteFlag(remoteFlag) {}

    virtual const nw4r::math::VEC3* get3DPosition(int idx);
    virtual void set3DPosition(const nw4r::math::VEC3& rPos);

    virtual void update();

    /******************************************************************************
     * startSoundWithRemotePlayer
     ******************************************************************************/

    virtual nw4r::snd::SoundHandle*
    startSoundWithRemotePlayer(u32 id, u32 remoteFlag, s32 handleNo = 0);

    virtual nw4r::snd::SoundHandle*
    startSoundWithRemotePlayer(unsigned int id, u32 remoteFlag,
                               s32 handleNo = 0);

    virtual nw4r::snd::SoundHandle*
    startSoundWithRemotePlayer(const char* pName, u32 remoteFlag,
                               s32 handleNo = 0);

    /******************************************************************************
     * startSound
     ******************************************************************************/

    virtual nw4r::snd::SoundHandle* startSound(u32 id, s32 handleNo = 0);

    virtual nw4r::snd::SoundHandle* startSound(unsigned int id,
                                               s32 handleNo = 0);

    virtual nw4r::snd::SoundHandle* startSoundIndex(u32 id, s32 index,
                                                    s32 handleNo = 0);

    virtual nw4r::snd::SoundHandle* startSound(const char* pName,
                                               s32 handleNo = 0);

    virtual nw4r::snd::SoundHandle*
    startSoundIndex(const char* pName, s32 index, s32 handleNo = 0);

    /******************************************************************************
     * holdSoundWithRemotePlayer
     ******************************************************************************/

    virtual nw4r::snd::SoundHandle*
    holdSoundWithRemotePlayer(u32 id, u32 remoteFlag, s32 handleNo = 0);

    virtual nw4r::snd::SoundHandle* holdSoundWithRemotePlayer(unsigned int id,
                                                              u32 remoteFlag,
                                                              s32 handleNo = 0);

    virtual nw4r::snd::SoundHandle* holdSoundWithRemotePlayer(const char* pName,
                                                              u32 remoteFlag,
                                                              s32 handleNo = 0);

    /******************************************************************************
     * holdSound
     ******************************************************************************/

    virtual nw4r::snd::SoundHandle* holdSound(u32 id, s32 handleNo = 0);

    virtual nw4r::snd::SoundHandle* holdSound(unsigned int id,
                                              s32 handleNo = 0);

    virtual nw4r::snd::SoundHandle* holdSoundIndex(u32 id, s32 index,
                                                   s32 handleNo = 0);

    virtual nw4r::snd::SoundHandle* holdSound(const char* pName,
                                              s32 handleNo = 0);

    virtual nw4r::snd::SoundHandle* holdSoundIndex(const char* pName, s32 index,
                                                   s32 handleNo = 0);

    /******************************************************************************
     * prepareSound
     ******************************************************************************/

    virtual nw4r::snd::SoundHandle* prepareSound(u32 id, s32 handleNo = 0);

    virtual nw4r::snd::SoundHandle* prepareSound(unsigned int id,
                                                 s32 handleNo = 0);

    virtual nw4r::snd::SoundHandle* prepareSoundIndex(u32 id, s32 index,
                                                      s32 handleNo = 0);

    virtual nw4r::snd::SoundHandle* prepareSound(const char* pName,
                                                 s32 handleNo = 0);

    virtual nw4r::snd::SoundHandle*
    prepareSoundIndex(const char* pName, s32 index, s32 handleNo = 0);

    /******************************************************************************
     * stopSound
     ******************************************************************************/

    virtual void stopSound(u32 id, int frames);
    virtual void stopSound(unsigned int id, int frames);
    virtual void stopSound(const char* pName, int frames);
    virtual void stopAllSound(int frames);

    virtual void setActorVolume(f32 volume, int frames);
    virtual f32 getOuterVolume();

    virtual void startSoundCommon(nw4r::snd::SoundHandle* pHandle, u32 id,
                                  s32 handleNo);
    virtual void holdSoundCommon(nw4r::snd::SoundHandle* pHandle, u32 id,
                                 s32 handleNo);
    virtual void prepareSoundCommon(nw4r::snd::SoundHandle* pHandle, u32 id,
                                    s32 handleNo);

    virtual void
    startSoundCommonWithRemotePlayer(nw4r::snd::SoundHandle* pHandle, u32 id,
                                     u32 remoteFlag, s32 handleNo);
    virtual void
    holdSoundCommonWithRemotePlayer(nw4r::snd::SoundHandle* pHandle, u32 id,
                                    u32 remoteFlag, s32 handleNo);

private:
    bool unk7C;
    u32 mRemoteFlag; // at 0x80
};

//! Shorthand for default specialization
typedef TRPSndObject<RP_MAX_CONTROLLERS> RPSndObject;

/******************************************************************************
 *
 * RPSndObjMgr
 *
 ******************************************************************************/

/**
 * @brief Sound object/actor manager
 */
class RPSndObjMgr {
public:
    /**
     * @brief Fades out all active sounds in the specified number of frames
     *
     * @param frames Fade out time
     */
    static void stopAllActorSound(int frames);

    /**
     * @brief Updates the state of all active sounds
     */
    static void update() {
        RPSndAudioActorBase* pIt = static_cast<RPSndAudioActorBase*>(
            nw4r::ut::List_GetFirst(&RPSndAudioActorBase::sActorList));

        for (; pIt != NULL;
             pIt = static_cast<RPSndAudioActorBase*>(nw4r::ut::List_GetNext(
                 &RPSndAudioActorBase::sActorList, pIt))) {

            if (pIt->mVolume.getFrame() > 0) {
                pIt->update();
            }
        }
    }
};

//! @}

#endif
