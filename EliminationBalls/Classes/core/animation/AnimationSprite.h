//
//  AnimationSprite.h
//  TestGame
//  Created by yinghcen ma on 13-10-23.
//
//

#ifndef TestGame_AnimationSprite_h
#define TestGame_AnimationSprite_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../BaseSprite.h"
#include "PartVO.h"

USING_NS_CC;
USING_NS_CC_EXT;

class AnimationSprite:
public BaseSprite,
//public cocos2d::extension::CCBMemberVariableAssigner,
public NodeLoaderListener
{
public:

	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AnimationSprite, create); 

	AnimationSprite();
	virtual ~AnimationSprite();   
	virtual void updataUI(BaseDataVO* datavo=NULL);
	void onNodeLoaded(cocos2d::Node * node, NodeLoader * nodeLoader);
	bool onAssignCCBMemberVariable(Object * pTarget, const char * pMemberVariableName, Node * pNode);
	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

	void runAnimationByTag(std::string name);
	PartVO* getDataVO(){ return dataVO;};
private:        

	CCBAnimationManager* mAnimationManager;
	PartVO* dataVO;
};

#endif
