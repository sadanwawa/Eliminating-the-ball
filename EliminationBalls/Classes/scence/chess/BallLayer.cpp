//
//  BallLayer.cpp
//  minGameTest
//
//  Created by 马 英臣 on 13-9-30.
//
//

#include "BallLayer.h"
#include "ChessLayer.h"
#include "GlobalUtil.h"
#include "ParticaleEffect.h"
#include "StaticConstant.h"

BallLayer::BallLayer()
{
    
}
BallLayer::~BallLayer(){
    CCLOG("BallLayer删除。");
}
//执行顺序构造函数->init->onNodeLoaded->(addchild)->onEnter
bool BallLayer::init(){
    if(!BaseLayer::init()){
        return false;
    }    
    return true;
}

void BallLayer::onEnter(){
    BaseLayer::onEnter();    
//    this->setTouchMode(Touch::DispatchMode::ALL_AT_ONCE);//ALL_AT_ONCE    
//    Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(this,100,true);
       
}
void BallLayer::onExit(){
    BaseLayer::onExit();    
   
}

SEL_MenuHandler BallLayer::onResolveCCBCCMenuItemSelector(cocos2d::Object * pTarget, const char * pSelectorName){
    //菜单事件    
    return NULL;
}
Control::Handler BallLayer::onResolveCCBCCControlSelector(cocos2d::Object * pTarget, const char * pSelectorName){
    //按钮事件
     CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onClickSelect", BallLayer::onClickSelect);   
    return NULL;
}
bool BallLayer::onAssignCCBMemberVariable(cocos2d::Object * pTarget, const char * pMemberVariableName, cocos2d::Node * pNode){
    //显示对象
    return false;
}
bool BallLayer::onAssignCCBCustomProperty(Object* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue){
    return false;
}
void BallLayer::onNodeLoaded(cocos2d::Node * node, cocos2d::extension::NodeLoader * nodeLoader){
    
}

bool BallLayer::ccTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent){   
    //判断自定义触摸逻辑  如果找到目标并不再继续响应 return true;
    if(BaseLayer::ccTouchBegan(pTouch, pEvent)){
             
        
        //表示点击到当前对象
        if(getDataVO()->getState()==1){
            //添加选中效果
            ChessLayer* layer=dynamic_cast<ChessLayer*>(this->getParent()->getParent());
            ChessDataVO* chessdata=layer->getDataVO();
            int selectId=chessdata->getCurrSelectId();
            if(selectId!=-1){//有选中
                if(selectId!=getDataVO()->getId()){
                    chessdata->setCurrSelectId(getDataVO()->getId());
                    getDataVO()->setSelect(true);
                    
                    std::string tag=POP_TAG::tag_selectball;
                    ParticaleEffect* node=dynamic_cast<ParticaleEffect*>(UIManager::Instance()->getLayerByType(CCBI::eff_selectball,tag));
                    node->setPosition(this->getPosition());
                    node->resetSystem();                      
                    return true;
                }                
            }            
            
            if(!getDataVO()->getSelect()){
                chessdata->setCurrSelectId(getDataVO()->getId());
                getDataVO()->setSelect(true);
                
                std::string tag=POP_TAG::tag_selectball;
                ParticaleEffect* node=dynamic_cast<ParticaleEffect*>(UIManager::Instance()->getLayerByType(CCBI::eff_selectball,tag));
                if(node){                    
                    node->setPosition(this->getPosition());
                    node->resetSystem();
                    return true;
                }                                
                layer->getChessEffect();//特效添加目标
                UIManager::Instance()->addPopLayer(CCBI::eff_selectball,layer->getChessEffect(),0,this->getPositionX(),this->getPositionY()+5,tag);
                UIManager::Instance()->openPopLayers();
                
                node=dynamic_cast<ParticaleEffect*>(UIManager::Instance()->getLayerByType(CCBI::eff_selectball,tag));
                node->setScale(0.7);
                
            }else{
                chessdata->setCurrSelectId(-1);
                getDataVO()->setSelect(false);
                //取消选中效果
                std::string tag=POP_TAG::tag_selectball;
                ParticaleEffect* node=dynamic_cast<ParticaleEffect*>(UIManager::Instance()->getLayerByType(CCBI::eff_selectball,tag));
                node->stopSystem();
                
                
                //            node->runAction(Sequence::create(
                //                                             DelayTime::create(0.5f),
                //                                             CCCallFunc::create(this, callfunc_selector(BallLayer::clearSelectEffect)),
                //                                             NULL
                //                                             ));            
                
            }
        }

        
        
        
        
        
        
        return true;
    }
    //return true;
    
    //没有找到目标 调用BaseLayer::ccTouchBegan(pTouch, pEvent) 继续响应;
    return false;
}

void BallLayer::updataUI(BaseDataVO* datavo){
    _datavo=datavo;
}

void BallLayer::onClickSelect(cocos2d::Object * sender, Control::EventType pControlEvent){   
    
}

void BallLayer::clearSelectEffect(){
        std::string tag="sellectballeff";
        UIManager::Instance()->removeLayerByType(CCBI::eff_selectball,tag);
}
