//
//  Node.h
//  BaseEngine
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef __A_Steroids__Node__
#define __A_Steroids__Node__

#include <iostream>
#include <vector>
#include "ShadersCache.h"
#include "datatypes.h"
#include "TouchProtocol.h"
#include "matrx4.h"
#include "Body.h"

#define Z_POS       0.00

class Body;

class Node : public TouchProtocol {
public:
    Node();
    virtual ~Node();
    virtual void render();
    virtual void update(float dt) {}
    virtual void eval();

    virtual void setVisible(bool flag);
    virtual bool isVisible();
    
    virtual void setPosition(const APoint &position);
    virtual void setPosition(float x, float y);
    virtual const APoint& getPosition();
    
    virtual void setContentSize(const ASize &size);
    virtual const ASize& getContentSize();
    
    virtual void setAnchorPoint(const APoint &anchorPoint);
    virtual const APoint& getAnchorPoint();
    
    virtual void setRotation(const float angle);
    virtual const float getRotation();
    
    virtual void setBoundingBox(ARect &rect);
    virtual ARect& getBoundingBox();
    
    matrix4 *getMatrix();
    ASize& winSize();
    
    virtual void setBody(Body *body);
    virtual Body *getBody();
    
    virtual void callback();
    
    void setShaderProgram(const char *programName);
    ShaderProgram *getShaderProgram();
    
    virtual void setTouchEnabled(bool touchEnabled);
    bool isTouchEnabled();
    
    void setParent(Node *parent);
    Node *getParent();
    
    virtual void touchesBegan(ASet *set) {}
    virtual void touchesMoved(ASet *set) {}
    virtual void touchesEnded(ASet *set) {}
    
    virtual void addToTouchDispatcher();
    
private:
    ShaderProgram *_shaderProgram;
    Body *_body;
    bool _isVisble;
    APoint _position;
    APoint _anchorPoint;
    ARect _boundingBox;
    ASize _contentSize;
    float _angle;
    bool _touchEnabled;
    Node *_parent;
    matrix4 _modelView;
    ASize _winSize;
};

#endif /* defined(__A_Steroids__Node__) */
