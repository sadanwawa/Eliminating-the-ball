
#ifndef EliminationBalls_SoundManager_h
#define EliminationBalls_SoundManager_h

#include "cocos-ext.h"
#include "Singleton.h"
#include "SimpleAudioEngine.h"
#include "StaticConstant.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define SOUND_BG_VOL 0.5f
#define SOUND_EFF_VOL 0.5f

using namespace std;
using namespace CocosDenshion;

typedef std::vector<const char*> LoadedSoundMap;

class SoundManager : public Singleton<SoundManager>, public Object
{
public:
    /*************************************************************************
     Construction and Destruction
     *************************************************************************/
	/*!
     \brief
     Constructs a new SoundManager.
     */
	SoundManager(void);    
    
	/*!
     \brief
     Destructor for SoundManager
     */
	~SoundManager(void);
    
    
    SimpleAudioEngine* AudioEngine();
    
    void setEffectsVolume(float val);
    void setBackgroundMusicVolume(float val);
    
    float getEffectsVolume();
    float getBackgroundMusicVolume();

    void setPlayMusic(bool bon);
    
    void setOnEffect(bool bon);
    void setOnBackGround(bool bon);
    
    bool getOnEffect(){ return mbOnEffect; }
    bool getOnBackGround(){ return mbOnBackGround; }
    
    void playEffect(const char* pszFilePath, bool bLoop = false);
    void playBackgroundMusic(const char* pszFilePath, bool bLoop = false);
    
    void preloadEffect(const char* pszFilePath);
    void preloadBackgroundMusic(const char* pszFilePath);
    
    void unloadEffect(const char* pszFilePath);
    void unloadAllEffect();
    
    void stopBackgroundMusic();
    
public:
    virtual void playBtnEffect();

protected:
    
    void addSoundEffect(const char* sound);
    void removeSoundEffect(const char* sound);
    
protected:
    
    bool mbOnEffect;
    bool mbOnBackGround;
    
    LoadedSoundMap mLoadedSoundMap;
    
};


#define CC_PLAY_BACKGROUND(SOUND, LOOP)\
    SoundManager::Instance()->playBackgroundMusic(SOUND, LOOP);

#define CC_STOP_BACKGROUND\
    SoundManager::Instance()->stopBackgroundMusic();

#define CC_PLAY_EFFECT(SOUND, LOOP)\
    SoundManager::Instance()->playEffect(SOUND, LOOP);

#define CC_PRELOAD_EFFECT(SOUND)\
SoundManager::Instance()->preloadEffect(SOUND);

#define CC_UNLOAD_EFFECT(SOUND)\
    SoundManager::Instance()->unloadEffect(SOUND);

#define CC_PLAY_EFFECT_BUTTON\
    SoundManager::Instance()->playEffect(STC::SOUND_UI_BTN.c_str());

#define CC_PLAY_EFFECT_LIST\
    SoundManager::Instance()->playEffect(STC::SOUND_UI_LIST.c_str());

#define CC_PLAY_CARD_MERGE\
    SoundManager::Instance()->playEffect(STC::SOUND_CARD_MERGE.c_str());



#endif
