//
//  ResourceManager.h
//  minGameTest
//
//  Created by 马 英臣 on 13-9-13.
//
//

#ifndef minGameTest_ResourceManager_h
#define minGameTest_ResourceManager_h


#include "cocos2d.h"
#include "../core/Singleton.h"
#include "cocos-ext.h"
//#include "../common/StaticConstant.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ResourceManager : public Singleton<ResourceManager>, public Object
{
public:
    ResourceManager();
    ~ResourceManager();
    
    virtual bool initialize();
    
};

#endif
