//
//  MainUILayerLoader.h
//  minGameTest
//
//  Created by 马 英臣 on 13-8-20.
//
//
#ifndef minGameTest_MainUILayerLoader_h
#define minGameTest_MainUILayerLoader_h
#include "MainUILayer.h"

/* Forward declaration. */
class CCBReader;
class MainUILayerLoader : public cocos2d::extension::LayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainUILayerLoader, loader);    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainUILayer);
};
#endif
