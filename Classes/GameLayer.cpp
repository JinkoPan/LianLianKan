//
//  GameLayer.cpp
//  LianLianKan
//
//  Created by Jinko on 15/2/3.
//
//

#include "GameLayer.h"
#include "TileBase.h"
#include <math.h>



bool GameLayer::init(){
    if (!Layer::init()) {
        return false;
    }
    firstClickItem = nullptr;
    secondClickItem = nullptr;
    
    memset(data_arr, 0, sizeof(int)*(ROW+2)*(COL+2));
    memset(tile_arr, 0, sizeof(TileBase*) * (ROW+2)*(COL+2));
    initMap();
    initView();
    

    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    MenuItemImage* closeItem = MenuItemImage::create("CloseNormal.png",                                                    "CloseSelected.png",CC_CALLBACK_1(GameLayer::onCloseHandler,this));
    closeItem->setPosition(visibleSize.width-closeItem->getContentSize().width/2,visibleSize.height-closeItem->getContentSize().height/2);
    
    MenuItemImage* shuffleItem = MenuItemImage::create("CloseNormal.png",                                                    "CloseSelected.png",CC_CALLBACK_1(GameLayer::onShuffleHandler, this));
    shuffleItem->setPosition(visibleSize.width-shuffleItem->getContentSize().width/2,visibleSize.height-shuffleItem->getContentSize().height-60);
    
    Menu* menu = Menu::create(closeItem,shuffleItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    drawNode = DrawNode::create();
    this->addChild(drawNode);
//    drawNode->drawLine(Vec2(100,100),Vec2(100,200), Color4F(0.5, 1, 0.5, 1));
    
    
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::touchBegan,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

bool GameLayer::touchBegan(Touch* touch, Event* event){
    Vec2 vec = touch->getLocationInView();
    vec = Director::getInstance()->convertToGL(vec);
    
    RowColPoint pt = getRowColByCoor(vec.x,vec.y);
    CCLOG("touch point x:%f, y:%f  row:%d, col:%d",vec.x,vec.y,pt.row,pt.col);
    if (firstClickItem == nullptr) {
        CCLOG(" one click item !");
        firstClickItem = tile_arr[pt.row][pt.col];
    }else if (secondClickItem == nullptr){
        CCLOG(" two click item !");
        secondClickItem = tile_arr[pt.row][pt.col];
        if (firstClickItem != nullptr && secondClickItem != nullptr) {
            checkLink(firstClickItem,secondClickItem);
        }
    }
    return true;
}

void GameLayer::initMap(){
    srand(static_cast<int>(time(0)));
    int len = ROW*COL;
    int value = 0;
    for (int i=0; i<len; i+=2,value++) {
        value = value%24;
        map_arr[i] = value;
        map_arr[i+1] = value;
    }
    int temp = 0;
    int index = 0;
    for (int j=0; j<len; j++) {
        index = rand()%len;
        if(j!=index){
            temp = map_arr[j];
            map_arr[j] = map_arr[index];
            map_arr[index] = temp;
        }
    }
}

void GameLayer::initView(){
    int count = 0;
    int value = 0;
    int row,col;
    for (int i=0; i<ROW; ++i) {
        for (int j=0; j<COL; ++j,count++) {

            value = map_arr[count]+1;
            TileBase* tile = new (std::nothrow)TileBase(map_arr[count]);
            if (tile!=nullptr) {
                row = i+1;
                col = j+1;
                tile->setRowCol(row,col);
                tile->setPosition(getCoorByRowCol(row,col));
                tile->setValue(value);
                this->addChild(tile);
                tile_arr[row][col] = tile;
                data_arr[row][col] = value;
            }
        }
    }
}

void GameLayer::checkLink(TileBase* tile1,TileBase* tile2){
    points.clear();
    CCLOG("value1: %d,value2: %d",tile1->getValue(),tile2->getValue());
    if(tile1 == tile2 || tile1->getValue() != tile2->getValue()){
        CCLOG("value not equal ! ");
        firstClickItem = nullptr;
        secondClickItem = nullptr;
        return;
    }

    bool flag = false;
    int row1 = tile1->getRow();
    int col1 = tile1->getCol();
    
    int row2 = tile2->getRow();
    int col2 = tile2->getCol();
    
    
    CCLOG(" ==== checkLink === ");
    if ((row1==row2 || col1 == col2) && lineCheck(row1,col1,row2,col2)) {
        CCLOG("first check");
        flag = true;
        addLinkPoints(row1,col1);
        addLinkPoints(row2,col2);
       
    }else if (data_arr[row1][col2]==0 && lineCheck(row1,col1,row1,col2)
              && lineCheck(row1,col2,row2,col2))
    {
        flag = true;
        addLinkPoints(row1,col1);
        addLinkPoints(row1,col2);
        addLinkPoints(row2,col2);
    }else if (data_arr[row2][col1]==0 && lineCheck(row1,col1,row2,col1)
              && lineCheck(row2,col1,row2,col2))
    {
        flag = true;
        addLinkPoints(row1,col1);
        addLinkPoints(row2,col1);
        addLinkPoints(row2,col2);
    }else{
        CCLOG("=== final check");
        for (int i= 0; i<ROW+2; i++) {
//            CCLOG("i: %d, row1: %d, col1: %d, row2: %d, col2: %d",i,row1,col1,row2,col2);
            if (lineCheck(row1, col1, i, col1) && lineCheck(i, col1, i,col2) && lineCheck(i, col2,row2, col2)) {
                flag = true;
                addLinkPoints(row1,col1);
                addLinkPoints(i,col1);
                addLinkPoints(i,col2);
                addLinkPoints(row2,col2);
                break;
            }
            
        }
        if (!flag){
            for (int i= 0; i<COL+2; i++) {
//                CCLOG("j: %d, row1: %d, col1: %d, row2: %d, col2: %d",i,row1,col1,row2,col2);
                if (lineCheck(row1, col1, row1, i) && lineCheck(row1, i,row2, i) && lineCheck(row2, i,row2, col2)) {
                    flag = true;
                    addLinkPoints(row1,col1);
                    addLinkPoints(row1,i);
                    addLinkPoints(row2,i);
                    addLinkPoints(row2,col2);
                    break;
                }
        
            }
        }
    }
    
    if (flag) {
//        CCLOG("flag == true");
        drawLine();
        tile1->removeFromParentAndCleanup(true);
        tile2->removeFromParentAndCleanup(true);
        
        tile_arr[row1][col1] = nullptr;
        tile_arr[row2][col2] = nullptr;
        data_arr[row1][col1] = 0;
        data_arr[row2][col2] = 0;
        
        delete tile1;
        delete tile2;

    }
    
    firstClickItem = nullptr;
    secondClickItem = nullptr;
    
}

void GameLayer::addLinkPoints(int row1,int col1){
    points.push_back(getCoorByRowCol(row1,col1));
}

void GameLayer::onShuffleHandler(Ref* pSender){
    int row = 0;
    int col = 0;
    int tempValue = 0;
    TileBase* tile1;
    TileBase* tile2;
    TileBase* temp;
    Vec2 pos;
    for (int i=1; i<ROW; i++) {
        for (int j=1; j<COL; j++) {
            row = rand()%ROW+1;
            col = rand()%COL+1;
            tile1 = tile_arr[i][j];
            tile2 = tile_arr[row][col];
            if (tile1!=nullptr && tile2!=nullptr){
                
                tempValue = data_arr[i][j];
                data_arr[i][j]= data_arr[row][col];
                data_arr[row][col] = tempValue;
                temp = tile_arr[i][j];
                tile_arr[i][j] = tile_arr[row][col];
                tile_arr[row][col] = temp;
                
                tile1->setRowCol(row, col);
                tile2->setRowCol(i,j);
                
                pos = tile1->getPosition();
                tile1->setPosition(tile2->getPosition());
                tile2->setPosition(pos);
                
                
            }
        }
    }
}

void GameLayer::onRemoveHandler(){
    int row1 = firstClickItem->getRow();
    int col1 = firstClickItem->getCol();
    int row2 = secondClickItem->getRow();
    int col2 = secondClickItem->getCol();
    
    firstClickItem->removeFromParentAndCleanup(true);
    secondClickItem->removeFromParentAndCleanup(true);
    
    
    
    tile_arr[row1][col1] = nullptr;
    tile_arr[row2][col2] = nullptr;
    
    delete firstClickItem;
    delete secondClickItem;
    
    firstClickItem = nullptr;
    secondClickItem = nullptr;
}


bool GameLayer::lineCheck(int row1, int col1, int row2, int col2){
    
    
    if (row1==row2) {
        if (col1>col2) {
            swap(col1, col2);
        }
        if (abs(col2-col1)==1) {
            if (data_arr[row1][col1]==0 || data_arr[row2][col2] == 0) {
                return true;
            }
            if (data_arr[row1][col1] == data_arr[row2][col2]) {
                return true;
            }
            return false;
        }
        for (int i=col1+1; i<col2; i++) {
            if (data_arr[row1][i]!=0) {
                return false;
            }
        }
        
    }else if (col1==col2) {
        if (row1>row2) {
            swap(row1, row2);
        }
        if (abs(row2-row1)==1) {
            if (data_arr[row1][col1]==0 || data_arr[row2][col2] == 0) {
                return true;
            }
            if (data_arr[row1][col1] == data_arr[row2][col2]) {
                return true;
            }
            return false;
        }
        for (int j=row1+1; j<row2; j++) {
            if (data_arr[j][col1]!=0) {
                return false;
            }
        }
    }
    return true;
}

void GameLayer::drawLine(){
    int len = (int)points.size();
    CCLOG("len:     %d",len);
    for (int i=0; i<len-1; i++) {
        drawNode->drawLine(points.at(i),points.at(i+1), Color4F(0.5, 1, 0.5, 1));
    }
    scheduleOnce(schedule_selector(GameLayer::clearLine), 0.5f);
}

void GameLayer::clearLine(float dt){
    CCLOG("clear line %f",dt);
    drawNode->clear();
}


void GameLayer::onCloseHandler(Ref* pSender){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}