#ifndef RENDERER_H
#define RENDERER_H

#include "pch.h"
#include "assets.h"
#include "context.h"

class Renderer {
public:
    Renderer();
    void render(Assets &assets, Context &context, Camera &camera);
};

#endif // RENDERER_H