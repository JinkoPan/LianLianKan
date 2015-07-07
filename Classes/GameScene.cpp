//
//  GameScene.cpp
//  LianLianKan
//
//  Created by Jinko on 15/2/3.
//
//

#include "GameScene.h"
#include "GameLayer.h"
#include "Utility.h"

bool GameScene::init(){
    if (!Scene::init()) {
        return false;
    }
    addSpriteFramesWithFileExt("Icon.plist");
    this->addChild(GameLayer::create());
    return true;
}