//
//  TileBase.cpp
//  LianLianKan
//
//  Created by Jinko on 15/2/3.
//
//

#include "TileBase.h"
#include "Utility.h"

TileBase::TileBase(int value){
    Node::init();
    _value = value;
    Sprite* bg = createSpriteWithName("rect-brown.png");
    this->addChild(bg);
    
    std::string spriteName = tile_type_arr[value];
    Sprite* icon = createSpriteWithName(spriteName);
    if (icon!=nullptr) {
        this->addChild(icon);
    }
    
}