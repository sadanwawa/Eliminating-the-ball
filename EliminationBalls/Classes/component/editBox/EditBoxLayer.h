//
//  EditBoxLayer.h
//  TestCpp
//
//  Created by James on 8/14/12.
//
//

#ifndef __TestCpp__EditBoxLayer__
#define __TestCpp__EditBoxLayer__

#include "cocos2d.h"
#include "cocos-ext.h"

class EditBoxLayer : public cocos2d::Layer, public cocos2d::extension::EditBoxDelegate
{
public:
    EditBoxLayer();
    virtual ~EditBoxLayer();
    virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::extension::EditBox* editBox);
private:
    cocos2d::extension::EditBox* _editName;
    cocos2d::extension::EditBox* _editPassword;
    cocos2d::extension::EditBox* _editEmail;
};

#endif /* defined(__TestCpp__EditBoxLayer__) */
