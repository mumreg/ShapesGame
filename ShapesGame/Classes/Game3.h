//
//  Game3.h
//  ShapesGame
//
//  Created by Mikhail Perekhodtsev on 16.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef __ShapesGame__Game3__
#define __ShapesGame__Game3__

#include <iostream>
#include "CAbstractGame.h"
#include "BaseEngine.h"

class Game3 : public CAbstractGame {
public:
    static Game3 *Create();
    ~Game3();
    
    virtual bool Init();
    virtual bool Draw();
    virtual bool Process(float dt);
    virtual bool Close();
    
    virtual bool MouseClick(float x, float y, bool down);
    
private:
    void drawFrame();
    
    Layer *layer;
    Sprite *closeButton;
    PolygonSprite *triangle;
    PolygonSprite *frameLines[4];
    
    bool closeClicked;
    
    APoint center;
    float radius;
    float dAngle;
    float angle;
    ASize winSize;
};

#endif /* defined(__ShapesGame__Game3__) */
