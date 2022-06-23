//
// Created by ByteDance on 2022/6/23.
//

#ifndef SKIAUI_IANIMATOR_H
#define SKIAUI_IANIMATOR_H

class IAnimator {

public:

    IAnimator();

    virtual ~IAnimator();

    virtual float getInterpolation(float factor) = 0;

    virtual void setDuration(long duration);

    virtual void start();

protected:

    long duration;

    long startTime;

};


#endif //SKIAUI_IANIMATOR_H
