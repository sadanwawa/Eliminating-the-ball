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
        _shortPath=NULL;
        
    };
    ~AStarModel(){
        
        
    };    
      
    //初始化所有节点数据 
    void initAStar(int lin,int row){
        _allStepVOs=Array::create();
        _allStepVOs->retain();

        for(int i=1;i<=lin;i++){
            for(int j=1;j<=row;j++){
                 GPoint* pt=new GPoint();
                 pt->lin=i;
                 pt->row=j;
                 StepVO* vo=new StepVO(pt);
                 vo->retain();
                _allStepVOs->addObject(vo);
                std::cout<<i<<","<<j<<"/n"<<std::endl;
            }           
        }                
        totalLineNum=lin;
        totalRowNum=row;
    }
        
    //更新节点状态
    
    
    //取得节点数组
    Array* getAllStepVOs(){
        return _allStepVOs;
    }
        
    //搜索路径
    bool searchPathByPoint(GPoint* pointA,GPoint* pointB);
           
    //地图行 列
    int totalLineNum;
    int totalRowNum;
    
   
private:
    
//vector 是标准C++库都可支持  
//    std::vector<StepVO*> _allStepVOs;//所有位置列表    
//    std::vector<StepVO*> _openList;    
//    std::vector<StepVO*> _closeList;
    
//Array 仅cocos支持 但可直接插入操作  元素必须为Object  所有要手动retain  release
    Array* _allStepVOs;//所有位置列表
    Array* _openList;    
    Array* _closeList;
    
    Array* _shortPath;
    
    void insertInOpenSteps(StepVO* stepVO);//open中插入当前step
    
    int computeHScoreFromCoord(GPoint* currPoint,GPoint* targetPoint);//计算估算距离
    
    int costToMoveFromStep(StepVO* fromStep,StepVO* toStep);
    
    //取得可通行的相邻节点
    Array* getALLNextToWalkableStepVOs(StepVO* stepvo);
    //通过位置(行列)取得当前节点
    StepVO* getStepVOByGPoint(GPoint* pt);
    //检测pt是否未超出地图区域
    bool checkInArea(GPoint* pt);
    
    //从当前节点（目标节点）逆向找到最短路径
    void constructPath(StepVO* targeVO);
    
    
};

#endif
