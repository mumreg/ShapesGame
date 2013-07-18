//
//  Game1.h
//  ShapesGame
//
//  Created by Mikhail Perekhodtsev on 16.07.13.
//
//

#ifndef __ShapesGame__Game1__
#define __ShapesGame__Game1__

#include <iostream>
#include "datatypes.h"
#include "CAbstractGame.h"
#include "BaseEngine.h"

class Game1 : public CAbstractGame {
public:
    static Game1 *Create();
    virtual bool Init();
    virtual bool Draw();
    virtual bool Process(float dt);
    virtual bool Close();
    
    virtual bool MouseClick(float x, float y, bool down);
    
    ~Game1();
private:
    ASize squareSize;
    APoint sqPosition;
    AVec2 sqVel;
    ASize winSize;
    
    bool boxClicked;
    bool closeClicked;
    
    Sprite *closeButton;
    PolygonSprite *box;
    Layer *layer;
};

#endif /* defined(__ShapesGame__Game1__) */
