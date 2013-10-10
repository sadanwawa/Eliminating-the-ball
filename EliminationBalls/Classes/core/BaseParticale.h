//
//  BaseParticale.h
//  minGameTest
//
//  Created by 马 英臣 on 13-9-30.
//pop对象基类
//

#ifndef minGameTest_BaseParticale_h
#define minGameTest_BaseParticale_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "BaseDataVO.h"

USING_NS_CC;
USING_NS_CC_EXT;

class BaseParticale:public ParticleSystemQuad{
public:

    BaseParticale();
    virtual ~BaseParticale();   
    virtual void updataUI(BaseDataVO* datavo=NULL);//更新UI  如果要初始化新的pop对象  只能在该处添加
        
private:        
    
};





#endif
