//
//  Utility.h
//  LianLianKan
//
//  Created by Jinko on 15/2/3.
//
//

#ifndef LianLianKan_Utility_h
#define LianLianKan_Utility_h

#include <string>
#include "cocos2d.h"



using namespace cocos2d;
using namespace std;

#define ROW (10)
#define COL (5)
#define TILE_WIDTH (88)
#define TILE_HEIGHT (100)
#define OFFSETX (200)
#define OFFSETY (-20)

struct RowColPoint{
    int row;
    int col;
};



inline void addSpriteFramesWithFileExt(std::string fileName);
inline cocos2d::SpriteFrame* getSpriteFrame(std::string spriteName);
inline Sprite* createSpriteWithName(string spriteName);
inline Vec2 getCoorByRowCol(int row,int col);
inline RowColPoint getRowColByCoor(int x,int y);


void addSpriteFramesWithFileExt(std::string fileName){
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(fileName);
}

cocos2d::SpriteFrame* getSpriteFrame(std::string spriteName){
    return SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteName);
}

Sprite* createSpriteWithName(string spriteName){
    SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteName);
    return Sprite::createWithSpriteFrame(spriteFrame);
}

Vec2 getCoorByRowCol(int row, int col){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    return Vec2(row * TILE_WIDTH + TILE_WIDTH/2+OFFSETX,visibleSize.height-col*TILE_HEIGHT-TILE_HEIGHT/2+OFFSETY);
}

RowColPoint getRowColByCoor(int x,int y){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    int row = (x-OFFSETX)/TILE_WIDTH;
    int col = (visibleSize.height-y+OFFSETY)/TILE_HEIGHT;
    return RowColPoint{row,col};
}





#endif
