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

    void measure(int widthMeasureSpec, int heightMeasureSpec) override;

    virtual void layout(int l, int t, int r, int b) override;

#pragma mark LinearLayoyt api

    /**
     * 暂时忽略reverse，只有2种方向
     * @param _orientation
     */
    virtual void setOrientation(Orientation _orientation);

    virtual Orientation getOrientation();

    virtual void layoutHorizontal(int l, int t, int r, int b);

    virtual void layoutVertical(int l, int t, int r, int b);

private:

    Orientation orientation = Orientation::HORIZONTAL;

};


#endif //SKIAUI_LINEARLAYOUT_H
