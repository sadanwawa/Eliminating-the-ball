//
//  Created by yingchen ma on 13-8-20.
//  Copyright (c) 2013年 马英臣. All rights reserved.
//

#include "UIManager.h"
#include "MainUILayerLoader.h"

// singleton instance pointer
template<> UIManager* Singleton<UIManager>::msSingleton	= NULL;

UIManager::UIManager()
{
    main_Node=NULL;
    ccNodeLoaderLibrary=NULL;   
}

UIManager::~UIManager()
{
       
}

bool UIManager::initialize()//注册所有弹窗
{        
    /* Create an autorelease NodeLoaderLibrary. */
    if(!ccNodeLoaderLibrary){
        ccNodeLoaderLibrary = NodeLoaderLibrary::newDefaultNodeLoaderLibrary();
        ccNodeLoaderLibrary->retain();
    }    
   ccNodeLoaderLibrary->registerNodeLoader("MainUILayer", MainUILayerLoader::loader());
       
    return true;
}

//===================方案2
void UIManager::setCurrScene(Node* node){
    if(main_Node!=node||main_Node==NULL){                
        main_Node=dynamic_cast<BaseScene*>(node);
        //main_Node->setTouchEnabled(false);//开启多点触摸  默认不开启
        
//        for(int i=0;i<_onOpenList.size();i++){
//            if(_onOpenList[i]){delete _onOpenList[i];};
//        }
        _onOpenList.clear();        
//        for(int i=0;i<_currPops.size();i++){
//            if(_currPops[i]){delete _currPops[i];};
//        }
        _currPops.clear();
    }    
}

void UIManager::addPopLayer(const char* fileName,Node* parent,int ease,Point p,const char* tag)
{    
    Node* pNode=NULL;    
    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);    
    /* Read a ccbi file. */
    Node * node = ccbReader->readNodeGraphFromFile(fileName, parent);
    node->retain();//为了保证创建的对象不会自动回收；
    ccbReader->release();//用完接着release    
    if(node != NULL) {
        pNode=node;
                
        PopData* popdata=new PopData();
        popdata->retain();
        popdata->pop=pNode;
        popdata->parent=parent;
        popdata->popType=fileName;
        popdata->tag=tag;
        popdata->point=p;
        popdata->ease=ease;               
        _onOpenList.push_back(popdata);        
    }    
}






//弹窗类型：1.全屏  2.居中显示 灰色遮罩 3.固定位置显示  无灰色遮罩（焦点可切换）；
void UIManager::openPopLayers(){//同时显示多个弹窗；（弹出可自定义时间间隔）
      
    int size=_onOpenList.size();
    CCASSERT(size<100,"to open too many pops!");
    float delay=0;
        
    while(_onOpenList.size()>0){//同时打开  延时处理
        Node* parentNode= _onOpenList[0]->parent!=NULL? _onOpenList[0]->parent:main_Node->getPopsNode();
        if(_onOpenList[0]->ease==0){
            // 
            // CallFuncND is no longer needed. It can simulated with std::bind()
            //必须是显示对象才可用 runAction();
            parentNode->addChild(_onOpenList[0]->pop);//
            _onOpenList[0]->pop->setPosition(_onOpenList[0]->point.x,_onOpenList[0]->point.y);
            _onOpenList[0]->pop->setVisible(false);
            
            FiniteTimeAction* actionA = Sequence::create(
                                           DelayTime::create(delay),//延时 
                                           CallFuncN::create(CC_CALLBACK_1(UIManager::showPopLayer, this, _onOpenList[0])),
                                           NULL);            
            _onOpenList[0]->pop->runAction(actionA);
            
            _currPops.push_back(_onOpenList[0]);
            deleteFromOpenList(_onOpenList[0]);
            
        }else if(_onOpenList[0]->ease==1){
            
            parentNode->addChild(_onOpenList[0]->pop);//
            _onOpenList[0]->pop->setScale(0.02);
            _onOpenList[0]->pop->setAnchorPoint(Point(0.5f,0.5f));
            _onOpenList[0]->pop->setPosition(_onOpenList[0]->point.x,_onOpenList[0]->point.y);            
            _onOpenList[0]->pop->setVisible(false);
                     
            FiniteTimeAction*  actionB = Sequence::create(
                                                          DelayTime::create(delay),//延时
                                                          CallFuncN::create(CC_CALLBACK_1(UIManager::showPopLayer, this, _onOpenList[0])),
                                                          ScaleTo::create(0.8,1),                                                                                                 
                                                          CallFunc::create( CC_CALLBACK_0(UIManager::playOpenActionOver,this)),
                                                          NULL);
            _onOpenList[0]->pop->runAction(actionB);
            
            _currPops.push_back(_onOpenList[0]);
            deleteFromOpenList(_onOpenList[0]);
                        
        }
        std::cout<<"===========new Pop=========about--->"<<_onOpenList[0]->popType<<std::endl;
        //TextureCache::getInstance()->dumpCachedTextureInfo();
        
        delay+=0.3;
    }    
}

void UIManager::showPopLayer(Object* sender, PopData* mpopdata){
    mpopdata->pop->setVisible(true);
}

void UIManager::playOpenActionOver(){
       
}

