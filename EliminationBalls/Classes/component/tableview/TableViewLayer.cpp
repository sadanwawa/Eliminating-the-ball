#include "TableViewLayer.h"
#include "TableViewItemCell.h"
#include "ScoreItemNode.h"
#include "UIManager.h"
#include "ScorcesModel.h"

USING_NS_CC;
USING_NS_CC_EXT;

//宏定义
//CREATE_CELL_ITEM()

//UPDATA_CELL_ITEM()


TableViewLayer::TableViewLayer(){

    TableView* tableView = TableView::create(this, Size(400, 460));
	tableView->setDirection(ScrollView::Direction::VERTICAL);
	tableView->setPosition(Point(0,0));
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	this->addChild(tableView);
	tableView->reloadData();
    tableView->setTouchPriority(-501);
};

TableViewLayer::~TableViewLayer(){
    
    Director::getInstance()->getTouchDispatcher()->removeDelegate(this);
    
};

// on "init" you need to initialize your instance
bool TableViewLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	
    return true;
}

//点击事件  响应对应item
void TableViewLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    CCLOG("当前item编号: %i", cell->getIdx());
}
//item尺寸
Size TableViewLayer::tableCellSizeForIndex(TableView *table, unsigned int idx)
{
    return Size(400,53);
}

//根据编号取得item 如果不存在直接创建
TableViewCell* TableViewLayer::tableCellAtIndex(TableView *table, unsigned int idx)
{
    String *string = String::createWithFormat("%d", idx);
    TableViewCell *cell = table->dequeueCell();//取得当前编号下的item
    if (!cell) {
        cell = new TableViewItemCell();
        cell->retain();
//        Sprite *sprite = Sprite::create("CloseNormal.png");
//        sprite->setAnchorPoint(Point::ZERO);
//        sprite->setPosition(Point(0, 0));
//        cell->addChild(sprite);

//        LabelTTF *label = LabelTTF::create(string->getCString(), "Helvetica", 20.0);
//        label->setPosition(Point::ZERO);
//		label->setAnchorPoint(Point::ZERO);
//        label->setTag(123);
        
       // ScoreItemNode * node=ScoreItemNode
        
        ScorceVO*vo=ScorcesModel::Instance()->getScorceVOByIndex(idx);
        vo->mid=idx+1;
        UIManager::Instance()->addPopLayer(CCBI::ui_scoreitem,cell,0,0,0,(std::string)string->getCString(),vo);
        UIManager::Instance()->openPopLayers();
        
        ScoreItemNode * node=dynamic_cast<ScoreItemNode*>(UIManager::Instance()->getLayerByType(CCBI::ui_scoreitem,(std::string)string->getCString()));
        node->setTag(123);
        
        //创建显示item
        //宏定义 创建cell item
        //type
        //ccbi
        //parent
        //CREATE_CELL_ITEM()
        
        
        //
        CCLOG("创建item %d", idx);
        
    }
    else
    {
        CCLOG("更新显示 %d", idx);
        //根据idx取得数据
        ScoreItemNode * node=(ScoreItemNode*)cell->getChildByTag(123);
        ScorceVO*vo=ScorcesModel::Instance()->getScorceVOByIndex(idx);
        vo->mid=idx+1;
        node->updataUI(vo);
        
    }
    return cell;
}

//设置item数据总数量
unsigned int TableViewLayer::numberOfCellsInTableView(TableView *table)
{
    return ScorcesModel::Instance()->getTotalNum();
}

void TableViewLayer::initInfo(int director,Size viewSize,Size itemSize,std::string itemType,std::string itemCcbi){
    
    
}

