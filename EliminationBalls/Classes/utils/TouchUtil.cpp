//
//  DataFormatUtil.cpp
//  GameWorld
//
//  Created by 英臣 马 on 13-03-06.
//  Copyright (c) 2013年 RenRenGame. All rights reserved.
//
#include "TouchUtil.h"

template<> TouchUtil* Singleton<TouchUtil>::msSingleton	= NULL;

bool TouchUtil::touchNode(Node*node,Touch*touch){
    if(!node->isVisible()){
        return false;
    }    
    Size size = node->getContentSize();     
    Point point =node->convertTouchToNodeSpace(touch);
    Rect rect = CCRectMake(0, 0, size.width, size.height);
    return rect.containsPoint(point);
    return true;
}

void TouchUtil::SearchTouchNode(Node* node){
    mchildNum=0;
    Layer* layer = dynamic_cast<Layer*>(node);
    if(layer){
        std::cout<<"====父级对象:"<<mchildNum<<std::endl;
        std::cout<<"当前layer description:"<<layer->description()<<std::endl;
        std::cout<<"当前layer触摸级别:"<<layer->getTouchPriority()<<std::endl;
        std::cout<<"当前layer ZOrder:"<<layer->getZOrder()<<std::endl;
        std::cout<<"当前layer 子元素数量:"<<layer->getChildrenCount()<<std::endl;
        std::cout<<"当前layer tag:"<<layer->getTag()<<std::endl;
        std::cout<<"当前layer number of running actions:"<<layer->getNumberOfRunningActions()<<std::endl;
        std::cout<<"当前layer OrderOfArrival:"<<layer->getOrderOfArrival()<<std::endl;
        
        int touchOrder=-layer->getOrderOfArrival();
//        Director::getInstance()->getTouchDispatcher()->removeDelegate(layer);
//        Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(layer,touchOrder,true);
        //Director::getInstance()->getTouchDispatcher()->addAndResetTouchDelegate(layer,touchOrder);
        //layer->setTouchPriority(touchOrder);
        setLayerTouchOrder(layer,touchOrder);                
    }
    SearchChildNode(node);
}

void TouchUtil::SearchChildNode(Node* node){
    Array* arr=node->getChildren();    
    Object* pObj = NULL;
    CCARRAY_FOREACH(arr, pObj) {        
        ControlButton* button=dynamic_cast<ControlButton*>(pObj);
        ScrollView* scroll=dynamic_cast<ScrollView*>(pObj);
        Menu*menu=dynamic_cast<Menu*>(pObj);
        Layer* childLayer = dynamic_cast<Layer*>(pObj);
        
        Sprite* sprite=dynamic_cast<Sprite*>(pObj);
        TextFieldTTF* textttf=dynamic_cast<TextFieldTTF*>(pObj);
        LabelTTF* labelttf=dynamic_cast<LabelTTF*>(pObj);
        LabelBMFont* labelBmp=dynamic_cast<LabelBMFont*>(pObj);
        Node* childnode = dynamic_cast<Node*>(pObj);
        
        if(button){
            mchildNum++;
            std::cout<<"按钮对象:"<<mchildNum<<std::endl;
            std::cout<<"当前layer description:"<<button->description()<<std::endl;
            std::cout<<"当前layer触摸级别:"<<button->getTouchPriority()<<std::endl;
            std::cout<<"当前layer ZOrder:"<<button->getZOrder()<<std::endl;
            std::cout<<"当前layer 子元素数量:"<<button->getChildrenCount()<<std::endl;
            std::cout<<"当前layer tag:"<<button->getTag()<<std::endl;
            std::cout<<"当前layer number of running actions:"<<button->getNumberOfRunningActions()<<std::endl;
            std::cout<<"当前layer OrderOfArrival:"<<button->getOrderOfArrival()<<std::endl;            
            int touchOrder=-button->getOrderOfArrival();
//            Director::getInstance()->getTouchDispatcher()->removeDelegate(button);
//            Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(button,touchOrder,true);
//            Director::getInstance()->getTouchDispatcher()->addAndResetTouchDelegate(button,touchOrder);                       
//            button->setTouchPriority(touchOrder);
            setLayerTouchOrder(button,touchOrder);
            continue;
        }else if(scroll){
            mchildNum++;
            std::cout<<"滑动列表对象:"<<mchildNum<<std::endl;
            std::cout<<"当前layer description:"<<scroll->description()<<std::endl;
            std::cout<<"当前layer触摸级别:"<<scroll->getTouchPriority()<<std::endl;
            std::cout<<"当前layer ZOrder:"<<scroll->getZOrder()<<std::endl;
            std::cout<<"当前layer 子元素数量:"<<scroll->getChildrenCount()<<std::endl;
            std::cout<<"当前layer tag:"<<scroll->getTag()<<std::endl;
            std::cout<<"当前layer number of running actions:"<<scroll->getNumberOfRunningActions()<<std::endl;
            std::cout<<"当前layer OrderOfArrival:"<<scroll->getOrderOfArrival()<<std::endl;
            int touchOrder=-scroll->getOrderOfArrival();
            //Director::getInstance()->getTouchDispatcher()->removeDelegate(scroll);
//            Director::getInstance()->getTouchDispatcher()->addAndResetTouchDelegate(scroll,touchOrder);                     
//            scroll->setTouchPriority(touchOrder);
            setLayerTouchOrder(scroll,touchOrder);            
            continue;
        }else if(menu){
            mchildNum++;
            std::cout<<"菜单对象:"<<mchildNum<<std::endl;
            std::cout<<"当前layer description:"<<menu->description()<<std::endl;
            std::cout<<"当前layer触摸级别:"<<menu->getTouchPriority()<<std::endl;
            std::cout<<"当前layer ZOrder:"<<menu->getZOrder()<<std::endl;
            std::cout<<"当前layer 子元素数量:"<<menu->getChildrenCount()<<std::endl;
            std::cout<<"当前layer tag:"<<menu->getTag()<<std::endl;
            std::cout<<"当前layer number of running actions:"<<menu->getNumberOfRunningActions()<<std::endl;
            std::cout<<"当前layer OrderOfArrival:"<<menu->getOrderOfArrival()<<std::endl;
            int touchOrder=-menu->getOrderOfArrival();                     
//            Director::getInstance()->getTouchDispatcher()->addAndResetTouchDelegate(menu,touchOrder);            
//            menu->setTouchPriority(touchOrder);
            setLayerTouchOrder(menu,touchOrder);
                        
            continue;
        }else if(textttf){
            mchildNum++;
            std::cout<<"TextFieldTTF对象:"<<mchildNum<<std::endl;
            continue;
        }else if(labelttf){
            mchildNum++;
            std::cout<<"LabelTTF对象:"<<mchildNum<<std::endl;
            continue;
        }else if(labelBmp){
            mchildNum++;
            std::cout<<"LabelBMFont对象:"<<mchildNum<<std::endl;
            continue;
        }else if(sprite){
            mchildNum++;
            std::cout<<"Sprite对象:"<<mchildNum<<std::endl;            
            
            continue;
        }else if(childLayer){
            mchildNum++;
            std::cout<<"Layer对象:"<<mchildNum<<std::endl;
            std::cout<<"当前layer description:"<<childLayer->description()<<std::endl;
            std::cout<<"当前layer触摸级别:"<<childLayer->getTouchPriority()<<std::endl;
            std::cout<<"当前layer ZOrder:"<<childLayer->getZOrder()<<std::endl;
            std::cout<<"当前layer 子元素数量:"<<childLayer->getChildrenCount()<<std::endl;
            std::cout<<"当前layer tag:"<<childLayer->getTag()<<std::endl;
            std::cout<<"当前layer number of running actions:"<<childLayer->getNumberOfRunningActions()<<std::endl;
            std::cout<<"当前layer OrderOfArrival:"<<childLayer->getOrderOfArrival()<<std::endl;
            int touchOrder=-childLayer->getOrderOfArrival();
//            Director::getInstance()->getTouchDispatcher()->removeDelegate(childLayer);
//            Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(childLayer,touchOrder,true);            
            
            setLayerTouchOrder(childLayer,touchOrder);            
            
            SearchChildNode(childLayer);
            continue;
        }else if(childnode){
            mchildNum++;
            std::cout<<"Node对象:"<<mchildNum<<std::endl;
            SearchChildNode(childnode);
        }
    }
}

