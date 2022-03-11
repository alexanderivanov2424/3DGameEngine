#ifndef WARMUPAPP_H
#define WARMUPAPP_H


#include "engine/application.h"


#include "engine/graphics/Graphics.h"
#include "engine/graphics/Camera.h"
#include "engine/graphics/Material.h"

class View;

class WarmupApp : public Application {
public:
    WarmupApp(View* view, int w, int h);
    ~WarmupApp();

    void onStartup(Graphics *g) override;

public:
    std::shared_ptr<Screen> menuScreen;
    std::shared_ptr<Screen> gameScreen;
    std::shared_ptr<Screen> endScreen;

};
#endif // WARMUPAPP_H
