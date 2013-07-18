//
//  GamesScene.cpp
//  ShapesGame
//
//  Created by Mikhail Perekhodtsev on 16.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "GamesScene.h"

GamesScene::GamesScene()
{    
    addToTouchDispatcher();
    gamesCount = 0;
    nextGame();
    
    setTouchEnabled(true);
}

void GamesScene::render()
{
    for (auto it = games.rbegin(); it != games.rend(); ++it) {
        (*it)->Draw();
    }
    
    Layer::render();
}

void GamesScene::nextGame()
{
    CAbstractGame *game = nullptr;
    
    switch (gamesCount) {
        case 0:
            game = CAbstractGame::Create(GAME1_STR);
            break;
        case 1:
            game = CAbstractGame::Create(GAME2_STR);
            break;
        case 2:
            game = CAbstractGame::Create(GAME3_STR);
        default:
            break;
    }
    
    if (game) {
        games.push_front(game);
        game->Start();
    }
    
    activeGame = games[0];
    gamesCount++;
}

void GamesScene::prevGame()
{
    CAbstractGame *gamePtr = games[0];
    
    games.pop_front();
    gamesCount--;
    
    delete gamePtr;
    
    if (gamesCount != 0) {
        activeGame = games[0];
        activeGame->Pause(false);
    }
    else {
        exit(0);
    }
}

void GamesScene::update(float dt)
{
    for (auto it = games.rbegin(); it != games.rend(); ++it) {
        (*it)->Process(dt);
    }
    
    if (activeGame->GetState() == kCGamePaused) {
        nextGame();
    }
    
    if (activeGame->GetState() == kCGameStopped) {
        prevGame();
    }
}

void GamesScene::touchesBegan(ASet *set)
{
    for (int i = 0; i < set->getSize(); i++) {
        APoint *p = set->getObjectAtIndex(i);
        activeGame->MouseClick(p->x, p->y, true);
    }
}

void GamesScene::touchesEnded(ASet *set)
{
    for (int i = 0; i < set->getSize(); i++) {
        APoint *p = set->getObjectAtIndex(i);
        activeGame->MouseClick(p->x, p->y, false);
    }
}