void TouchUtil::removeAllDelegate(Node* node){    
    Layer* layer = dynamic_cast<Layer*>(node);
    if(layer){
        Director::getInstance()->getTouchDispatcher()->removeDelegate(layer);        
    }
    removeChildDelegate(node);
}

void TouchUtil::removeChildDelegate(Node* node){
    Array* arr=node->getChildren();
    Object* pObj = NULL;
    CCARRAY_FOREACH(arr, pObj) {
        ControlButton* button=dynamic_cast<ControlButton*>(pObj);
        ScrollView* scroll=dynamic_cast<ScrollView*>(pObj);
        Menu*menu=dynamic_cast<Menu*>(pObj);
        Layer* childLayer = dynamic_cast<Layer*>(pObj);
        
        Sprite* sprite=dynamic_cast<Sprite*>(pObj);
        TextFieldTTF* textttf=dynamic_cast<TextFieldTTF*>(pObj);
        LabelTTF* labelttf=dynamic_cast<LabelTTF*>(pObj);
        LabelBMFont* labelBmp=dynamic_cast<LabelBMFont*>(pObj);
        Node* childnode = dynamic_cast<Node*>(pObj);
        
        if(button){                       
            Director::getInstance()->getTouchDispatcher()->removeDelegate(button);            
            continue;
        }else if(scroll){            
            Director::getInstance()->getTouchDispatcher()->removeDelegate(scroll);
            continue;
        }else if(menu){                                  
            Director::getInstance()->getTouchDispatcher()->removeDelegate(menu);            
            continue;
        }else if(textttf){             
            continue;
        }else if(labelttf){            
            continue;
        }else if(labelBmp){               
            continue;
        }else if(sprite){            
            continue;
        }else if(childLayer){                      
            Director::getInstance()->getTouchDispatcher()->removeDelegate(childLayer);
            removeChildDelegate(childLayer);
            continue;
        }else if(childnode){                
            removeChildDelegate(childnode);
        }
    }    
}

void TouchUtil::setLayerTouchOrder(Layer* node,int order){
    if(!node->isVisible())return;
    currTouchOrder-=1;
    //Director::getInstance()->getTouchDispatcher()->addAndResetTouchDelegate(node,currTouchOrder);
    node->setTouchPriority(currTouchOrder);
    std::cout<<"~~~当前触摸级别:"<<currTouchOrder<<std::endl;
}


