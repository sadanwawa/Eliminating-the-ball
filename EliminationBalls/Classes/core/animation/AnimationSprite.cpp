//  AnimationSprite.cpp
//  TestGame
//  Created by Âí Ó¢³¼ on 13-10-23.
//

#include "AnimationSprite.h"

AnimationSprite::AnimationSprite()
:mAnimationManager(NULL)
{
	dataVO=NULL;
}
AnimationSprite::~AnimationSprite(){	
	CCLOG("remove AnimationSprite"); 
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	if(dataVO)delete dataVO;
}

void AnimationSprite::updataUI(BaseDataVO* datavo){
	dataVO=dynamic_cast<PartVO*>(datavo);
}

bool AnimationSprite::onAssignCCBMemberVariable(Object * pTarget, const char * pMemberVariableName, Node * pNode) {
	//CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);
	return false;
}

void AnimationSprite::onNodeLoaded(cocos2d::Node * node, NodeLoader * nodeLoader){

}

void AnimationSprite::setAnimationManager(CCBAnimationManager *pAnimationManager){	
 	CC_SAFE_RELEASE_NULL(mAnimationManager);
 	mAnimationManager=pAnimationManager;
 	CC_SAFE_RETAIN(mAnimationManager);
}

void AnimationSprite::runAnimationByTag(std::string name){
	mAnimationManager->runAnimationsForSequenceNamedTweenDuration(name.c_str(),0.0f);
}
