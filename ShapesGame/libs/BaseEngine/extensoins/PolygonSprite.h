//
//  PolygonSprite.h
//  ShapesGame
//
//  Created by Mikhail Perekhodtsev on 17.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef __ShapesGame__PolygonSprite__
#define __ShapesGame__PolygonSprite__

#include <iostream>
#include "BaseEngine.h"

enum kPolygonType {
    kPolygon = 0,
    kCircle,
    kRectangle,
    kTriangle,
    kLine,
};

class PolygonSprite : public Node {
public:
    PolygonSprite(APoint *verts, int vertsN, AColor color, kPolygonType type);
    ~PolygonSprite();
    
    virtual void render();
    void setupDraw();
    
    static PolygonSprite *drawRect(APoint origin, ASize size);
    static PolygonSprite *drawCircle(APoint center, float radius, int segments);
    static PolygonSprite *drawLine(APoint start, APoint end, float width);
    
    void setColor(const AColor &color);
    AColor& getColor();
    
private:
    void generateVerts(APoint *verts, int vertsN, AColor color);
    
    GLuint _vertexBuffer;
    GLuint _indexBuffer;
    GLuint _positionLocation;
    GLuint _mvLocation;
    GLuint _colorLocation;
    
    AColor _color;
    AVertexColor *_vertices;
    GLubyte *_indicies;
    
    int _type;
    int _vertsN;
};

#endif /* defined(__ShapesGame__PolygonSprite__) */
