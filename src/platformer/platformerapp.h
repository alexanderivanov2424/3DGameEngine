#ifndef PLATFORMERAPP_H
#define PLATFORMERAPP_H

#include "engine/application.h"


#include "engine/graphics/Graphics.h"
#include "engine/graphics/Camera.h"
#include "engine/graphics/Material.h"

class PlatformerApp : public Application{
public:
    PlatformerApp(View* view, int w, int h);
    ~PlatformerApp();

    void onStartup(Graphics *g) override;

public:
    std::shared_ptr<Screen> gameScreen;
};

#endif // PLATFORMERAPP_H
