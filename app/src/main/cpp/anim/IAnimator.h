//
// Created by ByteDance on 2022/6/23.
//

#ifndef SKIAUI_IANIMATOR_H
#define SKIAUI_IANIMATOR_H

#include <cstdint>

class IAnimator {

public:

    IAnimator() {}

    virtual ~IAnimator() = 0;

    virtual float getInterpolation(float factor) = 0;

    virtual void setDuration(long duration) {
        this->duration = duration;
    };

    virtual void start() {

    }

protected:

    long duration;

    int64_t startTime;

};


#endif //SKIAUI_IANIMATOR_H
