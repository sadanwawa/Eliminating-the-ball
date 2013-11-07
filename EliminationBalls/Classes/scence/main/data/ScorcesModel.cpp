//
//  ScorcesModel.cpp
//  minGameTest
//
//  Created by 马 英臣 on 13-10-18.
//
//

#include "ScorcesModel.h"
#include "StaticConstant.h"
#include "DataFormatUtil.h"


// singleton instance pointer
template<> ScorcesModel* Singleton<ScorcesModel>::msSingleton	= NULL;

bool ScorcesModel::initialize(){
    
    return true;
}

//更新数据
void ScorcesModel::initData(){

}

//初始化新用户数据
void ScorcesModel::initGlobleData(){
    clearData();
    //是否第一次启动游戏
    bool isOldplayer=UserDefault::getInstance()->getBoolForKey(STC::userdata_oldplayer.c_str(),false);
    if(!isOldplayer){//新用户
        //初始化本地数据
        currTopScores=initTopScores;
        UserDefault::getInstance()->setBoolForKey(STC::userdata_oldplayer.c_str(),true);
        _allScoreVOs=Array::create();
        _allScoreVOs->retain();
        for(int i=0;i<totalNum;i++){
            ScorceVO* vo=new ScorceVO();
            vo->retain();
            vo->name="--";
            vo->scorces=0;
            vo->mid=i+1;
            _allScoreVOs->addObject(vo);
            
            //添加本地记录
            std::string record="--,0";
            std::string valuekey=STC::userdata_histScorces+DataFormatUtil::toString((i+1));
            UserDefault::getInstance()->setStringForKey(valuekey.c_str(), record);
            
        }
        UserDefault::getInstance()->flush();
    }else{
        //读取数据
        _allScoreVOs=Array::create();
        _allScoreVOs->retain();
        for(int i=0;i<totalNum;i++){
            ScorceVO* vo=new ScorceVO();
            vo->retain();
            std::string valuekey=STC::userdata_histScorces+DataFormatUtil::toString((i+1));
            std::string record=UserDefault::getInstance()->getStringForKey(valuekey.c_str(),"--,0");
            std::vector<std::string> vec;
            DataFormatUtil::splitToSVector(record,vec,",");
            
            vo->mid=i+1;
            vo->name=vec[0];
            vo->scorces=DataFormatUtil::toNumber<int>(vec[1].c_str());
            _allScoreVOs->addObject(vo);
            
            if(i==0){
                if(vo->scorces<initTopScores){
                    currTopScores=initTopScores;
                }else{
                    currTopScores=vo->scorces;
                }
            }
        }
    }
}

//插入数据记录
void ScorcesModel::insertRecord(std::string name,int scorce){
    ScorceVO* vo=new ScorceVO();
    vo->retain();
    vo->name=name;
    vo->scorces=scorce;
    
    int score = vo->scorces;
	int count = _allScoreVOs->count();
	int i = 0;
	for (; i < count; i++) {
		if (score>=dynamic_cast<ScorceVO*>(_allScoreVOs->objectAtIndex(i))->scorces) {
			break;
		}
	}
    _allScoreVOs->insertObject(vo, i);
    _allScoreVOs->removeLastObject();
    
    //本地重新保存 >i的记录
    for(int j=i;j<count;j++){
        std::string valuekey=STC::userdata_histScorces+DataFormatUtil::toString((j+1));
        ScorceVO* vo=dynamic_cast<ScorceVO*>(_allScoreVOs->objectAtIndex(j));
        std::string record=vo->name+","+DataFormatUtil::toString(vo->scorces);
        UserDefault::getInstance()->setStringForKey(valuekey.c_str(), record);
    }
}

ScorceVO* ScorcesModel::getScorceVOByIndex(int index){
    int count = _allScoreVOs->count();
    for(int i=0;i<count;i++){
        if(i==index)return dynamic_cast<ScorceVO*>(_allScoreVOs->objectAtIndex(i));
    }
    return NULL;
}

void ScorcesModel::clearData(){
    if(_allScoreVOs){
        _allScoreVOs->removeAllObjects();
        _allScoreVOs->release();
    }
}
