//
//  ChessLayer.h
//  minGameTest
//
//  Created by 马 英臣 on 13-8-20.
//
//

#ifndef minGameTest_ChessLayer_h
#define minGameTest_ChessLayer_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "BaseLayer.h"
#include "ChessBoardLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ChessLayer:
public BaseLayer
{   
public:
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ChessLayer, create);     
      
    ChessLayer();    
    virtual ~ChessLayer();        
    virtual void onEnter();
    virtual void onExit();    
    virtual bool init();  
    
    virtual bool ccTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);   
       
    
private:
    
    ChessBoardLayer* chessBoard;//棋盘
    Node* chessBalls;//小球
    Node* chessEffect;//特效层
    
    int _lin;//行
    int _row;//列
    float _gra;//间隔
        
    float _width;
    float _height;
    
    
    
};







#endif
