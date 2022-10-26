//
// Created by ByteDance on 2022/10/26.
//

#include "Button.h"

Button::Button() : TextView() {
    defaultRadius = 4;
    ripplePaint = new SkPaint();
    ripplePaint->setAntiAlias(true);
}

Button::~Button() {
    delete ripplePaint;
}
