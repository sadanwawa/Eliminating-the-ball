//本地应用 全局方法 工具类

#ifndef GameWorld_GlobalUtil_h
#define GameWorld_GlobalUtil_h

#include "../core/Singleton.h"
#include "UIManager.h"
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;


//小球颜色
typedef enum
{
    BALL_WHITE      = 1,
    BALL_YELLOW     = 2,
    BALL_BLUE       = 3,
    BALL_RED        = 4,
    BALL_GREEN      = 5,
    BALL_BROWN      = 6,
    BALL_PURPLE     = 7,
    BALL_FUCHSIA    = 8,
    BALL_BLACK      = 9,
    
}BALL_TYPE;


class GlobalUtil:public Singleton<GlobalUtil>{
public:
    GlobalUtil(){
       
    };
    ~GlobalUtil(){};    
   
    std::string getPlistByBallType(int type);
    
private:
    
    
};

#endif
