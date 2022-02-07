#include "titlescreen.h"

TitleScreen::TitleScreen(){

}

void TitleScreen::draw(Graphics *g){
    g->clearTransform();
    g->scale(20);
    g->drawShape("quad");
}
