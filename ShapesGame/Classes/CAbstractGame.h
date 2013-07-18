//
//  CAbstractGame.h
//  ShapesGame
//
//  Created by Mikhail Perekhodtsev on 16.07.13.
//
//

#ifndef __ShapesGame__CAbstractGame__
#define __ShapesGame__CAbstractGame__

#include <iostream>
#include "datatypes.h"

enum CGameState {
    kCGameRunning = 0,
    kCGameStopped,
    kCGamePaused,
};

#define GAME1_STR   "Game1"
#define GAME2_STR   "Game2"
#define GAME3_STR   "Game3"

class CAbstractGame {
    CGameState _state;
    
public:
    CAbstractGame() {}
    static CAbstractGame * Create(const std::string &name);
    CGameState GetState();
    
    virtual bool Start();
    virtual bool Pause(bool pause);
    virtual bool Close();
    virtual bool Init();
    
    virtual bool Process(float dt);
    virtual bool Draw();
    
    virtual bool MouseClick(float x, float y, bool down);
    virtual bool MouseMove(float x, float y, bool down);
    
    virtual ~CAbstractGame() {}
};

#endif /* defined(__ShapesGame__CAbstractGame__) */
