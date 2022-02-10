//
// Created by DZSB-000848 on 1/26/22.
//

#ifndef SKIAUI_LINEARLAYOUT_H
#define SKIAUI_LINEARLAYOUT_H


#include "ViewGroup.h"

class LinearLayout : public ViewGroup {

public:

    enum class Orientation {
        HORIZONTAL,
        VERTICAL
    };

public:

    LinearLayout();

    virtual ~LinearLayout();

    virtual void measure(float _width, YGMeasureMode widthMode, float _height,
                         YGMeasureMode heightMode) override;

    virtual void layout(float l, float t, float r, float b) override;

#pragma mark LinearLayoyt api

    /**
     * 暂时忽略reverse，只有2种方向
     * @param _orientation
     */
    virtual void setOrientation(Orientation _orientation);

    virtual Orientation getOrientation();

    virtual void layoutHorizontal(float l, float t, float r, float b);

    virtual void layoutVertical(float l, float t, float r, float b);

private:

    Orientation orientation = Orientation::HORIZONTAL;

};


#endif //SKIAUI_LINEARLAYOUT_H
