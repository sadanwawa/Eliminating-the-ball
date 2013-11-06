//
//  BaseParticale.h
//  minGameTest
//
//  Created by 马 英臣 on 13-11-06.
//  自定义TableviewLayer  使得table滑动列表功能模块与UI显示分离  方便使用
//

#ifndef minGameTest_TableViewLayer_h
#define minGameTest_TableViewLayer_h

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class TableViewLayer : public cocos2d::Layer, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
public:
    
    CREATE_FUNC(TableViewLayer);
    
    TableViewLayer();
    virtual ~TableViewLayer();
    virtual bool init();  
    //传入需要信息
    /*
     director 方向 1横向 2纵向
     viewSize 创建TableView尺寸
     itemSize 加载itemCell尺寸
     itemType itemCell 类名
     itemCcbi itemCell ccbi名
     */
    virtual void initInfo(int director,Size viewSize,Size itemSize,std::string itemType,std::string itemCcbi);
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {}
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
    virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, unsigned int idx);
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::TableView *table);
};

#endif // __TABLEVIEWTESTSCENE_H__
