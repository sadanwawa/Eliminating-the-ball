//
//  AnimationSpriteLoader.h
//  TestGame
//
//  Created by Âí Ó¢³¼ on 13-10-23.
//
//
#ifndef TestGame_AnimationSpriteLoader_h
#define TestGame_AnimationSpriteLoader_h
#include "AnimationSprite.h"

/* Forward declaration. */
class CCBReader;
class AnimationSpriteLoader : public cocos2d::extension::SpriteLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AnimationSpriteLoader, loader);    
protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AnimationSprite);
};
#endif

