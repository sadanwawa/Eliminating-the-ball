//
//  BaseNode.cpp
//  minGameTest
//
//  Created by 马 英臣 on 13-9-30.
//
//

#include "BaseNode.h"

BaseNode::BaseNode(){
    
}
BaseNode::~BaseNode(){
        
}

void BaseNode::updataUI(BaseDataVO* datavo){
    
    
}

void BaseNode::onEnter(){
     Node::onEnter();
}
void BaseNode::onExit(){
     Node::onExit();
}

bool BaseNode::init(){
    if(!Node::init()){
        return false;
    }
    return true;
}

void BaseNode::onNodeLoaded(cocos2d::Node * node, NodeLoader * nodeLoader){
    
    
}