//
//  PolygonSprite.cpp
//  ShapesGame
//
//  Created by Mikhail Perekhodtsev on 17.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include <math.h>
#include "PolygonSprite.h"

const AColor defColor = { 1.0, 1.0, 1.0, 1.0 };

PolygonSprite::PolygonSprite(APoint *verts, int vertsN, AColor color, kPolygonType type)
{
    _vertsN = vertsN;
    _color = color;
    _type = type;
    
    generateVerts(verts, vertsN, color);
    setupDraw();
    eval();
}

PolygonSprite *PolygonSprite::drawRect(APoint origin, ASize size)
{
    APoint *verts = new APoint[4];
    verts[0] = { 0, 0 };
    verts[1] = { 0, size.height };
    verts[2] = { size.width, 0 };
    verts[3] = { size.width, size.height };
    
    PolygonSprite *poly = new PolygonSprite(verts, 4, defColor, kRectangle);
    poly->setPosition({ origin.x + size.width/2, origin.y + size.height/2 });
    
    delete [] verts;
    
    return poly;
}

PolygonSprite *PolygonSprite::drawCircle(APoint center, float radius, int segments)
{
    APoint *verts = new APoint[segments + 1];
    //offset to radius is nessesary according to generateVerts procedure
    verts[0] = {radius, radius};
    float j = 0;
    for (int i = 0; i < segments; i++) {
        verts[i + 1].x = cosf(j * DegreesToRadiansFactor)*radius + radius;
        verts[i + 1].y = sinf(j * DegreesToRadiansFactor)*radius + radius;
        j += 720.0f/segments;
    }
    
    PolygonSprite *poly = new PolygonSprite(verts, segments + 1, defColor, kCircle);
    poly->setPosition(center);
    
    delete [] verts;
    
    return poly;
}

void PolygonSprite::generateVerts(APoint *verts, int vertsN, AColor color)
{
    float dx = 2.0f/winSize().width;
    float dy = 2.0f/winSize().height;
    
    APoint left = APointZero;
    APoint right = APointZero;
    APoint up = APointZero;
    APoint down = APointZero;
    
    for (int i = 0; i < vertsN; i++) {
        if (verts[i].x < left.x) {
            left = verts[i];
        }
        if (verts[i].x > right.x) {
            right = verts[i];
        }
        if (verts[i].y < down.y) {
            down = verts[i];
        }
        if (verts[i].y > up.y) {
            up = verts[i];
        }
    }
    
    float width = fabs(right.x - left.x);
    float height = fabs(up.y - down.y);
    
    ASize contentSize = { width - left.x, height - down.y };
    setContentSize(contentSize);
    
    APoint anchorPoint = getAnchorPoint();
    
    _vertices = (AVertexColor *)malloc(vertsN*sizeof(AVertexColor));
    _indicies = (GLubyte *)malloc(vertsN*sizeof(GLubyte));
    
    if (_vertices == NULL || _indicies == NULL) {
        printf("Error allocating memory for polygon sprite!\n");
        return;
    }
    
    memset(_vertices, 0, vertsN*sizeof(AVertexColor));
    memset(_indicies, 0, vertsN*sizeof(GLubyte));
    
    for (int i = 0; i < vertsN; i++) {
        
        _vertices[i] = {{ (verts[i].x - contentSize.width * anchorPoint.x)*dx,
                          (verts[i].y - contentSize.height * anchorPoint.y)*dy,
            Z_POS}, color};
        
        _indicies[i] = i;
    }
}

void PolygonSprite::setupDraw()
{
    setShaderProgram(kShaderColor);
    getShaderProgram()->use();
    
    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices[0])*_vertsN, _vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indicies[0])*_vertsN, _indicies, GL_DYNAMIC_DRAW);
    
    _mvLocation = glGetUniformLocation(getShaderProgram()->getProgram(), kShaderMVUniform);
    
    _positionLocation = glGetAttribLocation(getShaderProgram()->getProgram(), kShaderPositionAttr);
    _colorLocation = glGetAttribLocation(getShaderProgram()->getProgram(), kShaderColorAttr);
    glEnableVertexAttribArray(_positionLocation);
    glEnableVertexAttribArray(_colorLocation);
}

void PolygonSprite::render()
{
    if (!isVisible())
        return;
    
    setShaderProgram(kShaderColor);
    getShaderProgram()->use();
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glViewport(0, 0, winSize().width, winSize().height);
    
    glUniformMatrix4fv(_mvLocation, 1, 0, getMatrix()->glMatrix());
    
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    
    glVertexAttribPointer(_positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(AVertexColor), 0);
    glVertexAttribPointer(_colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(AVertexColor), (GLvoid*) (sizeof(float) * 3));
    
    int mode;
    
    switch (_type) {
        case kTriangle:
        case kRectangle:
                mode = GL_TRIANGLE_STRIP;
            break;
        case kCircle:
                mode = GL_TRIANGLE_FAN;
            break;
        case kLine:
                mode = GL_LINES;
            break;
        default:
                mode = GL_TRIANGLE_STRIP;
            break;
    }
    
    glDrawElements(mode, _vertsN, GL_UNSIGNED_BYTE, 0);
}

void PolygonSprite::setColor(const AColor &color)
{
    _color = color;
    for (int i = 0; i < _vertsN; i++) {
        _vertices[i].color = _color;
    }
    
    setupDraw();
}

AColor& PolygonSprite::getColor()
{
    return _color;
}

PolygonSprite::~PolygonSprite()
{
    delete [] _vertices;
    delete [] _indicies;
}