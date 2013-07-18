//
//  GamesScene.h
//  ShapesGame
//
//  Created by Mikhail Perekhodtsev on 16.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef __ShapesGame__GamesScene__
#define __ShapesGame__GamesScene__

#include <iostream>
#include <deque>
#include "BaseEngine.h"

#include "CAbstractGame.h"

class GamesScene : public Layer {
public:
    GamesScene();
    
    virtual void render();
    virtual void update(float dt);
    
    virtual void touchesBegan(ASet *set);
    virtual void touchesEnded(ASet *set);
    
private:
    void nextGame();
    void prevGame();
    
    CAbstractGame *activeGame;
    int gamesCount;
    std::deque<CAbstractGame *>games;
};

#endif /* defined(__ShapesGame__GamesScene__) */
