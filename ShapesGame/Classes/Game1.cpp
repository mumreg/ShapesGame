//
//  Game1.cpp
//  ShapesGame
//
//  Created by Mikhail Perekhodtsev on 16.07.13.
//
//

#include "Game1.h"
#include "Utils.h"

const float MOVE_TIME = 2.0f;
const AColor boxColor = { 255/255.0f, 36/255.0f, 0, 1.0f };

using namespace std;

Game1 *Game1::Create()
{
    Game1 *pGame = new Game1();
    return pGame;
}

bool Game1::Init()
{
    winSize = getWinSize();
    
    layer = new Layer();
    closeButton = new Sprite("close_button1.png");
    closeButton->setPosition(closeButton->getBoundingBox().size.width/2,
                             winSize.height - closeButton->getBoundingBox().size.height/2);
    layer->addChild(closeButton);
    
    squareSize = {winSize.width/8, winSize.width/8};
    sqPosition = {squareSize.width/2, winSize.height/2};
    sqVel = {winSize.width/MOVE_TIME, 0};
    
    box = PolygonSprite::drawRect(sqPosition, squareSize);
    box->setColor(boxColor);
    layer->addChild(box);
    
    boxClicked = false;
    
    return true;
}

bool Game1::Close()
{
    layer->setVisible(false);
    CAbstractGame::Close();
    return true;
}

bool Game1::Draw()
{
    if (GetState() == kCGameStopped) {
        return false;
    }
    else {
        layer->render();
        return true;
    }
}

bool Game1::Process(float dt)
{
    if (GetState() == kCGameRunning) {
        if (sqPosition.x >= winSize.width - box->getBoundingBox().size.width/2) {
            sqVel = APointZero;
        }
        
        sqPosition.x += sqVel.x*dt;
        sqPosition.y += sqVel.y*dt;
        
        box->setPosition(sqPosition);
        
        return true;
    }
    else {
        return false;
    }
}

bool Game1::MouseClick(float x, float y, bool down)
{
    APoint clickPoint = {x, y};
    
    if (down) { //touchBegan
        if (rectContainsPoint(&box->getBoundingBox(), &clickPoint)) {
            boxClicked = true;
        }
        if (rectContainsPoint(&closeButton->getBoundingBox(), &clickPoint)) {
            closeClicked = true;
        }
    }
    else { //touchEnded
        if (rectContainsPoint(&box->getBoundingBox(), &clickPoint) && boxClicked) {
            boxClicked = false;
            Pause(true);
        }
        if (rectContainsPoint(&closeButton->getBoundingBox(), &clickPoint) && closeClicked) {
            Close();
            closeClicked = false;
        }
    }

    return false;
}

Game1::~Game1()
{
    delete layer;
}
