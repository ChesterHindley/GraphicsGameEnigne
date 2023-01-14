#pragma once
#include "GraphicsObject.h"
class Bindable : protected GraphicsObject // 
{
protected:
    Bindable(Graphics& g) :GraphicsObject(g)
    {}
    public:
    virtual void bind() = 0;
    virtual ~Bindable() {}


};

