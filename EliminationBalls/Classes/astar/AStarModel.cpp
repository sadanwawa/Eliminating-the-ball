//
//  AStarModel.cpp
//  minGameTest
//
//  Created by 马 英臣 on 13-10-11.
//
//

#include "AStarModel.h"


// singleton instance pointer
template<> AStarModel* Singleton<AStarModel>::msSingleton	= NULL;

//插入openList合适位置
void AStarModel::insertInOpenSteps(StepVO* stepVO)
{
	int stepFScore = stepVO->getValueF(); 
	int count = _openList->count();
	int i = 0; 
	for (; i < count; i++) {        
		if (stepFScore <=dynamic_cast<StepVO*>(_openList->objectAtIndex(i))->getValueF()) {
			break;
		}
	}	        
    _openList->insertObject(stepVO, i);        
}

//计算估算值 当前位置  到目标位置
int AStarModel::computeHScoreFromCoord(GPoint* currPoint,GPoint* targetPoint)
{	
    return (abs(targetPoint->lin-currPoint->lin)+abs(targetPoint->row-currPoint->row))*10;
}

int AStarModel::costToMoveFromStep(StepVO* fromStep,StepVO* toStep)
{
	return ((fromStep->point->lin != toStep->point->lin) && (fromStep->point->row!= toStep->point->row)) ? 14 : 10;
}

//通过位置(行列)取得当前节点
StepVO* AStarModel::getStepVOByGPoint(GPoint* pt){
    
    int len=_allStepVOs->count();
    for(int i=0;i<len;i++){
        StepVO* step=dynamic_cast<StepVO*>(_allStepVOs->objectAtIndex(i));
        if(step->point->lin==pt->lin&&step->point->row==pt->row){
            return step;
        }        
    }
    return NULL;
}

bool AStarModel::checkInArea(GPoint* pt){
    return  pt->lin>=1&&pt->lin<=totalRowNum&&pt->row>=1&&pt->row<=totalLineNum;
}

Array* AStarModel::getALLNextToWalkableStepVOs(StepVO* stepvo)
{	
    Array* arr=Array::create();
    arr->retain();
    bool t = false;
    bool l = false;
    bool b = false;
    bool r = false;
	
    GPoint* pt=stepvo->point;
    
    //Top
    GPoint* p=new GPoint();
    p->lin=pt->lin;
    p->row=pt->row+1;
    StepVO* vo=getStepVOByGPoint(p);
    if(p->row<=totalLineNum&&vo->isWalkAble){
        arr->addObject(vo);
        t=true;
    }
    
    //Left
    
    p->lin=pt->lin-1;
    p->row=pt->row;
    vo=getStepVOByGPoint(p);
    if(p->lin>=1&&vo->isWalkAble){
        arr->addObject(vo);
        l=true;
    }
    
    //Bottom
    p->lin=pt->lin;
    p->row=pt->row-1;
    vo=getStepVOByGPoint(p);
    if(p->row>=1&&vo->isWalkAble){
        arr->addObject(vo);
        b=true;
    }
	
	// Right
    p->lin=pt->lin+1;
    p->row=pt->row;
    vo=getStepVOByGPoint(p);
    if(p->lin<=totalRowNum&&vo->isWalkAble){
        arr->addObject(vo);
        r=true;
    }
    
//    // Top Left
//    p->lin=pt->lin-1;
//    p->row=pt->row+1;
//    vo=getStepVOByGPoint(p);
//    if(t && l && checkInArea(p)&&vo->isWalkAble){
//        arr->addObject(vo);
//    }
//    
//	//  Bottom Left
//    p->lin=pt->lin-1;
//    p->row=pt->row-1;
//    vo=getStepVOByGPoint(p);
//    if(b && l && checkInArea(p)&&vo->isWalkAble){
//        arr->addObject(vo);
//    }
//	
//	// Top Right
//    p->lin=pt->lin+1;
//    p->row=pt->row+1;
//    vo=getStepVOByGPoint(p);
//    if(t && r && checkInArea(p)&&vo->isWalkAble){
//        arr->addObject(vo);
//    }
//		
//	// Bottom Right
//    p->lin=pt->lin+1;
//    p->row=pt->row-1;
//    vo=getStepVOByGPoint(p);
//    if(b && r && checkInArea(p)&&vo->isWalkAble){
//        arr->addObject(vo);
//    }
    delete  p;
	return arr;
}

