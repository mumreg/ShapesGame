//
//  Layer.h
//  BaseEngine
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef __A_Steroids__Layer__
#define __A_Steroids__Layer__

#include <iostream>
#include "Node.h"

class Layer : public Node {
public:
    Layer() {}
    virtual ~Layer();
    
    void addChild(Node *object);
    void removeChild(Node *object, bool cleanup);
    std::vector<Node *> *children();
    virtual void render();
    virtual void update(float dt);
private:
    std::vector<Node *> _childs;
};

#endif /* defined(__A_Steroids__Layer__) */
