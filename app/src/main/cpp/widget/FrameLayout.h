//
// Created by DZSB-000848 on 2/15/22.
//

#ifndef SKIAUI_FRAMELAYOUT_H
#define SKIAUI_FRAMELAYOUT_H


#include "ViewGroup.h"

class FrameLayout : public ViewGroup {

public:

    void layout(float l, float t, float r, float b) override;

};


#endif //SKIAUI_FRAMELAYOUT_H
