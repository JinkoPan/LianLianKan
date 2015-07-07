//
//  TileBase.h
//  LianLianKan
//
//  Created by Jinko on 15/2/3.
//
//

#ifndef __LianLianKan__TileBase__
#define __LianLianKan__TileBase__

#include <stdio.h>
#include "cocos2d.h"
#include <string>

using namespace cocos2d;

class TileBase:public Node{
public:
//    bool init();
//    CREATE_FUNC(TileBase);
    TileBase(int value);
    inline int getRow(){ return row;};
    inline void setRow(int value){ row = value;};
    inline int getCol(){ return col;};
    inline void setCol(int value){ col = value;};
    inline void setRowCol(int r,int c){ row = r;col = c;};
    inline int getValue(){ return _value;};
    inline void setValue(int value){ _value = value;};
    
public:
    const std::string tile_type_arr[24] = {
        "Bunny.png",
        "Carrot.png",
        "ColorfulFeathers.png",
        "DiamondTiger.png",
        "ElectricCat.png",
        "EssenceofLife.png",
        "ExoticFrog.png",
        "FairyFruit.png",
        "Figurines.png",
        "StarGrass.png",
        "LightningCloud.png",
        "MilkBeasts.png",
        "MouseSoul.png",
        "MushroomWorm.png",
        "RainbowFlower.png",
        "SnakeSpiritFlower.png",
        "Soil.png",
        "Staff.png",
        "StrangeStone.png",
        "StupidFish.png",
        "ThunderbirdSoul.png",
        "Totem.png",
        "ToyWorm.png",
        "VenetianFruit.png"
        
    };
    bool isSelected = false;
private:
    int row;
    int col;
    int _value;
    
};


#endif /* defined(__LianLianKan__TileBase__) */
