//
//  ParticaleEffect.h
//  minGameTest
//
//  Created by 马 英臣 on 13-8-20.
//
//

#ifndef minGameTest_ParticaleEffect_h
#define minGameTest_ParticaleEffect_h


#include "cocos2d.h"
#include "cocos-ext.h"
#include "BaseNode.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ParticaleEffect:
public BaseNode,
public NodeLoaderListener

{   
public:
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ParticaleEffect, create);     
      
    ParticaleEffect();    
    virtual ~ParticaleEffect();        
       
    virtual void onNodeLoaded(cocos2d::Node * node, NodeLoader * nodeLoader);
       
    
private:   
    
};







#endif
