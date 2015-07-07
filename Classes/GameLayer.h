//
//  GameLayer.h
//  LianLianKan
//
//  Created by Jinko on 15/2/3.
//
//

#ifndef __LianLianKan__GameLayer__
#define __LianLianKan__GameLayer__

#include <stdio.h>
#include "cocos2d.h"
#include "Utility.h"
#include "TileBase.h"
#include <vector>
#include "2d/CCDrawNode.h"

using namespace cocos2d;

class GameLayer:public Layer{
public:
    bool init();
    CREATE_FUNC(GameLayer);
    bool touchBegan(Touch* touch,Event* event);
    void initMap();
    void initView();
    void onCloseHandler(Ref* pSender);
    void checkLink(TileBase* tile1,TileBase* tile2);
    bool lineCheck(int row1,int col1,int row2,int col2);
    void onRemoveHandler();
    void onShuffleHandler(Ref* pSender);
    void addLinkPoints(int row1,int col1);
    void clearLine(float dt);
    void drawLine();
    
    
public:
    int map_arr[ROW*COL];
    int data_arr[ROW+2][COL+2];
    TileBase* tile_arr[ROW+2][COL+2];
    TileBase* firstClickItem = nullptr;
    TileBase* secondClickItem = nullptr;
    vector<Vec2> points;
    DrawNode* drawNode;
    
};

#endif /* defined(__LianLianKan__GameLayer__) */
