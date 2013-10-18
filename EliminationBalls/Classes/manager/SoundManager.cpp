
#include <iostream>
#include "SoundManager.h"
#include "SimpleAudioEngine.h"
#include "StaticConstant.h"
#include "DataFormatUtil.h"

using namespace CocosDenshion;

// singleton instance pointer
template<> SoundManager* Singleton<SoundManager>::msSingleton	= NULL;


/*************************************************************************
 Constructor
 *************************************************************************/
SoundManager::SoundManager(void):
mbOnEffect(true),
mbOnBackGround(true)
{
    
             
        AudioEngine()->setBackgroundMusicVolume(1);
        
        setOnEffect(true);
        setOnBackGround(true);

   
}

/*************************************************************************
 Destructor
 *************************************************************************/
SoundManager::~SoundManager(void)
{
}

SimpleAudioEngine* SoundManager::AudioEngine(){
    return SimpleAudioEngine::getInstance();
}
void SoundManager::setEffectsVolume(float val)
{
      
    
    AudioEngine()->setEffectsVolume(val);
    
}
void SoundManager::setBackgroundMusicVolume(float val)
{
        
    AudioEngine()->setBackgroundMusicVolume(val);
    
}

float SoundManager::getEffectsVolume()
{
      
    return AudioEngine()->getEffectsVolume();
}

float SoundManager::getBackgroundMusicVolume()
{
     
    return AudioEngine()->getBackgroundMusicVolume();
}
void SoundManager::setOnEffect(bool bon)
{
       
    if(!mbOnEffect)
        AudioEngine()->pauseAllEffects();
    else
        AudioEngine()->resumeAllEffects();
}

void SoundManager::setOnBackGround(bool bon)
{
      
    if(!mbOnBackGround)
        AudioEngine()->pauseBackgroundMusic();
    else
        AudioEngine()->resumeBackgroundMusic();
}

void SoundManager::playEffect(const char* pszFilePath, bool bLoop)
{
    
    if(mbOnEffect)
    {
        preloadEffect(pszFilePath);
        std::string fullpath ="" ;//GetFileFullPath(pszFilePath);
        AudioEngine()->playEffect(fullpath.c_str(), bLoop);
    }
}
void SoundManager::playBackgroundMusic(const char* pszFilePath, bool bLoop)
{
    
    std::string fullpath ="" ;//GetFileFullPath(pszFilePath);
    AudioEngine()->playBackgroundMusic(fullpath.c_str(), bLoop);
    if(!mbOnEffect)AudioEngine()->stopBackgroundMusic();
}

void SoundManager::stopBackgroundMusic()
{
   
    
    if(mbOnEffect)
        AudioEngine()->stopBackgroundMusic();
}

void SoundManager::preloadEffect(const char* pszFilePath)
{
        
    std::string fullpath = "" ;//GetFileFullPath(pszFilePath);
    
    AudioEngine()->preloadEffect(fullpath.c_str());
    
    addSoundEffect(pszFilePath);
}
void SoundManager::preloadBackgroundMusic(const char* pszFilePath)
{
   
    
    std::string fullpath = "" ;//GetFileFullPath(pszFilePath);
    
    AudioEngine()->preloadBackgroundMusic(fullpath.c_str());
}
void SoundManager::unloadEffect(const char* pszFilePath)
{
    
    
    std::string fullpath = "" ;//GetFileFullPath(pszFilePath);
    
    AudioEngine()->unloadEffect(fullpath.c_str());    
    removeSoundEffect(pszFilePath);
}

void SoundManager::unloadAllEffect()
{
    LoadedSoundMap::iterator it = mLoadedSoundMap.begin();
    for (; it != mLoadedSoundMap.end(); ++it) {
        unloadEffect(*it);
    }
    mLoadedSoundMap.clear();
}

void SoundManager::addSoundEffect(const char* sound)
{
    CCAssert(sound, "sound is null !");
    
    LoadedSoundMap::iterator it = mLoadedSoundMap.begin();
    for (; it != mLoadedSoundMap.end(); ++it) {
        if(strcmp(*it, sound) == 0) return ;
    }
    
    mLoadedSoundMap.push_back(sound);
}
void SoundManager::removeSoundEffect(const char* sound)
{
    LoadedSoundMap::iterator it = mLoadedSoundMap.begin();
    for (; it != mLoadedSoundMap.end(); ++it) {
        if(strcmp(*it, sound) == 0)
        {
            mLoadedSoundMap.erase(it);
            break;
        }
    }
}
void SoundManager::playBtnEffect()
{
   
}