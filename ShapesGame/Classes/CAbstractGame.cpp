//
//  CAbstractGame.cpp
//  ShapesGame
//
//  Created by Mikhail Perekhodtsev on 16.07.13.
//
//

#include "CAbstractGame.h"

#include "Game1.h"
#include "Game2.h"
#include "Game3.h"

using namespace std;

bool CAbstractGame::Init()
{
    _state = kCGameStopped;
    
    return true;
}

CAbstractGame *CAbstractGame::Create(const std::string &name)
{
    CAbstractGame *pGame = nullptr;
    
    if (name == string(GAME1_STR)) {
        pGame = Game1::Create();
    }
    if (name == string(GAME2_STR)) {
        pGame = Game2::Create();
    }
    if (name == string(GAME3_STR)) {
        pGame = Game3::Create();
    }
    
    if (pGame)
        pGame->Init();
    
    return pGame;
}

CGameState CAbstractGame::GetState()
{
    return _state;
}

bool CAbstractGame::Start()
{
    _state = kCGameRunning;
    return true;
}

bool CAbstractGame::Close()
{
    _state = kCGameStopped;
    return true;
}

bool CAbstractGame::Pause(bool pause)
{
    if (pause) {
        _state = kCGamePaused;
    }
    else {
        _state = kCGameRunning;
    }
    return true;
}

bool CAbstractGame::Draw()
{
    //override me
    return true;
}

bool CAbstractGame::Process(float dt)
{
    //override me
    return true;
}

bool CAbstractGame::MouseClick(float x, float y, bool down)
{
    //override me
    return false;
}

bool CAbstractGame::MouseMove(float x, float y, bool down)
{
    //override me
    return true;
}

