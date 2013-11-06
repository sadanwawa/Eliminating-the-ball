//
//  ScorcesListLayerLoader.h
//  minGameTest
//
//  Created by 马 英臣 on 13-11-05.
//
//
#ifndef minGameTest_ScorcesListLayerLoader_h
#define minGameTest_ScorcesListLayerLoader_h
#include "ScorcesListLayer.h"

/* Forward declaration. */
class CCBReader;
class ScorcesListLayerLoader : public cocos2d::extension::LayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ScorcesListLayerLoader, loader);    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ScorcesListLayer);
};
#endif
