
//
//  MenuLayer.h
//  LianLianKan
//
//  Created by Jinko on 15/2/3.
//
//

#ifndef __LianLianKan__MenuLayer__
#define __LianLianKan__MenuLayer__

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class MenuLayer:public Layer{
public:
    bool init();
    CREATE_FUNC(MenuLayer);
    void startGame(Ref* pSender);
};

#endif /* defined(__LianLianKan__MenuLayer__) */
