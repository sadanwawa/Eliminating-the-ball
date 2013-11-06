//
//  ScoreItemNodeLoader.h
//  minGameTest
//
//  Created by 马 英臣 on 13-11-06.
//
//
#ifndef minGameTest_ScoreItemNodeLoader_h
#define minGameTest_ScoreItemNodeLoader_h
#include "ScoreItemNode.h"

/* Forward declaration. */
class CCBReader;
class ScoreItemNodeLoader : public cocos2d::extension::NodeLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ScoreItemNodeLoader, loader);    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ScoreItemNode);
};
#endif
