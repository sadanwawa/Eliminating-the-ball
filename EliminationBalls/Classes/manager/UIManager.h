//
//  UIManager.h
//  GameWorld
//
//  Created by yingchen ma on 13-8-20.
//  Copyright (c) 2013年 马英臣. All rights reserved.
//
/*
 UIManager两种设计方案：
 1.
 
 2.
 
 */
#ifndef GameWorld_UIManager_h
#define GameWorld_UIManager_h

#include "cocos2d.h"
#include "../core/Singleton.h"
#include "cocos-ext.h"
#include <map>
#include <string>
#include "../core/BaseScene.h"
#include "../core/BaseLayer.h"
#include "../core/BaseSprite.h"
#include "../core/BaseParticale.h"

USING_NS_CC;
USING_NS_CC_EXT;

namespace CCBI {
    //ccb ui        
//    static const std::string ui_help = "ui_help.ccbi";
//    static const std::string ui_main = "ui_main.ccbi";
    static const std::string ui_main="ui_main.ccbi";
    static const std::string ui_ball_white="ui_ball_white.ccbi";
    static const std::string ui_ball_yellow="ui_ball_yellow.ccbi";
    static const std::string ui_ball_blue="ui_ball_blue.ccbi";
    static const std::string ui_ball_red="ui_ball_red.ccbi";
    static const std::string ui_ball_purple="ui_ball_purple.ccbi";
    static const std::string ui_ball_brown="ui_ball_brown.ccbi";
    static const std::string ui_ball_green="ui_ball_green.ccbi";
    static const std::string ui_ball_fuchsia="ui_ball_fuchsia.ccbi";
    static const std::string ui_ball_black="ui_ball_black.ccbi";
    
    static const std::string eff_selectball="eff_selectball.ccbi";
    static const std::string ui_gameover="ui_gameover.ccbi";
    
    
}

//弹窗类型
typedef enum
{
    POP_TYPE0     = 0,//居中弹窗，周边灰色半透明遮罩（该类弹窗中直接子对象要默认以绝对位置排布）不可穿透
    POP_TYPE1     = 1,//设置位置弹窗。（可定位位置）周边透明 可穿透触摸 显示部分不可穿透    
    
    
} POP_TYPE;

//弹出方式
typedef enum
{
    POP_OPEN0     = 0,//依次顺序弹出，默认弹出时间间隔；时间间隔为0同时弹出
    POP_OPEN1     = 1,//缩放单个弹出 关闭当前后开启下一个弹窗
    
} POP_OPEN;


//struct PopData{
//    Node* pop=NULL;
//    Node* parent=NULL;
//    const char* popType="";  //ccbi名称 作为弹窗类型
//    const char* tag="pop1";//该弹窗tag
//    int ease=0;//打开动画类型  0无动画  1缩放  2渐变  3移动出现
//    int totalnums=1;//该类型弹窗当前总数
//    Point point;    
//};


//继承Object，利用cocos的引用计数内存管理机制 释放对象
class PopData :public Object{
public:
    PopData(){
    
        pop=NULL;
        layer=NULL;
        node=NULL;
        sprite=NULL;
        particale=NULL;
        
        dataVo=NULL;
        parent=NULL;
        popType="";  //ccbi名称 作为弹窗类型
        tag="pop1";//该弹窗tag
        ease=0;//打开动画类型  0无动画  1缩放  2渐变  3移动出现
        totalnums=1;//该类型弹窗当前总数
        
        x=0;
        y=0;
        
    };
    ~PopData(){};
    Node* pop;
    
    BaseLayer* layer;
    BaseNode* node;
    BaseSprite* sprite;
    BaseParticale* particale;
    
    Node* parent;
    
    BaseDataVO*dataVo;
    
    std::string popType;  //ccbi名称 作为弹窗类型
    std::string tag;//该弹窗tag
    int ease;//打开动画类型  0无动画  1缩放  2渐变  3移动出现
    int totalnums;//该类型弹窗当前总数
        
    float x;
    float y;
};

class UIManager : public Singleton<UIManager>, public Object
{
public:
    UIManager();
    ~UIManager();

    virtual bool initialize();

    NodeLoaderLibrary * ccNodeLoaderLibrary;
            
    void addPopLayer(std::string fileName,Node* parent=NULL,int ease=0,float x=0,float y=0,std::string tag="pop1",BaseDataVO* vo=NULL);
    void openPopLayers(float Ddelay=0.3);//同时打开多个 时间间隔
    void openPopLayer();//一个关闭再打开另一个
    
    void setCurrScene(Node* node);
    
    //只在当前scene中调用  不同场景切换时不需要调用
    void removeLayerByNode(Node* node);
    //移除某一类型的弹窗；
    void removeLayersByType(std::string fileName);
    //根据类型和tag移除某个弹窗
    void removeLayerByType(std::string fileName,std::string tag="pop1");
    
    //删除当前pop弹窗
    void removeSingleLayerByNode(Node* node);
    
    
    Node* getLayerByType(std::string fileName,std::string tag="pop1");
    
    //重命名tag
    void replaceLayerTag(std::string fileName,std::string tag,std::string tagTo);
    
    
protected:
       
private:
    
    //data管理
    std::vector<PopData*> _currPops;//当前显示列表中的pop
    std::vector<PopData*> _onOpenList;//待显示列表

    //sence中的baseLayer
    BaseScene* main_Node;
        
    int getPopTotalNums(std::string fileName);//取得当前类型弹窗总数
    void updataPopTotalNums(std::string fileName,int totalNums);//更新当前类型弹窗总数
    
    //删除待打开弹窗数据
    void deleteFromOpenList(PopData* data);
        
    void showPopLayer(Object* sender, PopData* data);
    void playOpenActionOver();
    
    bool _isOpening;


};

#endif