// Go backward from a step (the final one) to reconstruct the shortest computed path
//从当前节点（目标节点）查找到最短路径
void AStarModel::constructPath(StepVO* targeVO)
{		
	do {
        if(targeVO->parent!=NULL){
            _shortPath->addObject(targeVO);
        }
        targeVO=targeVO->parent;       
	} while (targeVO != NULL); // Until there is not more parent
	
	// Call the popStepAndAnimate to initiate the animations
	//[self popStepAndAnimate];
}


bool AStarModel::searchPathByPoint(GPoint* pointA,GPoint* pointB){

    CCLOG("起始点:(%d,%d),目标点:(%d,%d)",pointA->lin,pointA->row,pointB->lin,pointB->row);
    _openList=Array::create();
    _openList->retain();
    _closeList=Array::create();
    _closeList->retain();
        
    _shortPath=Array::create();
    _shortPath->retain();

    //StepVO* targetStep=getStepVOByGPoint(pointB);
    //当前节点加入open列表
    insertInOpenSteps(getStepVOByGPoint(pointA));
    
    do{        //_openList[0]总是f最小的那个
        StepVO* stepvo=dynamic_cast<StepVO*>(_openList->objectAtIndex(0));
        //CCLOG("当前点:(%d,%d)",stepvo->point->lin,stepvo->point->row);
        //当前节点放入close列表
        _closeList->addObject(stepvo);
        //当前节点从open列表移除
        _openList->removeObjectAtIndex(0);
        
        if((stepvo->point->lin==pointB->lin)&&(stepvo->point->row==pointB->row)){//找到目标点
            constructPath(stepvo);//逆向检索路径
            _openList=NULL;
            _closeList=NULL;
            break;           
        }
        
        //取得所有相邻可通过节点
        Array* nextSteps=getALLNextToWalkableStepVOs(stepvo);
        int len=nextSteps->count();
        for(int i=0;i<len;i++){
            StepVO* step=dynamic_cast<StepVO*>(nextSteps->objectAtIndex(i));            
            // Check if the step isn't already in the closed set
            //如果在close列表中
            if(_closeList->containsObject(step)){                
                continue;
            }
            // Compute the cost form the current step to that step
            //从当前位置移动到相邻位置的花费
			int moveCost = costToMoveFromStep(stepvo,step);
			
			// Check if the step is already in the open list
            //检测step是否在open表中			
            //Integer index=_openList->indexOfObject(step);
            if(!_openList->containsObject(step)){//不在open列表，添加                
                // Set the current step as the parent
				step->parent = stepvo;
                step->valueG = stepvo->valueG+moveCost;                
                step->valueH=computeHScoreFromCoord(step->point,pointB);
                insertInOpenSteps(step);				                
            }else{//在open列表中
                               
                if((stepvo->valueG+moveCost)<step->valueG){//新的路径代价比较小
                    step->valueG=stepvo->valueG+moveCost;                    
                    //从当前openlist 移除
                    int index=_openList->indexOfObject(step);//当前位置
                    _openList->removeObjectAtIndex(index);
                    //_openList->removeObject(step);
                    
                    //插入合适位置
                    insertInOpenSteps(step);
                }
            }
        }
        
        nextSteps->release();        
        
    }while (_openList->count()>0);
    
    int len=_shortPath->count();
    
    if(_shortPath->count()>0){
        _shortPath->reverseObjects();//倒序
        //找到路径
        for(int i=0;i<len;i++){
            StepVO* vo=dynamic_cast<StepVO*>(_shortPath->objectAtIndex(i));
            CCLOG("当前点:(%d,%d)",vo->point->lin,vo->point->row);
        }        
        return true;
    }    
    return false;
}

void AStarModel::clearData(){
    _allStepVOs->removeAllObjects();
    _allStepVOs->release();
    _openList->release();
    _closeList->release();
    _shortPath->release();
}




