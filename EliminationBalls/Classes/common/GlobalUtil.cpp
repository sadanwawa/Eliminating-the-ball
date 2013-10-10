
#include "GlobalUtil.h"

template<> GlobalUtil* Singleton<GlobalUtil>::msSingleton	= NULL;

std::string GlobalUtil::getPlistByBallType(int type){
    std::string tarplist="";    
    switch (type) {
        case BALL_WHITE:
            tarplist=CCBI::ui_ball_white;
            break;
        case BALL_YELLOW:
            tarplist=CCBI::ui_ball_yellow;
            break;
        case BALL_BLUE:
            tarplist=CCBI::ui_ball_blue;
            break;
        case BALL_RED:
            tarplist=CCBI::ui_ball_red;
            break;
        case BALL_PURPLE:
            tarplist=CCBI::ui_ball_purple;
            break;
        case BALL_BROWN:
            tarplist=CCBI::ui_ball_brown;
            break;
        case BALL_GREEN:
            tarplist=CCBI::ui_ball_green;
            break;
        case BALL_FUCHSIA:
            tarplist=CCBI::ui_ball_fuchsia;
            break;
        case BALL_BLACK:
            tarplist=CCBI::ui_ball_black;
            break;
        default:
            break;
    }
    return tarplist;    
}