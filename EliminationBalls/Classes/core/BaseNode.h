//
//  BaseNode.h
//  minGameTest
//
//  Created by 马 英臣 on 13-9-30.
//pop对象基类
//

#ifndef minGameTest_BaseNode_h
#define minGameTest_BaseNode_h

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class BaseNode:public Node{
public:

    BaseNode();
    virtual ~BaseNode();   
    virtual void updataUI();//更新UI  如果要初始化新的pop对象  只能在该处添加
        
private:        
    
};





#endif
