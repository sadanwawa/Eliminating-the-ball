//
//  EditBoxLayer.cpp
//  TestCpp
//
//  Created by James on 8/14/12.
//
//

#include "EditBoxLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;


EditBoxLayer::EditBoxLayer()
{
    Point visibleOrigin = EGLView::getInstance()->getVisibleOrigin();
    Size visibleSize = EGLView::getInstance()->getVisibleSize();
    
    Size editBoxSize = Size(visibleSize.width - 100, 60);

    // top
    _editName = EditBox::create(editBoxSize, Scale9Sprite::create("green_edit.png"));
    _editName->setPosition(Point(0,0));
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    _editName->setFontName("Paint Boy");
    #else
	_editName->setFontName("fonts/Paint Boy.ttf");
    #endif
    _editName->setFontSize(25);
    _editName->setFontColor(Color3B::RED);
    _editName->setPlaceHolder("Name:");
    _editName->setPlaceholderFontColor(Color3B::WHITE);
    _editName->setMaxLength(8);
    _editName->setReturnType(EditBox::KeyboardReturnType::DONE);
    _editName->setDelegate(this);
    addChild(_editName);
    
    // middle
//    _editPassword = EditBox::create(editBoxSize, Scale9Sprite::create("extensions/orange_edit.png"));
//    _editPassword->setPosition(Point(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/2));
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//	_editPassword->setFont("American Typewriter", 30);
//#else
//	_editPassword->setFont("fonts/American Typewriter.ttf", 30);
//#endif
//    _editPassword->setFontColor(Color3B::GREEN);
//    _editPassword->setPlaceHolder("Password:");
//    _editPassword->setMaxLength(6);
//    _editPassword->setInputFlag(EditBox::InputFlag::PASSWORD);
//    _editPassword->setInputMode(EditBox::InputMode::SINGLE_LINE);
//    _editPassword->setDelegate(this);
//    addChild(_editPassword);
//    
//    // bottom
//    _editEmail = EditBox::create(Size(editBoxSize.width, editBoxSize.height), Scale9Sprite::create("extensions/yellow_edit.png"));
//    _editEmail->setPosition(Point(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/4));
//    _editEmail->setAnchorPoint(Point(0.5, 1.0f));
//    _editEmail->setPlaceHolder("Email:");
//    _editEmail->setInputMode(EditBox::InputMode::EMAIL_ADDRESS);
//    _editEmail->setDelegate(this);
//    addChild(_editEmail);

}

EditBoxLayer::~EditBoxLayer()
{
    Director::getInstance()->getTouchDispatcher()->removeDelegate(this);
    Director::getInstance()->getTouchDispatcher()->removeDelegate(_editName);
}

void EditBoxLayer::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox)
{
    log("editBox %p DidBegin !", editBox);
}

void EditBoxLayer::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox)
{
    log("editBox %p DidEnd !", editBox);
}

void EditBoxLayer::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text)
{
    log("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void EditBoxLayer::editBoxReturn(EditBox* editBox)
{
    log("editBox %p was returned !",editBox);
    
    
    
}

