//
// Created by ByteDance on 2022/6/22.
//

#ifndef SKIAUI_MOVINGDRAWTEST_H
#define SKIAUI_MOVINGDRAWTEST_H

#include "ITestDraw.h"

class MovingDrawTest : public ITestDraw {

public:

    MovingDrawTest();

    ~MovingDrawTest();

    virtual void doDrawTest(int drawCount, SkCanvas *canvas, int width, int height) override;

};


#endif //SKIAUI_MOVINGDRAWTEST_H
