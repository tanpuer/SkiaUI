//
// Created by ByteDance on 2022/6/23.
//

#include "LinearAnimator.h"

LinearAnimator::LinearAnimator(float start, float end) : IAnimator() {

}

LinearAnimator::~LinearAnimator() {

}

float LinearAnimator::getInterpolation(float factor) {
    return (end - start) * factor + start;
}
