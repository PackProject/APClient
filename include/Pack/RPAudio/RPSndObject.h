#ifndef RP_AUDIO_SND_OBJECT_H
#define RP_AUDIO_SND_OBJECT_H
#include <Pack/RPAudio/RPSndMoveValueF32.h>
#include <Pack/RPTypes.h>

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
class RPSndAudioActorBase : public EGG::Disposer {
public:
    RPSndAudioActorBase(UNKWORD arg0) : mIsSilenced(false), WORD_0x14(arg0) {
        nw4r::ut::List_Append(&sActorList, this);
    }

    virtual ~RPSndAudioActorBase() {
        nw4r::ut::List_Remove(&sActorList, this);
    } // at 0x8

    virtual void stopSound(u32 id, int frames) = 0;            // at 0xC
    virtual void stopSound(unsigned int id, int frames) = 0;   // at 0x10
    virtual void stopSound(const char* pName, int frames) = 0; // at 0x14
    virtual void stopAllSound(int frames) = 0;                 // at 0x18

    virtual void setActorVolume(f32 volume, int frames) = 0; // at 0x1C
    virtual void update() = 0;                               // at 0x20

    static nw4r::ut::List& getActorList() {
        return sActorList;
    }

protected:
    RPSndMoveValueF32 mVolume; // at 0x8
    bool mIsSilenced;          // at 0x10
    UNKWORD WORD_0x14;         // at 0x14

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
    TRPSndAudioHandles() : mHandleCount(N), COUNT_0xC(N) {}

    ~TRPSndAudioHandles() {
        mHandleCount = 0;
        COUNT_0xC = 0;
    }

    virtual f32 getOuterVolume() {
        return 1.0f;
    } // at 0x8
    virtual f32 getOuterPitch() {
        return 1.0f;
    } // at 0xC

protected:
    s32 mHandleCount;
    s32 COUNT_0xC;
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

    virtual const nw4r::math::VEC3* get3DPosition(int idx) {
        return NULL;
    } // at 0x10
};

/******************************************************************************
 *
 * TRPSndAudio3DActor
 *
 ******************************************************************************/
template <int N> class TRPSndAudio3DActor : public EGG::AudioSound3DActor {
public:
    TRPSndAudio3DActor(nw4r::snd::SoundArchivePlayer& rPlayer) {
        for (int i = 0; i < N; i++) {
#line 375
            EGG_ASSERT(smCommon3DManager[i]);

            mSound3DActors[i] =
                new nw4r::snd::Sound3DActor(rPlayer, smCommon3DManager[i]);
        }
    }

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
          BOOL_0x7C(false),
          mRemoteFlag(remoteFlag) {}

    virtual const nw4r::math::VEC3* get3DPosition(int idx);   // at 0x10
    virtual void set3DPosition(const nw4r::math::VEC3& rPos); // at 0x14

    virtual void calc();   // at 0x18
    virtual void update(); // at 0x1C

    virtual nw4r::snd::SoundHandle* startSoundWithRemotePlayer(u32, u32,
                                                               s32); // at 0x20
    virtual nw4r::snd::SoundHandle*
    startSoundWithRemotePlayer(unsigned int, u32, s32); // at 0x24
    virtual nw4r::snd::SoundHandle* startSoundWithRemotePlayer(const char*, u32,
                                                               s32); // at 0x28

    virtual nw4r::snd::SoundHandle* startSound(u32 id,
                                               u32 handle = 0); // at 0x20
    virtual nw4r::snd::SoundHandle* startSound(unsigned int id,
                                               u32 handle = 0); // at 0x24

    // TODO.... more virtual functions....

private:
    bool BOOL_0x7C;
    u32 mRemoteFlag;
};

//! @}

#endif
