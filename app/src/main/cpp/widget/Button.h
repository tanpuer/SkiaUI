//
// Created by ByteDance on 2022/10/26.
//

#ifndef SKIAUI_BUTTON_H
#define SKIAUI_BUTTON_H


#include "TextView.h"

class Button : public TextView {

public:

    Button();

    ~Button();

private:

    SkPaint *ripplePaint;

    int defaultRadius;

};


#endif //SKIAUI_BUTTON_H
