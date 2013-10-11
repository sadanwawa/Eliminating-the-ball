//
//  AStarModel.h
//  minGameTest
//
//  Created by 马 英臣 on 13-10-11.
//A*算法实现
//

#ifndef minGameTest_AStarModel_h
#define minGameTest_AStarModel_h


#include "cocos2d.h"
#include "../core/Singleton.h"
#include "cocos-ext.h"
#include "StepVO.h"
//#include "../common/StaticConstant.h"

USING_NS_CC;
USING_NS_CC_EXT;

class AStarModel : public Singleton<AStarModel>, public Object
{
public:
    AStarModel(){
        _allStepVOs=NULL;
        _openList=NULL;
        _closeList=NULL;
        totalLineNum=0;
        totalRowNum=0;
    };
    ~AStarModel(){
        
        
    };    
      
    //初始化所有位置数据 
    void initAStar(Array* vec,int lin,int row){
                
        
        
        _allStepVOs=vec;
        totalLineNum=lin;
        totalRowNum=row;
    }
    //搜索路径
    bool searchPathByPoint(Point pointA,Point pointB);
           
    //地图行 列
    int totalLineNum;
    int totalRowNum;
    
   
private:
    
//vector 是标准C++库都可支持  
//    std::vector<StepVO*> _allStepVOs;//所有位置列表    
//    std::vector<StepVO*> _openList;    
//    std::vector<StepVO*> _closeList;
    
//Array 仅cocos支持 但可直接插入操作
    Array* _allStepVOs;//所有位置列表
    Array* _openList;    
    Array* _closeList;
    
    
    void insertInOpenSteps(StepVO* stepVO);//open中插入当前step
    
    int computeHScoreFromCoord(Point currPoint,Point targetPoint);//计算估算距离
    
    int costToMoveFromStep(StepVO* fromStep,StepVO* toStep);
    
    //取得可通行的相邻节点
    Array* getALLNextToWalkableStepVOs(StepVO* stepvo);
    //通过位置(行列)取得当前节点
    StepVO* getStepVOByGPoint(Point pt);
    //检测pt是否未超出地图区域
    bool checkInArea(Point pt);
    

    
    
};

#endif
