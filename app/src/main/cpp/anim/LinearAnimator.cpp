//
// Created by ByteDance on 2022/6/23.
//

#include "LinearAnimator.h"
#include "native_log.h"

LinearAnimator::LinearAnimator(float translateX, float translateY)
        : IAnimator(), translateX(translateX), translateY(translateY) {

}

LinearAnimator::~LinearAnimator() {

}

float LinearAnimator::getInterpolation(float factor) {
    return static_cast<float >(endTime - currTime) / static_cast<float >(duration);
}

void LinearAnimator::update(SkIRect &rect) {
    if (currTime > endTime) {
        end = true;
        return;
    }
    auto interpolation = getInterpolation(1.0f);
    ALOGD("LinearAnimator::update %ld %ld %f", currTime, endTime, interpolation)
    auto x = translateX * interpolation;
    auto y = translateY * interpolation;
    rect.setLTRB(rect.left() + x, rect.top() + y, rect.right() + x, rect.bottom() + y);
}
