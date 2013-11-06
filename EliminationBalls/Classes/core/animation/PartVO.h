//
//  PartVO.h
//  TestGame
//  Created by 马 英臣 on 13-10-23.
//  角色数据

#ifndef TestGame_PartVO_h
#define TestGame_PartVO_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../BaseDataVO.h"
#include "../../manager/ResourceManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

class PartVO :public BaseDataVO{
public:
	PartVO(int type,std::string url=""){
		typePart=type;
        urlPart=url;
		state=0;
		isSelect=false;
		startPoint=Point(0,0);
		offsetLong=0;
	};
	virtual ~PartVO(){
		
	};	

	int getPartType(){
		return typePart;
	}

	inline int getState(){
		return state;
	}
	inline void setState(int mstate){
		state=mstate;
	}
	std::string getPartUrl(){
		return urlPart;
	}

	inline bool getSelect(){
		return isSelect;
	}
	inline void setSelect(bool boo){
		isSelect=boo;
	}

	Point getStartPoint(){
		return startPoint;
	}

	void setStartPoint(Point pt){
		startPoint=pt;
	}

	inline float getOffSetX(){
		return offsetLong;
	}
	inline void setOffSetX(float offset){
		offsetLong=offset;
	}


private:
	
	int typePart;
	
	std::string urlPart;
	
	int state;		
    
    bool isSelect;

	Point startPoint;
	
	float offsetLong;
};

#endif
