//
//  Game2.cpp
//  ShapesGame
//
//  Created by Mikhail Perekhodtsev on 16.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "Game2.h"

const int SEGMENTS_N = 180;
const float MOVE_TIME = 5.0f;
const float RADIUS = 60.0f;
const float OFFSET = 2.0f;
const AColor circleColor = {0, 222/255.0f, 1.0f, 1.0f};

Game2* Game2::Create()
{
    Game2 *pGame = new Game2();
    return pGame;
}

bool Game2::Init()
{
    winSize = getWinSize();
    
    layer = new Layer();
    closeButton = new Sprite("close_button2.png");
    closeButton->setPosition(closeButton->getBoundingBox().size.width*1.5f,
                             winSize.height - closeButton->getBoundingBox().size.height/2);
    layer->addChild(closeButton);
    
    radius = RADIUS;
    circlePos = { radius + OFFSET, radius + OFFSET };
    circle = PolygonSprite::drawCircle(circlePos, radius, SEGMENTS_N);
    circle->setColor(circleColor);
    layer->addChild(circle);
    
    velX = (winSize.width - radius*2 - OFFSET*2)/(MOVE_TIME/4);
    velY = (winSize.height - radius*2 - OFFSET*2)/(MOVE_TIME/4);
    
    circleVel = { velX, 0 };
    
    return true;
}

bool Game2::Draw()
{
    if (GetState() != kCGameStopped) {
        layer->render();
        return true;
    }
    else {
        return false;
    }
}

bool Game2::Process(float dt)
{
    if (GetState() != kCGameStopped) {
        ProcessCircle();
        
        circlePos.x += circleVel.x*dt;
        circlePos.y += circleVel.y*dt;
        
        circle->setPosition(circlePos);
        return true;
    }
    else {
        return false;
    }
}

void Game2::ProcessCircle()
{
    if (circlePos.x >= winSize.width - radius - OFFSET && circlePos.y == radius + OFFSET) {
        circlePos = { winSize.width - radius - OFFSET, radius + OFFSET };
        circleVel = { 0, velY };
    }
    if (circlePos.x >= winSize.width - radius - OFFSET && circlePos.y >= winSize.height - radius - OFFSET) {
        circlePos = { winSize.width - radius - OFFSET, winSize.height - radius - OFFSET };
        circleVel = { -velX, 0 };
    }
    if (circlePos.x <= radius + OFFSET && circlePos.y >= winSize.height - radius - OFFSET) {
        circlePos = { radius + OFFSET, winSize.height - radius - OFFSET };
        circleVel = { 0, -velY };
    }
    if (circlePos.x <= radius + OFFSET && circlePos.y <= radius + OFFSET) {
        circlePos = { radius + OFFSET, radius + OFFSET };
        circleVel = { velX, 0 };
    }
}

bool Game2::Close()
{
    layer->setVisible(false);
    return CAbstractGame::Close();
}

bool Game2::MouseClick(float x, float y, bool down)
{
    APoint clickPoint = {x, y};
    
    if (down) { //touchBegan
        if (rectContainsPoint(&circle->getBoundingBox(), &clickPoint)) {
            circleClicked = true;
        }
        if (rectContainsPoint(&closeButton->getBoundingBox(), &clickPoint)) {
            closeClicked = true;
        }
    }
    else { //touchEnded
        if (rectContainsPoint(&circle->getBoundingBox(), &clickPoint) && circleClicked) {
            circleClicked = false;
            Pause(true);
        }
        if (rectContainsPoint(&closeButton->getBoundingBox(), &clickPoint) && closeClicked) {
            Close();
            closeClicked = false;
        }
    }
    
    return false;
}

Game2::~Game2()
{
    delete layer; //sprites will be deleted here too
}