void UIManager::removeLayerByNode(Node* node){    
    for(std::vector<PopData*>::iterator it=_currPops.begin(); it!=_currPops.end(); )
    {
        if((* it)->pop==node){            
            std::cout<<"当前还没删除popData数据"<<std::endl;            
            node->removeFromParentAndCleanup(true);            
            CC_SAFE_RELEASE(node);//保证删除node对象；
            CC_SAFE_RELEASE((* it));//保证删除nodeData对象；
            it = _currPops.erase(it);            
        }else{
            ++it;
        }
    }    
}

void UIManager::removeLayersByType(const char* fileName){
    for(std::vector<PopData*>::iterator it=_currPops.begin(); it!=_currPops.end(); )
    {
        if((* it)->popType==fileName){
            (* it)->pop->removeFromParentAndCleanup(true);                        
            CC_SAFE_RELEASE((* it)->pop);//保证删除node对象；
            CC_SAFE_RELEASE((* it));//保证删除nodeData对象；
            it = _currPops.erase(it);//erase放在release后面
            
        }else{
            ++it;
        }
    }    
}

void UIManager::removeLayerByType(const char* fileName,const char* tag){
    for(std::vector<PopData*>::iterator it=_currPops.begin(); it!=_currPops.end(); )
    {
        if((* it)->popType==fileName&&((* it)->tag==tag||(* it)->totalnums==1||(* it)->tag==NULL)){
            (* it)->pop->removeFromParentAndCleanup(true);   
            
            CC_SAFE_RELEASE((* it)->pop);//保证删除node对象；
            CC_SAFE_RELEASE((* it));//保证删除nodeData对象；
            it = _currPops.erase(it);   
            
        }else{
            ++it;
        }
    }    
}

Node* UIManager::getLayerByType(const char* fileName,const char* tag){
    
    Node* node=NULL;
    for(std::vector<PopData*>::iterator it=_currPops.begin(); it!=_currPops.end(); )
    {
        if((* it)->popType==fileName&&((* it)->tag==tag||(* it)->totalnums==1||(* it)->tag==NULL)){
            node=(* it)->pop;
            break;
        }else{
            ++it;
        }
    }    
    return node;
}


//删除待打开弹窗数据
void UIManager::deleteFromOpenList(PopData* data){
    for(std::vector<PopData*>::iterator it=_onOpenList.begin(); it!=_onOpenList.end(); )
    {
        if(* it ==data){
            it = _onOpenList.erase(it);            
        }else{
            ++it;
        }
    }    
}

int UIManager::getPopTotalNums(const char* fileName){
    int totalNums=0;
    int size=_currPops.size();
    for(int i=0;i<size;i++){
        if(_currPops[i]->popType==fileName){
            totalNums+=1;
        }        
    }    
    return totalNums;
}

void UIManager::updataPopTotalNums(const char* fileName,int totalNums){    
    int size=_currPops.size();
    for(int i=0;i<size;i++){
        if(_currPops[i]->popType==fileName){            
            _currPops[i]->totalnums=totalNums;
        }
    }
}

//===================方案2end

//每次打开一个
//弹窗类型：1.全屏  2.居中显示 灰色遮罩 3.固定位置显示  无灰色遮罩（焦点可切换）；
void UIManager::openPopLayer(){//同时显示多个弹窗；（弹出可自定义时间间隔）
    
    int size=_onOpenList.size();
    CCASSERT(size<100,"to open too many pops!");
    float delay=0;
    
    while(_onOpenList.size()>0){//同时打开  延时处理
        Node* parentNode= _onOpenList[0]->parent!=NULL? _onOpenList[0]->parent:main_Node->getPopsNode();
        if(_onOpenList[0]->ease==0){
            //
            // CallFuncND is no longer needed. It can simulated with std::bind()
            //必须是显示对象才可用 runAction();
            parentNode->addChild(_onOpenList[0]->pop);//
            _onOpenList[0]->pop->setPosition(_onOpenList[0]->point.x,_onOpenList[0]->point.y);
            _onOpenList[0]->pop->setVisible(false);
            
            FiniteTimeAction* actionA = Sequence::create(
                                                         DelayTime::create(delay),//延时
                                                         CallFuncN::create(CC_CALLBACK_1(UIManager::showPopLayer, this, _onOpenList[0])),
                                                         NULL);
            _onOpenList[0]->pop->runAction(actionA);
            
            _currPops.push_back(_onOpenList[0]);
            deleteFromOpenList(_onOpenList[0]);
            
        }else if(_onOpenList[0]->ease==1){
            
            parentNode->addChild(_onOpenList[0]->pop);//
            _onOpenList[0]->pop->setPosition(_onOpenList[0]->point.x,_onOpenList[0]->point.y);
            _onOpenList[0]->pop->setScale(0.02);
            _onOpenList[0]->pop->setVisible(false);
            
            FiniteTimeAction*  actionB = Sequence::create(
                                                          DelayTime::create(delay),//延时
                                                          CallFuncN::create(CC_CALLBACK_1(UIManager::showPopLayer, this, _onOpenList[0])),
                                                          ScaleTo::create(0.8,1),
                                                          CallFunc::create( CC_CALLBACK_0(UIManager::playOpenActionOver,this)),
                                                          NULL);
            _onOpenList[0]->pop->runAction(actionB);
            
            _currPops.push_back(_onOpenList[0]);
            deleteFromOpenList(_onOpenList[0]);
            
        }
        std::cout<<"===========new Pop=========about--->"<<_onOpenList[0]->popType<<std::endl;
        TextureCache::getInstance()->dumpCachedTextureInfo();
        
        delay+=0.3;
    }    
}




