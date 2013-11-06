//
//  ScoreItemNode.h
//  minGameTest
//
//  Created by 马 英臣 on 13-11-06.
//  得分记录 item
//

#ifndef minGameTest_ScoreItemNode_h
#define minGameTest_ScoreItemNode_h


#include "cocos2d.h"
#include "cocos-ext.h"
#include "BaseNode.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ScoreItemNode:
public BaseNode,
public NodeLoaderListener//

{   
public:
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ScoreItemNode, create);     
      
    ScoreItemNode();    
    virtual ~ScoreItemNode();        
    void updataUI(BaseDataVO* datavo=NULL);  
    virtual void onNodeLoaded(cocos2d::Node * node, NodeLoader * nodeLoader);
       
    
private:   
    
};







#endif
