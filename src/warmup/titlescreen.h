#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "engine/graphics/GraphicsDebug.h"
#include "engine/graphics/Graphics.h"
#include "engine/graphics/Camera.h"
#include "engine/graphics/Material.h"

#include "engine/screen.h"

class TitleScreen: Screen{
public:
    TitleScreen();

public:
    void draw(Graphics *g);
};

#endif // TITLESCREEN_H
