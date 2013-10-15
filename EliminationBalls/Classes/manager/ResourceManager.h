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

#define DESIGN_RESOLUTION_480X320    0
#define DESIGN_RESOLUTION_960X640    1
#define DESIGN_RESOLUTION_568X320    2
#define DESIGN_RESOLUTION_1136X640   3
#define DESIGN_RESOLUTION_1024X768   4
#define DESIGN_RESOLUTION_2048X1536  5


typedef struct tagResource
{
    cocos2d::Size size;
    char directory[100];
}Resource;

static Resource iphone4Resource      =  { cocos2d::Size(320, 480),   "media" };
static Resource iphone4HDResource    =  { cocos2d::Size(640, 960),   "media" };
static Resource iphone5Resource      =  { cocos2d::Size(320, 568),   "media" };
static Resource iphone5HDResource    =  { cocos2d::Size(640, 1136),  "media" };
static Resource ipad2Resource        =  { cocos2d::Size(768, 1024),  "media"   };
static Resource ipad2HDResource      =  { cocos2d::Size(1536, 2048), "media" };


#if (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_480X320)
static cocos2d::Size designResolutionSize = cocos2d::Size(320, 480);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_960X640)
static cocos2d::Size designResolutionSize = cocos2d::Size(640, 960);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_568X320)
static cocos2d::Size designResolutionSize = cocos2d::Size(320, 568);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_1136X640)
static cocos2d::Size designResolutionSize = cocos2d::Size(640, 1136);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_1024X768)
static cocos2d::Size designResolutionSize = cocos2d::Size(768, 1024);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_2048X1536)
static cocos2d::Size designResolutionSize = cocos2d::Size(1536, 2048);
#else
#error unknown target design resolution!
#endif



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
