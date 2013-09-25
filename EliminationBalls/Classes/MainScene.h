//
//  MainScene.h
//  minGameTest
//
//  Created by 马 英臣 on 13-8-15.
//
//

#ifndef minGameTest_MainScene_h
#define minGameTest_MainScene_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "HelloWorldScene.h"
//#include "UIManager.h"
#include "core/BaseScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MainScene: public BaseScene{
    
public:
    
    MainScene();    
    virtual ~MainScene();
    
    virtual bool init();//覆盖
    
    static cocos2d::Scene* scene();//覆盖
    
    CREATE_FUNC(MainScene);//覆盖

    
    
        
protected:
   
    
private:
    
    
    

};


#endif
