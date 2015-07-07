//
//  MenuScene.cpp
//  LianLianKan
//
//  Created by Jinko on 15/2/3.
//
//

#include "MenuScene.h"
#include "MenuLayer.h"

bool MenuScene::init(){
    if (!Scene::init()) {
        return false;
    }
    this->addChild(MenuLayer::create());
    return true;
}