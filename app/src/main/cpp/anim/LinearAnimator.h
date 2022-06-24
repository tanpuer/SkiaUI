//
// Created by ByteDance on 2022/6/23.
//

#ifndef SKIAUI_LINEARANIMATOR_H
#define SKIAUI_LINEARANIMATOR_H


#include "IAnimator.h"

class LinearAnimator : public IAnimator {

public:

    enum class AnimatorType {
        Scale,
        Rotate,
        Translate,
    };

public:

    LinearAnimator(float translateX, float translateY);

    virtual ~LinearAnimator();

    virtual float getInterpolation(float factor) override;

    void update(SkIRect &rect) override;

private:

    float translateX, translateY;

};


#endif //SKIAUI_LINEARANIMATOR_H
