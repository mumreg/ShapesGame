//
//  Node.cpp
//  BaseEngine
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include <math.h>

#include "Node.h"
#include "Utils.h"
#include "TouchDispatcher.h"

using namespace std;

Node::Node()
{
    _angle = 0.0f;
    _position = {0, 0};
    _anchorPoint = {0.5f, 0.5f};
    _isVisble = true;
    _touchEnabled = false;
    _winSize = getWinSize();
    
    _modelView.setIdentity();
}

void Node::render()
{
    if (!_isVisble) {
        return;
    }
}

void Node::setAnchorPoint(const APoint &anchorPoint)
{
    _anchorPoint = anchorPoint;
}

const APoint& Node::getAnchorPoint()
{
    return _anchorPoint;
}

void Node::setVisible(bool flag)
{
    _isVisble = flag;
}

bool Node::isVisible()
{
    return _isVisble;
}

void Node::setPosition(const APoint &position)
{
    _position = position;
    eval();
}

void Node::setPosition(float x, float y)
{
    setPosition({ x, y });
}

const APoint& Node::getPosition()
{
    return _position;
}

void Node::setRotation(const float angle)
{
    _angle = angle;
    eval();
}

const float Node::getRotation()
{
    return _angle;
}

void Node::setTouchEnabled(bool touchEnabled)
{
    _touchEnabled = touchEnabled;
}

bool Node::isTouchEnabled()
{
    return _touchEnabled;
}

void Node::addToTouchDispatcher()
{
    TouchDispatcher::sharedInstance()->addObject(this);
}

void Node::setShaderProgram(const char *programName)
{
    _shaderProgram = ShadersCache::sharedInstance()->getProgram(programName);
}

void Node::setContentSize(const ASize &size)
{
    _contentSize = size;
}

const ASize& Node::getContentSize()
{
    return _contentSize;
}

void Node::setBoundingBox(ARect &rect)
{
    _boundingBox = rect;
}

ARect& Node::getBoundingBox()
{
    _boundingBox = { {_position.x - _contentSize.width/2, _position.y - _contentSize.height/2},
                    _contentSize };
    return _boundingBox;
}

void Node::setParent(Node *parent)
{
    _parent = parent;
}

Node *Node::getParent()
{
    return _parent;
}

void Node::callback()
{
    //override me
}

void Node::setBody(Body *body)
{
    _body = body;
}

Body *Node::getBody()
{
    return _body;
}

ShaderProgram *Node::getShaderProgram()
{
    return _shaderProgram;
}

matrix4 *Node::getMatrix()
{
    return &_modelView;
}

void Node::eval()
{
    APoint position = getPosition();
    
    float dx = 2.0f/_winSize.width;
    float dy = 2.0f/_winSize.height;
    
    matrix4 translate;
    translate.setIdentity();
    
    float *translateArr = translate.glMatrix();
    translateArr[12] = -1.0f + position.x*dx ;
    translateArr[13] = -1.0f + position.y*dy;
    translateArr[14] = 0.0f;
    
    float angle = getRotation()*DegreesToRadiansFactor;
    
    matrix4 rotate;
    rotate.setIdentity();
    
    float *rotateArr = rotate.glMatrix();
    rotateArr[0] = cosf(angle);
    rotateArr[1] = sinf(angle);
    rotateArr[4] = -sinf(angle);
    rotateArr[5] = cosf(angle);
    
    _modelView = translate * rotate;
}

ASize &Node::winSize()
{
    return _winSize;
}

Node::~Node()
{
    //override me
}