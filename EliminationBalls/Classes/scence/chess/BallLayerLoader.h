//
//  BallLayerLoader.h
//  minGameTest
//
//  Created by 马 英臣 on 13-8-20.
//
//
#ifndef minGameTest_BallLayerLoader_h
#define minGameTest_BallLayerLoader_h
#include "BallLayer.h"

/* Forward declaration. */
class CCBReader;
class BallLayerLoader : public cocos2d::extension::LayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(BallLayerLoader, loader);    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(BallLayer);
};
#endif
