//
//  GameOverLayerLoader.h
//  minGameTest
//
//  Created by 马 英臣 on 13-10-18.
//
//
#ifndef minGameTest_GameOverLayerLoader_h
#define minGameTest_GameOverLayerLoader_h
#include "GameOverLayer.h"

/* Forward declaration. */
class CCBReader;
class GameOverLayerLoader : public cocos2d::extension::LayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GameOverLayerLoader, loader);    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GameOverLayer);
};
#endif
