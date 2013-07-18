//
//  Game3.cpp
//  ShapesGame
//
//  Created by Mikhail Perekhodtsev on 16.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include <math.h>
#include "Game3.h"

const float TRI_SIZE = 128.0f;
const float FRAME_WIDTH = 2.0f;
const float ANGLE_SPEED = 1.0f;
const AColor triangleColor = {3/255.0f, 252/255.0f, 36/255.0f, 1.0f};

Game3 *Game3::Create()
{
    Game3 *pGame = new Game3();
    return pGame;
}

bool Game3::Init()
{
    winSize = getWinSize();
    
    layer = new Layer();
    closeButton = new Sprite("close_button3.png");
    closeButton->setPosition(winSize.width/2,
                             winSize.height - closeButton->getBoundingBox().size.height/2);
    layer->addChild(closeButton);
    
    drawFrame();
    
    APoint verts[]= { {0, 0 },
                      { TRI_SIZE/2, TRI_SIZE },
                      { TRI_SIZE, 0 }};
    AColor color = { 1.0, 1.0f, 1.0f, 1.0f };
    triangle = new PolygonSprite(verts, 3, color, kTriangle);
    triangle->setPosition(winSize.width/2, winSize.height/8);
    triangle->setColor(triangleColor);
    layer->addChild(triangle);
    
    radius = winSize.width/6;
    center = { triangle->getPosition().x, triangle->getPosition().y + radius };
    dAngle = ANGLE_SPEED;
    angle = 180.0f;
    
    return true;
}

void Game3::drawFrame()
{
    
    frameLines[0] = PolygonSprite::drawRect({ winSize.width/4, 0 } , { FRAME_WIDTH, winSize.height } );
    frameLines[1] = PolygonSprite::drawRect({ winSize.width/4, winSize.height - FRAME_WIDTH }, { winSize.width/4*2, FRAME_WIDTH });
    frameLines[2] = PolygonSprite::drawRect({ winSize.width - winSize.width/4, 0 }, { FRAME_WIDTH, winSize.height });
    frameLines[3] = PolygonSprite::drawRect({ winSize.width/4, 0 }, { winSize.width/4*2, FRAME_WIDTH });
    
    for (int i = 0; i < 4; i++) {
        layer->addChild(frameLines[i]);
    }
}

bool Game3::Close()
{
    layer->setVisible(false);
    CAbstractGame::Close();
    return true;
}

bool Game3::Draw()
{
    if (GetState() == kCGameStopped) {
        return false;
    }
    else {
        layer->render();
        return true;
    }
}

bool Game3::Process(float dt)
{
    if (GetState() == kCGameRunning) {
        APoint trianglePos = triangle->getPosition();
        
        trianglePos.x = sinf(angle*DegreesToRadiansFactor)*radius + center.x;
        trianglePos.y = cosf(angle*DegreesToRadiansFactor)*radius + center.y;
        
        angle += dAngle;
        
        triangle->setPosition(trianglePos);
        
        return true;
    }
    else {
        return false;
    }
}

bool Game3::MouseClick(float x, float y, bool down)
{
    APoint clickPoint = {x, y};
    
    if (down) { //touchBegan
        if (rectContainsPoint(&closeButton->getBoundingBox(), &clickPoint)) {
            closeClicked = true;
        }
    }
    else { //touchEnded
        if (rectContainsPoint(&closeButton->getBoundingBox(), &clickPoint) && closeClicked) {
            Close();
            closeClicked = false;
        }
    }
    
    return false;
}

Game3::~Game3()
{
    delete layer;
}
