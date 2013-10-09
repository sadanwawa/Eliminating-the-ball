//
//  DataFormatUtil.h
//  GameWorld
//
//  Created by 英臣 马 on 13-03-06.
//  Copyright (c) 2013年 RenRenGame. All rights reserved.
//

#ifndef GameWorld_TouchUtil_h
#define GameWorld_TouchUtil_h

#include "../core/Singleton.h"
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class TouchUtil:public Singleton<TouchUtil>{
public:
    TouchUtil(){
        mchildNum=0;
        currTouchOrder=-1;
    };
    ~TouchUtil(){};    
    bool touchNode(Node*node,Touch*touch);
            
    //开始 遍历所有显示对象 搜索可触摸子对象 重新设置触摸层级
    void SearchTouchNode(Node* node);
    
    //移除触摸事件  包括子对象中的触摸事件
    void removeAllDelegate(Node* node);
    
private:
    
    int mchildNum;//当前对象位置
    //搜索可触摸子对象
    void SearchChildNode(Node* node);
    
    //移除子对象中的触摸事件
    void removeChildDelegate(Node* node);
    
    void setLayerTouchOrder(Layer* node,int order);
    
    
    int currTouchOrder;

};

#endif
