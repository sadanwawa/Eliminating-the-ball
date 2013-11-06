//
//  ResourceManager.cpp
//  minGameTest
//
//  Created by 马 英臣 on 13-9-13.
//
//

#include "ResourceManager.h"


// singleton instance pointer
template<> ResourceManager* Singleton<ResourceManager>::msSingleton	= NULL;

ResourceManager::ResourceManager(){
    //screenSize=cocos2d::Size(960, 640);
    screenwhR=1.0f;
    designwhR=1.0f;
    scalefactor=1.0f;
};
ResourceManager::~ResourceManager(){
    
};

bool ResourceManager::initialize(){
    //全屏方案1:设计上UI不方便拆分，需要确定一个（也可多个）设计尺寸：部分缩放实现一边全屏，一边黑边；
    
    //全屏方案2:一套资源，按照相对规则显示设计元素（靠上、下、左、右；中间元素按照舞台百分比现实）
    
    Director* director = Director::getInstance();
    EGLView* eglView = EGLView::getInstance();
    //eglView->setFrameSize(1024, 768);
    
    Size framesize=eglView->getFrameSize();
    Size designsize=eglView->getDesignResolutionSize();
    //宽高
    CCLOG("framesize：w:%f,h:%f",framesize.width,framesize.height);
    CCLOG("designsize：w:%f,h:%f",designsize.width,designsize.height);
    
    screenSize=framesize;
    
    //设计方案尺寸(一套资源对应一个设计尺寸)
    eglView->setDesignResolutionSize(designResolutionSize.height, designResolutionSize.width, ResolutionPolicy::SHOW_ALL);
    designsize=eglView->getDesignResolutionSize();
    
    
    screenwhR=framesize.width/framesize.height;
    screenwhR=screenwhR>1?screenwhR:(1/screenwhR);
    designwhR=designsize.width/designsize.height;
    designwhR=designwhR>1?designwhR:(1/designwhR);
    
    if(screenwhR>designwhR){
    //以小边缩放
        float minscreen=MIN(framesize.width, framesize.height);
        float mindesign=MIN(designsize.width, designsize.height);
        scalefactor=minscreen/mindesign;
    }else{
        //以长边缩放
        float maxscreen=MAX(framesize.width, framesize.height);
        float maxdesign=MAX(designsize.width, designsize.height);
        scalefactor=maxscreen/maxdesign;
    }
    CCLOG("缩放因子：%f",scalefactor);
    director->setContentScaleFactor(scalefactor);
    
    framesize=eglView->getFrameSize();
    //宽高
    CCLOG("====framesize：w:%f,h:%f",framesize.width,framesize.height);
    CCLOG("====designsize：w:%f,h:%f",designsize.width,designsize.height);

    
    return true;
};

