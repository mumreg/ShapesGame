//
//  Game2.h
//  ShapesGame
//
//  Created by Mikhail Perekhodtsev on 16.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef __ShapesGame__Game2__
#define __ShapesGame__Game2__

#include <iostream>
#include "CAbstractGame.h"
#include "BaseEngine.h"

class Game2 : public CAbstractGame {
public:
    static Game2 *Create();
    ~Game2();
    
    virtual bool Init();
    virtual bool Draw();
    virtual bool Process(float dt);
    virtual bool Close();
    
    virtual bool MouseClick(float x, float y, bool down);
    
private:
    void ProcessCircle();
    
    Layer *layer;
    Sprite *closeButton;
    PolygonSprite *circle;
    
    bool closeClicked;
    bool circleClicked;
    
    ASize winSize;
    APoint circlePos;
    AVec2 circleVel;
    float velX;
    float velY;
    float radius;
};

#endif /* defined(__ShapesGame__Game2__) */
