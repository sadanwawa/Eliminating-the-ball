//
//  StaticConstant.h
//  
//  Created by yinghcen ma on 13-8-19.
//  Copyright (c) 2013年 RenRenGame. All rights reserved.
//

#ifndef minGameTest_StaticConstant_h
#define minGameTest_StaticConstant_h

#include "cocos2d.h"

USING_NS_CC;

//UI触摸层级枚举
typedef enum
{
    MAIN_PRIORITY     = 0,
    POP_PRIORITY     = -300,
    
}UI_PRIORITY;

namespace STC {//本地数据 字段
    
    static const std::string userdata_histScorces="histScorces";//历史记录
    
}
//UI tag枚举
namespace POP_TAG {
    static const std::string tag_readyball="readyball";//准备区小球
    static const std::string tag_chessball="chessball_";//棋盘小球    
    static const std::string tag_selectball="sellectballeff";//选中小球特效    
}


#endif
