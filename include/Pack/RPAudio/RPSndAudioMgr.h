#ifndef RP_AUDIO_SND_AUDIO_MGR_H
#define RP_AUDIO_SND_AUDIO_MGR_H
#include <egg/audio.h>
#include <egg/core.h>

#include <nw4r/snd.h>

#include <RPTypes.h>

//! @addtogroup rp_audio
//! @{

/**
 * @brief RP sound manager (BGM, SFX, etc.)
 */
class RPSndAudioMgr : public EGG::ExpAudioMgr {
    RP_SINGLETON_DECL_EX(RPSndAudioMgr);

public:
    /* virtual */ bool loadGroup(UNKWORD, nw4r::snd::SoundHeap*, UNKWORD);

    void setSystemSeFadeInFrame(s16 frame);

    bool startSound(u32 id) {
        return RPSndAudioMgr::startSound(&mSndHandleStrm, id);
    }
    bool startSound(const char* name) {
        return RPSndAudioMgr::startSound(&mSndHandleStrm, name);
    }

    void stopAllSoud();

    bool attachArchive(const char* archiveName, bool bStaticPath,
                       nw4r::snd::SoundHeap* heap);
    bool startSound(nw4r::snd::SoundHandle* handle, u32 id);
    bool startSound(nw4r::snd::SoundHandle* handle, const char* name);

    void changeScene();

    nw4r::snd::SoundHandle* getSoundHandleSeq() {
        return &mSndHandleSeq;
    }
    nw4r::snd::SoundHandle* getSoundHandleStrm() {
        return &mSndHandleStrm;
    }

private:
    char _8A0[0x920 - 0x8A0];
    nw4r::snd::SoundHandle mSndHandleSeq;  // at 0x920
    nw4r::snd::SoundHandle mSndHandleStrm; // at 0x924
};

//! @}

#endif
