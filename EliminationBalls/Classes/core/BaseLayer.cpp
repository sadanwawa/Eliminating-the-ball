//
//  BaseLayer.cpp
//  minGameTest
//
//  Created by 马 英臣 on 13-9-3.
//
//

#include "BaseLayer.h"
#include "TouchUtil.h"

BaseLayer::BaseLayer(){
    _dataVo=NULL;
}
BaseLayer::~BaseLayer(){
        
}

const char* BaseLayer::description()
{
    return "";
}

void BaseLayer::onEnter(){
    Layer::onEnter();    
    
}
void BaseLayer::onExit(){
    Layer::onExit();    
    
}

bool BaseLayer::init(){
    if(!Layer::init()){
        return false;
    }   
    return true;
}

void BaseLayer::updataUI(BaseDataVO* data){
    _dataVo=data;
}

void BaseLayer::onNodeLoaded(cocos2d::Node * node, NodeLoader * nodeLoader){
        
}

bool BaseLayer::ccTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent){
    if(pTouch){
        if(pEvent){//有预定义事件
            return  Layer::ccTouchBegan(pTouch, pEvent);
        }else{//没有预定义触发事件  根据当前碰触对象区域判断            
            //根据位置和区域  判断是否碰触
            //return TouchUtil::Instance()->touchNode(this, pTouch);
            return  Layer::ccTouchBegan(pTouch, pEvent);
        }      
    }    
    return false ;
}






