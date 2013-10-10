//
//  Created by yingchen ma on 13-8-20.
//  Copyright (c) 2013年 马英臣. All rights reserved.
//

#include "UIManager.h"
#include "MainUILayerLoader.h"
#include "BallLayerLoader.h"
#include "ParticaleEffectLoader.h"

// singleton instance pointer
template<> UIManager* Singleton<UIManager>::msSingleton	= NULL;

UIManager::UIManager()
{
    main_Node=NULL;
    ccNodeLoaderLibrary=NULL;
    _isOpening=false;
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
   ccNodeLoaderLibrary->registerNodeLoader("BallLayer", BallLayerLoader::loader());
   ccNodeLoaderLibrary->registerNodeLoader("ParticaleEffect", ParticaleEffectLoader::loader());
    
    
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

void UIManager::addPopLayer(std::string fileName,Node* parent,int ease,float x,float y,std::string tag,BaseDataVO* vo)
{   //只添加数据。。。。
    Node* pNode=NULL;    
    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);    
    /* Read a ccbi file. */
    Node * node = ccbReader->readNodeGraphFromFile(fileName.c_str(), parent);
    
    //BaseLayer
    
    //BaseNode    
    
    node->retain();//为了保证创建的对象不会自动回收；
    ccbReader->release();//用完接着release    
    if(node != NULL) {
        pNode=node;
        PopData* popdata=new PopData();
        popdata->retain();                
        popdata->pop=pNode;
        BaseLayer* layer=dynamic_cast<BaseLayer*>(node);
        BaseNode* node=dynamic_cast<BaseNode*>(node);
        BaseParticale* particale=dynamic_cast<BaseParticale*>(node);
        BaseSprite* sprite=dynamic_cast<BaseSprite*>(node);
        
        if(layer){
            popdata->layer=layer;
        }else if(particale){
            popdata->particale=particale;
        }else if(sprite){
            popdata->sprite=sprite;
        }else{
            popdata->node=node;
        }
                
        popdata->parent=parent;
        popdata->popType=fileName;
        popdata->tag=tag;
        popdata->x=x;
        popdata->y=y;
        popdata->ease=ease;
        popdata->dataVo=vo;        
        _onOpenList.push_back(popdata);        
    }    
}

//弹窗类型：1.全屏  2.居中显示 灰色遮罩 3.固定位置显示  无灰色遮罩（焦点可切换）；
void UIManager::openPopLayers(float Ddelay){//同时显示多个弹窗；（弹出可自定义时间间隔）
//    if(_isOpening){
//        return;
//    }
//    _isOpening=true;
    int size=_onOpenList.size();
    CCASSERT(size<100,"to open too many pops!");
    float delay=0;
    
    std::vector<Node*> popVec;
    std::vector<BaseDataVO*> voVec;//逻辑数据
    popVec.clear();
    voVec.clear();
    while(_onOpenList.size()>0){//同时打开  延时处理        
        PopData* currPopData=_onOpenList[0];
        Node* parentNode= currPopData->parent!=NULL? currPopData->parent:main_Node->getPopsNode();
                
        if(currPopData->ease==0){
            // 
            // CallFuncND is no longer needed. It can simulated with std::bind()
            //必须是显示对象才可用 runAction();
            parentNode->addChild(currPopData->pop);//
            currPopData->pop->setPosition(currPopData->x,currPopData->y);
            currPopData->pop->setVisible(false);
            
            FiniteTimeAction* actionA = Sequence::create(
                                           DelayTime::create(delay),//延时 
                                           CallFuncN::create(CC_CALLBACK_1(UIManager::showPopLayer, this, currPopData)),
                                           NULL);            
            currPopData->pop->runAction(actionA);
                       
            
        }else if(currPopData->ease==1){
            
            parentNode->addChild(currPopData->pop);//
            currPopData->pop->setScale(0.02);
            currPopData->pop->setAnchorPoint(Point(0.5f,0.5f));
            currPopData->pop->setPosition(currPopData->x,currPopData->y);            
            currPopData->pop->setVisible(false);
                     
            FiniteTimeAction*  actionB = Sequence::create(
                                                          DelayTime::create(delay),//延时
                                                          CallFuncN::create(CC_CALLBACK_1(UIManager::showPopLayer, this, currPopData)),
                                                          ScaleTo::create(0.8,1),                                                                                                 
                                                          CallFunc::create( CC_CALLBACK_0(UIManager::playOpenActionOver,this)),
                                                          NULL);
            currPopData->pop->runAction(actionB);
                                   
        }
         std::cout<<"===========new Pop=========about--->"<<currPopData->popType<<std::endl;
        _currPops.push_back(currPopData);
        popVec.push_back(currPopData->pop);
        voVec.push_back(currPopData->dataVo);        
        deleteFromOpenList(currPopData);
               
        //TextureCache::getInstance()->dumpCachedTextureInfo();        
        delay+=Ddelay;
    }
    
    for(int i=0;i<popVec.size();i++){
        //更新当前pop   updataUI()
        BaseLayer* layer=dynamic_cast<BaseLayer*>(popVec[i]);
        BaseNode* node=dynamic_cast<BaseNode*>(popVec[i]);        
        BaseParticale* particale=dynamic_cast<BaseParticale*>(popVec[i]);
        BaseSprite* sprite=dynamic_cast<BaseSprite*>(popVec[i]);
        
        if(layer){
            layer->updataUI(voVec[i]);
        }else if(node){
            node->updataUI(voVec[i]);
        }else if(particale){
            
        }else if(sprite){
            
        }
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

void UIManager::removeLayersByType(std::string fileName){
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

void UIManager::removeLayerByType(std::string fileName,std::string tag){
    for(std::vector<PopData*>::iterator it=_currPops.begin(); it!=_currPops.end(); )
    {
        if((* it)->popType==fileName&&((* it)->tag==tag)){
            (* it)->pop->removeFromParentAndCleanup(true);   
            
            CC_SAFE_RELEASE((* it)->pop);//保证删除node对象；
            CC_SAFE_RELEASE((* it));//保证删除nodeData对象；
            it = _currPops.erase(it);   
            
        }else{
            ++it;
        }
    }    
}

Node* UIManager::getLayerByType(std::string fileName,std::string tag){
    
    Node* node=NULL;
    for(std::vector<PopData*>::iterator it=_currPops.begin(); it!=_currPops.end(); )
    {
        if((* it)->popType==fileName&&((* it)->tag==tag)){
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

int UIManager::getPopTotalNums(std::string fileName){
    int totalNums=0;
    int size=_currPops.size();
    for(int i=0;i<size;i++){
        if(_currPops[i]->popType==fileName){
            totalNums+=1;
        }        
    }    
    return totalNums;
}

void UIManager::updataPopTotalNums(std::string fileName,int totalNums){
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
    
    
}




