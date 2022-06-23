//
// Created by ByteDance on 2022/6/23.
//

#ifndef SKIAUI_LINEARANIMATOR_H
#define SKIAUI_LINEARANIMATOR_H


#include "IAnimator.h"

class LinearAnimator : public IAnimator {

public:

    LinearAnimator(float start, float end);

    virtual ~LinearAnimator();

    float getInterpolation(float factor) override;

private:

    float start, end;

};


#endif //SKIAUI_LINEARANIMATOR_H
