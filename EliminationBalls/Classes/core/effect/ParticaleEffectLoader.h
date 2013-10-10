//
//  ParticaleEffectLoader.h
//  minGameTest
//
//  Created by 马 英臣 on 13-8-20.
//
//
#ifndef minGameTest_ParticaleEffectLoader_h
#define minGameTest_ParticaleEffectLoader_h
#include "ParticaleEffect.h"

/* Forward declaration. */
class CCBReader;
class ParticaleEffectLoader : public cocos2d::extension::NodeLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ParticaleEffectLoader, loader);    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ParticaleEffect);
};
#endif
