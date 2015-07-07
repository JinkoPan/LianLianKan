//
//  MenuLayer.cpp
//  LianLianKan
//
//  Created by Jinko on 15/2/3.
//
//

#include "MenuLayer.h"
#include "GameScene.h"

bool MenuLayer::init(){
    if (!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    MenuItemImage* startItem = MenuItemImage::create("menu_start.png", "menu_start.png", CC_CALLBACK_1(MenuLayer::startGame, this));
    
    Menu* menu = Menu::create(startItem, NULL);
//    menu->set
    menu->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    this->addChild(menu);
    
    return true;
}

void MenuLayer::startGame(Ref* pSender){
    Director::getInstance()->replaceScene(GameScene::create());
}